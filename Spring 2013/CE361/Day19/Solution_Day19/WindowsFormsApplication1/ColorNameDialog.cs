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
	public partial class ColorNameDialog : Form
	{
		public string colorName;

		public ColorNameDialog()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			colorName = textBox1.Text;
			DialogResult = System.Windows.Forms.DialogResult.OK;
		}
	}
}
