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
		Rectangle[,] rectArray;
		int rows = 3, columns = 5;
		Pen pen = new Pen(Color.Red, 3);
		Pen selectPen = new Pen(Color.Green, 3);

		public Form1()
		{
			InitializeComponent();
			this.DoubleBuffered = true;
			rectArray = new Rectangle[columns, rows];
			int dx = this.ClientSize.Width / (columns + 1);
			int dy = this.ClientSize.Height / (rows + 1);
			for (int c = 0; c < columns; c++)
				for (int r = 0; r < rows; r++)
					rectArray[c, r] = new Rectangle(dx + c * dx, dy + r * dy, 10, 10);

		}

		private void Form1_Paint(object sender, PaintEventArgs e)
		{
			Graphics g = e.Graphics;
			for (int c = 0; c < columns; c++)
				for (int r = 0; r < rows; r++)
					g.DrawRectangle(pen, rectArray[c, r]);
		}

		private void Form1_Resize(object sender, EventArgs e)
		{
			float dx = (float)this.ClientSize.Width / (columns + 1);
			float dy = this.ClientSize.Height / (rows + 1.0F);
			for (int c = 0; c < columns; c++)
				for (int r = 0; r < rows; r++)
					rectArray[c, r] = new Rectangle((int)(dx + c * dx), (int)(dy + r * dy), 10, 10);
			Invalidate();
		}

		private void Form1_MouseDown(object sender, MouseEventArgs e)
		{
			Graphics g = this.CreateGraphics();
			for (int c=0; c<columns; c++)
				for (int r = 0; r < rows; r++)
				{
					if (rectArray[c, r].Contains(e.Location))
						g.DrawRectangle(selectPen, rectArray[c, r]);
				}
		}
	}
}
