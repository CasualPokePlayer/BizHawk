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

		public enum WiimoteButtons : ushort
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

		public enum WiimoteInputReq : int
		{
			CORE_BUTTONS = 0,
			CORE_ACCEL = 1,
			CORE_IR_BASIC = 2,
			CORE_IR_EXTENDED = 3,
			CORE_IR_FULL = 4,
			END_INPUT = 0xFF,
		}

		public enum CoreButtons : ushort
		{
			Left = 0x0001,
			Right = 0x0002,
			Down = 0x0004,
			Up = 0x0008,
			Plus = 0x0010,
			// 3 bits not relevant here
			Two = 0x0100,
			One = 0x0200,
			B = 0x0400,
			A = 0x0800,
			Minus = 0x1000,
			// 2 bits not relevant here
			Home = 0x8000,
		}

		public const CoreButtons CoreButtonsMask =
			CoreButtons.Left | CoreButtons.Right | CoreButtons.Down | CoreButtons.Up |
			CoreButtons.Plus | CoreButtons.Two | CoreButtons.One | CoreButtons.B |
			CoreButtons.A | CoreButtons.Minus | CoreButtons.Home;

		[StructLayout(LayoutKind.Sequential)]
		public struct CoreAccel
		{
			public ushort X;
			public ushort Y;
			public ushort Z;
		}

		public enum CoreIRBasicHi : byte
		{
			X2 = 0x03,
			Y2 = 0x0C,
			X1 = 0x30,
			Y1 = 0xC0,
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct CoreIRBasic
		{
			public byte X1;
			public byte Y1;
			public CoreIRBasicHi Hi;
			public byte X2;
			public byte Y2;
		}

		public enum CoreIRExtendedSzHi : byte
		{
			Sz = 0x0F,
			X = 0x30,
			Y = 0xC0,
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct CoreIRExtended
		{
			public byte X;
			public byte Y;
			public CoreIRExtendedSzHi SzHi;
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct CoreIRFull
		{
			// can't inherit a struct in a struct, and a class is managed, so...
			public byte X;
			public byte Y;
			public CoreIRExtendedSzHi SzHi;
			// note: min/max have 7 bits of granularity
			public byte XMin;
			public byte YMin;
			public byte XMax;
			public byte YMax;
			public byte ZeroPadding;
			public byte Intensity;
		}

		[UnmanagedFunctionPointer(cc)]
		public delegate void WiiPadCallback(IntPtr p, WiimoteInputReq which, int controllerID);

		[BizImport(cc)]
		public abstract void Dolphin_SetWiiPadCallback(WiiPadCallback cb);

		[BizImport(cc)]
		public abstract IntPtr Dolphin_GetAudio(ref int sz);

		[BizImport(cc)]
		public abstract int Dolphin_StateSize(bool compressed);

		[BizImport(cc)]
		public abstract void Dolphin_SaveState(byte[] buf, int sz, bool compressed);

		[BizImport(cc)]
		public abstract void Dolphin_LoadState(byte[] buf, int sz, bool compressed);

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

		[BizImport(cc)]
		public abstract int Dolphin_GetVSyncNumerator();

		[BizImport(cc)]
		public abstract int Dolphin_GetVSyncDenominator();

		[UnmanagedFunctionPointer(cc)]
		public delegate bool MPlusConfigCallback(int n);

		[UnmanagedFunctionPointer(cc)]
		public delegate Dolphin.DolphinWiiPadSettings.WiimoteExtensions ExtensionConfigCallback(int n);

		[BizImport(cc)]
		public abstract void Dolphin_SetConfigCallbacks(MPlusConfigCallback mplus, ExtensionConfigCallback extension);

		[BizImport(cc)]
		public abstract ulong Dolphin_GetTicks();
	}
}
