using System;

using BizHawk.BizInvoke;
using BizHawk.Common;
using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Consoles.Nintendo.Gameboy;

namespace BizHawk.Emulation.Cores.Nintendo.ThreeDSVC
{
	[PortedCore(CoreNames.ThreeDSVC, "Nintendo", singleInstance: true)]
	[ServiceNotApplicable(new[] { typeof(IDriveLight) })]
	public partial class ThreeDSVC : IGameboyCommon, IInputPollable
	{
		private static readonly Lib3DSVC _core;

		static ThreeDSVC()
		{
			var resolver = new DynamicLibraryImportResolver("lib3dsvc.dll", hasLimitedLifetime: false);
			_core = BizInvoker.GetInvoker<Lib3DSVC>(resolver, CallingConventionAdapters.Native);
		}

		private readonly BasicServiceProvider _serviceProvider;

		private readonly Gameboy.GBDisassembler _disassembler = new() { UseRGBDSSyntax = true };

		public bool IsCgb { get; set; }

		private static ThreeDSVC CurrentCore;

		[CoreConstructor(VSystemID.Raw.GB)]
		[CoreConstructor(VSystemID.Raw.GBC)]
		public ThreeDSVC(byte[] file)
		{
			CurrentCore?.Dispose();
			CurrentCore = this;

			_serviceProvider = new BasicServiceProvider(this);

			ControllerDefinition = Gameboy.Gameboy.CreateControllerDefinition(false, false, false, false);

			_core.VC_Init(file, file.Length);

			_stateBuf = new byte[_core.VC_StateLength()];

			IsCgb = _core.VC_IsCGB();

			InitMemoryDomains();
			InitMemoryCallbacks();

			_serviceProvider.Register<IDisassemblable>(_disassembler);

			const string TRACE_HEADER = "SM83: PC, opcode, registers (AF, BC, DE, HL, SP, LY, CY)";
			Tracer = new TraceBuffer(TRACE_HEADER);
			_serviceProvider.Register(Tracer);
			_traceCallback = MakeTrace;

			ResetCounters();
		}

		public int LagCount { get; set; }

		public bool IsLagFrame { get; set; }

		[FeatureNotImplemented]
		public IInputCallbackSystem InputCallbacks => throw new NotImplementedException();

		public bool IsCGBMode()
			=> IsCgb;

		public bool IsCGBDMGMode()
			=> false;

		public IGPUMemoryAreas LockGPU()
		{
			var _vram = IntPtr.Zero;
			var _bgpal = IntPtr.Zero;
			var _sppal = IntPtr.Zero;
			var _oam = IntPtr.Zero;
			int unused = 0;
			if (!_core.VC_GetMemoryArea(Lib3DSVC.MemoryAreas.VRAM, ref _vram, ref unused)
				|| !_core.VC_GetMemoryArea(Lib3DSVC.MemoryAreas.BGPAL, ref _bgpal, ref unused)
				|| !_core.VC_GetMemoryArea(Lib3DSVC.MemoryAreas.OBJPAL, ref _sppal, ref unused)
				|| !_core.VC_GetMemoryArea(Lib3DSVC.MemoryAreas.OAM, ref _oam, ref unused))
			{
				throw new InvalidOperationException($"Unexpected error in {nameof(_core.VC_GetMemoryArea)}()");
			}

			return new GPUMemoryAreas()
			{
				Vram = _vram,
				Oam = _oam,
				Sppal = _sppal,
				Bgpal = _bgpal,
			};
		}

		private class GPUMemoryAreas : IGPUMemoryAreas
		{
			public IntPtr Vram { get; init; }

			public IntPtr Oam { get; init; }

			public IntPtr Sppal { get; init; }

			public IntPtr Bgpal { get; init; }

			public void Dispose() { }
		}

		private ScanlineCallback _scanlineCallback;

		public void SetScanlineCallback(ScanlineCallback callback, int line)
		{
			if (line == -1)
			{
				_scanlineCallback = callback;
			}
			else if (line == -2)
			{
				callback(_core.VC_GetIOReg(0x40));
			}
			else
			{
				// not supported currently, so...
				_scanlineCallback = callback;
			}
		}

		public void SetPrinterCallback(PrinterCallback callback)
		{

		}
	}
}
