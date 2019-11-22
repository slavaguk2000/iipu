namespace Laba_4
{
    partial class USBView
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
            this.components = new System.ComponentModel.Container();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.ejectButton = new System.Windows.Forms.Button();
            this.DeviceName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.usbList = new System.Windows.Forms.ListView();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.usbDevices = new System.Windows.Forms.ListView();
            this.Description = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SuspendLayout();
            // 
            // timer
            // 
            this.timer.Tick += new System.EventHandler(this.TickTimer);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 179);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 13);
            this.label1.TabIndex = 3;
            // 
            // timer1
            // 
            this.timer1.Interval = 8000;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(-14, 84);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 13);
            this.label2.TabIndex = 6;
            // 
            // ejectButton
            // 
            this.ejectButton.Location = new System.Drawing.Point(12, 195);
            this.ejectButton.Name = "ejectButton";
            this.ejectButton.Size = new System.Drawing.Size(75, 23);
            this.ejectButton.TabIndex = 8;
            this.ejectButton.Text = "Извлечь";
            this.ejectButton.UseVisualStyleBackColor = true;
            this.ejectButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // DeviceName
            // 
            this.DeviceName.Text = "Название";
            this.DeviceName.Width = 111;
            // 
            // usbList
            // 
            this.usbList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.DeviceName});
            this.usbList.HideSelection = false;
            this.usbList.Location = new System.Drawing.Point(12, 34);
            this.usbList.Name = "usbList";
            this.usbList.Size = new System.Drawing.Size(115, 158);
            this.usbList.TabIndex = 7;
            this.usbList.UseCompatibleStateImageBehavior = false;
            this.usbList.View = System.Windows.Forms.View.Details;
            this.usbList.MouseClick += new System.Windows.Forms.MouseEventHandler(this.UsbList_MouseClick);
            this.usbList.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.ExecuteDevice);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(32, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Flash";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(154, 15);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "USB-devices";
            this.label4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // usbDevices
            // 
            this.usbDevices.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.Description});
            this.usbDevices.HideSelection = false;
            this.usbDevices.Location = new System.Drawing.Point(157, 34);
            this.usbDevices.Name = "usbDevices";
            this.usbDevices.Size = new System.Drawing.Size(300, 158);
            this.usbDevices.TabIndex = 10;
            this.usbDevices.UseCompatibleStateImageBehavior = false;
            this.usbDevices.SelectedIndexChanged += new System.EventHandler(this.listView1_SelectedIndexChanged);
            // 
            // USBView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(469, 221);
            this.Controls.Add(this.usbDevices);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.ejectButton);
            this.Controls.Add(this.usbList);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "USBView";
            this.Text = "USB Manager";
            this.Load += new System.EventHandler(this.LoadForm);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label2;
        public System.Windows.Forms.Button ejectButton;
        private System.Windows.Forms.ColumnHeader DeviceName;
        private System.Windows.Forms.ListView usbList;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ListView usbDevices;
        private System.Windows.Forms.ColumnHeader Description;
    }
}

