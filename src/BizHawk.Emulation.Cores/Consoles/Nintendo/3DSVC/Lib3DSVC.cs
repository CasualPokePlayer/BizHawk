using System;
using System.Runtime.InteropServices;

using BizHawk.BizInvoke;
using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.ThreeDSVC
{
	public abstract class Lib3DSVC
	{
		private const CallingConvention cc = CallingConvention.Cdecl;

		[Flags]
		public enum Buttons : byte
		{
			A = 0x01,
			B = 0x02,
			SELECT = 0x04,
			START = 0x08,
			RIGHT = 0x10,
			LEFT = 0x20,
			UP = 0x40,
			DOWN = 0x80,
		}

		[BizImport(cc)]
		public abstract void VC_Init(byte[] romdata, int romlength);

		[BizImport(cc)]
		public abstract void VC_Deinit();

		[BizImport(cc)]
		public abstract bool VC_IsCGB();

		[BizImport(cc)]
		public abstract void VC_Reset();

		[BizImport(cc)]
		public abstract void VC_RunFrame(Buttons buttons, int[] videobuf, short[] soundbuf, ref int nsamps);

		[BizImport(cc)]
		public abstract int VC_SramLength();

		[BizImport(cc)]
		public abstract int VC_SramDirty();

		[BizImport(cc)]
		public abstract void VC_SaveSram(byte[] dst);

		[BizImport(cc)]
		public abstract void VC_LoadSram(byte[] src);

		[BizImport(cc)]
		public abstract int VC_StateLength();

		[BizImport(cc)]
		public abstract bool VC_SaveStateBinary(byte[] src, int len);

		[BizImport(cc)]
		public abstract bool VC_LoadStateBinary(byte[] src, int len);

		[BizImport(cc)]
		public abstract void VC_SaveStateText(ref TextStateFPtrs ff);

		[BizImport(cc)]
		public abstract void VC_LoadStateText(ref TextStateFPtrs ff);

		public enum MemoryAreas : int
		{
			ROM,
			WRAM,
			VRAM,
			CartRAM,
			OAM,
			HRAM,
			MMIO,
			BGPAL,
			OBJPAL,
		}

		[BizImport(cc)]
		public abstract bool VC_GetMemoryArea(MemoryAreas which, ref IntPtr ptr, ref int len);

		[BizImport(cc)]
		public abstract byte VC_GetIOReg(byte index);

		[BizImport(cc)]
		public abstract byte VC_Peek(ushort addr);

		[BizImport(cc)]
		public abstract void VC_Poke(ushort addr, byte val);

		public enum CpuRegisters : int
		{
			PC,
			SP,
			AF,
			BC,
			DE,
			HL,
			A,
			F,
			B,
			C,
			D,
			E,
			H,
			L,
		}

		[BizImport(cc)]
		public abstract void VC_GetRegs(int[] dst);

		[BizImport(cc)]
		public abstract void VC_SetReg(CpuRegisters which, int val);

		public enum MemoryCallbacks : int
		{
			READ,
			WRITE,
			EXECUTE,
		}

		[UnmanagedFunctionPointer(cc)]
		public delegate void MemoryCallback(ushort addr, byte val);

		[BizImport(cc)]
		public abstract void VC_SetMemoryCallback(MemoryCallbacks which, MemoryCallback callback);

		[UnmanagedFunctionPointer(cc)]
		public delegate void TraceCallback();

		[BizImport(cc)]
		public abstract void VC_SetTraceCallback(TraceCallback callback);

		[BizImport(cc)]
		public abstract long VC_CycleCount();
	}
}
