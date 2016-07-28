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
		Point position;
		Brush brush = new SolidBrush(Color.Green);
		Font font = new Font("Arial", 24);
		Point stringPosition;

		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_MouseDown(object sender, MouseEventArgs e)
		{
			position = e.Location;
			Invalidate();
		}

		private void Form1_Paint(object sender, PaintEventArgs e)
		{
			Graphics g = e.Graphics;
			//Point p = new Point(ClientSize.Width/4, ClientSize.Height/4);
			g.DrawString(position.ToString(), font, brush, stringPosition);
		}

		private void Form1_Resize(object sender, EventArgs e)
		{
			Graphics g = CreateGraphics();
			font = new System.Drawing.Font(font.FontFamily, ClientSize.Width / 20);
			SizeF stringSize = g.MeasureString(position.ToString(), font);
			int x = (int)(ClientSize.Width / 2 - stringSize.Width / 2);
			int y = (int)(ClientSize.Height / 2 - stringSize.Height / 2);
			stringPosition = new Point(x, y);
			Invalidate();
			float ratio = ClientSize.Width / font.SizeInPoints;
			Console.WriteLine(ratio);

		}
	}
}