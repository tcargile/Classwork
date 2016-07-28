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
		Object sender;

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
			((Control)this.sender).BackColor = Color.White;
		}

		private void randomToolStripMenuItem_Click(object sender, EventArgs e)
		{
			((Control)this.sender).BackColor = Color.FromArgb(rand.Next(128, 256), rand.Next(128, 256), rand.Next(128, 256));

		}

		private void control_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button == System.Windows.Forms.MouseButtons.Right)
			{
				this.sender = sender;
				Point p = new Point(this.Location.X + ((Control)sender).Location.X,
					this.Location.Y + ((Control)sender).Location.Y);
				contextMenuStrip1.Show( p);
			}
		}
	}
}
