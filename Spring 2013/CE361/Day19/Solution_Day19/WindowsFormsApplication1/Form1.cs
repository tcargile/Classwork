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
		Form2 form2;
		Point position;
		Brush brush = new SolidBrush(Color.Green);
		Font font = new Font("Arial", 12);
		Point stringPosition;

		public Form1()
		{
			InitializeComponent();
			Form1_Resize(this, new EventArgs());
		}

		private void Form1_MouseDown(object sender, MouseEventArgs e)
		{
			position = e.Location;
			Invalidate();
			Form1_Resize(this, e);
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

		private void button1_Click(object sender, EventArgs e)
		{
			ColorDialog dlg = new ColorDialog();
			DialogResult dr = dlg.ShowDialog();
			if (dr == System.Windows.Forms.DialogResult.OK)
				BackColor = dlg.Color;
		}

		private void button2_Click(object sender, EventArgs e)
		{
			FontDialog dlg = new FontDialog();
			DialogResult dr = dlg.ShowDialog();
			if (dr == System.Windows.Forms.DialogResult.OK)
				font = dlg.Font;
			Invalidate();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			form2 = new Form2();
			form2.Show();
			
		}

		private void button4_Click(object sender, EventArgs e)
		{
			if (form2 == null)
			{
				MessageBox.Show("Must create Form2 first");
				return;
			}
				
			ColorDialog dlg = new ColorDialog();
			DialogResult dr = dlg.ShowDialog();
			if (dr == System.Windows.Forms.DialogResult.OK)
				form2.BackColor = dlg.Color;
		}

		private void button5_Click(object sender, EventArgs e)
		{
			ColorNameDialog dlg = new ColorNameDialog();
			DialogResult dr = dlg.ShowDialog();
			if (dr == System.Windows.Forms.DialogResult.OK)
				BackColor = Color.FromName(dlg.colorName);
		}
	}
}