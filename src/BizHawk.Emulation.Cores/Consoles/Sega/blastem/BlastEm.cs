using System;
using System.IO;

using BizHawk.Common;
using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Properties;
using BizHawk.Emulation.Cores.Waterbox;

namespace BizHawk.Emulation.Cores.Consoles.Sega.BlastEm
{
	[PortedCore(CoreNames.BlastEm, "Michael Pavone", "c6ffbe21a169", "https://www.retrodev.com/repos/blastem")]
	public class BlastEm : WaterboxCore, IRegionable
	{
		private readonly LibBlastEm _core;

		[CoreConstructor(VSystemID.Raw.GEN, Priority = CorePriority.High)]
		public BlastEm(CoreComm comm, GameInfo game, byte[] rom, bool deterministic)
			: base(comm, new Configuration
			{
				MaxSamples = 2048,
				DefaultWidth = 320,
				DefaultHeight = 224,
				MaxWidth = 347,
				MaxHeight = 294 * 2,
				SystemId = VSystemID.Raw.GEN,
			})
		{

			_core = PreInit<LibBlastEm>(new WaterboxOptions
			{
				Filename = "blastem.wbx",
				SbrkHeapSizeKB = 32 * 1024,
				SealedHeapSizeKB = 32 * 1024,
				InvisibleHeapSizeKB = 32 * 1024,
				MmapHeapSizeKB = 32 * 1024,
				PlainHeapSizeKB = 32 * 1024,
				SkipCoreConsistencyCheck = comm.CorePreferences.HasFlag(CoreComm.CorePreferencesFlags.WaterboxCoreConsistencyCheck),
				SkipMemoryConsistencyCheck = comm.CorePreferences.HasFlag(CoreComm.CorePreferencesFlags.WaterboxMemoryConsistencyCheck),
			});

			var db = Util.DecompressGzipFile(new MemoryStream(Resources.BLASTEM_ROM_DB.Value));
			_exe.AddReadonlyFile(db, "rom.db");

			if (_core.Init(rom, rom.Length))
			{
				throw new InvalidOperationException("Core rejected the file!");
			}

			_exe.RemoveReadonlyFile("rom.db");

			using (_exe.EnterExit())
			{
				_exe.Seal();
			}
			//PostInit();
			ControllerDefinition = PicoDriveController;
			DeterministicEmulation = true;

			VsyncNumerator = 53693175;
			VsyncDenominator = 3420 * 262;
		}

		public static readonly ControllerDefinition PicoDriveController = new ControllerDefinition
		{
			Name = "PicoDrive Genesis Controller",
			BoolButtons =
			{
				"P1 Up", "P1 Down", "P1 Left", "P1 Right", "P1 A", "P1 B", "P1 C", "P1 Start", "P1 X", "P1 Y", "P1 Z", "P1 Mode",
				"P2 Up", "P2 Down", "P2 Left", "P2 Right", "P2 A", "P2 B", "P2 C", "P2 Start", "P2 X", "P2 Y", "P2 Z", "P2 Mode",
				"Power", "Reset"
			}
		};

		private static readonly string[] ButtonOrders =
		{
			"P1 Up", "P1 Down", "P1 Left", "P1 Right", "P1 B", "P1 C", "P1 A", "P1 Start", "P1 Z", "P1 Y", "P1 X", "P1 Mode",
			"P2 Up", "P2 Down", "P2 Left", "P2 Right", "P2 B", "P2 C", "P2 A", "P2 Start", "P2 Z", "P2 Y", "P2 X", "P2 Mode",
			"Power", "Reset"
		};

		protected override LibWaterboxCore.FrameInfo FrameAdvancePrep(IController controller, bool render, bool rendersound)
		{
			var b = 0;
			var v = 1;
			foreach (var s in ButtonOrders)
			{
				if (controller.IsPressed(s))
					b |= v;
				v <<= 1;
			}

			return new LibBlastEm.FrameInfo
			{
				Time = 0,
				P1Keys = b & 0xFFF,
				P2Keys = (b >> 12) & 0xFFF,
				Reset = (b >> 24) & 3,
				Overscan = 0,
			};
		}

		public DisplayType Region => DisplayType.NTSC;
	}
}
