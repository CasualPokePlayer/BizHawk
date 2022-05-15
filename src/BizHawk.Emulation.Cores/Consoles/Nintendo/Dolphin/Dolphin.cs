using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;

using BizHawk.BizInvoke;
using BizHawk.Common;
using BizHawk.Emulation.Common;

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
				"--video_backend=Vulkan", // todo: config
				"--audio_emulation=HLE", // todo: config
				"--platform=headless",
			});

			_syncSettings.ApplyNativeSettings(args);
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
	}
}
