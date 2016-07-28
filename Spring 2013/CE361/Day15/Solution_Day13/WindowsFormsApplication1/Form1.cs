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
		public Form1()
		{
			InitializeComponent();
		}


		private void textBox1_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode != Keys.Enter)
				return;
			BackColor = Color.FromName(textBox1.Text);
			textBox2.Focus();
			textBox2.SelectAll();
		}

		private void numericUpDown_ValueChanged(object sender, EventArgs e)
		{
			BackColor = Color.FromArgb((int)numericUpDown_Red.Value, 
				(int)numericUpDown_Green.Value, (int)numericUpDown_Blue.Value);
		}

		private void textBox2_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
			{
				int color = 255 << 24 | int.Parse(textBox2.Text);
				BackColor = Color.FromArgb(color);
				textBox1.Focus();
				textBox1.SelectAll();
			}
			if (e.KeyCode == Keys.R)
			{
				Console.WriteLine(textBox2.Text);
				int red = int.Parse(textBox2.Text) % 256;
				BackColor = Color.FromArgb(red, 0, 0);
			}
		}

		private void textBox2_TextChanged(object sender, EventArgs e)
		{
			//Console.WriteLine("In Textchanged " + textBox2.Text);
			//if (textBox2.Text.Length > 0)
			//   textBox2.Text = textBox2.Text.Substring(0, textBox2.Text.Length - 1);
		}

		private void textBox2_KeyUp(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.R)
				textBox2.Text = textBox2.Text.Substring(0, textBox2.Text.Length - 1);
			Console.WriteLine("Key up " + textBox2.Text);
		}
	}
}
