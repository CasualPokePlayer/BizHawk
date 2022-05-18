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
		public Dolphin(CoreLoadParameters<object, DolphinSyncSettings> lp)
		{
			_serviceProvider = new(this);
			_syncSettings = lp.SyncSettings ?? new();

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

			InitMemoryDomains();

			ResetCounters();
		}

		private ControllerDefinition CreateControllerDefinition()
		{
			var ret = new ControllerDefinition("GameCube Front Panel");
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

					ret.AddXYPair($"P{i + 1} Main Stick {{0}}", AxisPairOrientation.RightAndUp, (0).RangeTo(255), 128);
					ret.AddXYPair($"P{i + 1} C Stick {{0}}", AxisPairOrientation.RightAndUp, (0).RangeTo(255), 128);
					ret.AddAxis($"P{i + 1} Analog L", (0).RangeTo(255), 128);
					ret.AddAxis($"P{i + 1} Analog R", (0).RangeTo(255), 128);
				}
			}
			return ret;
		}
	}
}
