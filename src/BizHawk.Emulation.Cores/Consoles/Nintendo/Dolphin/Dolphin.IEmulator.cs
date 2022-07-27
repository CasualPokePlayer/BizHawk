using System;
using System.Threading;

using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	public partial class Dolphin : IEmulator
	{
		private readonly BasicServiceProvider _serviceProvider;

		public IEmulatorServiceProvider ServiceProvider => _serviceProvider;

		public ControllerDefinition ControllerDefinition { get; }

		public int Frame { get; set; }

		public string SystemId => IsWii ? VSystemID.Raw.Wii : VSystemID.Raw.GC;

		public bool DeterministicEmulation { get; }

		public bool FrameAdvance(IController controller, bool render, bool renderSound = true)
		{
			Interlocked.Exchange(ref _controller, controller);
			IsLagFrame = true;

			// deferred until input callback occurs
			bool swapDisc = _controller.IsPressed("Swap Disc");
			if (swapDisc && !_didSwapDisc)
			{
				_doSwapDisc = true;
			}
			else if (!swapDisc && _didSwapDisc)
			{
				_didSwapDisc = false;
			}

			_doReset = _controller.IsPressed("Reset");

			bool gpuLagged = _core.Dolphin_FrameStep(render, ref _width, ref _height);

			if (_settings.GPULagFrames)
			{
				IsLagFrame = gpuLagged; 
			}

			if (renderSound)
			{
				ProcessSound();
			}

			Frame++;
			if (IsLagFrame)
			{
				LagCount++;
			}

			return true;
		}

		public void ResetCounters()
		{
			Frame = 0;
			LagCount = 0;
			IsLagFrame = false;
		}

		private bool _disposed = false;

		public void Dispose()
		{
			if (_disposed)
			{
				return;
			}

			if (_vhandle.IsAllocated)
			{
				_vhandle.Free();
			}

			_core.Dolphin_SetFrameBuffer(IntPtr.Zero);
			_core.Dolphin_SetGCPadCallback(null);
			_core.Dolphin_SetWiiPadCallback(null);

			if (HostRunning)
			{
				if (_isDumpingDtm)
				{
					EndDtmDump();
				}

				_core.Dolphin_Shutdown();
				while (HostRunning)
				{
					Thread.Sleep(1);
				}
				_hostThread = null;
			}
			else
			{
				if (_isDumpingDtm)
				{
					// uh oh
					_dtm?.Flush();
					_dtm?.Close();
					_dtm?.Dispose();
					_isDumpingDtm = false;
					_dtm = null;
				}
			}

			_core.Dolphin_SetConfigCallbacks(null, null);
			CurrentCore = null;
			_disposed = true;
		}
	}
}
