namespace ReactionTimeTester
{
    partial class Form_Config
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
            this._lblPortName = new System.Windows.Forms.Label();
            this._lblBaudRate = new System.Windows.Forms.Label();
            this._lblDataBits = new System.Windows.Forms.Label();
            this._lblStopBits = new System.Windows.Forms.Label();
            this._lblHandshake = new System.Windows.Forms.Label();
            this._lblParity = new System.Windows.Forms.Label();
            this._ddlPortName = new System.Windows.Forms.ComboBox();
            this._ddlBaudRate = new System.Windows.Forms.ComboBox();
            this._ddlDataBits = new System.Windows.Forms.ComboBox();
            this._ddlStopBits = new System.Windows.Forms.ComboBox();
            this._ddlHandshake = new System.Windows.Forms.ComboBox();
            this._ddlParity = new System.Windows.Forms.ComboBox();
            this._btnConfirm = new System.Windows.Forms.Button();
            this._btnDefault = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // _lblPortName
            // 
            this._lblPortName.AutoSize = true;
            this._lblPortName.Location = new System.Drawing.Point(13, 16);
            this._lblPortName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this._lblPortName.Name = "_lblPortName";
            this._lblPortName.Size = new System.Drawing.Size(75, 16);
            this._lblPortName.TabIndex = 0;
            this._lblPortName.Text = "Port Name";
            // 
            // _lblBaudRate
            // 
            this._lblBaudRate.AutoSize = true;
            this._lblBaudRate.Location = new System.Drawing.Point(13, 48);
            this._lblBaudRate.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this._lblBaudRate.Name = "_lblBaudRate";
            this._lblBaudRate.Size = new System.Drawing.Size(74, 16);
            this._lblBaudRate.TabIndex = 1;
            this._lblBaudRate.Text = "Baud Rate";
            // 
            // _lblDataBits
            // 
            this._lblDataBits.AutoSize = true;
            this._lblDataBits.Location = new System.Drawing.Point(13, 80);
            this._lblDataBits.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this._lblDataBits.Name = "_lblDataBits";
            this._lblDataBits.Size = new System.Drawing.Size(64, 16);
            this._lblDataBits.TabIndex = 1;
            this._lblDataBits.Text = "Data Bits";
            // 
            // _lblStopBits
            // 
            this._lblStopBits.AutoSize = true;
            this._lblStopBits.Location = new System.Drawing.Point(13, 112);
            this._lblStopBits.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this._lblStopBits.Name = "_lblStopBits";
            this._lblStopBits.Size = new System.Drawing.Size(64, 16);
            this._lblStopBits.TabIndex = 1;
            this._lblStopBits.Text = "Stop Bits";
            // 
            // _lblHandshake
            // 
            this._lblHandshake.AutoSize = true;
            this._lblHandshake.Location = new System.Drawing.Point(13, 144);
            this._lblHandshake.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this._lblHandshake.Name = "_lblHandshake";
            this._lblHandshake.Size = new System.Drawing.Size(78, 16);
            this._lblHandshake.TabIndex = 1;
            this._lblHandshake.Text = "Handshake";
            // 
            // _lblParity
            // 
            this._lblParity.AutoSize = true;
            this._lblParity.Location = new System.Drawing.Point(13, 176);
            this._lblParity.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this._lblParity.Name = "_lblParity";
            this._lblParity.Size = new System.Drawing.Size(45, 16);
            this._lblParity.TabIndex = 1;
            this._lblParity.Text = "Parity";
            // 
            // _ddlPortName
            // 
            this._ddlPortName.FormattingEnabled = true;
            this._ddlPortName.Location = new System.Drawing.Point(96, 13);
            this._ddlPortName.Margin = new System.Windows.Forms.Padding(4);
            this._ddlPortName.Name = "_ddlPortName";
            this._ddlPortName.Size = new System.Drawing.Size(160, 24);
            this._ddlPortName.TabIndex = 2;
            // 
            // _ddlBaudRate
            // 
            this._ddlBaudRate.FormattingEnabled = true;
            this._ddlBaudRate.Location = new System.Drawing.Point(96, 45);
            this._ddlBaudRate.Margin = new System.Windows.Forms.Padding(4);
            this._ddlBaudRate.Name = "_ddlBaudRate";
            this._ddlBaudRate.Size = new System.Drawing.Size(160, 24);
            this._ddlBaudRate.TabIndex = 2;
            // 
            // _ddlDataBits
            // 
            this._ddlDataBits.FormattingEnabled = true;
            this._ddlDataBits.Location = new System.Drawing.Point(96, 77);
            this._ddlDataBits.Margin = new System.Windows.Forms.Padding(4);
            this._ddlDataBits.Name = "_ddlDataBits";
            this._ddlDataBits.Size = new System.Drawing.Size(160, 24);
            this._ddlDataBits.TabIndex = 2;
            // 
            // _ddlStopBits
            // 
            this._ddlStopBits.FormattingEnabled = true;
            this._ddlStopBits.Location = new System.Drawing.Point(96, 109);
            this._ddlStopBits.Margin = new System.Windows.Forms.Padding(4);
            this._ddlStopBits.Name = "_ddlStopBits";
            this._ddlStopBits.Size = new System.Drawing.Size(160, 24);
            this._ddlStopBits.TabIndex = 2;
            // 
            // _ddlHandshake
            // 
            this._ddlHandshake.FormattingEnabled = true;
            this._ddlHandshake.Location = new System.Drawing.Point(96, 141);
            this._ddlHandshake.Margin = new System.Windows.Forms.Padding(4);
            this._ddlHandshake.Name = "_ddlHandshake";
            this._ddlHandshake.Size = new System.Drawing.Size(160, 24);
            this._ddlHandshake.TabIndex = 2;
            // 
            // _ddlParity
            // 
            this._ddlParity.FormattingEnabled = true;
            this._ddlParity.Location = new System.Drawing.Point(96, 173);
            this._ddlParity.Margin = new System.Windows.Forms.Padding(4);
            this._ddlParity.Name = "_ddlParity";
            this._ddlParity.Size = new System.Drawing.Size(160, 24);
            this._ddlParity.TabIndex = 2;
            // 
            // _btnConfirm
            // 
            this._btnConfirm.Location = new System.Drawing.Point(16, 208);
            this._btnConfirm.Margin = new System.Windows.Forms.Padding(4);
            this._btnConfirm.Name = "_btnConfirm";
            this._btnConfirm.Size = new System.Drawing.Size(100, 28);
            this._btnConfirm.TabIndex = 3;
            this._btnConfirm.Text = "OK";
            this._btnConfirm.UseVisualStyleBackColor = true;
            this._btnConfirm.Click += new System.EventHandler(this._btnConfirm_Click);
            // 
            // _btnDefault
            // 
            this._btnDefault.Location = new System.Drawing.Point(156, 208);
            this._btnDefault.Margin = new System.Windows.Forms.Padding(4);
            this._btnDefault.Name = "_btnDefault";
            this._btnDefault.Size = new System.Drawing.Size(100, 28);
            this._btnDefault.TabIndex = 4;
            this._btnDefault.Text = "Default";
            this._btnDefault.UseVisualStyleBackColor = true;
            this._btnDefault.Click += new System.EventHandler(this._btnDefault_Click);
            // 
            // Form_Config
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(274, 249);
            this.Controls.Add(this._btnDefault);
            this.Controls.Add(this._btnConfirm);
            this.Controls.Add(this._ddlParity);
            this.Controls.Add(this._ddlHandshake);
            this.Controls.Add(this._ddlStopBits);
            this.Controls.Add(this._ddlDataBits);
            this.Controls.Add(this._ddlBaudRate);
            this.Controls.Add(this._ddlPortName);
            this.Controls.Add(this._lblParity);
            this.Controls.Add(this._lblHandshake);
            this.Controls.Add(this._lblStopBits);
            this.Controls.Add(this._lblDataBits);
            this.Controls.Add(this._lblBaudRate);
            this.Controls.Add(this._lblPortName);
            this.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "Form_Config";
            this.Text = "Serial Port Config";
            this.Load += new System.EventHandler(this.Form_Config_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label _lblPortName;
        private System.Windows.Forms.Label _lblBaudRate;
        private System.Windows.Forms.Label _lblDataBits;
        private System.Windows.Forms.Label _lblStopBits;
        private System.Windows.Forms.Label _lblHandshake;
        private System.Windows.Forms.Label _lblParity;
        private System.Windows.Forms.ComboBox _ddlPortName;
        private System.Windows.Forms.ComboBox _ddlBaudRate;
        private System.Windows.Forms.ComboBox _ddlDataBits;
        private System.Windows.Forms.ComboBox _ddlStopBits;
        private System.Windows.Forms.ComboBox _ddlHandshake;
        private System.Windows.Forms.ComboBox _ddlParity;
        private System.Windows.Forms.Button _btnConfirm;
        private System.Windows.Forms.Button _btnDefault;
    }
}