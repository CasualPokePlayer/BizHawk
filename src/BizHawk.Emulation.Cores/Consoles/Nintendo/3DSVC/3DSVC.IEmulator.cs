using System.Collections.Generic;

using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.ThreeDSVC
{
	public partial class ThreeDSVC : IEmulator
	{
		public IEmulatorServiceProvider ServiceProvider => _serviceProvider;

		public ControllerDefinition ControllerDefinition { get; }

		private static readonly IReadOnlyList<string> GB_BUTTON_ORDER_IN_BITMASK = new[] { "Down", "Up", "Left", "Right", "Start", "Select", "B", "A", };

		private Lib3DSVC.Buttons FrameAdvancePrep(IController controller)
		{
			uint b = 0;
			for (var i = 0; i < 8; i++)
			{
				b <<= 1;
				if (controller.IsPressed(GB_BUTTON_ORDER_IN_BITMASK[i])) b |= 1;
			}

			IsLagFrame = false;

			if (controller.IsPressed("Power"))
			{
				_core.VC_Reset();
			}

			_core.VC_SetTraceCallback(Tracer.IsEnabled() ? _traceCallback : null);

			return (Lib3DSVC.Buttons)b;
		}

		public bool FrameAdvance(IController controller, bool render, bool rendersound)
		{
			var buttons = FrameAdvancePrep(controller);

			_core.VC_RunFrame(buttons, VideoBuffer, _soundoutbuff, ref _soundoutbuffcontains);

			if (!rendersound)
			{
				DiscardSamples();
			}

			FrameAdvancePost();

			return true;
		}

		private void FrameAdvancePost()
		{
			if (IsLagFrame)
			{
				LagCount++;
			}

			Frame++;

			_scanlineCallback?.Invoke(_core.VC_GetIOReg(0x40));
		}

		public int Frame { get; private set; }

		public string SystemId => VSystemID.Raw.GB;

		public bool DeterministicEmulation => true;

		public void ResetCounters()
		{
			Frame = 0;
			LagCount = 0;
			IsLagFrame = false;
		}

		private bool _disposed = false;

		public void Dispose()
		{
			if (!_disposed)
			{
				_core.VC_Deinit();
				_disposed = true;
				CurrentCore = null;
			}
		}
	}
}
