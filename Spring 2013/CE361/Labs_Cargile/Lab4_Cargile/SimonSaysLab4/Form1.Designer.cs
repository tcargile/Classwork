namespace SimonSaysLab4
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
            this.YellowButton = new System.Windows.Forms.Button();
            this.SimonLogo = new System.Windows.Forms.Label();
            this.YellowBack = new System.Windows.Forms.Label();
            this.BlueButton = new System.Windows.Forms.Button();
            this.BlueBack = new System.Windows.Forms.Label();
            this.RedButton = new System.Windows.Forms.Button();
            this.RedBack = new System.Windows.Forms.Label();
            this.GreenButton = new System.Windows.Forms.Button();
            this.GreenBack = new System.Windows.Forms.Label();
            this.StartButton = new System.Windows.Forms.Button();
            this.RepeatButton = new System.Windows.Forms.Button();
            this.DifficultyLabel = new System.Windows.Forms.Label();
            this.LengthLabel = new System.Windows.Forms.Label();
            this.LengthText = new System.Windows.Forms.TextBox();
            this.Difficulty3 = new System.Windows.Forms.RadioButton();
            this.Difficulty2 = new System.Windows.Forms.RadioButton();
            this.Difficulty1 = new System.Windows.Forms.RadioButton();
            this.Difficulty4 = new System.Windows.Forms.RadioButton();
            this.Difficulty5 = new System.Windows.Forms.RadioButton();
            this.DiffLogo1 = new System.Windows.Forms.Label();
            this.DiffLogo2 = new System.Windows.Forms.Label();
            this.DiffLogo3 = new System.Windows.Forms.Label();
            this.DiffLogo4 = new System.Windows.Forms.Label();
            this.DiffLogo5 = new System.Windows.Forms.Label();
            this.MessageBox = new System.Windows.Forms.Label();
            this.DifficultyTimer = new System.Windows.Forms.Timer(this.components);
            this.ColorChangeTimer = new System.Windows.Forms.Timer(this.components);
            this.RepeatTimer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // YellowButton
            // 
            this.YellowButton.Enabled = false;
            this.YellowButton.Location = new System.Drawing.Point(32, 234);
            this.YellowButton.Name = "YellowButton";
            this.YellowButton.Size = new System.Drawing.Size(90, 90);
            this.YellowButton.TabIndex = 2;
            this.YellowButton.UseVisualStyleBackColor = true;
            this.YellowButton.Click += new System.EventHandler(this.YellowButton_Click);
            this.YellowButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.YellowButton_MouseClick);
            // 
            // SimonLogo
            // 
            this.SimonLogo.BackColor = System.Drawing.SystemColors.MenuText;
            this.SimonLogo.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.SimonLogo.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.SimonLogo.Font = new System.Drawing.Font("Franklin Gothic Medium", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SimonLogo.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.SimonLogo.Location = new System.Drawing.Point(158, 91);
            this.SimonLogo.Name = "SimonLogo";
            this.SimonLogo.Size = new System.Drawing.Size(151, 38);
            this.SimonLogo.TabIndex = 4;
            this.SimonLogo.Text = "Simon Says";
            this.SimonLogo.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // YellowBack
            // 
            this.YellowBack.BackColor = System.Drawing.Color.DarkGoldenrod;
            this.YellowBack.Location = new System.Drawing.Point(3, 205);
            this.YellowBack.Name = "YellowBack";
            this.YellowBack.Size = new System.Drawing.Size(149, 149);
            this.YellowBack.TabIndex = 5;
            // 
            // BlueButton
            // 
            this.BlueButton.Enabled = false;
            this.BlueButton.Location = new System.Drawing.Point(344, 234);
            this.BlueButton.Name = "BlueButton";
            this.BlueButton.Size = new System.Drawing.Size(90, 90);
            this.BlueButton.TabIndex = 6;
            this.BlueButton.UseVisualStyleBackColor = true;
            this.BlueButton.Click += new System.EventHandler(this.BlueButton_Click);
            this.BlueButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.BlueButton_MouseClick);
            // 
            // BlueBack
            // 
            this.BlueBack.BackColor = System.Drawing.Color.DarkBlue;
            this.BlueBack.Location = new System.Drawing.Point(315, 205);
            this.BlueBack.Name = "BlueBack";
            this.BlueBack.Size = new System.Drawing.Size(149, 149);
            this.BlueBack.TabIndex = 7;
            // 
            // RedButton
            // 
            this.RedButton.Enabled = false;
            this.RedButton.Location = new System.Drawing.Point(344, 32);
            this.RedButton.Name = "RedButton";
            this.RedButton.Size = new System.Drawing.Size(90, 90);
            this.RedButton.TabIndex = 8;
            this.RedButton.UseVisualStyleBackColor = true;
            this.RedButton.Click += new System.EventHandler(this.RedButton_Click);
            this.RedButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.RedButton_MouseClick);
            // 
            // RedBack
            // 
            this.RedBack.BackColor = System.Drawing.Color.Maroon;
            this.RedBack.Location = new System.Drawing.Point(315, 3);
            this.RedBack.Name = "RedBack";
            this.RedBack.Size = new System.Drawing.Size(149, 149);
            this.RedBack.TabIndex = 9;
            // 
            // GreenButton
            // 
            this.GreenButton.Enabled = false;
            this.GreenButton.Location = new System.Drawing.Point(32, 32);
            this.GreenButton.Name = "GreenButton";
            this.GreenButton.Size = new System.Drawing.Size(90, 90);
            this.GreenButton.TabIndex = 10;
            this.GreenButton.UseVisualStyleBackColor = true;
            this.GreenButton.Click += new System.EventHandler(this.GreenButton_Click);
            this.GreenButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GreenButton_MouseClick);
            // 
            // GreenBack
            // 
            this.GreenBack.BackColor = System.Drawing.Color.DarkGreen;
            this.GreenBack.Location = new System.Drawing.Point(3, 3);
            this.GreenBack.Name = "GreenBack";
            this.GreenBack.Size = new System.Drawing.Size(149, 149);
            this.GreenBack.TabIndex = 11;
            // 
            // StartButton
            // 
            this.StartButton.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StartButton.Location = new System.Drawing.Point(158, 132);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(58, 23);
            this.StartButton.TabIndex = 12;
            this.StartButton.Text = "Start";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // RepeatButton
            // 
            this.RepeatButton.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RepeatButton.Location = new System.Drawing.Point(251, 132);
            this.RepeatButton.Name = "RepeatButton";
            this.RepeatButton.Size = new System.Drawing.Size(58, 23);
            this.RepeatButton.TabIndex = 13;
            this.RepeatButton.Text = "Repeat";
            this.RepeatButton.UseVisualStyleBackColor = true;
            this.RepeatButton.Click += new System.EventHandler(this.RepeatButton_Click);
            // 
            // DifficultyLabel
            // 
            this.DifficultyLabel.BackColor = System.Drawing.SystemColors.MenuText;
            this.DifficultyLabel.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.DifficultyLabel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.DifficultyLabel.Font = new System.Drawing.Font("Franklin Gothic Medium", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DifficultyLabel.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.DifficultyLabel.Location = new System.Drawing.Point(158, 214);
            this.DifficultyLabel.Name = "DifficultyLabel";
            this.DifficultyLabel.Size = new System.Drawing.Size(151, 23);
            this.DifficultyLabel.TabIndex = 14;
            this.DifficultyLabel.Text = "Difficulty";
            this.DifficultyLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // LengthLabel
            // 
            this.LengthLabel.BackColor = System.Drawing.SystemColors.InfoText;
            this.LengthLabel.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.LengthLabel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.LengthLabel.Font = new System.Drawing.Font("Franklin Gothic Medium", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LengthLabel.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.LengthLabel.Location = new System.Drawing.Point(158, 280);
            this.LengthLabel.Name = "LengthLabel";
            this.LengthLabel.Size = new System.Drawing.Size(151, 23);
            this.LengthLabel.TabIndex = 15;
            this.LengthLabel.Text = "Sequence Length";
            this.LengthLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // LengthText
            // 
            this.LengthText.Location = new System.Drawing.Point(186, 306);
            this.LengthText.Name = "LengthText";
            this.LengthText.Size = new System.Drawing.Size(94, 20);
            this.LengthText.TabIndex = 16;
            // 
            // Difficulty3
            // 
            this.Difficulty3.AutoSize = true;
            this.Difficulty3.Location = new System.Drawing.Point(226, 243);
            this.Difficulty3.Name = "Difficulty3";
            this.Difficulty3.Size = new System.Drawing.Size(14, 13);
            this.Difficulty3.TabIndex = 17;
            this.Difficulty3.UseVisualStyleBackColor = true;
            this.Difficulty3.CheckedChanged += new System.EventHandler(this.Difficulty3_CheckedChanged);
            // 
            // Difficulty2
            // 
            this.Difficulty2.AutoSize = true;
            this.Difficulty2.Location = new System.Drawing.Point(206, 243);
            this.Difficulty2.Name = "Difficulty2";
            this.Difficulty2.Size = new System.Drawing.Size(14, 13);
            this.Difficulty2.TabIndex = 18;
            this.Difficulty2.UseVisualStyleBackColor = true;
            this.Difficulty2.CheckedChanged += new System.EventHandler(this.Difficulty2_CheckedChanged);
            // 
            // Difficulty1
            // 
            this.Difficulty1.Checked = true;
            this.Difficulty1.Location = new System.Drawing.Point(186, 243);
            this.Difficulty1.Name = "Difficulty1";
            this.Difficulty1.Size = new System.Drawing.Size(14, 13);
            this.Difficulty1.TabIndex = 19;
            this.Difficulty1.TabStop = true;
            this.Difficulty1.UseVisualStyleBackColor = true;
            this.Difficulty1.CheckedChanged += new System.EventHandler(this.Difficulty1_CheckedChanged);
            // 
            // Difficulty4
            // 
            this.Difficulty4.AutoSize = true;
            this.Difficulty4.Location = new System.Drawing.Point(246, 243);
            this.Difficulty4.Name = "Difficulty4";
            this.Difficulty4.Size = new System.Drawing.Size(14, 13);
            this.Difficulty4.TabIndex = 20;
            this.Difficulty4.UseVisualStyleBackColor = true;
            this.Difficulty4.CheckedChanged += new System.EventHandler(this.Difficulty4_CheckedChanged);
            // 
            // Difficulty5
            // 
            this.Difficulty5.AutoSize = true;
            this.Difficulty5.Location = new System.Drawing.Point(266, 243);
            this.Difficulty5.Name = "Difficulty5";
            this.Difficulty5.Size = new System.Drawing.Size(14, 13);
            this.Difficulty5.TabIndex = 21;
            this.Difficulty5.UseVisualStyleBackColor = true;
            this.Difficulty5.CheckedChanged += new System.EventHandler(this.Difficulty5_CheckedChanged);
            // 
            // DiffLogo1
            // 
            this.DiffLogo1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.DiffLogo1.Location = new System.Drawing.Point(183, 259);
            this.DiffLogo1.Name = "DiffLogo1";
            this.DiffLogo1.Size = new System.Drawing.Size(17, 13);
            this.DiffLogo1.TabIndex = 22;
            this.DiffLogo1.Text = "1";
            this.DiffLogo1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // DiffLogo2
            // 
            this.DiffLogo2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.DiffLogo2.Location = new System.Drawing.Point(203, 259);
            this.DiffLogo2.Name = "DiffLogo2";
            this.DiffLogo2.Size = new System.Drawing.Size(17, 13);
            this.DiffLogo2.TabIndex = 23;
            this.DiffLogo2.Text = "2";
            this.DiffLogo2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // DiffLogo3
            // 
            this.DiffLogo3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.DiffLogo3.Location = new System.Drawing.Point(223, 259);
            this.DiffLogo3.Name = "DiffLogo3";
            this.DiffLogo3.Size = new System.Drawing.Size(17, 13);
            this.DiffLogo3.TabIndex = 24;
            this.DiffLogo3.Text = "3";
            this.DiffLogo3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // DiffLogo4
            // 
            this.DiffLogo4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.DiffLogo4.Location = new System.Drawing.Point(243, 259);
            this.DiffLogo4.Name = "DiffLogo4";
            this.DiffLogo4.Size = new System.Drawing.Size(17, 13);
            this.DiffLogo4.TabIndex = 25;
            this.DiffLogo4.Text = "4";
            this.DiffLogo4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // DiffLogo5
            // 
            this.DiffLogo5.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.DiffLogo5.Location = new System.Drawing.Point(263, 259);
            this.DiffLogo5.Name = "DiffLogo5";
            this.DiffLogo5.Size = new System.Drawing.Size(17, 13);
            this.DiffLogo5.TabIndex = 26;
            this.DiffLogo5.Text = "5";
            this.DiffLogo5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MessageBox
            // 
            this.MessageBox.Font = new System.Drawing.Font("Franklin Gothic Medium", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MessageBox.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.MessageBox.Location = new System.Drawing.Point(12, 166);
            this.MessageBox.Name = "MessageBox";
            this.MessageBox.Size = new System.Drawing.Size(442, 24);
            this.MessageBox.TabIndex = 27;
            this.MessageBox.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // DifficultyTimer
            // 
            this.DifficultyTimer.Interval = 1000;
            this.DifficultyTimer.Tick += new System.EventHandler(this.DifficultyTimer_Tick);
            // 
            // ColorChangeTimer
            // 
            this.ColorChangeTimer.Interval = 500;
            this.ColorChangeTimer.Tick += new System.EventHandler(this.ColorChangeTimer_Tick);
            // 
            // RepeatTimer
            // 
            this.RepeatTimer.Interval = 1000;
            this.RepeatTimer.Tick += new System.EventHandler(this.RepeatTimer_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.MenuText;
            this.ClientSize = new System.Drawing.Size(466, 356);
            this.Controls.Add(this.MessageBox);
            this.Controls.Add(this.DiffLogo5);
            this.Controls.Add(this.DiffLogo4);
            this.Controls.Add(this.DiffLogo3);
            this.Controls.Add(this.DiffLogo2);
            this.Controls.Add(this.DiffLogo1);
            this.Controls.Add(this.Difficulty5);
            this.Controls.Add(this.Difficulty4);
            this.Controls.Add(this.Difficulty1);
            this.Controls.Add(this.Difficulty2);
            this.Controls.Add(this.Difficulty3);
            this.Controls.Add(this.LengthText);
            this.Controls.Add(this.RepeatButton);
            this.Controls.Add(this.StartButton);
            this.Controls.Add(this.GreenButton);
            this.Controls.Add(this.GreenBack);
            this.Controls.Add(this.RedButton);
            this.Controls.Add(this.RedBack);
            this.Controls.Add(this.BlueButton);
            this.Controls.Add(this.BlueBack);
            this.Controls.Add(this.SimonLogo);
            this.Controls.Add(this.YellowButton);
            this.Controls.Add(this.YellowBack);
            this.Controls.Add(this.DifficultyLabel);
            this.Controls.Add(this.LengthLabel);
            this.Name = "Form1";
            this.Text = "Simon Says";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button YellowButton;
        private System.Windows.Forms.Label SimonLogo;
        private System.Windows.Forms.Label YellowBack;
        private System.Windows.Forms.Button BlueButton;
        private System.Windows.Forms.Label BlueBack;
        private System.Windows.Forms.Button RedButton;
        private System.Windows.Forms.Label RedBack;
        private System.Windows.Forms.Button GreenButton;
        private System.Windows.Forms.Label GreenBack;
        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.Button RepeatButton;
        private System.Windows.Forms.Label DifficultyLabel;
        private System.Windows.Forms.Label LengthLabel;
        private System.Windows.Forms.TextBox LengthText;
        private System.Windows.Forms.RadioButton Difficulty3;
        private System.Windows.Forms.RadioButton Difficulty2;
        private System.Windows.Forms.RadioButton Difficulty1;
        private System.Windows.Forms.RadioButton Difficulty4;
        private System.Windows.Forms.RadioButton Difficulty5;
        private System.Windows.Forms.Label DiffLogo1;
        private System.Windows.Forms.Label DiffLogo2;
        private System.Windows.Forms.Label DiffLogo3;
        private System.Windows.Forms.Label DiffLogo4;
        private System.Windows.Forms.Label DiffLogo5;
        private System.Windows.Forms.Label MessageBox;
        private System.Windows.Forms.Timer DifficultyTimer;
        private System.Windows.Forms.Timer ColorChangeTimer;
        private System.Windows.Forms.Timer RepeatTimer;
    }
}

