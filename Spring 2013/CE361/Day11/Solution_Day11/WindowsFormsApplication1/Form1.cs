using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
	public partial class Form1 : Form
	{
		Random rand = new Random();

		public Form1()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			Color color = Color.FromArgb(rand.Next(256), rand.Next(256), rand.Next(256));
			this.BackColor = color;
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			Color color = Color.FromArgb(rand.Next(256), rand.Next(256), rand.Next(256));
			this.BackColor = color;
		}

		private void button2_Click(object sender, EventArgs e)
		{
			timer1.Start();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			timer1.Stop();
		}

		private void radioButton1_CheckedChanged(object sender, EventArgs e)
		{
			if (radioButton1.Checked)
				button1.BackColor = Color.Red;
		}

		private void radioButton2_CheckedChanged(object sender, EventArgs e)
		{
			if (radioButton2.Checked)
				button1.BackColor = Color.Green;

		}

		private void radioButton3_CheckedChanged(object sender, EventArgs e)
		{
			if (radioButton3.Checked)
				button1.BackColor = Color.Blue;

		}
	}
}
