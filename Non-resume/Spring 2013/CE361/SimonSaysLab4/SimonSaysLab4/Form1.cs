//Trevor Cargile
//813542789
//CompE361 - Lab 4.
//Sounds credit to Patrick Haller.

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Media;

namespace SimonSaysLab4
{
    public partial class Form1 : Form
    {
        Random rand = new Random();
        SoundPlayer soundPlayer;

        int Diffint;
        int Colorint;
        int Repint;

        int TimerStop = 0;

        List<int> Sequence = new List<int>();
        int sequenceholder = 0;
        int length;

        int userinput;
        int x;

        public Form1()
        {
            InitializeComponent();
        }

        private void GreenButton_Click(object sender, EventArgs e)
        {
            this.GreenBack.BackColor = System.Drawing.Color.DarkGreen;
            userinput = 3;
            //UserTimer.Stop();
            //UserTimer.Start();

            soundPlayer = new SoundPlayer(Properties.Resources.high_beep);
            soundPlayer.Play();

            checkinput();
        }

        private void GreenButton_MouseClick(object sender, EventArgs e)
        {
            this.GreenBack.BackColor = System.Drawing.Color.LawnGreen;
        }

        private void RedButton_Click(object sender, EventArgs e)
        {
            this.RedBack.BackColor = System.Drawing.Color.Maroon;
            userinput = 2;
            //UserTimer.Stop();
            //UserTimer.Start();

            soundPlayer = new SoundPlayer(Properties.Resources.normal_beep);
            soundPlayer.Play();

            checkinput();
        }

        private void RedButton_MouseClick(object sender, EventArgs e)
        {
            this.RedBack.BackColor = System.Drawing.Color.Red;
        }

        private void YellowButton_Click(object sender, EventArgs e)
        {
            this.YellowBack.BackColor = System.Drawing.Color.DarkGoldenrod;
            userinput = 1;
            //UserTimer.Stop();
            //UserTimer.Start();

            soundPlayer = new SoundPlayer(Properties.Resources.low_beep);
            soundPlayer.Play();

            checkinput();
        }

        private void YellowButton_MouseClick(object sender, EventArgs e)
        {
            this.YellowBack.BackColor = System.Drawing.Color.Yellow;
        }

        private void BlueButton_Click(object sender, EventArgs e)
        {
            this.BlueBack.BackColor = System.Drawing.Color.DarkBlue;
            userinput = 0;
            //UserTimer.Stop();
            //UserTimer.Start();

            soundPlayer = new SoundPlayer(Properties.Resources.lower_beep);
            soundPlayer.Play();

            checkinput();
        }

        private void BlueButton_MouseClick(object sender, EventArgs e)
        {
            this.BlueBack.BackColor = System.Drawing.Color.Aqua;
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            MessageBox.ForeColor = System.Drawing.Color.White;
            try
            {
                Sequence.Clear();

                Diffint = DifficultyTimer.Interval;
                Repint = RepeatTimer.Interval;
                Colorint = ColorChangeTimer.Interval;

                TimerStop = 0;
                sequenceholder = 0;

                int testinput;
                testinput = int.Parse(LengthText.Text);

                if (testinput <= 0)
                    throw new Exception("Input is less than or equal to zero.");


                MessageBox.Text = "";
                LockAll();
                DifficultyTimer.Start();
            }
            catch
            {
                MessageBox.ForeColor = System.Drawing.Color.Red;
                MessageBox.Text = "Error! Input is not a positive integer.";
            }
        }

        public void checkinput()
        {
            if (Sequence[sequenceholder] != userinput)
            {
                MessageBox.ForeColor = System.Drawing.Color.Red;
                MessageBox.Text = "Wrong! Press Repeat to try again, or Start to make new sequence.";
                EnableMost();

                soundPlayer = new SoundPlayer(Properties.Resources.beep_3);
                soundPlayer.Play();
                //UserTimer.Stop();
            }
            else if (sequenceholder == length - 1)
            {
                MessageBox.ForeColor = System.Drawing.Color.LawnGreen;
                MessageBox.Text = "Correct!";
                EnableMost();

                soundPlayer = new SoundPlayer(Properties.Resources.ding);
                soundPlayer.Play();
                //UserTimer.Stop();
            }
            sequenceholder++;
        }

        private void DifficultyTimer_Tick(object sender, EventArgs e)
        {
            x = rand.Next(4);

            if (x == 3)
            {
                this.GreenBack.BackColor = System.Drawing.Color.LawnGreen;
                ColorChangeTimer.Start();

                soundPlayer = new SoundPlayer(Properties.Resources.high_beep);
                soundPlayer.Play();

            }
            else if (x == 2)
            {
                this.RedBack.BackColor = System.Drawing.Color.Red;
                ColorChangeTimer.Start();

                soundPlayer = new SoundPlayer(Properties.Resources.normal_beep);
                soundPlayer.Play();

            }
            else if (x == 1)
            {
                this.YellowBack.BackColor = System.Drawing.Color.Yellow;
                ColorChangeTimer.Start();

                soundPlayer = new SoundPlayer(Properties.Resources.low_beep);
                soundPlayer.Play();

            }
            else
            {
                this.BlueBack.BackColor = System.Drawing.Color.Aqua;
                ColorChangeTimer.Start();

                soundPlayer = new SoundPlayer(Properties.Resources.lower_beep);
                soundPlayer.Play();

            }

            Sequence.Add(x);
            sequenceholder++;

            TimerStop++;
            if (TimerStop % int.Parse(LengthText.Text) == 0)
            {
                RedButton.Enabled = true;
                BlueButton.Enabled = true;
                GreenButton.Enabled = true;
                YellowButton.Enabled = true;
                length = sequenceholder;
                sequenceholder = 0;
                //UserTimer.Start();
                DifficultyTimer.Stop();
            }
        }

        private void ColorChangeTimer_Tick(object sender, EventArgs e)
        {
            this.GreenBack.BackColor = System.Drawing.Color.DarkGreen;
            this.RedBack.BackColor = System.Drawing.Color.Maroon;
            this.YellowBack.BackColor = System.Drawing.Color.DarkGoldenrod;
            this.BlueBack.BackColor = System.Drawing.Color.DarkBlue;

            ColorChangeTimer.Stop();
        }

        //private void UserTimer_Tick(object sender, EventArgs e)
        //{
        //    MessageBox.Text = "Gameover. You took too long.";
        //    UserTimer.Stop();
        //    EnableMost();

        //    this.GreenBack.BackColor = System.Drawing.Color.DarkGreen;
        //    this.RedBack.BackColor = System.Drawing.Color.Maroon;
        //    this.YellowBack.BackColor = System.Drawing.Color.DarkGoldenrod;
        //    this.BlueBack.BackColor = System.Drawing.Color.DarkBlue;
        //}

        public void LockAll()
        {
            RedButton.Enabled = false;
            BlueButton.Enabled = false;
            GreenButton.Enabled = false;
            YellowButton.Enabled = false;
            StartButton.Enabled = false;
            RepeatButton.Enabled = false;
            LengthText.Enabled = false;
            Difficulty1.Enabled = false;
            Difficulty2.Enabled = false;
            Difficulty3.Enabled = false;
            Difficulty4.Enabled = false;
            Difficulty5.Enabled = false;
        }

        public void EnableMost()
        {
            RedButton.Enabled = false;
            BlueButton.Enabled = false;
            GreenButton.Enabled = false;
            YellowButton.Enabled = false;
            StartButton.Enabled = true;
            RepeatButton.Enabled = true;
            LengthText.Enabled = true;
            Difficulty1.Enabled = true;
            Difficulty2.Enabled = true;
            Difficulty3.Enabled = true;
            Difficulty4.Enabled = true;
            Difficulty5.Enabled = true;
        }

        private void RepeatButton_Click(object sender, EventArgs e)
        {
            MessageBox.ForeColor = System.Drawing.Color.White;
            try
            {
                if (TimerStop == 0)
                    throw new Exception("Check to see if Repeat pressed before Start.");

                TimerStop = 0;
                sequenceholder = 0;
                MessageBox.Text = "Repeating sequence with previous difficulty...";

                LockAll();
                RepeatTimer.Interval = Repint;
                DifficultyTimer.Interval = Diffint;
                ColorChangeTimer.Interval = Colorint;

                RepeatTimer.Start();

            }
            catch
            {
                MessageBox.ForeColor = System.Drawing.Color.Red;
                MessageBox.Text = "Error! There is nothing to repeat. Please click Start.";
                EnableMost();
            }
        }

        private void RepeatTimer_Tick(object sender, EventArgs e)
        {
            int x;

            x = Sequence[sequenceholder];

            if (x == 3)
            {
                this.GreenBack.BackColor = System.Drawing.Color.LawnGreen;
                ColorChangeTimer.Start();

                soundPlayer = new SoundPlayer(Properties.Resources.high_beep);
                soundPlayer.Play();

            }
            else if (x == 2)
            {
                this.RedBack.BackColor = System.Drawing.Color.Red;
                ColorChangeTimer.Start();

                soundPlayer = new SoundPlayer(Properties.Resources.normal_beep);
                soundPlayer.Play();

            }
            else if (x == 1)
            {
                this.YellowBack.BackColor = System.Drawing.Color.Yellow;
                ColorChangeTimer.Start();

                soundPlayer = new SoundPlayer(Properties.Resources.low_beep);
                soundPlayer.Play();

            }
            else
            {
                this.BlueBack.BackColor = System.Drawing.Color.Aqua;
                ColorChangeTimer.Start();

                soundPlayer = new SoundPlayer(Properties.Resources.lower_beep);
                soundPlayer.Play();

            }

            sequenceholder++;
            TimerStop++;

            if (TimerStop % (length) == 0)
            {
                RepeatTimer.Stop();
                RedButton.Enabled = true;
                BlueButton.Enabled = true;
                GreenButton.Enabled = true;
                YellowButton.Enabled = true;
                //UserTimer.Start();
                sequenceholder = 0;
                MessageBox.Text = "";
            }
        }

        private void Difficulty1_CheckedChanged(object sender, EventArgs e)
        {
            if (Difficulty1.Checked)
            {
                DifficultyTimer.Interval = 1000;
                RepeatTimer.Interval = 1000;
                //UserTimer.Interval = 5000;
                ColorChangeTimer.Interval = 500;
            }
        }

        private void Difficulty2_CheckedChanged(object sender, EventArgs e)
        {
            if (Difficulty2.Checked)
            {
                DifficultyTimer.Interval = 500;
                RepeatTimer.Interval = 500;
                //UserTimer.Interval = 2500;
                ColorChangeTimer.Interval = 250;
            }
        }

        private void Difficulty3_CheckedChanged(object sender, EventArgs e)
        {
            if (Difficulty3.Checked)
            {
                DifficultyTimer.Interval = 333;
                RepeatTimer.Interval = 333;
                //UserTimer.Interval = 1565;
                ColorChangeTimer.Interval = 167;
            }
        }

        private void Difficulty4_CheckedChanged(object sender, EventArgs e)
        {
            if (Difficulty4.Checked)
            {
                DifficultyTimer.Interval = 250;
                RepeatTimer.Interval = 250;
                //UserTimer.Interval = 1250;
                ColorChangeTimer.Interval = 125;
            }
        }

        private void Difficulty5_CheckedChanged(object sender, EventArgs e)
        {
            if (Difficulty5.Checked)
            {
                DifficultyTimer.Interval = 200;
                RepeatTimer.Interval = 200;
                //UserTimer.Interval = 1000;
                ColorChangeTimer.Interval = 100;
            }
        }
    }
}
