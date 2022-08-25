using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Components.LR35902;

namespace BizHawk.Emulation.Cores.Nintendo.ThreeDSVC
{
	public partial class ThreeDSVC
	{
		private ITraceable Tracer { get; }
		private readonly Lib3DSVC.TraceCallback _traceCallback;

		private void MakeTrace()
		{
			int[] regs = new int[6];
			_core.VC_GetRegs(regs);

			Tracer.Put(new(
				disassembly: LR35902.Disassemble(
					(ushort)regs[0],
					addr => _core.VC_Peek(addr),
					true,
					out _).PadRight(36),
				registerInfo:
					$"AF:{regs[2]:X4} BC:{regs[3]:X4} DE:{regs[4]:X4} HL:{regs[5]:X4} " +
					$"SP:{regs[1]:X4} LY:{_core.VC_GetIOReg(0x44):X2} CY:{TotalExecutedCycles}"
				));
		}
	}
}
