using System;
using System.Windows.Forms;

using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Nintendo.Dolphin;

namespace BizHawk.Client.EmuHawk
{
	public partial class DolphinConfig : Form
	{
		private readonly ISettingsAdapter _settable;
		private readonly Dolphin.DolphinSettings _s;
		private readonly Dolphin.DolphinSyncSettings _ss;

		public DolphinConfig(ISettingsAdapter settable)
		{
			_settable = settable;
			_s = _settable.GetSettings() as Dolphin.DolphinSettings;
			_ss = _settable.GetSyncSettings() as Dolphin.DolphinSyncSettings;

			InitializeComponent();
			Icon = Properties.Resources.DolphinIcon;
		}

		private void CancelBtn_Click(object sender, EventArgs e)
		{
			// Add confirmation of cancelling change
			DialogResult = DialogResult.Cancel;
			Close();
		}

		private void Button1_Click(object sender, EventArgs e)
		{
			_s.UseCompressedStates = UseCompressedStatesCB.Checked;
			_s.GPULagFrames = GPULagFramesCB.Checked;
			_s.DumpDTM = DumpDTMCB.Checked;
			_settable.PutCoreSettings(_s);

			_ss.ApplyPerGameSettings = ApplyPerGameSettingsCB.Checked;
			_settable.PutCoreSyncSettings(_ss);

			DialogResult = DialogResult.OK;
			Close();
		}

		private void DolphinConfig_Load(object sender, EventArgs e)
		{
			MainSettingsPropertyGrid.SelectedObject = _ss.MainSettings;
			WiiPadSettingsPropertyGrid.SelectedObject = _ss.WiiPadSettings;
			GFXSettingsPropertyGrid.SelectedObject = _ss.GFXSettings;
			SYSCONFSettingsPropertyGrid.SelectedObject = _ss.SYSCONFSettings;
			ApplyPerGameSettingsCB.Checked = _ss.ApplyPerGameSettings;
			UseCompressedStatesCB.Checked = _s.UseCompressedStates;
			GPULagFramesCB.Checked = _s.GPULagFrames;
			DumpDTMCB.Checked = _s.DumpDTM;
		}
	}
}
