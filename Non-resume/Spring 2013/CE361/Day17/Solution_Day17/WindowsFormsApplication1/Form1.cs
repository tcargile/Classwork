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
		Pen pen = new Pen(Color.Red, 3);
		List<Rectangle> list = new List<Rectangle>();
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_MouseDown(object sender, MouseEventArgs e)
		{
			int x = e.X - 10;
			int y = e.Y - 10;
			//Graphics g = this.CreateGraphics();
			//g.DrawRectangle(pen, x, y, 20, 20);
			Rectangle rect = new Rectangle(x, y, 20, 20);
			list.Add(rect);
			Invalidate();

		}

		private void Form1_Paint(object sender, PaintEventArgs e)
		{
			foreach (Rectangle r in list)
				e.Graphics.DrawRectangle(pen, r);
		}
	}
}
