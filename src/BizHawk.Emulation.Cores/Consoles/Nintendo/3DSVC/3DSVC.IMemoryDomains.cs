using System;
using System.Collections.Generic;

using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.ThreeDSVC
{
	public partial class ThreeDSVC
	{
		private readonly List<MemoryDomain> _memoryDomains = new();

		private IMemoryDomains MemoryDomains { get; set; }

		private void CreateMemoryDomain(Lib3DSVC.MemoryAreas which, string name)
		{
			IntPtr data = IntPtr.Zero;
			int length = 0;

			if (!_core.VC_GetMemoryArea(which, ref data, ref length))
			{
				throw new Exception($"{nameof(Lib3DSVC.VC_GetMemoryArea)}() failed!");
			}

			// if length == 0, it's an empty block; (usually rambank on some carts); that's ok
			if (data != IntPtr.Zero && length > 0)
			{
				_memoryDomains.Add(new MemoryDomainIntPtr(name, MemoryDomain.Endian.Little, data, length, true, 1));
			}
		}

		private void InitMemoryDomains()
		{
			CreateMemoryDomain(Lib3DSVC.MemoryAreas.ROM, "ROM");
			CreateMemoryDomain(Lib3DSVC.MemoryAreas.WRAM, "WRAM");
			CreateMemoryDomain(Lib3DSVC.MemoryAreas.CartRAM, "CartRAM");
			CreateMemoryDomain(Lib3DSVC.MemoryAreas.VRAM, "VRAM");
			CreateMemoryDomain(Lib3DSVC.MemoryAreas.HRAM, "HRAM");
			CreateMemoryDomain(Lib3DSVC.MemoryAreas.MMIO, "MMIO");

			// also add a special memory domain for the system bus, where calls get sent directly to the core each time
			_memoryDomains.Add(new MemoryDomainDelegate("System Bus", 65536, MemoryDomain.Endian.Little,
				addr =>
				{
					if (addr is < 0 or > 0xFFFF) throw new ArgumentOutOfRangeException(paramName: nameof(addr), addr, message: "address out of range");
					return _core.VC_Peek((ushort)addr);
				},
				(addr, val) =>
				{
					if (addr is < 0 or > 0xFFFF) throw new ArgumentOutOfRangeException(paramName: nameof(addr), addr, message: "address out of range");
					_core.VC_Poke((ushort)addr, val);
				}, 1));

			MemoryDomains = new MemoryDomainList(_memoryDomains);
			_serviceProvider.Register(MemoryDomains);
		}
	}
}
