namespace WindowsFormsApplication3
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
			this.components = new System.ComponentModel.Container();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.colorsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.formToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.redToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.greenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.blueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.instructionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.label1 = new System.Windows.Forms.Label();
			this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.colorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.whiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.randomToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.menuStrip1.SuspendLayout();
			this.contextMenuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.colorsToolStripMenuItem,
            this.helpToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(282, 28);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// colorsToolStripMenuItem
			// 
			this.colorsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.formToolStripMenuItem});
			this.colorsToolStripMenuItem.Name = "colorsToolStripMenuItem";
			this.colorsToolStripMenuItem.Size = new System.Drawing.Size(63, 24);
			this.colorsToolStripMenuItem.Text = "Colors";
			// 
			// formToolStripMenuItem
			// 
			this.formToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.redToolStripMenuItem,
            this.greenToolStripMenuItem,
            this.blueToolStripMenuItem});
			this.formToolStripMenuItem.Name = "formToolStripMenuItem";
			this.formToolStripMenuItem.Size = new System.Drawing.Size(152, 24);
			this.formToolStripMenuItem.Text = "Form";
			// 
			// redToolStripMenuItem
			// 
			this.redToolStripMenuItem.Name = "redToolStripMenuItem";
			this.redToolStripMenuItem.Size = new System.Drawing.Size(152, 24);
			this.redToolStripMenuItem.Text = "Red";
			this.redToolStripMenuItem.Click += new System.EventHandler(this.redToolStripMenuItem_Click);
			// 
			// greenToolStripMenuItem
			// 
			this.greenToolStripMenuItem.Name = "greenToolStripMenuItem";
			this.greenToolStripMenuItem.Size = new System.Drawing.Size(152, 24);
			this.greenToolStripMenuItem.Text = "Green";
			// 
			// blueToolStripMenuItem
			// 
			this.blueToolStripMenuItem.Name = "blueToolStripMenuItem";
			this.blueToolStripMenuItem.Size = new System.Drawing.Size(152, 24);
			this.blueToolStripMenuItem.Text = "Blue";
			// 
			// helpToolStripMenuItem
			// 
			this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem,
            this.instructionsToolStripMenuItem});
			this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
			this.helpToolStripMenuItem.Size = new System.Drawing.Size(53, 24);
			this.helpToolStripMenuItem.Text = "Help";
			// 
			// aboutToolStripMenuItem
			// 
			this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
			this.aboutToolStripMenuItem.Size = new System.Drawing.Size(153, 24);
			this.aboutToolStripMenuItem.Text = "About";
			this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
			// 
			// instructionsToolStripMenuItem
			// 
			this.instructionsToolStripMenuItem.Name = "instructionsToolStripMenuItem";
			this.instructionsToolStripMenuItem.Size = new System.Drawing.Size(153, 24);
			this.instructionsToolStripMenuItem.Text = "Instructions";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.ContextMenuStrip = this.contextMenuStrip1;
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 25.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(66, 85);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(139, 52);
			this.label1.TabIndex = 1;
			this.label1.Text = "label1";
			// 
			// contextMenuStrip1
			// 
			this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.colorToolStripMenuItem});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new System.Drawing.Size(115, 28);
			// 
			// colorToolStripMenuItem
			// 
			this.colorToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.whiteToolStripMenuItem,
            this.randomToolStripMenuItem});
			this.colorToolStripMenuItem.Name = "colorToolStripMenuItem";
			this.colorToolStripMenuItem.Size = new System.Drawing.Size(152, 24);
			this.colorToolStripMenuItem.Text = "Color";
			// 
			// whiteToolStripMenuItem
			// 
			this.whiteToolStripMenuItem.Name = "whiteToolStripMenuItem";
			this.whiteToolStripMenuItem.Size = new System.Drawing.Size(152, 24);
			this.whiteToolStripMenuItem.Text = "White";
			this.whiteToolStripMenuItem.Click += new System.EventHandler(this.whiteToolStripMenuItem_Click);
			// 
			// randomToolStripMenuItem
			// 
			this.randomToolStripMenuItem.Name = "randomToolStripMenuItem";
			this.randomToolStripMenuItem.Size = new System.Drawing.Size(152, 24);
			this.randomToolStripMenuItem.Text = "Random";
			this.randomToolStripMenuItem.Click += new System.EventHandler(this.randomToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(282, 255);
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.label1);
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "Form1";
			this.Text = "Green";
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.contextMenuStrip1.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem colorsToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem formToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem redToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem greenToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem blueToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem instructionsToolStripMenuItem;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
		private System.Windows.Forms.ToolStripMenuItem colorToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem whiteToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem randomToolStripMenuItem;
	}
}

