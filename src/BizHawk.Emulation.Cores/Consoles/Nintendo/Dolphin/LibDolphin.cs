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

		public enum PadButtons : ushort
		{
			Left = 0x0001,
			Right = 0x0002,
			Down = 0x0004,
			Up = 0x0008,
			Z = 0x0010,
			R = 0x0020,
			L = 0x0040,
			A = 0x0100,
			B = 0x0200,
			X = 0x0400,
			Y = 0x0800,
			Start = 0x1000,
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct GCPadStatus
		{
			public PadButtons Buttons;
			public byte StickX;
			public byte StickY;
			public byte SubstickX;
			public byte SubstickY;
			public byte TriggerLeft;
			public byte TriggerRight;
			public byte AnalogA;
			public byte AnalogB;
			public bool IsConnected;
		}

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
