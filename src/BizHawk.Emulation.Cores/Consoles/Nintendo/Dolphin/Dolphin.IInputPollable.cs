using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

using BizHawk.BizInvoke;
using BizHawk.Common;
using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Components;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	public partial class Dolphin : IInputPollable
	{
		public int LagCount { get; set; }
		public bool IsLagFrame { get; set; }
		public IInputCallbackSystem InputCallbacks { get; } = new InputCallbackSystem();

		private IController _controller = NullController.Instance;

		private readonly LibDolphin.GCPadCallback _gcpadcb;

		private void GCPadCallback(IntPtr padStatus, int controllerID)
		{
			IsLagFrame = false;
			InputCallbacks.Call();
			// todo
		}
	}
}
