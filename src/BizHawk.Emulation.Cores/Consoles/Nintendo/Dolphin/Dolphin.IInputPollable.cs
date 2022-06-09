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
			lock (_controller)
			{
				IsLagFrame = false;
				InputCallbacks.Call();

				var p = (LibDolphin.GCPadStatus*)padStatus;
				var n = controllerID + 1;

				p->Buttons = 0;
				p->Buttons |= (LibDolphin.PadButtons)0x0080; // PAD_USE_ORIGIN
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

				if ((p->Buttons & LibDolphin.PadButtons.L) != 0)
				{
					p->TriggerLeft = 0xFF;
				}
				else
				{
					p->TriggerLeft = (byte)_controller.AxisValue($"P{n} Analog L");
					if (p->TriggerLeft == 0xFF)
					{
						p->Buttons |= LibDolphin.PadButtons.L;
					}
				}

				if ((p->Buttons & LibDolphin.PadButtons.R) != 0)
				{
					p->TriggerRight = 0xFF;
				}
				else
				{
					p->TriggerRight = (byte)_controller.AxisValue($"P{n} Analog R");
					if (p->TriggerRight == 0xFF)
					{
						p->Buttons |= LibDolphin.PadButtons.R;
					}
				}

				p->AnalogA = (byte)(((p->Buttons & LibDolphin.PadButtons.A) != 0) ? 0xFF : 0);
				p->AnalogB = (byte)(((p->Buttons & LibDolphin.PadButtons.B) != 0) ? 0xFF : 0);

				p->IsConnected = true;

				if (_isDumpingDtm)
				{
					DumpGCPadToDtm(p);
				}
			}
		}

		private readonly LibDolphin.WiiPadCallback _wiipadcb;

		private unsafe void WiiPadCallback(IntPtr rpt, LibDolphin.WiimoteInputReq which, int controllerID)
		{
			lock (_controller)
			{
				var n = controllerID + 5;

				switch (which)
				{
					case LibDolphin.WiimoteInputReq.CORE_BUTTONS:
						{
							var p = *(LibDolphin.CoreButtons*)rpt;
							p &= ~LibDolphin.CoreButtonsMask;

							if (_controller.IsPressed($"P{n} Left"))
								p |= LibDolphin.CoreButtons.Left;
							if (_controller.IsPressed($"P{n} Right"))
								p |= LibDolphin.CoreButtons.Right;
							if (_controller.IsPressed($"P{n} Down"))
								p |= LibDolphin.CoreButtons.Down;
							if (_controller.IsPressed($"P{n} Up"))
								p |= LibDolphin.CoreButtons.Up;
							if (_controller.IsPressed($"P{n} Plus"))
								p |= LibDolphin.CoreButtons.Plus;
							if (_controller.IsPressed($"P{n} Two"))
								p |= LibDolphin.CoreButtons.Two;
							if (_controller.IsPressed($"P{n} One"))
								p |= LibDolphin.CoreButtons.One;
							if (_controller.IsPressed($"P{n} B"))
								p |= LibDolphin.CoreButtons.B;
							if (_controller.IsPressed($"P{n} A"))
								p |= LibDolphin.CoreButtons.A;
							if (_controller.IsPressed($"P{n} Minus"))
								p |= LibDolphin.CoreButtons.Minus;
							if (_controller.IsPressed($"P{n} Home"))
								p |= LibDolphin.CoreButtons.Home;

							*(LibDolphin.CoreButtons*)rpt = p;
							break;
						}
					case LibDolphin.WiimoteInputReq.CORE_ACCEL:
						{
							var p = (LibDolphin.CoreAccel*)rpt;
							p->X = (ushort)_controller.AxisValue($"P{n} Accelerometer X");
							p->Y = (ushort)_controller.AxisValue($"P{n} Accelerometer Y");
							p->Z = (ushort)_controller.AxisValue($"P{n} Accelerometer Z");
							break;
						}
					case LibDolphin.WiimoteInputReq.CORE_IR_BASIC:
						{
							if (_controller.IsPressed($"P{n} IR Pointing"))
							{
								var p = (LibDolphin.CoreIRBasic*)rpt;
								var c = GetIRCoords(n);

								p[0].X1 = (byte)(c.X1 & 0xFF);
								p[0].Y1 = (byte)(c.Y1 & 0xFF);
								p[0].Hi &= ~(LibDolphin.CoreIRBasicHi.X1 | LibDolphin.CoreIRBasicHi.Y1);
								p[0].Hi |= (LibDolphin.CoreIRBasicHi)((c.X1 >> 8) << 4) & LibDolphin.CoreIRBasicHi.X1;
								p[0].Hi |= (LibDolphin.CoreIRBasicHi)((c.Y1 >> 8) << 6) & LibDolphin.CoreIRBasicHi.Y1;

								p[0].X2 = (byte)(c.X2 & 0xFF);
								p[0].Y2 = (byte)(c.Y2 & 0xFF);
								p[0].Hi &= ~(LibDolphin.CoreIRBasicHi.X2 | LibDolphin.CoreIRBasicHi.Y2);
								p[0].Hi |= (LibDolphin.CoreIRBasicHi)((c.X2 >> 8) << 0) & LibDolphin.CoreIRBasicHi.X2;
								p[0].Hi |= (LibDolphin.CoreIRBasicHi)((c.Y2 >> 8) << 2) & LibDolphin.CoreIRBasicHi.Y2;
							}
							break;
						}
					case LibDolphin.WiimoteInputReq.CORE_IR_EXTENDED:
						{
							if (_controller.IsPressed($"P{n} IR Pointing"))
							{
								var p = (LibDolphin.CoreIRExtended*)rpt;
								var c = GetIRCoords(n);
								var sz = _controller.AxisValue($"P{n} IR Z") / 48;

								p[0].X = (byte)(c.X1 & 0xFF);
								p[0].Y = (byte)(c.Y1 & 0xFF);
								p[0].SzHi = 0;
								p[0].SzHi |= (LibDolphin.CoreIRExtendedSzHi)sz & LibDolphin.CoreIRExtendedSzHi.Sz;
								p[0].SzHi |= (LibDolphin.CoreIRExtendedSzHi)((c.X1 >> 8) << 4) & LibDolphin.CoreIRExtendedSzHi.X;
								p[0].SzHi |= (LibDolphin.CoreIRExtendedSzHi)((c.Y1 >> 8) << 6) & LibDolphin.CoreIRExtendedSzHi.Y;

								p[1].X = (byte)(c.X2 & 0xFF);
								p[1].Y = (byte)(c.Y2 & 0xFF);
								p[1].SzHi = 0;
								p[1].SzHi |= (LibDolphin.CoreIRExtendedSzHi)sz & LibDolphin.CoreIRExtendedSzHi.Sz;
								p[1].SzHi |= (LibDolphin.CoreIRExtendedSzHi)((c.X2 >> 8) << 4) & LibDolphin.CoreIRExtendedSzHi.X;
								p[1].SzHi |= (LibDolphin.CoreIRExtendedSzHi)((c.Y2 >> 8) << 6) & LibDolphin.CoreIRExtendedSzHi.Y;
							}
							break;
						}
					case LibDolphin.WiimoteInputReq.CORE_IR_FULL:
						{
							if (_controller.IsPressed($"P{n} IR Pointing"))
							{
								var p = (LibDolphin.CoreIRFull*)rpt;
								var c = GetIRCoords(n);
								var sz = _controller.AxisValue($"P{n} IR Z") / 48;
								const double Tau = 6.2831853071795862; // apparently not available in Math here

								p[0].X = (byte)(c.X1 & 0xFF);
								p[0].Y = (byte)(c.Y1 & 0xFF);
								p[0].SzHi = 0;
								p[0].SzHi |= (LibDolphin.CoreIRExtendedSzHi)sz & LibDolphin.CoreIRExtendedSzHi.Sz;
								p[0].SzHi |= (LibDolphin.CoreIRExtendedSzHi)((c.X1 >> 8) << 4) & LibDolphin.CoreIRExtendedSzHi.X;
								p[0].SzHi |= (LibDolphin.CoreIRExtendedSzHi)((c.Y1 >> 8) << 6) & LibDolphin.CoreIRExtendedSzHi.Y;

								p[0].XMin = (byte)(Math.Max(c.X1 - sz, 0) & 0x7F);
								p[0].YMin = (byte)(Math.Max(c.Y1 - sz, 0) & 0x7F);
								p[0].XMax = (byte)(Math.Min(c.X1 + sz, 1023) & 0x7F);
								p[0].YMax = (byte)(Math.Min(c.Y1 + sz, 767) & 0x7F);

								p[0].ZeroPadding = 0;
								p[0].Intensity = (byte)Math.Round((p[0].XMax - p[0].XMin) * (p[0].YMax - p[0].YMin) / 8 / 8 * Tau / 8);

								p[1].X = (byte)(c.X2 & 0xFF);
								p[1].Y = (byte)(c.Y2 & 0xFF);
								p[1].SzHi = 0;
								p[1].SzHi |= (LibDolphin.CoreIRExtendedSzHi)sz & LibDolphin.CoreIRExtendedSzHi.Sz;
								p[1].SzHi |= (LibDolphin.CoreIRExtendedSzHi)((c.X2 >> 8) << 4) & LibDolphin.CoreIRExtendedSzHi.X;
								p[1].SzHi |= (LibDolphin.CoreIRExtendedSzHi)((c.Y2 >> 8) << 6) & LibDolphin.CoreIRExtendedSzHi.Y;

								p[1].XMin = (byte)(Math.Max(c.X2 - sz, 0) & 0x7F);
								p[1].YMin = (byte)(Math.Max(c.Y2 - sz, 0) & 0x7F);
								p[1].XMax = (byte)(Math.Min(c.X2 + sz, 1023) & 0x7F);
								p[1].YMax = (byte)(Math.Min(c.Y2 + sz, 767) & 0x7F);

								p[1].ZeroPadding = 0;
								p[1].Intensity = (byte)Math.Round((p[1].XMax - p[1].XMin) * (p[1].YMax - p[1].YMin) / 8 / 8 * Tau / 8);
							}
							break;
						}
					case LibDolphin.WiimoteInputReq.END_INPUT:
						{
							IsLagFrame = false;
							InputCallbacks.Call();
							if (_isDumpingDtm)
							{
								// todo...
							}
							break;
						}
				}
			}
		}

		private struct IRCoords
		{
			public int X1;
			public int Y1;
			public int X2;
			public int Y2;
		}

		private IRCoords GetIRCoords(int n)
		{
			var ret = new IRCoords();
			var x = _controller.AxisValue($"P{n} IR X");
			var y = _controller.AxisValue($"P{n} IR Y");
			var z = _controller.AxisValue($"P{n} IR Z");

			ret.X1 = x - z / 2;
			ret.X2 = x + z / 2;

			ret.Y1 = ret.Y2 = y;

			if (ret.X1 < 0 || ret.X1 > 1023 || ret.Y1 < 0 || ret.Y1 > 767)
				ret.X1 = ret.Y1 = 0xFFFF;
			if (ret.X2 < 0 || ret.X2 > 1023 || ret.Y2 < 0 || ret.Y2 > 767)
				ret.X2 = ret.Y2 = 0xFFFF;

			return ret;
		}
	}
}
