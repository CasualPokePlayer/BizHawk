using System;
using System.Collections.Generic;

using BizHawk.Common;
using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	public partial class Dolphin
	{
		private readonly List<MemoryDomain> _memoryDomains = new();

		private MemoryDomainList MemoryDomains { get; set; }

		private void CreateMemoryDomain(LibDolphin.MEMPTR_IDS which, string name)
		{
			IntPtr data = IntPtr.Zero;
			int length = 0;

			if (!_core.Dolphin_GetMemPtr(which, ref data, ref length))
			{
				throw new Exception($"{nameof(_core.Dolphin_GetMemPtr)}() failed!");
			}

			if (data != IntPtr.Zero && length > 0)
			{
				_memoryDomains.Add(new MemoryDomainIntPtr(name, MemoryDomain.Endian.Big, data, length, true, 4));
			}
		}

		private void InitMemoryDomains()
		{
			CreateMemoryDomain(LibDolphin.MEMPTR_IDS.RAM, "RAM");
			CreateMemoryDomain(LibDolphin.MEMPTR_IDS.EXRAM, "ExRAM");
			CreateMemoryDomain(LibDolphin.MEMPTR_IDS.L1Cache, "L1 Cache");
			CreateMemoryDomain(LibDolphin.MEMPTR_IDS.FakeVMEM, "Fake VMEM");

			_memoryDomains.Add(new DolphinMMU(_core));

			MemoryDomains = new(_memoryDomains);
			_serviceProvider.Register<IMemoryDomains>(MemoryDomains);
		}

		private class DolphinMMU : MemoryDomain
		{
			private readonly LibDolphin _core;

			public DolphinMMU(LibDolphin core)
			{
				Name = "System Bus";
				Size = 1L << 32;
				WordSize = 4;
				EndianType = Endian.Big;
				Writable = true;
				_core = core;
			}

			public override byte PeekByte(long addr)
			{
				return _core.Dolphin_ReadU8((uint)addr);
			}

			public override ushort PeekUshort(long addr, bool bigEndian)
			{
				return _core.Dolphin_ReadU16((uint)addr, bigEndian);
			}

			public override uint PeekUint(long addr, bool bigEndian)
			{
				return _core.Dolphin_ReadU32((uint)addr, bigEndian);
			}

			public override void PokeByte(long addr, byte val)
			{
				_core.Dolphin_WriteU8((uint)addr, val);
			}

			public override void PokeUshort(long addr, ushort val, bool bigEndian)
			{
				_core.Dolphin_WriteU16((uint)addr, val, bigEndian);
			}

			public override void PokeUint(long addr, uint val, bool bigEndian)
			{
				_core.Dolphin_WriteU32((uint)addr, val, bigEndian);
			}

			public override void BulkPeekByte(Range<long> addresses, byte[] values)
			{
				if (addresses == null || values == null)
				{
					throw new ArgumentException();
				}

				if ((long)addresses.Count() != values.Length)
				{
					throw new InvalidOperationException("Invalid length of values array");
				}

				_core.Dolphin_ReadBulkU8((uint)addresses.Start, values.Length, values);
			}

			public override void BulkPeekUshort(Range<long> addresses, bool bigEndian, ushort[] values)
			{
				if (addresses == null || values == null)
				{
					throw new ArgumentException();
				}
				var start = addresses.Start;
				var end = addresses.EndInclusive + 1;

				if ((start & 1) != 0 || (end & 1) != 0)
				{
					throw new InvalidOperationException("The API contract doesn't define what to do for unaligned reads and writes!");
				}

				if (values.LongLength * 2 != end - start)
				{
					// a longer array could be valid, but nothing needs that so don't support it for now
					throw new InvalidOperationException("Invalid length of values array");
				}

				_core.Dolphin_ReadBulkU16((uint)start, values.Length, values, bigEndian);
			}

			public override void BulkPeekUint(Range<long> addresses, bool bigEndian, uint[] values)
			{
				if (addresses == null || values == null)
				{
					throw new ArgumentException();
				}
				var start = addresses.Start;
				var end = addresses.EndInclusive + 1;

				if ((start & 3) != 0 || (end & 3) != 0)
				{
					throw new InvalidOperationException("The API contract doesn't define what to do for unaligned reads and writes!");
				}

				if (values.LongLength * 4 != end - start)
				{
					// a longer array could be valid, but nothing needs that so don't support it for now
					throw new InvalidOperationException("Invalid length of values array");
				}

				_core.Dolphin_ReadBulkU32((uint)start, values.Length, values, bigEndian);
			}
		}
	}
}
