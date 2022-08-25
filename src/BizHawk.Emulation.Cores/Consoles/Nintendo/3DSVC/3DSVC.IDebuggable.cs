using System;
using System.Collections.Generic;

using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.ThreeDSVC
{
	public partial class ThreeDSVC : IDebuggable
	{
		public IDictionary<string, RegisterValue> GetCpuFlagsAndRegisters()
		{
			int[] data = new int[6];
			_core.VC_GetRegs(data);

			return new Dictionary<string, RegisterValue>
			{
				["PC"] = (ushort)(data[0] & 0xFFFF),
				["SP"] = (ushort)(data[1] & 0xFFFF),
				["AF"] = (ushort)(data[2] & 0xFFFF),
				["BC"] = (ushort)(data[3] & 0xFFFF),
				["DE"] = (ushort)(data[4] & 0xFFFF),
				["HL"] = (ushort)(data[5] & 0xFFFF),
			};
		}

		public void SetCpuRegister(string register, int value)
			=> _core.VC_SetReg((Lib3DSVC.CpuRegisters)Enum.Parse(typeof(Lib3DSVC.CpuRegisters), register, true), value);

		public bool CanStep(StepType type) => false;

		[FeatureNotImplemented]
		public void Step(StepType type) => throw new NotImplementedException();

		public long TotalExecutedCycles
			=> _core.VC_CycleCount();

		private readonly MemoryCallbackSystem _memoryCallbacks = new(new[] { "System Bus" });

		public IMemoryCallbackSystem MemoryCallbacks => _memoryCallbacks;

		private Lib3DSVC.MemoryCallback _readCallback;
		private Lib3DSVC.MemoryCallback _writeCallback;
		private Lib3DSVC.MemoryCallback _execCallback;

		private void InitMemoryCallbacks()
		{
			Lib3DSVC.MemoryCallback CreateCallback(MemoryCallbackFlags flags, Func<bool> getHasCBOfType)
			{
				var rawFlags = (uint)flags;
				return (addr, val) =>
				{
					if (getHasCBOfType())
					{
						MemoryCallbacks.CallMemoryCallbacks(addr, val, rawFlags, "System Bus");
					}
				};
			}

			_readCallback = CreateCallback(MemoryCallbackFlags.AccessRead, () => MemoryCallbacks.HasReads);
			_writeCallback = CreateCallback(MemoryCallbackFlags.AccessWrite, () => MemoryCallbacks.HasWrites);
			_execCallback = CreateCallback(MemoryCallbackFlags.AccessExecute, () => MemoryCallbacks.HasExecutes);

			_memoryCallbacks.ActiveChanged += SetMemoryCallbacks;
		}

		private void SetMemoryCallbacks()
		{
			_core.VC_SetMemoryCallback(Lib3DSVC.MemoryCallbacks.READ, MemoryCallbacks.HasReads ? _readCallback : null);
			_core.VC_SetMemoryCallback(Lib3DSVC.MemoryCallbacks.WRITE, MemoryCallbacks.HasWrites ? _writeCallback : null);
			_core.VC_SetMemoryCallback(Lib3DSVC.MemoryCallbacks.EXECUTE, MemoryCallbacks.HasExecutes ? _execCallback : null);
		}
	}
}
