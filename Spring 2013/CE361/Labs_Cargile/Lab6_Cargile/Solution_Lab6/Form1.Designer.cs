namespace Solution_Lab6
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
            this.menuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.setRowsAndColumnsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.instructionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.changeFontToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.changeBackColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.changeTokenColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectedTokenColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fontColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.titleFontToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startmenuColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startmenuFontToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startmenuFontColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.NimLogo = new System.Windows.Forms.Label();
            this.bottimer = new System.Windows.Forms.Timer(this.components);
            this.pretimer = new System.Windows.Forms.Timer(this.components);
            this.startgametimer = new System.Windows.Forms.Timer(this.components);
            this.panel1 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button_nosecond = new System.Windows.Forms.Button();
            this.button_yesfirst = new System.Windows.Forms.Button();
            this.gofirstlabel = new System.Windows.Forms.Label();
            this.endgametimer = new System.Windows.Forms.Timer(this.components);
            this.label_youscore = new System.Windows.Forms.Label();
            this.label_mescore = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(284, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // menuToolStripMenuItem
            // 
            this.menuToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newGameToolStripMenuItem,
            this.setRowsAndColumnsToolStripMenuItem,
            this.instructionsToolStripMenuItem,
            this.changeFontToolStripMenuItem});
            this.menuToolStripMenuItem.Name = "menuToolStripMenuItem";
            this.menuToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.menuToolStripMenuItem.Text = "Menu";
            // 
            // newGameToolStripMenuItem
            // 
            this.newGameToolStripMenuItem.Name = "newGameToolStripMenuItem";
            this.newGameToolStripMenuItem.Size = new System.Drawing.Size(202, 22);
            this.newGameToolStripMenuItem.Text = "New Game";
            this.newGameToolStripMenuItem.Click += new System.EventHandler(this.newGameToolStripMenuItem_Click);
            // 
            // setRowsAndColumnsToolStripMenuItem
            // 
            this.setRowsAndColumnsToolStripMenuItem.Name = "setRowsAndColumnsToolStripMenuItem";
            this.setRowsAndColumnsToolStripMenuItem.Size = new System.Drawing.Size(202, 22);
            this.setRowsAndColumnsToolStripMenuItem.Text = "Set Rows and Columns";
            this.setRowsAndColumnsToolStripMenuItem.Click += new System.EventHandler(this.setRowsAndColumnsToolStripMenuItem_Click);
            // 
            // instructionsToolStripMenuItem
            // 
            this.instructionsToolStripMenuItem.Name = "instructionsToolStripMenuItem";
            this.instructionsToolStripMenuItem.Size = new System.Drawing.Size(202, 22);
            this.instructionsToolStripMenuItem.Text = "Instructions";
            this.instructionsToolStripMenuItem.Click += new System.EventHandler(this.instructionsToolStripMenuItem_Click);
            // 
            // changeFontToolStripMenuItem
            // 
            this.changeFontToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.changeBackColorToolStripMenuItem,
            this.changeTokenColorToolStripMenuItem,
            this.selectedTokenColorToolStripMenuItem,
            this.fontColorToolStripMenuItem,
            this.titleFontToolStripMenuItem,
            this.startmenuColorToolStripMenuItem,
            this.startmenuFontToolStripMenuItem,
            this.startmenuFontColorToolStripMenuItem});
            this.changeFontToolStripMenuItem.Name = "changeFontToolStripMenuItem";
            this.changeFontToolStripMenuItem.Size = new System.Drawing.Size(202, 22);
            this.changeFontToolStripMenuItem.Text = "Change Font and Colors";
            // 
            // changeBackColorToolStripMenuItem
            // 
            this.changeBackColorToolStripMenuItem.Name = "changeBackColorToolStripMenuItem";
            this.changeBackColorToolStripMenuItem.Size = new System.Drawing.Size(207, 22);
            this.changeBackColorToolStripMenuItem.Text = "Back Color";
            this.changeBackColorToolStripMenuItem.Click += new System.EventHandler(this.changeBackColorToolStripMenuItem_Click);
            // 
            // changeTokenColorToolStripMenuItem
            // 
            this.changeTokenColorToolStripMenuItem.Name = "changeTokenColorToolStripMenuItem";
            this.changeTokenColorToolStripMenuItem.Size = new System.Drawing.Size(207, 22);
            this.changeTokenColorToolStripMenuItem.Text = "Token Color";
            this.changeTokenColorToolStripMenuItem.Click += new System.EventHandler(this.changeTokenColorToolStripMenuItem_Click);
            // 
            // selectedTokenColorToolStripMenuItem
            // 
            this.selectedTokenColorToolStripMenuItem.Name = "selectedTokenColorToolStripMenuItem";
            this.selectedTokenColorToolStripMenuItem.Size = new System.Drawing.Size(207, 22);
            this.selectedTokenColorToolStripMenuItem.Text = "Selected Token Color";
            this.selectedTokenColorToolStripMenuItem.Click += new System.EventHandler(this.selectedTokenColorToolStripMenuItem_Click);
            // 
            // fontColorToolStripMenuItem
            // 
            this.fontColorToolStripMenuItem.Name = "fontColorToolStripMenuItem";
            this.fontColorToolStripMenuItem.Size = new System.Drawing.Size(207, 22);
            this.fontColorToolStripMenuItem.Text = "Title Color";
            this.fontColorToolStripMenuItem.Click += new System.EventHandler(this.fontColorToolStripMenuItem_Click);
            // 
            // titleFontToolStripMenuItem
            // 
            this.titleFontToolStripMenuItem.Name = "titleFontToolStripMenuItem";
            this.titleFontToolStripMenuItem.Size = new System.Drawing.Size(207, 22);
            this.titleFontToolStripMenuItem.Text = "Title Font";
            this.titleFontToolStripMenuItem.Click += new System.EventHandler(this.titleFontToolStripMenuItem_Click);
            // 
            // startmenuColorToolStripMenuItem
            // 
            this.startmenuColorToolStripMenuItem.Name = "startmenuColorToolStripMenuItem";
            this.startmenuColorToolStripMenuItem.Size = new System.Drawing.Size(207, 22);
            this.startmenuColorToolStripMenuItem.Text = "Pop-up menu Color";
            this.startmenuColorToolStripMenuItem.Click += new System.EventHandler(this.startmenuColorToolStripMenuItem_Click);
            // 
            // startmenuFontToolStripMenuItem
            // 
            this.startmenuFontToolStripMenuItem.Name = "startmenuFontToolStripMenuItem";
            this.startmenuFontToolStripMenuItem.Size = new System.Drawing.Size(207, 22);
            this.startmenuFontToolStripMenuItem.Text = "Pop-up menu Font";
            this.startmenuFontToolStripMenuItem.Click += new System.EventHandler(this.startmenuFontToolStripMenuItem_Click);
            // 
            // startmenuFontColorToolStripMenuItem
            // 
            this.startmenuFontColorToolStripMenuItem.Name = "startmenuFontColorToolStripMenuItem";
            this.startmenuFontColorToolStripMenuItem.Size = new System.Drawing.Size(207, 22);
            this.startmenuFontColorToolStripMenuItem.Text = "Pop-up menu Font Color";
            this.startmenuFontColorToolStripMenuItem.Click += new System.EventHandler(this.startmenuFontColorToolStripMenuItem_Click);
            // 
            // NimLogo
            // 
            this.NimLogo.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.NimLogo.Font = new System.Drawing.Font("Tahoma", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NimLogo.Location = new System.Drawing.Point(0, 24);
            this.NimLogo.Name = "NimLogo";
            this.NimLogo.Size = new System.Drawing.Size(284, 37);
            this.NimLogo.TabIndex = 1;
            this.NimLogo.Text = "Nim";
            this.NimLogo.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.NimLogo.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            // 
            // bottimer
            // 
            this.bottimer.Interval = 1000;
            this.bottimer.Tick += new System.EventHandler(this.bottimer_Tick);
            // 
            // pretimer
            // 
            this.pretimer.Interval = 1000;
            this.pretimer.Tick += new System.EventHandler(this.pretimer_Tick);
            // 
            // startgametimer
            // 
            this.startgametimer.Enabled = true;
            this.startgametimer.Interval = 2500;
            this.startgametimer.Tick += new System.EventHandler(this.startgametimer_Tick);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Location = new System.Drawing.Point(0, 61);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(284, 201);
            this.panel1.TabIndex = 4;
            this.panel1.Visible = false;
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label1.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Location = new System.Drawing.Point(52, 102);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(181, 102);
            this.label1.TabIndex = 0;
            this.label1.Visible = false;
            // 
            // button_nosecond
            // 
            this.button_nosecond.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.button_nosecond.Location = new System.Drawing.Point(145, 171);
            this.button_nosecond.Name = "button_nosecond";
            this.button_nosecond.Size = new System.Drawing.Size(75, 23);
            this.button_nosecond.TabIndex = 1;
            this.button_nosecond.Text = "No";
            this.button_nosecond.UseVisualStyleBackColor = true;
            this.button_nosecond.Visible = false;
            this.button_nosecond.Click += new System.EventHandler(this.button_nosecond_Click);
            // 
            // button_yesfirst
            // 
            this.button_yesfirst.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.button_yesfirst.Location = new System.Drawing.Point(64, 171);
            this.button_yesfirst.Name = "button_yesfirst";
            this.button_yesfirst.Size = new System.Drawing.Size(75, 23);
            this.button_yesfirst.TabIndex = 2;
            this.button_yesfirst.Text = "Yes";
            this.button_yesfirst.UseVisualStyleBackColor = true;
            this.button_yesfirst.Visible = false;
            this.button_yesfirst.Click += new System.EventHandler(this.button_yesfirst_Click);
            // 
            // gofirstlabel
            // 
            this.gofirstlabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.gofirstlabel.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.gofirstlabel.Font = new System.Drawing.Font("Tahoma", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.gofirstlabel.Location = new System.Drawing.Point(64, 102);
            this.gofirstlabel.Name = "gofirstlabel";
            this.gofirstlabel.Size = new System.Drawing.Size(156, 47);
            this.gofirstlabel.TabIndex = 3;
            this.gofirstlabel.Text = "Would you like to go first?";
            this.gofirstlabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.gofirstlabel.Visible = false;
            // 
            // endgametimer
            // 
            this.endgametimer.Interval = 500;
            this.endgametimer.Tick += new System.EventHandler(this.endgametimer_Tick);
            // 
            // label_youscore
            // 
            this.label_youscore.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label_youscore.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label_youscore.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_youscore.Location = new System.Drawing.Point(64, 176);
            this.label_youscore.Name = "label_youscore";
            this.label_youscore.Size = new System.Drawing.Size(156, 14);
            this.label_youscore.TabIndex = 5;
            this.label_youscore.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label_youscore.Visible = false;
            // 
            // label_mescore
            // 
            this.label_mescore.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label_mescore.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label_mescore.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_mescore.Location = new System.Drawing.Point(64, 154);
            this.label_mescore.Name = "label_mescore";
            this.label_mescore.Size = new System.Drawing.Size(156, 14);
            this.label_mescore.TabIndex = 6;
            this.label_mescore.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label_mescore.Visible = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.label_mescore);
            this.Controls.Add(this.label_youscore);
            this.Controls.Add(this.button_nosecond);
            this.Controls.Add(this.button_yesfirst);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.NimLogo);
            this.Controls.Add(this.gofirstlabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.panel1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Nim";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem menuToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newGameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem setRowsAndColumnsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem instructionsToolStripMenuItem;
        private System.Windows.Forms.Label NimLogo;
        private System.Windows.Forms.ToolStripMenuItem changeFontToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem changeBackColorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem changeTokenColorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem selectedTokenColorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fontColorToolStripMenuItem;
        private System.Windows.Forms.Timer bottimer;
        private System.Windows.Forms.Timer pretimer;
        private System.Windows.Forms.Timer startgametimer;
        private System.Windows.Forms.Label panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button_nosecond;
        private System.Windows.Forms.Button button_yesfirst;
        private System.Windows.Forms.Label gofirstlabel;
        private System.Windows.Forms.ToolStripMenuItem startmenuColorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startmenuFontToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startmenuFontColorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem titleFontToolStripMenuItem;
        private System.Windows.Forms.Timer endgametimer;
        private System.Windows.Forms.Label label_youscore;
        private System.Windows.Forms.Label label_mescore;
    }
}

