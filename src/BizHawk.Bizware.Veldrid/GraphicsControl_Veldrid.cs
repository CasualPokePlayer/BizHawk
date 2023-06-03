#nullable enable

using System;
using System.Windows.Forms;

using BizHawk.Bizware.BizwareGL;

namespace BizHawk.Bizware.Veldrid
{
	internal class VeldridControlWrapper : Control, IGraphicsControl
	{
		public RenderTargetWrapper RenderTargetWrapper
		{
			get => throw new NotImplementedException();
			set => throw new NotImplementedException();
		}

		private readonly IGL _owner;
		private readonly Action<int, int> _resizeCallback;
		private readonly Action<bool> _setVsyncCallback;
		private readonly Action _swapBuffersCallback;

		public VeldridControlWrapper(IGL owner, Action<int, int> resizeCallback, Action<bool> setVsyncCallback, Action swapBuffersCallback)
		{
			_owner = owner;
			_resizeCallback = resizeCallback;
			_setVsyncCallback = setVsyncCallback;
			_swapBuffersCallback = swapBuffersCallback;
			ClientSize = new(1, 1);

			Resize += (_, _) => _resizeCallback(ClientSize.Width, ClientSize.Height);
		}

		public void SetVsync(bool state)
		{
			_setVsyncCallback(state);
		}

		public void Begin()
		{
			_owner.BeginScene();
		}

		public void End()
		{
			_owner.EndScene();
		}

		public void SwapBuffers()
		{
			_swapBuffersCallback();
		}
	}
}