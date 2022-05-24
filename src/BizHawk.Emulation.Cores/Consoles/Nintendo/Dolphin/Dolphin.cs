using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Text;
using System.Threading;

using BizHawk.BizInvoke;
using BizHawk.Common;
using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Properties;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	[PortedCore(CoreNames.Dolphin, "Dolphin Team", "5.0-16444-dirty", "https://github.com/dolphin-emu/dolphin", singleInstance: true, isReleased: false)]
	public partial class Dolphin
	{
		private static readonly LibDolphin _core;

		static Dolphin()
		{
			var resolver = new DynamicLibraryImportResolver(
				OSTailoredCode.IsUnixHost ? "libdolphin-emu-nogui.so" : "dolphin-emu-nogui.dll", hasLimitedLifetime: false);
			_core = BizInvoker.GetInvoker<LibDolphin>(resolver, CallingConventionAdapters.Native);
		}

		private Thread _hostThread;
		private volatile bool _hostRunning;

		private void ExecuteHostThread(string gamePath)
		{
			List<string> args = new(new[]
			{
				"BizHawk",
				"--user=DolphinUserFolder",
				$"--exec={gamePath}",
				"--platform=headless",
			});

			ApplyNativeSettings(args);
			_core.Dolphin_Main(args.Count, args.ToArray());
			_hostRunning = false;
		}

		private static string GetGameId(string path)
		{
			using var reader = new StreamReader(path, Encoding.UTF8);
			var ret = new char[6];
			reader.Read(ret, 0, 6);
			return new string(ret);
		}

		[CoreConstructor(VSystemID.Raw.GC)]
		[CoreConstructor(VSystemID.Raw.Wii)]
		public Dolphin(CoreLoadParameters<DolphinSettings, DolphinSyncSettings> lp)
		{
			_serviceProvider = new(this);
			_settings = lp.Settings ?? new();
			_syncSettings = lp.SyncSettings ?? new();
			SystemId = lp.Game.System;
			IsWii = SystemId == VSystemID.Raw.Wii;
			_isDumpingDtm = !IsWii && _settings.DumpDTM && lp.DeterministicEmulationRequested;
			if (_isDumpingDtm)
			{
				InitDtmDump(lp.Game.Name, GetGameId(lp.Discs[0].DiscPath));
			}

			if (Directory.Exists("DolphinUserFolder"))
			{
				Directory.Delete("DolphinUserFolder", true);
			}
			Directory.CreateDirectory("DolphinUserFolder");
			if (_syncSettings.ApplyPerGameSettings)
			{
				using var gameSettings = new ZipArchive(new MemoryStream(Util.DecompressGzipFile(new MemoryStream(Resources.DOLPHINGAMESETTINGS.Value))), ZipArchiveMode.Read, false);
				gameSettings.ExtractToDirectory("Dolphin");
			}

			DeterministicEmulation = lp.DeterministicEmulationRequested || _syncSettings.MainSettings.EnableCustomRTC;
			ControllerDefinition = CreateControllerDefinition();

			mpluscb = MotionPlusConfigCallback;
			extensioncb = ExtensionConfigCallback;
			_core.Dolphin_SetConfigCallbacks(mpluscb, extensioncb);

			_hostRunning = true;
			_hostThread = new Thread(() => ExecuteHostThread(lp.Discs[0].DiscPath)) { IsBackground = true };
			_hostThread.Start();

			while (!_core.Dolphin_BootupSuccessful())
			{
				if (!_hostRunning)
				{
					throw new Exception("Dolphin failed to bootup!");
				}

				Thread.Sleep(1);
			}

			_framecb = FrameCallback;
			_core.Dolphin_SetFrameCallback(_framecb);

			_gcpadcb = GCPadCallback;
			_core.Dolphin_SetGCPadCallback(_gcpadcb);

			if (IsWii)
			{
				_wiipadcb = WiiPadCallback;
				_core.Dolphin_SetWiiPadCallback(_wiipadcb);
			}

			InitMemoryDomains();

			ResetCounters();
		}

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

			return ret.MakeImmutable();
		}

		// todo: remove when possible

		private readonly LibDolphin.MPlusConfigCallback mpluscb;
		private readonly LibDolphin.ExtensionConfigCallback extensioncb;

		private bool MotionPlusConfigCallback(int n)
		{
			return Wiimotes[n].HasMotionPlus;
		}

		private DolphinWiiPadSettings.WiimoteExtensions ExtensionConfigCallback(int n)
		{
			return Wiimotes[n].Extension;
		}

		private bool _isDumpingDtm;

		private BinaryWriter _dtm;

		private void InitDtmDump(string gameName, string gameID)
		{
			_inputCount = 0;

			if (!Directory.Exists("DolphinDTMs"))
			{
				Directory.CreateDirectory("DolphinDTMs");
			}

			_dtm = new(new FileStream($"DolphinDTMs/{gameName}_{DateTime.Now.Ticks}.dtm", FileMode.CreateNew, FileAccess.Write));
			_dtm.Seek(0, SeekOrigin.Begin);

			// https://tasvideos.org/EmulatorResources/DTM
			_dtm.Write(Encoding.UTF8.GetBytes("DTM\u001a")); // signature
			_dtm.Write(Encoding.UTF8.GetBytes(gameID)); // game id
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
			_dtm.Write(Encoding.UTF8.GetBytes("BizHawk")); // author name...
			_dtm.Write(new byte[32 - 7]); // 0 pad author name
			var videoBackend = Enum.GetName(typeof(DolphinMainSettings.GFXBackends), _syncSettings.MainSettings.GFXBackend);
			_dtm.Write(Encoding.UTF8.GetBytes(videoBackend)); // video backend name...
			_dtm.Write(new byte[16 - videoBackend.Length]); // 0 pad video backend name
			_dtm.Write(new byte[16]); // audio emulator, not actually implemented in upstream
			_dtm.Write(new byte[16]); // md5 of iso... probably don't want to implement this yet
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
			_dtm.Write(new byte[40]); // name of second iso for double disc game... not sure how to support this yet
			_dtm.Write(new byte[20]
			{
				0xC4, 0x14, 0x67, 0xA8, 0xEB, 0x07, 0x60, 0x45, 0xE2, 0xA1, 0x4C, 0x7C, 0x0A, 0x15, 0xD5, 0x0F, 0x74, 0xD2, 0x6E, 0xC2,
			}); // hash of revision this fork is based on (5.0-16426)
			_dtm.Write(0); // dsp pirom hash... not actually hooked up atm
			_dtm.Write(0); // dsp coef hash... not actually hooked up atm
			_dtm.Write(0L); // NOTE: tick count, set at end
			_dtm.Write(new byte[11]); // reserved
			Debug.Assert(_dtm.BaseStream.Position == 256);
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
			buttons |= false ? (1 << 4) : 0; // change disc (not supported)
			buttons |= false ? (1 << 5) : 0; // reset (not supported)
			buttons |= (byte)(p->IsConnected ? (1 << 6) : 0); // is connected (this is always true)
			buttons |= true ? (1 << 7) : 0; // use origin (this is always true)
			_dtm.Write(buttons);

			_dtm.Write(p->TriggerLeft);
			_dtm.Write(p->TriggerRight);
			_dtm.Write(p->StickX);
			_dtm.Write(p->StickY);
			_dtm.Write(p->SubstickX);
			_dtm.Write(p->SubstickY);
		}
	}
}
