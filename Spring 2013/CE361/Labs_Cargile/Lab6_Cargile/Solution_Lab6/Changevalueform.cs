using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Solution_Lab6
{
    public partial class Changevalueform : Form
    {

        public int row, column;

        public Changevalueform()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                row = int.Parse(textBox_Rows.Text);
                column = int.Parse(textBox_Columns.Text);
                DialogResult = System.Windows.Forms.DialogResult.OK;
            }
            catch
            {
                MessageBox.Show("Error. Input is not of type int.");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = System.Windows.Forms.DialogResult.Cancel;
        }
    }
}
