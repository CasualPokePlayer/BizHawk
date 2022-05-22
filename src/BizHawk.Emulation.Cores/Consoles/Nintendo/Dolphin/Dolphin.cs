using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
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
			if (OSTailoredCode.IsUnixHost)
			{
				throw new NotImplementedException();
			}

			var resolver = new DynamicLibraryImportResolver("dolphin-emu-nogui.dll", hasLimitedLifetime: false);
			_core = BizInvoker.GetInvoker<LibDolphin>(resolver, CallingConventionAdapters.Native);
		}

		private Thread _hostThread;
		private volatile bool _hostRunning;

		private void ExecuteHostThread(string gamePath)
		{
			List<string> args = new(new[]
			{
				"BizHawk",
				"--user=Dolphin",
				$"--exec={gamePath}",
				"--platform=headless",
			});

			ApplyNativeSettings(args);
			_core.Dolphin_Main(args.Count, args.ToArray());
			_hostRunning = false;
		}

		[CoreConstructor(VSystemID.Raw.GC)]
		[CoreConstructor(VSystemID.Raw.Wii)]
		public Dolphin(CoreLoadParameters<object, DolphinSyncSettings> lp)
		{
			_serviceProvider = new(this);
			_syncSettings = lp.SyncSettings ?? new();
			SystemId = lp.Game.System;
			IsWii = SystemId == VSystemID.Raw.Wii;

			if (Directory.Exists("Dolphin"))
			{
				Directory.Delete("Dolphin", true);
			}
			Directory.CreateDirectory("Dolphin");
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
	}
}
