﻿using System;
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
    /// Interaction logic for WhoFirst.xaml
    /// </summary>
    public partial class WhoFirst : Window
    {
        public WhoFirst()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = false;
        }
    }
}
