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
	public partial class Form1 : Form
	{
		Rectangle rect;
		Pen pen = new Pen(Color.Red, 10);
		Brush brush = new SolidBrush(Color.PowderBlue);

		public Form1()
		{
			InitializeComponent();
			int w = this.ClientSize.Width;
			int h = this.ClientSize.Height;
			rect = new Rectangle(w / 4, h / 4, w / 2, h / 2);
			this.DoubleBuffered = true;
		}

		private void Form1_Paint(object sender, PaintEventArgs e)
		{
			Graphics g = e.Graphics;
			g.DrawRectangle(pen, rect);
			g.FillRectangle(brush, rect);
		}

		private void Form1_Resize(object sender, EventArgs e)
		{
			int w = this.ClientSize.Width;
			int h = this.ClientSize.Height;
			rect = new Rectangle(w / 4, h / 4, w / 2, h / 2);
			Invalidate();

		}
	}
}
