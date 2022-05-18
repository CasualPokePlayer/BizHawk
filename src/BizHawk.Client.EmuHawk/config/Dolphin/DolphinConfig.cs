using System;
using System.Windows.Forms;

using BizHawk.Emulation.Cores.Nintendo.Dolphin;

namespace BizHawk.Client.EmuHawk
{
	public partial class DolphinConfig : Form
	{
		private readonly IMainFormForConfig _mainForm;
		private readonly Dolphin.DolphinSyncSettings _ss;

		public DolphinConfig(
			IMainFormForConfig mainForm,
			Dolphin.DolphinSyncSettings ss)
		{
			_mainForm = mainForm;
			_ss = ss;

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
			_ss.ApplyPerGameSettings = ApplyPerGameSettingsCB.Checked;
			_mainForm.PutCoreSyncSettings(_ss);
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
		}
	}
}
