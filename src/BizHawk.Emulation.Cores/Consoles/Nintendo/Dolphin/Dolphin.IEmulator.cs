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

		public string SystemId => VSystemID.Raw.GC;

		public bool DeterministicEmulation { get; }

		public bool FrameAdvance(IController controller, bool render, bool renderSound = true)
		{
			_controller = controller;
			IsLagFrame = true;

			_core.Dolphin_FrameStep();

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

		public void Dispose()
		{
			if (_hostRunning)
			{
				_core.Dolphin_Shutdown();
				while (_hostRunning)
				{
					Thread.Sleep(1);
				}
				_hostThread = null;
			}
		}
	}
}
