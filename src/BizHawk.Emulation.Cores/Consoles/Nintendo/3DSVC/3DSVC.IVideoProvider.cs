using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.ThreeDSVC
{
	public partial class ThreeDSVC : IVideoProvider
	{
		private readonly int[] VideoBuffer = new int[160 * 144];

		public int[] GetVideoBuffer()
			=> VideoBuffer;

		public int VirtualWidth => 160;

		public int VirtualHeight => 144;

		public int BufferWidth => 160;

		public int BufferHeight => 144;

		public int BackgroundColor => 0;

		public int VsyncNumerator => 262144;

		public int VsyncDenominator => 4389;
	}
}
