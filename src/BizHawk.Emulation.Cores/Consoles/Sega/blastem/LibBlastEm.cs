using BizHawk.BizInvoke;
using BizHawk.Emulation.Cores.Waterbox;
using System;
using System.Runtime.InteropServices;

namespace BizHawk.Emulation.Cores.Consoles.Sega.BlastEm
{
	public abstract class LibBlastEm : LibWaterboxCore
	{
		[StructLayout(LayoutKind.Sequential)]
		public new class FrameInfo : LibWaterboxCore.FrameInfo
		{
			public long Time;
			public int P1Keys;
			public int P2Keys;
			public int Reset;
			public int Overscan;
		}

		[BizImport(CC)]
		public abstract bool Init(byte[] rom, int sz);
	}
}
