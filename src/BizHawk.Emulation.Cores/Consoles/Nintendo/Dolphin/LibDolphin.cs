using System;
using System.Runtime.InteropServices;

using BizHawk.BizInvoke;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	public abstract class LibDolphin
	{
		private const CallingConvention cc = CallingConvention.Cdecl;

		[BizImport(cc, Compatibility = true)]
		public abstract int Dolphin_Main(int argc, string[] argv);

		[BizImport(cc)]
		public abstract void Dolphin_Shutdown();

		[BizImport(cc)]
		public abstract bool Dolphin_BootupSuccessful();

		[UnmanagedFunctionPointer(cc)]
		public delegate void FrameCallback(IntPtr data, int width, int height, int pitch);

		[BizImport(cc)]
		public abstract void Dolphin_SetFrameCallback(FrameCallback cb);

		[BizImport(cc)]
		public abstract void Dolphin_FrameStep();

		[UnmanagedFunctionPointer(cc)]
		public delegate void GCPadCallback(IntPtr padStatus, int controllerID);

		[BizImport(cc)]
		public abstract void Dolphin_SetGCPadCallback(GCPadCallback cb);

		[BizImport(cc)]
		public abstract void Dolphin_GetAudio(ref IntPtr data, ref int sz);

		[BizImport(cc)]
		public abstract IntPtr Dolphin_SaveState(ref int sz);

		[BizImport(cc)]
		public abstract int Dolphin_LoadState(byte[] buf, int sz);

		public enum MEMPTR_IDS
		{
			RAM = 0,
			EXRAM = 1,
			L1Cache = 2,
			FakeVMEM = 3,
		}

		[BizImport(cc)]
		public abstract bool Dolphin_GetMemPtr(MEMPTR_IDS which, ref IntPtr ptr, ref int sz);

		[BizImport(cc)]
		public abstract byte Dolphin_ReadU8(uint addr);

		[BizImport(cc)]
		public abstract ushort Dolphin_ReadU16(uint addr, bool bigEndian);

		[BizImport(cc)]
		public abstract uint Dolphin_ReadU32(uint addr, bool bigEndian);

		[BizImport(cc)]
		public abstract void Dolphin_ReadBulkU8(uint startAddr, int numAddrs, byte[] buf);

		[BizImport(cc)]
		public abstract void Dolphin_ReadBulkU16(uint startAddr, int numAddrs, ushort[] buf, bool bigEndian);

		[BizImport(cc)]
		public abstract void Dolphin_ReadBulkU32(uint startAddr, int numAddrs, uint[] buf, bool bigEndian);

		[BizImport(cc)]
		public abstract void Dolphin_WriteU8(uint addr, byte val);

		[BizImport(cc)]
		public abstract void Dolphin_WriteU16(uint addr, ushort val, bool bigEndian);

		[BizImport(cc)]
		public abstract void Dolphin_WriteU32(uint addr, uint val, bool bigEndian);
	}
}
