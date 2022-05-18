namespace BizHawk.Client.EmuHawk
{
	partial class DolphinConfig
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            this.DolphinConfigTabControl = new System.Windows.Forms.TabControl();
            this.MainSettingsTabPage = new System.Windows.Forms.TabPage();
            this.MainSettingsPropertyGrid = new System.Windows.Forms.PropertyGrid();
            this.WiiPadSettingsTabPage = new System.Windows.Forms.TabPage();
            this.WiiPadSettingsPropertyGrid = new System.Windows.Forms.PropertyGrid();
            this.GFXSettingsTabPage = new System.Windows.Forms.TabPage();
            this.GFXSettingsPropertyGrid = new System.Windows.Forms.PropertyGrid();
            this.SYSCONFSettingsTabPage = new System.Windows.Forms.TabPage();
            this.SYSCONFSettingsPropertyGrid = new System.Windows.Forms.PropertyGrid();
            this.GeneralSettingsTabPage = new System.Windows.Forms.TabPage();
            this.SaveButton = new System.Windows.Forms.Button();
            this.CancelBT = new System.Windows.Forms.Button();
            this.ApplyPerGameSettingsCB = new System.Windows.Forms.CheckBox();
            this.DolphinConfigTabControl.SuspendLayout();
            this.MainSettingsTabPage.SuspendLayout();
            this.WiiPadSettingsTabPage.SuspendLayout();
            this.GFXSettingsTabPage.SuspendLayout();
            this.SYSCONFSettingsTabPage.SuspendLayout();
            this.SuspendLayout();
            // 
            // DolphinConfigTabControl
            // 
            this.DolphinConfigTabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.DolphinConfigTabControl.Controls.Add(this.MainSettingsTabPage);
            this.DolphinConfigTabControl.Controls.Add(this.WiiPadSettingsTabPage);
            this.DolphinConfigTabControl.Controls.Add(this.GFXSettingsTabPage);
            this.DolphinConfigTabControl.Controls.Add(this.SYSCONFSettingsTabPage);
            this.DolphinConfigTabControl.Location = new System.Drawing.Point(-2, -2);
            this.DolphinConfigTabControl.Name = "DolphinConfigTabControl";
            this.DolphinConfigTabControl.SelectedIndex = 0;
            this.DolphinConfigTabControl.Size = new System.Drawing.Size(580, 369);
            this.DolphinConfigTabControl.TabIndex = 0;
            // 
            // MainSettingsTabPage
            // 
            this.MainSettingsTabPage.Controls.Add(this.MainSettingsPropertyGrid);
            this.MainSettingsTabPage.Location = new System.Drawing.Point(4, 22);
            this.MainSettingsTabPage.Name = "MainSettingsTabPage";
            this.MainSettingsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.MainSettingsTabPage.Size = new System.Drawing.Size(572, 343);
            this.MainSettingsTabPage.TabIndex = 9;
            this.MainSettingsTabPage.Text = "Main";
            this.MainSettingsTabPage.UseVisualStyleBackColor = true;
            // 
            // MainSettingsPropertyGrid
            // 
            this.MainSettingsPropertyGrid.Location = new System.Drawing.Point(3, 3);
            this.MainSettingsPropertyGrid.Name = "MainSettingsPropertyGrid";
            this.MainSettingsPropertyGrid.PropertySort = System.Windows.Forms.PropertySort.Categorized;
            this.MainSettingsPropertyGrid.Size = new System.Drawing.Size(566, 337);
            this.MainSettingsPropertyGrid.TabIndex = 0;
            this.MainSettingsPropertyGrid.ToolbarVisible = false;
            // 
            // WiiPadSettingsTabPage
            // 
            this.WiiPadSettingsTabPage.Controls.Add(this.WiiPadSettingsPropertyGrid);
            this.WiiPadSettingsTabPage.Location = new System.Drawing.Point(4, 22);
            this.WiiPadSettingsTabPage.Name = "WiiPadSettingsTabPage";
            this.WiiPadSettingsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.WiiPadSettingsTabPage.Size = new System.Drawing.Size(572, 343);
            this.WiiPadSettingsTabPage.TabIndex = 10;
            this.WiiPadSettingsTabPage.Text = "Wiimotes";
            this.WiiPadSettingsTabPage.UseVisualStyleBackColor = true;
            // 
            // WiiPadSettingsPropertyGrid
            // 
            this.WiiPadSettingsPropertyGrid.Location = new System.Drawing.Point(3, 3);
            this.WiiPadSettingsPropertyGrid.Name = "WiiPadSettingsPropertyGrid";
            this.WiiPadSettingsPropertyGrid.PropertySort = System.Windows.Forms.PropertySort.Categorized;
            this.WiiPadSettingsPropertyGrid.Size = new System.Drawing.Size(566, 337);
            this.WiiPadSettingsPropertyGrid.TabIndex = 1;
            this.WiiPadSettingsPropertyGrid.ToolbarVisible = false;
            // 
            // GFXSettingsTabPage
            // 
            this.GFXSettingsTabPage.Controls.Add(this.GFXSettingsPropertyGrid);
            this.GFXSettingsTabPage.Location = new System.Drawing.Point(4, 22);
            this.GFXSettingsTabPage.Name = "GFXSettingsTabPage";
            this.GFXSettingsTabPage.Size = new System.Drawing.Size(572, 343);
            this.GFXSettingsTabPage.TabIndex = 11;
            this.GFXSettingsTabPage.Text = "GFX";
            this.GFXSettingsTabPage.UseVisualStyleBackColor = true;
            // 
            // GFXSettingsPropertyGrid
            // 
            this.GFXSettingsPropertyGrid.Location = new System.Drawing.Point(3, 3);
            this.GFXSettingsPropertyGrid.Name = "GFXSettingsPropertyGrid";
            this.GFXSettingsPropertyGrid.PropertySort = System.Windows.Forms.PropertySort.Categorized;
            this.GFXSettingsPropertyGrid.Size = new System.Drawing.Size(566, 337);
            this.GFXSettingsPropertyGrid.TabIndex = 2;
            this.GFXSettingsPropertyGrid.ToolbarVisible = false;
            // 
            // SYSCONFSettingsTabPage
            // 
            this.SYSCONFSettingsTabPage.Controls.Add(this.SYSCONFSettingsPropertyGrid);
            this.SYSCONFSettingsTabPage.Location = new System.Drawing.Point(4, 22);
            this.SYSCONFSettingsTabPage.Name = "SYSCONFSettingsTabPage";
            this.SYSCONFSettingsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.SYSCONFSettingsTabPage.Size = new System.Drawing.Size(572, 343);
            this.SYSCONFSettingsTabPage.TabIndex = 12;
            this.SYSCONFSettingsTabPage.Text = "SYSCONF";
            this.SYSCONFSettingsTabPage.UseVisualStyleBackColor = true;
            // 
            // SYSCONFSettingsPropertyGrid
            // 
            this.SYSCONFSettingsPropertyGrid.Location = new System.Drawing.Point(3, 3);
            this.SYSCONFSettingsPropertyGrid.Name = "SYSCONFSettingsPropertyGrid";
            this.SYSCONFSettingsPropertyGrid.PropertySort = System.Windows.Forms.PropertySort.Categorized;
            this.SYSCONFSettingsPropertyGrid.Size = new System.Drawing.Size(566, 337);
            this.SYSCONFSettingsPropertyGrid.TabIndex = 3;
            this.SYSCONFSettingsPropertyGrid.ToolbarVisible = false;
            // 
            // GeneralSettingsTabPage
            // 
            this.GeneralSettingsTabPage.Location = new System.Drawing.Point(0, 0);
            this.GeneralSettingsTabPage.Name = "GeneralSettingsTabPage";
            this.GeneralSettingsTabPage.Size = new System.Drawing.Size(200, 100);
            this.GeneralSettingsTabPage.TabIndex = 0;
            // 
            // SaveButton
            // 
            this.SaveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.SaveButton.Location = new System.Drawing.Point(409, 373);
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.Size = new System.Drawing.Size(75, 23);
            this.SaveButton.TabIndex = 100;
            this.SaveButton.Text = "Save";
            this.SaveButton.UseVisualStyleBackColor = true;
            this.SaveButton.Click += new System.EventHandler(this.Button1_Click);
            // 
            // CancelBT
            // 
            this.CancelBT.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.CancelBT.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.CancelBT.Location = new System.Drawing.Point(490, 373);
            this.CancelBT.Name = "CancelBT";
            this.CancelBT.Size = new System.Drawing.Size(75, 23);
            this.CancelBT.TabIndex = 105;
            this.CancelBT.Text = "Cancel";
            this.CancelBT.UseVisualStyleBackColor = true;
            this.CancelBT.Click += new System.EventHandler(this.CancelBtn_Click);
            // 
            // ApplyPerGameSettingsCB
            // 
            this.ApplyPerGameSettingsCB.AutoSize = true;
            this.ApplyPerGameSettingsCB.Location = new System.Drawing.Point(12, 373);
            this.ApplyPerGameSettingsCB.Name = "ApplyPerGameSettingsCB";
            this.ApplyPerGameSettingsCB.Size = new System.Drawing.Size(143, 17);
            this.ApplyPerGameSettingsCB.TabIndex = 106;
            this.ApplyPerGameSettingsCB.Text = "Apply Per Game Settings";
            this.ApplyPerGameSettingsCB.UseVisualStyleBackColor = true;
            // 
            // DolphinConfig
            // 
            this.AcceptButton = this.SaveButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.CancelBT;
            this.ClientSize = new System.Drawing.Size(577, 401);
            this.Controls.Add(this.ApplyPerGameSettingsCB);
            this.Controls.Add(this.CancelBT);
            this.Controls.Add(this.SaveButton);
            this.Controls.Add(this.DolphinConfigTabControl);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "DolphinConfig";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Dolphin Settings";
            this.Load += new System.EventHandler(this.DolphinConfig_Load);
            this.DolphinConfigTabControl.ResumeLayout(false);
            this.MainSettingsTabPage.ResumeLayout(false);
            this.WiiPadSettingsTabPage.ResumeLayout(false);
            this.GFXSettingsTabPage.ResumeLayout(false);
            this.SYSCONFSettingsTabPage.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TabControl DolphinConfigTabControl;
		private System.Windows.Forms.TabPage GeneralSettingsTabPage;
		private System.Windows.Forms.TabPage MainSettingsTabPage;
		private System.Windows.Forms.TabPage WiiPadSettingsTabPage;
		private System.Windows.Forms.TabPage GFXSettingsTabPage;
		private System.Windows.Forms.TabPage SYSCONFSettingsTabPage;
		private System.Windows.Forms.PropertyGrid MainSettingsPropertyGrid;
		private System.Windows.Forms.PropertyGrid WiiPadSettingsPropertyGrid;
		private System.Windows.Forms.PropertyGrid GFXSettingsPropertyGrid;
		private System.Windows.Forms.PropertyGrid SYSCONFSettingsPropertyGrid;
		private System.Windows.Forms.Button SaveButton;
		private System.Windows.Forms.Button CancelBT;
		private System.Windows.Forms.CheckBox ApplyPerGameSettingsCB;
	}
}