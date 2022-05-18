using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;

using BizHawk.Common;
using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Nintendo.Dolphin;

namespace BizHawk.Emulation.Cores
{
	[Schema(VSystemID.Raw.GC)]
	// ReSharper disable once UnusedMember.Global
	public class GameCubeSchema : IVirtualPadSchema
	{
		public IEnumerable<PadSchema> GetPadSchemas(IEmulator core, Action<string> showMessageBox)
		{
			if (core is Dolphin dolphin)
			{
				var ss = dolphin.GetSyncSettings();
				var gcSlots = new[]
				{
					ss.MainSettings.SIDevice0,
					ss.MainSettings.SIDevice1,
					ss.MainSettings.SIDevice2,
					ss.MainSettings.SIDevice3,
				};
				for (int i = 0; i < 4; i++)
				{
					if (gcSlots[i] is Dolphin.DolphinMainSettings.SIDevices.Controller)
					{
						yield return GameCubeController(i + 1);
					}
				}
			}
		}

		private static PadSchema GameCubeController(int controller)
		{
			var axisSpec = new AxisSpec(0.RangeTo(255), 128);
			return new PadSchema
			{
				Size = new Size(500, 290),
				DisplayName = $"GameCube Controller Player {controller}",
				Buttons = new PadSchemaControl[]
				{
					ButtonSchema.Up(32, 50, controller),
					ButtonSchema.Down(32, 71, controller),
					ButtonSchema.Left(11, 62, controller),
					ButtonSchema.Right(53, 62, controller),
					new ButtonSchema(3, 32, controller, "L"),
					new ButtonSchema(191, 32, controller, "R"),
					new ButtonSchema(148, 62, controller, "B"),
					new ButtonSchema(169, 50, controller, "Y"),
					new ButtonSchema(190, 62, controller, "X"),
					new ButtonSchema(169, 71, controller, "A"),
					new ButtonSchema(112, 62, controller, "Start", "S"),
					new ButtonSchema(90, 62, controller, "Z"),
					new AnalogSchema(3, 120, $"P{controller} Main Stick X")
					{
						Spec = axisSpec,
						SecondarySpec = axisSpec,
					},
					new AnalogSchema(260, 120, $"P{controller} C Stick X")
					{
						Spec = axisSpec,
						SecondarySpec = axisSpec,
					},
					new SingleAxisSchema(240, 15, controller, "Analog L")
					{
						TargetSize = new Size(226, 40),
						MinValue = axisSpec.Min,
						MaxValue = axisSpec.Max,
					},
					new SingleAxisSchema(240, 72, controller, "Analog R")
					{
						TargetSize = new Size(226, 40),
						MinValue = axisSpec.Min,
						MaxValue = axisSpec.Max,
					},
				}
			};
		}
	}
}
