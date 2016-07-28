namespace WindowsFormsApplication1
{
	partial class Form1
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
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.numericUpDown_Red = new System.Windows.Forms.NumericUpDown();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.numericUpDown_Green = new System.Windows.Forms.NumericUpDown();
			this.label4 = new System.Windows.Forms.Label();
			this.numericUpDown_Blue = new System.Windows.Forms.NumericUpDown();
			this.label5 = new System.Windows.Forms.Label();
			this.textBox2 = new System.Windows.Forms.TextBox();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Red)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Green)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Blue)).BeginInit();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBox1.Location = new System.Drawing.Point(71, 65);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(163, 34);
			this.textBox1.TabIndex = 3;
			this.textBox1.TabStop = false;
			this.textBox1.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox1_KeyDown);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(40, 103);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(225, 29);
			this.label1.TabIndex = 1;
			this.label1.Text = "Change Form Color";
			// 
			// numericUpDown_Red
			// 
			this.numericUpDown_Red.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.numericUpDown_Red.Location = new System.Drawing.Point(105, 175);
			this.numericUpDown_Red.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
			this.numericUpDown_Red.Name = "numericUpDown_Red";
			this.numericUpDown_Red.Size = new System.Drawing.Size(69, 34);
			this.numericUpDown_Red.TabIndex = 0;
			this.numericUpDown_Red.ValueChanged += new System.EventHandler(this.numericUpDown_ValueChanged);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label2.Location = new System.Drawing.Point(207, 177);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(58, 29);
			this.label2.TabIndex = 3;
			this.label2.Text = "Red";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label3.Location = new System.Drawing.Point(195, 229);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(80, 29);
			this.label3.TabIndex = 5;
			this.label3.Text = "Green";
			// 
			// numericUpDown_Green
			// 
			this.numericUpDown_Green.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.numericUpDown_Green.Location = new System.Drawing.Point(105, 225);
			this.numericUpDown_Green.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
			this.numericUpDown_Green.Name = "numericUpDown_Green";
			this.numericUpDown_Green.Size = new System.Drawing.Size(69, 34);
			this.numericUpDown_Green.TabIndex = 1;
			this.numericUpDown_Green.ValueChanged += new System.EventHandler(this.numericUpDown_ValueChanged);
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label4.Location = new System.Drawing.Point(195, 287);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(62, 29);
			this.label4.TabIndex = 7;
			this.label4.Text = "Blue";
			// 
			// numericUpDown_Blue
			// 
			this.numericUpDown_Blue.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.numericUpDown_Blue.Location = new System.Drawing.Point(105, 283);
			this.numericUpDown_Blue.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
			this.numericUpDown_Blue.Name = "numericUpDown_Blue";
			this.numericUpDown_Blue.Size = new System.Drawing.Size(69, 34);
			this.numericUpDown_Blue.TabIndex = 2;
			this.numericUpDown_Blue.ValueChanged += new System.EventHandler(this.numericUpDown_ValueChanged);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label5.Location = new System.Drawing.Point(40, 414);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(238, 29);
			this.label5.TabIndex = 9;
			this.label5.Text = "Change Form Color2";
			// 
			// textBox2
			// 
			this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBox2.Location = new System.Drawing.Point(71, 376);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new System.Drawing.Size(163, 34);
			this.textBox2.TabIndex = 4;
			this.textBox2.TabStop = false;
			this.textBox2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
			this.textBox2.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox2_KeyDown);
			this.textBox2.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textBox2_KeyUp);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(365, 501);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.textBox2);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.numericUpDown_Blue);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.numericUpDown_Green);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.numericUpDown_Red);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.textBox1);
			this.Name = "Form1";
			this.Text = "Form1";
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Red)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Green)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Blue)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.NumericUpDown numericUpDown_Red;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.NumericUpDown numericUpDown_Green;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.NumericUpDown numericUpDown_Blue;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox textBox2;
	}
}

