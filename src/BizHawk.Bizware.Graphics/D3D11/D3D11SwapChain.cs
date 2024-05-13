using System;

using Vortice.Direct3D11;
using Vortice.DXGI;

using DXGIResultCode = Vortice.DXGI.ResultCode;

namespace BizHawk.Bizware.Graphics
{
	public sealed class D3D11SwapChain : IDisposable
	{
		public readonly struct ControlParameters
		{
			public readonly IntPtr Handle;
			public readonly int Width;
			public readonly int Height;
			public readonly bool Vsync;

			public ControlParameters(IntPtr handle, int width, int height, bool vsync)
			{
				Handle = handle;
				Width = Math.Max(width, 1);
				Height = Math.Max(height, 1);
				Vsync = vsync;
			}
		}

		internal class SwapChainResources : IDisposable
		{
			public ID3D11Device Device;
			public ID3D11DeviceContext Context;
			public ID3D11Texture2D BackBufferTexture;
			public ID3D11RenderTargetView RTV;
			public IDXGISwapChain1 SwapChain;

			public void Dispose()
			{
				// Device/Context not owned by this class
				Device = null;
				Context = null;
				BackBufferTexture?.Dispose();
				BackBufferTexture = null;
				RTV?.Dispose();
				RTV = null;
				SwapChain?.Dispose();
				SwapChain = null;
			}
		}

		private static readonly SharpGen.Runtime.Result D3DDDIERR_DEVICEREMOVED = new(2289436784UL);

		private readonly SwapChainResources _resources;
		private readonly Action<ControlParameters> _resetDeviceCallback;

		private ID3D11Device Device => _resources.Device;
		private ID3D11DeviceContext Context => _resources.Context;
		private ID3D11Texture2D BackBufferTexture => _resources.BackBufferTexture;
		private ID3D11RenderTargetView RTV => _resources.RTV;
		private IDXGISwapChain1 SwapChain => _resources.SwapChain;

		internal D3D11SwapChain(SwapChainResources resources, Action<ControlParameters> resetDeviceCallback)
		{
			_resources = resources;
			_resetDeviceCallback = resetDeviceCallback;
		}

		public void Dispose()
			=> _resources.Dispose();

		public void SetBackBuffer()
			=> Context.OMSetRenderTargets(RTV);

		public void PresentBuffer(ControlParameters cp)
		{
			SetBackBuffer();

			var result = SwapChain.Present(cp.Vsync ? 1 : 0);
			if (result == DXGIResultCode.DeviceReset
				|| result == DXGIResultCode.DeviceRemoved
				|| result == D3DDDIERR_DEVICEREMOVED)
			{
				_resetDeviceCallback(cp);
			}
		}

		public void Refresh(ControlParameters cp)
		{
			// must be released in order to resize these buffers
			BackBufferTexture.Dispose();
			RTV.Dispose();

			SwapChain.ResizeBuffers(
				bufferCount: 2,
				cp.Width,
				cp.Height,
				Format.B8G8R8A8_UNorm,
				SwapChainFlags.AllowTearing);

			_resources.BackBufferTexture = SwapChain.GetBuffer<ID3D11Texture2D>(0);
			_resources.RTV = Device.CreateRenderTargetView(BackBufferTexture);
		}
	}
}
