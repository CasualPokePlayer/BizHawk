using System;

using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	public partial class Dolphin : IInputPollable
	{
		public int LagCount { get; set; }
		public bool IsLagFrame { get; set; }
		public IInputCallbackSystem InputCallbacks { get; } = new InputCallbackSystem();

		private IController _controller = NullController.Instance;

		private readonly LibDolphin.GCPadCallback _gcpadcb;

		private unsafe void GCPadCallback(IntPtr padStatus, int controllerID)
		{
			IsLagFrame = false;
			InputCallbacks.Call();

			var p = (LibDolphin.GCPadStatus*)padStatus;
			var n = controllerID + 1;

			p->Buttons = 0;
			if (_controller.IsPressed($"P{n} Left"))
				p->Buttons |= LibDolphin.PadButtons.Left;
			if (_controller.IsPressed($"P{n} Right"))
				p->Buttons |= LibDolphin.PadButtons.Right;
			if (_controller.IsPressed($"P{n} Down"))
				p->Buttons |= LibDolphin.PadButtons.Down;
			if (_controller.IsPressed($"P{n} Up"))
				p->Buttons |= LibDolphin.PadButtons.Up;
			if (_controller.IsPressed($"P{n} Z"))
				p->Buttons |= LibDolphin.PadButtons.Z;
			if (_controller.IsPressed($"P{n} R"))
				p->Buttons |= LibDolphin.PadButtons.R;
			if (_controller.IsPressed($"P{n} L"))
				p->Buttons |= LibDolphin.PadButtons.L;
			if (_controller.IsPressed($"P{n} A"))
				p->Buttons |= LibDolphin.PadButtons.A;
			if (_controller.IsPressed($"P{n} B"))
				p->Buttons |= LibDolphin.PadButtons.B;
			if (_controller.IsPressed($"P{n} X"))
				p->Buttons |= LibDolphin.PadButtons.X;
			if (_controller.IsPressed($"P{n} Y"))
				p->Buttons |= LibDolphin.PadButtons.Y;
			if (_controller.IsPressed($"P{n} Start"))
				p->Buttons |= LibDolphin.PadButtons.Start;

			p->StickX = (byte)_controller.AxisValue($"P{n} Main Stick X");
			p->StickY = (byte)_controller.AxisValue($"P{n} Main Stick Y");
			p->SubstickX = (byte)_controller.AxisValue($"P{n} C Stick X");
			p->SubstickY = (byte)_controller.AxisValue($"P{n} C Stick Y");
			p->TriggerLeft = (byte)_controller.AxisValue($"P{n} Analog L");
			p->TriggerRight = (byte)_controller.AxisValue($"P{n} Analog R");
			p->AnalogA = (byte)(((p->Buttons & LibDolphin.PadButtons.A) != 0) ? 0xFF : 0);
			p->AnalogB = (byte)(((p->Buttons & LibDolphin.PadButtons.B) != 0) ? 0xFF : 0);
			p->IsConnected = true;
		}
	}
}
