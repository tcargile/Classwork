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
			BackColor = Color.FromArgb(rand.Next(128, 256), rand.Next(128, 256), rand.Next(128, 256));
			listBox1.Items.Add(BackColor);
		}

		private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
		{
			object obj = listBox1.SelectedItem;
			if (obj is Color)
				BackColor = (Color)obj;
			else
				button1.Location = (Point)obj;

		}

		private void Form1_MouseDown(object sender, MouseEventArgs e)
		{
			button1.Location = e.Location;
			listBox1.Items.Add(e.Location);
		}
	}
}
