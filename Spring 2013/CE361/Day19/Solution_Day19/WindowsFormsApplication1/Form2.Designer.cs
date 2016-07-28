namespace WindowsFormsApplication1
{
	partial class Form2
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
			this.button1 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.button1.Location = new System.Drawing.Point(12, 203);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 52);
			this.button1.TabIndex = 1;
			this.button1.Text = "Form1 color";
			this.button1.UseVisualStyleBackColor = true;
			// 
			// Form2
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
			this.ClientSize = new System.Drawing.Size(282, 255);
			this.Controls.Add(this.button1);
			this.Location = new System.Drawing.Point(500, 500);
			this.Name = "Form2";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Form2";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button button1;
	}
}