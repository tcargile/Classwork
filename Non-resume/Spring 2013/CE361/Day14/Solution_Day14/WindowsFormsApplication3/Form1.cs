using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication3
{
	public partial class Form1 : Form
	{
		Random rand = new Random();

		public Form1()
		{
			InitializeComponent();
		}

		private void redToolStripMenuItem_Click(object sender, EventArgs e)
		{
			BackColor = Color.Red;
		}

		private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
		{
			string aboutString = 
@"Menu demo
Damo Day14
asdf
";

			MessageBox.Show(aboutString);
		}

		private void whiteToolStripMenuItem_Click(object sender, EventArgs e)
		{
			label1.BackColor = Color.White;
		}

		private void randomToolStripMenuItem_Click(object sender, EventArgs e)
		{
			label1.BackColor = Color.FromArgb(rand.Next(128, 256), rand.Next(128, 256), rand.Next(128, 256));

		}
	}
}
