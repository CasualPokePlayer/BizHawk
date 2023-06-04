#nullable enable

using System;
using System.Windows.Forms;

using BizHawk.Bizware.BizwareGL;
using Veldrid;

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
		private readonly Func<GraphicsDevice> _getDevice;

		public VeldridControlWrapper(IGL owner, Func<GraphicsDevice> getDevice)
		{
			_owner = owner;
			_getDevice = getDevice;

			ClientSize = new(1, 1); // must be at least 1x1 for Vulkan
			Resize += (_, _) => _getDevice().ResizeMainWindow((uint)ClientSize.Width, (uint)ClientSize.Height);
		}

		public void SetVsync(bool state)
		{
			_getDevice().SyncToVerticalBlank = state;
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
			_getDevice().SwapBuffers();
		}
	}
}