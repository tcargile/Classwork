using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
	public partial class Form2 : Form
	{
		Random rand = new Random();
		Label[] labs = new Label[5];

		public Form2()
		{
			InitializeComponent();
			labs[0] = label1;
			labs[1] = label2;
			labs[2] = label3;
			labs[3] = label4;
			labs[4] = label5;

		}

		private void button1_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < labs.Length; i++)
			{
				labs[i].BackColor = Color.FromArgb(rand.Next(128, 256), rand.Next(128, 256), rand.Next(128, 256), rand.Next(128, 256));
			}
		}
	}
}
