using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

using BizHawk.BizInvoke;
using BizHawk.Common;
using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Properties;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	[PortedCore(CoreNames.Dolphin, "Dolphin Team", "5.0-16426", "https://github.com/dolphin-emu/dolphin", singleInstance: true, isReleased: false)]
	public partial class Dolphin : IRomInfo
	{
		private static readonly LibDolphin _core;

		static Dolphin()
		{
			var resolver = new DynamicLibraryImportResolver(
				OSTailoredCode.IsUnixHost ? "libdolphin-emu-nogui.so" : "dolphin-emu-nogui.dll", hasLimitedLifetime: false);
			_core = BizInvoker.GetInvoker<LibDolphin>(resolver, CallingConventionAdapters.Native);
		}

		private Thread _hostThread;
		private bool HostRunning => _hostThread?.IsAlive ?? false;

		private void ExecuteHostThread(string gamePath, string secondDiscPath)
		{
			List<string> args = new(new[]
			{
				"BizHawk",
				"--user=DolphinUserFolder",
				$"--exec={gamePath}",
				"--platform=headless",
			});

			if (secondDiscPath is not null)
			{
				args.Add($"--exec={secondDiscPath}");
			}

			ApplyNativeSettings(args);
			_core.Dolphin_Main(args.Count, args.ToArray());
		}

		private static string GetGameId(string path)
		{
			if (path is null)
			{
				return new string(new char[6]);
			}

			using var fs = new FileStream(path, FileMode.Open, FileAccess.Read);
			using var reader = new BinaryReader(fs, Encoding.ASCII);

			var ret = new char[6];
			int readBeInt()
			{
				var be32 = reader.ReadBytes(4);
				return unchecked(be32[0] << 24 | be32[1] << 16 | be32[2] << 8 | be32[3]);
			}

			switch (Path.GetExtension(path).ToLowerInvariant())
			{
				case ".iso":
				case ".gcm":
					reader.Read(ret, 0, 6);
					break;
				case ".ciso":
					// header ends at 0x8000
					reader.ReadBytes(0x8000);
					reader.Read(ret, 0, 6);
					break;
				case ".tgc":
					{
						reader.ReadBytes(8);
						var headerEnd = readBeInt();
						if (headerEnd - 8 < 0)
						{
							break;
						}
						reader.ReadBytes(headerEnd - 8);
						reader.Read(ret, 0, 6);
						break;
					}
				case ".gcz":
					// ID is in compressed data, so...
					break;
				case ".wia":
				case ".rvz":
					// offset 0x58 stores the first 80 bytes of the disc uncompressed
					reader.ReadBytes(0x58);
					reader.Read(ret, 0, 6);
					break;
				case ".wbfs":
					// header ends at 0x200
					reader.ReadBytes(0x200);
					reader.Read(ret, 0, 6);
					break;
			}

			return new string(ret);
		}

		private static unsafe uint HashAdler32(byte[] data)
		{
			const uint MOD_ADLER = 65521;
			uint a = 1, b = 0;
			int len = data.Length;

			fixed (byte* dataPtr = data)
			{
				var p = dataPtr;
				while (len != 0)
				{
					int tlen = len > 5550 ? 5550 : len;
					len -= tlen;

					do
					{
						a += *p++;
						b += a;
					} while (tlen-- != 0);

					a = (a & 0xffff) + (a >> 16) * (65536 - MOD_ADLER);
					b = (b & 0xffff) + (b >> 16) * (65536 - MOD_ADLER);
				}

				if (a >= MOD_ADLER)
				{
					a -= MOD_ADLER;
				}

				b = (b & 0xffff) + (b >> 16) * (65536 - MOD_ADLER);

				if (b >= MOD_ADLER)
				{
					b -= MOD_ADLER;
				}

				return (b << 16) | a;
			}
		}

		private static Dolphin CurrentCore;

		[CoreConstructor(VSystemID.Raw.GC)]
		[CoreConstructor(VSystemID.Raw.Wii)]
		public Dolphin(CoreLoadParameters<DolphinSettings, DolphinSyncSettings> lp)
		{
			if (lp.Discs.Count > 2 || (lp.Discs.Count > 0 && lp.Roms.Count > 0))
			{
				throw new Exception("Wrong number of discs and/or ROMs!");
			}

			CurrentCore?.Dispose();
			CurrentCore = this;

			string gamePath = lp.Discs.FirstOrDefault()?.DiscPath ?? lp.Roms[0].RomPath;
			_multiDisc = lp.Discs.Count == 2;

			if (lp.Discs.Count > 0)
			{
				RomDetails = $"{lp.Game.Name}\r\nCRC32:{lp.Game.Hash}";
			}

			_serviceProvider = new(this);

			_settings = lp.Settings ?? new();
			_syncSettings = lp.SyncSettings ?? new();

			IsWii = lp.Game.System == VSystemID.Raw.Wii;

			if (Directory.Exists("DolphinUserFolder"))
			{
				Directory.Delete("DolphinUserFolder", true);
			}

			Directory.CreateDirectory("DolphinUserFolder");
			Directory.CreateDirectory("DolphinUserFolder/GC");
			Directory.CreateDirectory("DolphinUserFolder/GC/EUR");
			Directory.CreateDirectory("DolphinUserFolder/GC/USA");
			Directory.CreateDirectory("DolphinUserFolder/GC/JAP");

			if (_syncSettings.ApplyPerGameSettings)
			{
				using var gameSettings = new ZipArchive(new MemoryStream(Util.DecompressGzipFile(new MemoryStream(Resources.DOLPHINGAMESETTINGS.Value))), ZipArchiveMode.Read, false);
				gameSettings.ExtractToDirectory("DolphinUserFolder");
			}

			if (!Directory.Exists("Sys"))
			{
				Directory.CreateDirectory("Sys");
				using var sysFolder = new ZipArchive(new MemoryStream(Util.DecompressGzipFile(new MemoryStream(Resources.DOLPHINSYSFOLDER.Value))), ZipArchiveMode.Read, false);
				sysFolder.ExtractToDirectory("Sys");
			}

			if (!IsWii && !_syncSettings.MainSettings.SkipIPL)
			{
				var ipl = lp.Comm.CoreFileProvider.GetFirmwareOrThrow(new("GC/Wii", "IPL"), "Cannot find IPL ROM, change sync settings to skip IPL boot");
				// probably wrong
				File.WriteAllBytes("DolphinUserFolder/GC/EUR/IPL.bin", ipl);
				File.WriteAllBytes("DolphinUserFolder/GC/USA/IPL.bin", ipl);
				File.WriteAllBytes("DolphinUserFolder/GC/JAP/IPL.bin", ipl);
			}
			else
			{
				var ipl = lp.Comm.CoreFileProvider.GetFirmware(new("GC/Wii", "IPL"));
				if (ipl is not null)
				{
					lp.Comm.Notify("Using user-provided IPL ROM for font files");
					// probably wrong
					File.WriteAllBytes("DolphinUserFolder/GC/EUR/IPL.bin", ipl);
					File.WriteAllBytes("DolphinUserFolder/GC/USA/IPL.bin", ipl);
					File.WriteAllBytes("DolphinUserFolder/GC/JAP/IPL.bin", ipl);
				}
			}

			_isDumpingDtm = _settings.DumpDTM && lp.DeterministicEmulationRequested;

			uint iromHash = 0;
			uint coefHash = 0;

			if (!_syncSettings.MainSettings.DSPHLE)
			{
				// built-in rom hashs
				iromHash = 0xE789B5A5;
				coefHash = 0xA4A575F5;

				var coef = lp.Comm.CoreFileProvider.GetFirmware(new("GC/Wii", "DSP COEF"));
				if (coef is not null)
				{
					lp.Comm.Notify("Using user-provided DSP COEF");
					File.WriteAllBytes("DolphinUserFolder/GC/dsp_coef.bin", coef);
					if (_isDumpingDtm) // no need to hash like this if we aren't dumping
					{
						coefHash = HashAdler32(coef);
					}
				}

				var irom = lp.Comm.CoreFileProvider.GetFirmware(new("GC/Wii", "DSP IROM"));
				if (irom is not null)
				{
					lp.Comm.Notify("Using user-provided DSP IROM");
					File.WriteAllBytes("DolphinUserFolder/GC/dsp_rom.bin", irom);
					if (_isDumpingDtm) // ditto
					{
						iromHash = HashAdler32(irom);
					}
				}
			}

			if (_isDumpingDtm)
			{
				var secondDiscName = new byte[40];
				if (_multiDisc)
				{
					var name = Encoding.UTF8.GetBytes(Path.GetFileName(lp.Discs[1].DiscPath));
					if (name.Length <= 40)
					{
						Array.Copy(name, secondDiscName, name.Length);
					}
					else
					{
						throw new Exception("Second disc name is too large for DTM dump!");
					}
				}

				var gameHash = new byte[16];
				_core.Dolphin_HashMedium(gamePath, gameHash, false, true);

				InitDtmDump(lp.Game.Name, GetGameId(lp.Discs.FirstOrDefault()?.DiscPath), secondDiscName, gameHash, iromHash, coefHash);
			}

			DeterministicEmulation = lp.DeterministicEmulationRequested || _syncSettings.MainSettings.EnableCustomRTC;
			ControllerDefinition = CreateControllerDefinition();

			mpluscb = n => Wiimotes[n].HasMotionPlus;
			extensioncb = n => Wiimotes[n].Extension;
			_core.Dolphin_SetConfigCallbacks(mpluscb, extensioncb);

			_gcpadcb = GCPadCallback;
			_core.Dolphin_SetGCPadCallback(_gcpadcb);

			if (IsWii)
			{
				_wiipadcb = WiiPadCallback;
				_core.Dolphin_SetWiiPadCallback(_wiipadcb);
			}

			_hostThread = new Thread(() => ExecuteHostThread(gamePath, _multiDisc ? lp.Discs[1].DiscPath : null)) { IsBackground = true };
			_hostThread.Start();

			while (!_core.Dolphin_BootupSuccessful())
			{
				if (!HostRunning)
				{
					Dispose();
					throw new Exception("Dolphin failed to bootup!");
				}

				Thread.Sleep(1);
			}

			_vhandle = GCHandle.Alloc(_vbuf, GCHandleType.Pinned);
			_core.Dolphin_SetFrameBuffer(_vhandle.AddrOfPinnedObject());

			InitMemoryDomains();

			ResetCounters();
		}

		public string RomDetails { get; }

		private bool IsWii { get; }

		public class Wiimote
		{
			public bool IsActive { get; }
			public bool HasMotionPlus { get; }
			public DolphinWiiPadSettings.WiimoteExtensions Extension { get; }

			public Wiimote(bool active, bool motionPlus, DolphinWiiPadSettings.WiimoteExtensions extension)
			{
				IsActive = active;
				HasMotionPlus = motionPlus;
				Extension = extension;
			}
		}

		public Wiimote[] Wiimotes { get; private set; }

		private ControllerDefinition CreateControllerDefinition()
		{
			var ret = new ControllerDefinition((IsWii ? "Wii" : "GameCube") + " Controls");

			var gcSlots = new[]
			{
				_syncSettings.MainSettings.SIDevice0,
				_syncSettings.MainSettings.SIDevice1,
				_syncSettings.MainSettings.SIDevice2,
				_syncSettings.MainSettings.SIDevice3,
			};

			for (int i = 0; i < 4; i++)
			{
				if (gcSlots[i] is DolphinMainSettings.SIDevices.Controller)
				{
					foreach (var b in Enum.GetValues(typeof(LibDolphin.PadButtons)))
					{
						ret.BoolButtons.Add($"P{i + 1} {Enum.GetName(typeof(LibDolphin.PadButtons), b)}");
					}

					ret.AddXYPair($"P{i + 1} Main Stick {{0}}", AxisPairOrientation.RightAndUp, 0.RangeTo(255), 128);
					ret.AddXYPair($"P{i + 1} C Stick {{0}}", AxisPairOrientation.RightAndUp, 0.RangeTo(255), 128);
					ret.AddAxis($"P{i + 1} Analog L", 0.RangeTo(255), 0);
					ret.AddAxis($"P{i + 1} Analog R", 0.RangeTo(255), 0);
				}
			}

			if (IsWii)
			{
				var wms = _syncSettings.WiiPadSettings;
				Wiimotes = new[]
				{
					new Wiimote(wms.Wiimote1, wms.Wiimote1MotionPlus, wms.Wiimote1Extension),
					new Wiimote(wms.Wiimote2, wms.Wiimote2MotionPlus, wms.Wiimote2Extension),
					new Wiimote(wms.Wiimote3, wms.Wiimote3MotionPlus, wms.Wiimote3Extension),
					new Wiimote(wms.Wiimote4, wms.Wiimote4MotionPlus, wms.Wiimote4Extension),
				};

				for (int i = 0; i < 4; i++)
				{
					if (Wiimotes[i].IsActive)
					{
						foreach (var b in Enum.GetValues(typeof(LibDolphin.CoreButtons)))
						{
							ret.BoolButtons.Add($"P{i + 5} {Enum.GetName(typeof(LibDolphin.CoreButtons), b)}");
						}

						ret.AddXYZTriple($"P{i + 5} Accelerometer {{0}}", 0.RangeTo(1023), 512);

						ret.BoolButtons.Add($"P{i + 5} IR Pointing");
						ret.AddXYPair($"P{i + 5} IR {{0}}", AxisPairOrientation.LeftAndDown, 0.RangeTo(1023), 512, 0.RangeTo(767), 384);
						ret.AddAxis($"P{i + 5} IR Z", 0.RangeTo(767), 384);

						if (Wiimotes[i].HasMotionPlus)
						{
							// ???
						}

						switch (Wiimotes[i].Extension)
						{
							case DolphinWiiPadSettings.WiimoteExtensions.None:
								break;
							case DolphinWiiPadSettings.WiimoteExtensions.Nunchuk:
								// todo
								break;
						}
					}
				}
			}

			if (_multiDisc)
			{
				ret.BoolButtons.Add("Swap Disc");
			}

			ret.BoolButtons.Add("Reset");

			return ret.MakeImmutable();
		}

		// todo: remove these callbacks when possible
		private readonly LibDolphin.MPlusConfigCallback mpluscb;
		private readonly LibDolphin.ExtensionConfigCallback extensioncb;

		private bool _isDumpingDtm;

		private BinaryWriter _dtm;

		private void InitDtmDump(string gameName, string gameID, byte[] secondDiscName, byte[] gameHash, uint iromHash, uint coefHash)
		{
			_inputCount = 0;

			if (!Directory.Exists("DolphinDTMs"))
			{
				Directory.CreateDirectory("DolphinDTMs");
			}

			_dtm = new(new FileStream($"DolphinDTMs/{gameName}_{DateTime.Now.Ticks}.dtm", FileMode.CreateNew, FileAccess.Write));
			_dtm.Seek(0, SeekOrigin.Begin);

			// https://tasvideos.org/EmulatorResources/DTM
			_dtm.Write(Encoding.ASCII.GetBytes("DTM\u001a")); // signature
			_dtm.Write(Encoding.ASCII.GetBytes(gameID)); // game id
			_dtm.Write(IsWii); // wii (always false for now)
			var controllers = 0;
			controllers |= _syncSettings.MainSettings.SIDevice0 != DolphinMainSettings.SIDevices.None ? (1 << 0) : 0;
			controllers |= _syncSettings.MainSettings.SIDevice1 != DolphinMainSettings.SIDevices.None ? (1 << 1) : 0;
			controllers |= _syncSettings.MainSettings.SIDevice2 != DolphinMainSettings.SIDevices.None ? (1 << 2) : 0;
			controllers |= _syncSettings.MainSettings.SIDevice3 != DolphinMainSettings.SIDevices.None ? (1 << 3) : 0;
			if (IsWii) // should this be always rather?
			{
				controllers |= _syncSettings.WiiPadSettings.Wiimote1 ? (1 << 4) : 0;
				controllers |= _syncSettings.WiiPadSettings.Wiimote2 ? (1 << 5) : 0;
				controllers |= _syncSettings.WiiPadSettings.Wiimote3 ? (1 << 6) : 0;
				controllers |= _syncSettings.WiiPadSettings.Wiimote4 ? (1 << 7) : 0;
			}
			_dtm.Write((byte)controllers); // controllers
			_dtm.Write(false); // not going to be supporting starting from savestate
			_dtm.Write(0L); // NOTE: vi count, set at end
			_dtm.Write(0L); // NOTE: input count, set at end
			_dtm.Write(0L); // NOTE: lag count, set at end
			_dtm.Write(new byte[8]); // reserved
			_dtm.Write(0); // NOTE: re-record count... don't have access to that, so user can set it manually if they want
			_dtm.Write(Encoding.ASCII.GetBytes("BizHawk")); // author name...
			_dtm.Write(new byte[32 - 7]); // 0 pad author name
			var videoBackend = Enum.GetName(typeof(DolphinMainSettings.GFXBackends), _syncSettings.MainSettings.GFXBackend);
			_dtm.Write(Encoding.ASCII.GetBytes(videoBackend)); // video backend name...
			_dtm.Write(new byte[16 - videoBackend.Length]); // 0 pad video backend name
			_dtm.Write(new byte[16]); // audio emulator, not actually implemented in upstream
			_dtm.Write(gameHash); // md5 of iso...
			// dolphin only supports UNIX timestamps with 4 bytes of width, although the movie header has it with 8 bytes...
			_dtm.Write((long)(uint)(_syncSettings.MainSettings.CustomRTCValue - new DateTime(1970, 1, 1, 0, 0, 0)).TotalSeconds);
			_dtm.Write(true); // yes, these are valid sync settings
			// well, maybe, game specific settings aren't set here
			// if these are problematic, they are probably easy enough to set manually
			_dtm.Write(true); // skip idle (legacy setting)
			_dtm.Write(false); // dual core (always false)
			_dtm.Write(_syncSettings.SYSCONFSettings.PGS); // progressive scan
			_dtm.Write(_syncSettings.MainSettings.DSPHLE); // DSP HLE
			_dtm.Write(false); // fast disc speed (always false)
			_dtm.Write((byte)_syncSettings.MainSettings.CPUCore); // cpu core
			_dtm.Write(_syncSettings.GFXSettings.EFBAccessEnable); // efb access enable
			_dtm.Write(true); // efb copy enable (legacy setting)
			_dtm.Write(_syncSettings.GFXSettings.EFBToTextureEnable); // skip efb copy to ram
			_dtm.Write(false); // efb copy cache enable (legacy setting)
			_dtm.Write(_syncSettings.GFXSettings.EFBEmulateFormatChanges); // efb emulate format changes
			_dtm.Write(_syncSettings.GFXSettings.ImmediateXFBEnable); // immediate xfb enable
			_dtm.Write(_syncSettings.GFXSettings.XFBToTextureEnable); // skip xfb copy to ram
			var memcards = 0;
			memcards |= _syncSettings.MainSettings.SlotA == DolphinMainSettings.EXIDeviceType.MemoryCardFolder ? (1 << 0) : 0;
			memcards |= _syncSettings.MainSettings.SlotB == DolphinMainSettings.EXIDeviceType.MemoryCardFolder ? (1 << 1) : 0;
			_dtm.Write((byte)memcards); // memcards
			_dtm.Write(true); // not supporting starting from SRAM
			_dtm.Write((byte)0); // bongos (not supported)
			_dtm.Write(true); // sync GPU (this is more useless, since it only matters in dual core)
			_dtm.Write(false); // netplay (wtf?)
			_dtm.Write(_syncSettings.SYSCONFSettings.E60); // pal60
			_dtm.Write(IsWii ? (byte)_syncSettings.SYSCONFSettings.LNG : (byte)_syncSettings.MainSettings.SelectedLanguage); // language
			_dtm.Write(new byte[1]); // reserved
			_dtm.Write(_syncSettings.MainSettings.JITFollowBranch); // jit follow branch
			_dtm.Write(true); // use FMA (probably a safe bet this is enabled, it rolled out around 2012-2013, disable manually if needed)
			_dtm.Write((byte)0); // gba controllers (not even built in so...)
			_dtm.Write(new byte[7]); // reserved
			_dtm.Write(secondDiscName); // name of second disc for double disc game
			_dtm.Write(new byte[20]
			{
				0xC4, 0x14, 0x67, 0xA8, 0xEB, 0x07, 0x60, 0x45, 0xE2, 0xA1, 0x4C, 0x7C, 0x0A, 0x15, 0xD5, 0x0F, 0x74, 0xD2, 0x6E, 0xC2,
			}); // hash of revision this fork is based on (5.0-16426)
			_dtm.Write(iromHash); // dsp pirom hash
			_dtm.Write(coefHash); // dsp coef hash
			_dtm.Write(0L); // NOTE: tick count, set at end
			_dtm.Write(new byte[11]); // reserved
			Trace.Assert(_dtm.BaseStream.Position == 256);
		}

		private void EndDtmDump()
		{
			// finish header
			_dtm.Seek(0x0D, SeekOrigin.Begin);
			_dtm.Write((long)Frame);
			_dtm.Write(_inputCount);
			_dtm.Write((long)LagCount);
			_dtm.Seek(0xED, SeekOrigin.Begin);
			_dtm.Write(_core.Dolphin_GetTicks());

			// cleanup
			_dtm.Flush();
			_dtm.Close();
			_dtm.Dispose();
			_dtm = null;
			_isDumpingDtm = false;
		}

		private long _inputCount;

		private unsafe void DumpGCPadToDtm(LibDolphin.GCPadStatus* p)
		{
			byte buttons = 0;
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.Start) != 0) ? (1 << 0) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.A) != 0) ? (1 << 1) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.B) != 0) ? (1 << 2) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.X) != 0) ? (1 << 3) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.Y) != 0) ? (1 << 4) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.Z) != 0) ? (1 << 5) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.Up) != 0) ? (1 << 6) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.Down) != 0) ? (1 << 7) : 0);
			_dtm.Write(buttons);

			buttons = 0;
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.Left) != 0) ? (1 << 0) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.Right) != 0) ? (1 << 1) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.L) != 0) ? (1 << 2) : 0);
			buttons |= (byte)(((p->Buttons & LibDolphin.PadButtons.R) != 0) ? (1 << 3) : 0);
			buttons |= (byte)(_doSwapDisc ? (1 << 4) : 0); // change disc
			buttons |= (byte)(_doReset ? (1 << 5) : 0); // reset
			buttons |= (byte)(p->IsConnected ? (1 << 6) : 0); // is connected (this is always true)
			buttons |= false ? (1 << 7) : 0; // PAD_GET_ORIGIN (this is always false due to how the code works)
			_dtm.Write(buttons);

			_dtm.Write(p->TriggerLeft);
			_dtm.Write(p->TriggerRight);
			_dtm.Write(p->StickX);
			_dtm.Write(p->StickY);
			_dtm.Write(p->SubstickX);
			_dtm.Write(p->SubstickY);

			_inputCount++;
		}

		private unsafe void DumpWiiPadToDtm(byte* rpt)
		{
			byte len = *rpt switch
			{
				0x30 => 1 + 2,
				0x31 => 1 + 2 + 3,
				0x32 => 1 + 2 + 8,
				0x33 => 1 + 2 + 3 + 12,
				0x34 => 1 + 2 + 19,
				0x35 => 1 + 2 + 3 + 16,
				0x36 => 1 + 2 + 10 + 9,
				0x37 => 1 + 2 + 3 + 10 + 9,
				0x3D => 1 + 21,
				0x3E or 0x3F => 1 + 2 + 1 + 18,
				_ => throw new InvalidOperationException(),
			};

			_dtm.Write(len);
			for (int i = 0; i < len; i++)
			{
				_dtm.Write(*rpt++);
			}

			_inputCount++;
		}

		public static string QuickHashDisc(string path)
		{
			var hash = new byte[4];
			_core.Dolphin_HashMedium(path, hash, true, CurrentCore is null);
			string ret = "";
			foreach (var b in hash)
				ret += b.ToString("X2");

			return ret;
		}
	}
}
