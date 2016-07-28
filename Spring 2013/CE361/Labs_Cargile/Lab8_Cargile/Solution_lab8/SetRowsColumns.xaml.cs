using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Solution_lab8
{
    /// <summary>
    /// Interaction logic for SetRowsColumns.xaml
    /// </summary>
    public partial class SetRowsColumns : Window
    {
        public int row, column = 0;

        public SetRowsColumns()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                row = int.Parse(textBox1.Text);
                column = int.Parse(textBox2.Text);
                if (row < 3 || column < 1)
                    throw new Exception("Error.");
                else
                    DialogResult = true;
            }
            catch
            {
                MessageBox.Show("Invalid values. They must be positive integers. Row must be greater than 2 and column must be greater than 0.");
            }
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = false;
        }
    }
}
