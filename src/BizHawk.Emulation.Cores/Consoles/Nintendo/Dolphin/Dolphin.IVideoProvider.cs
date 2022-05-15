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
	public partial class Dolphin : IVideoProvider
	{
		public int VirtualWidth => BufferWidth;
		public int VirtualHeight => BufferHeight;
		public int BufferWidth { get; private set; } = 640;
		public int BufferHeight { get; private set; } = 480;
		public int VsyncNumerator => 60;
		public int VsyncDenominator => 1;
		public int BackgroundColor => 0;

		private int[] _vbuf = new int[640 * 480];
		public int[] GetVideoBuffer() => _vbuf;

		private readonly LibDolphin.FrameCallback _framecb;

		private unsafe void FrameCallback(IntPtr data, int width, int height, int pitch)
		{
			if (_vbuf.Length < width * height)
			{
				_vbuf = new int[width * height];
			}

			BufferWidth = width;
			BufferHeight = height;

			byte* src = (byte*)data;
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					int p = src[j * 4] << 16;
					p |= src[j * 4 + 1] << 8;
					p |= src[j * 4 + 2];
					_vbuf[width * i + j] = p;
				}
				src += pitch;
			}
		}
	}
}
