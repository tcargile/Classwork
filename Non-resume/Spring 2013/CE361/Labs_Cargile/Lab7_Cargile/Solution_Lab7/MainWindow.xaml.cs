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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Solution_Lab7
{
    public partial class MainWindow : Window
    {
        int textboxfocus = 1;
        int operation = 0;
        int enterflag;
        int consoleline = 0;
        int index;
        int firstchecked = 0;
        Complex firstoperand = new Complex();
        Complex secondoperand = new Complex();
        Complex answer = new Complex();
        Complex storedopearnd = new Complex();

        public MainWindow()
        {
            InitializeComponent();
            textBox_part1operand.Focus();
        }

        private void radioButton1_Checked(object sender, RoutedEventArgs e)
        {
            firstchecked = 1;
            label1.Visibility = Visibility.Visible;
            label2.Visibility = Visibility.Visible;
            Part1AnswerTypeLabel.Visibility = Visibility.Hidden;
            Part2AnswerTypeLabel.Visibility = Visibility.Hidden;

            Complex.mode = MODE.Polar;

            if (enterflag != 0)
            {
                textBox_Console.Items.Clear();
                if (operation == 0)
                    textBox_Console.Items.Add(firstoperand.ToString());
                else
                    textBox_Console.Items.Add(firstoperand.ToString() + " " + displayoperation());

                textBox_part1operand.Text = firstoperand.Magnitude.ToString("F");
                textBox_part2operand.Text = firstoperand.Angle.ToString("F");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;
        }

        private void radioButton2_Checked(object sender, RoutedEventArgs e)
        {
            if (firstchecked == 1)
            {
                label1.Visibility = Visibility.Hidden;
                label2.Visibility = Visibility.Hidden;
                Part1AnswerTypeLabel.Visibility = Visibility.Visible;
                Part2AnswerTypeLabel.Visibility = Visibility.Visible;

                Complex.mode = MODE.Rectangular;

                if (enterflag != 0)
                {
                    textBox_Console.Items.Clear();
                    if (operation == 0)
                        textBox_Console.Items.Add(firstoperand.ToString());
                    else
                        textBox_Console.Items.Add(firstoperand.ToString() + " " + displayoperation());

                    textBox_part1operand.Text = firstoperand.Real.ToString("F");
                    textBox_part2operand.Text = firstoperand.Imag.ToString("F");
                }
            }
            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;
        }

        private void textBox_GotFocus(object sender, RoutedEventArgs e)
        {
            if (sender.Equals(textBox_part1operand))
                textboxfocus = 1;
            else if (sender.Equals(textBox_part2operand))
                textboxfocus = 2;
        }

        private void operationbuttonadd_Click(object sender, RoutedEventArgs e)
        {
            operation = 1;
            textBox_Console.Items[consoleline] = textBox_Console.Items[consoleline] + " + ";
            disable_opnumpad();
            enable_numpad();

            textBox_part1operand.Focus();
            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void operationbuttonsub_Click(object sender, RoutedEventArgs e)
        {
            operation = 2;
            textBox_Console.Items[consoleline] = textBox_Console.Items[consoleline] + " - ";
            disable_opnumpad();
            enable_numpad();

            textBox_part1operand.Focus();
            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void operationbuttonmul_Click(object sender, RoutedEventArgs e)
        {
            operation = 3;
            textBox_Console.Items[consoleline] = textBox_Console.Items[consoleline] + " * ";
            disable_opnumpad();
            enable_numpad();

            textBox_part1operand.Focus();
            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void operationbuttondiv_Click(object sender, RoutedEventArgs e)
        {
            operation = 4;
            textBox_Console.Items[consoleline] = textBox_Console.Items[consoleline] + " / ";
            disable_opnumpad();
            enable_numpad();

            textBox_part1operand.Focus();
            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void numberbuttondot_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, ".");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, ".");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbuttonneg_Click(object sender, RoutedEventArgs e)
        {
            if (textboxfocus == 1)
            {
                if (textBox_part1operand.Text.Contains('-'))
                {
                    textBox_part1operand.Text = textBox_part1operand.Text.Replace("-", "");
                    index--;
                }
                else
                {
                    textBox_part1operand.Text = "-" + textBox_part1operand.Text;
                    index++;
                }
            }
            else if (textboxfocus == 2)
            {
                if (textBox_part2operand.Text.Contains('-'))
                {
                    textBox_part2operand.Text = textBox_part2operand.Text.Replace("-", "");
                    index--;
                }
                else
                {
                    textBox_part2operand.Text = "-" + textBox_part2operand.Text;
                    index++;
                }
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void numberbutton1_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "1");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "1");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton2_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "2");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "2");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton3_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "3");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "3");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton4_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "4");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "4");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton5_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "5");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "5");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton6_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "6");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "6");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton7_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "7");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "7");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton8_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "8");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "8");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton9_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "9");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "9");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton0_Click(object sender, RoutedEventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.Text.Length && textboxfocus == 1 && textBox_part1operand.Text.Length != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.Text.Length && textboxfocus == 2 && textBox_part2operand.Text.Length != 0)
            {
                textBox_part2operand.Text = "";
                index = 0;
            }

            if (textboxfocus == 1)
            {
                textBox_part1operand.Text = textBox_part1operand.Text.Insert(index, "0");
            }
            else if (textboxfocus == 2)
            {
                textBox_part2operand.Text = textBox_part2operand.Text.Insert(index, "0");
            }

            //if (consoleline > 2)
                //textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            textBox_part1operand.Text = "";
            textBox_part2operand.Text = "";
            textBox_Console.Items.Clear();

            enterflag = 0;

            enable_numpad();
            disable_opnumpad();

            consoleline = 0;
            textBox_part1operand.Focus();
            //textBox_Console.TopIndex = consoleline;
            textBox_error.Text = "";
            operation = 0;
        }

        private void buttonStore_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (Complex.mode == MODE.Rectangular)
                {
                    storedopearnd.Real = double.Parse(textBox_part1operand.Text);
                    storedopearnd.Imag = double.Parse(textBox_part2operand.Text);
                }
                else
                {
                    if (double.Parse(textBox_part1operand.Text) < 0)
                        throw new Exception("Magnitude can't be less than 0.");

                    storedopearnd.Magnitude = double.Parse(textBox_part1operand.Text);
                    storedopearnd.Angle = double.Parse(textBox_part2operand.Text);
                }

                listboxanswers.Items.Add(storedopearnd.ToString());

                //if (consoleline > 2)
                    //textBox_Console.TopIndex = consoleline - 1;
                textBox_error.Text = "";
            }
            catch
            {
                textBox_error.Text = "Error. Can't store invalid inputs.";
                textBox_part1operand.Focus();
            }
        }

        private void buttonEnter_Click(object sender, RoutedEventArgs e)
        {
            if (enterflag == 0)
            {
                try
                {
                    if (textboxfocus == 1)
                    {
                        textBox_part2operand.Focus();
                        index = textBox_part2operand.Text.Length;
                    }
                    else
                    {
                        if (Complex.mode == MODE.Rectangular)
                        {
                            firstoperand.Real = double.Parse(textBox_part1operand.Text);
                            firstoperand.Imag = double.Parse(textBox_part2operand.Text);
                        }
                        else
                        {
                            if (double.Parse(textBox_part1operand.Text) < 0)
                                throw new Exception("Magnitude can't be less than 0.");

                            firstoperand.Magnitude = double.Parse(textBox_part1operand.Text);
                            firstoperand.Angle = double.Parse(textBox_part2operand.Text);
                        }

                        textBox_part1operand.Text = firstoperand.Real.ToString("F");
                        textBox_part2operand.Text = firstoperand.Imag.ToString("F");

                        textBox_Console.Items.Add(firstoperand.ToString());
                        enable_opnumpad();
                        disable_numpad();
                        enterflag = 1;
                    }
                    textBox_error.Text = "";
                }
                catch
                {
                    textBox_error.Text = "Error. Can't evaluate invalid inputs.";
                    textBox_part1operand.Focus();
                }
            }
            else if (enterflag == 1)
            {
                try
                {
                    if (textboxfocus == 1)
                        textBox_part2operand.Focus();
                    else
                    {
                        if (Complex.mode == MODE.Rectangular)
                        {
                            secondoperand.Real = double.Parse(textBox_part1operand.Text);
                            secondoperand.Imag = double.Parse(textBox_part2operand.Text);
                        }
                        else
                        {
                            if (double.Parse(textBox_part1operand.Text) < 0)
                                throw new Exception("Magnitude can't be zero.");

                            secondoperand.Magnitude = double.Parse(textBox_part1operand.Text);
                            secondoperand.Angle = double.Parse(textBox_part2operand.Text);
                        }

                        answer = calculateAnswer();

                        if (Complex.mode == MODE.Rectangular)
                        {
                            textBox_part1operand.Text = answer.Real.ToString("F");
                            textBox_part2operand.Text = answer.Imag.ToString("F");
                        }
                        else
                        {
                            textBox_part1operand.Text = answer.Magnitude.ToString("F");
                            textBox_part2operand.Text = answer.Angle.ToString("F");
                        }

                        textBox_Console.Items[consoleline] = firstoperand.ToString() + " " + displayoperation() + " " + secondoperand.ToString() + " = " + answer.ToString();

                        button_setprevoperand.IsEnabled = true;

                        firstoperand = answer;

                        textBox_Console.Items.Add(firstoperand.ToString());

                        disable_numpad();
                        enable_opnumpad();
                        consoleline++;
                    }
                    textBox_error.Text = "";
                }
                catch
                {
                    textBox_error.Text = "Error. Can't evaluate invalid inputs.";
                    textBox_part1operand.Focus();
                }
            }
        }

        private void disable_numpad()
        {
            textBox_part1operand.IsEnabled = false;
            textBox_part2operand.IsEnabled = false;
            button_setprevoperand.IsEnabled = false;
            numberbuttonneg.IsEnabled = false;
            numberbutton0.IsEnabled = false;
            numberbutton1.IsEnabled = false;
            numberbutton2.IsEnabled = false;
            numberbutton3.IsEnabled = false;
            numberbutton4.IsEnabled = false;
            numberbutton5.IsEnabled = false;
            numberbutton6.IsEnabled = false;
            numberbutton7.IsEnabled = false;
            numberbutton8.IsEnabled = false;
            numberbutton9.IsEnabled = false;
            numberbuttondot.IsEnabled = false;
            buttonEnter.IsEnabled = false;
        }

        private void enable_numpad()
        {
            textBox_part1operand.IsEnabled = true;
            textBox_part2operand.IsEnabled = true;
            button_setprevoperand.IsEnabled = true;
            numberbuttonneg.IsEnabled = true;
            numberbutton0.IsEnabled = true;
            numberbutton1.IsEnabled = true;
            numberbutton2.IsEnabled = true;
            numberbutton3.IsEnabled = true;
            numberbutton4.IsEnabled = true;
            numberbutton5.IsEnabled = true;
            numberbutton6.IsEnabled = true;
            numberbutton7.IsEnabled = true;
            numberbutton8.IsEnabled = true;
            numberbutton9.IsEnabled = true;
            numberbuttondot.IsEnabled = true;
            buttonEnter.IsEnabled = true;
        }

        private void disable_opnumpad()
        {
            operationbuttonadd.IsEnabled = false;
            operationbuttondiv.IsEnabled = false;
            operationbuttonmul.IsEnabled = false;
            operationbuttonsub.IsEnabled = false;
        }

        private void enable_opnumpad()
        {
            operationbuttonadd.IsEnabled = true;
            operationbuttondiv.IsEnabled = true;
            operationbuttonmul.IsEnabled = true;
            operationbuttonsub.IsEnabled = true;
        }

        public char displayoperation()
        {
            if (operation == 1)
                return '+';
            else if (operation == 2)
                return '-';
            else if (operation == 3)
                return '*';
            else if (operation == 4)
                return '/';
            else
                return ' ';
        }

        public Complex calculateAnswer()
        {
            if (operation == 1)
                return firstoperand + secondoperand;
            else if (operation == 2)
                return firstoperand - secondoperand;
            else if (operation == 3)
                return firstoperand * secondoperand;
            else
                return firstoperand / secondoperand;
        }

        private void button_setprevoperand_Click(object sender, RoutedEventArgs e)
        {
            if (enterflag == 0)
            {
                try
                {
                    firstoperand = fromListOperand();

                    if (Complex.mode == MODE.Rectangular)
                    {
                        textBox_part1operand.Text = firstoperand.Real.ToString("F");
                        textBox_part2operand.Text = firstoperand.Imag.ToString("F");
                    }
                    else
                    {
                        textBox_part1operand.Text = firstoperand.Magnitude.ToString("F");
                        textBox_part2operand.Text = firstoperand.Angle.ToString("F");
                    }

                    textBox_Console.Items.Add(firstoperand.ToString());

                    button_setprevoperand.IsEnabled = true;

                    disable_numpad();
                    enable_opnumpad();
                    enterflag++;
                }
                catch
                {
                    textBox_error.Text = "Error. Can't evaluate invalid inputs.";
                    textBox_part1operand.Focus();
                }
            }
            else if (enterflag == 1)
            {
                try
                {
                    secondoperand = fromListOperand();

                    answer = calculateAnswer();
                    textBox_Console.Items[consoleline] = firstoperand.ToString() + " " + displayoperation() + " " + secondoperand.ToString() + " = " + answer.ToString();

                    if (Complex.mode == MODE.Rectangular)
                    {
                        textBox_part1operand.Text = answer.Real.ToString("F");
                        textBox_part2operand.Text = answer.Imag.ToString("F");
                    }
                    else
                    {
                        textBox_part1operand.Text = answer.Magnitude.ToString("F");
                        textBox_part2operand.Text = answer.Angle.ToString("F");
                    }

                    firstoperand = answer;

                    textBox_Console.Items.Add(firstoperand.ToString());

                    disable_numpad();
                    enable_opnumpad();
                    consoleline++;
                    textBox_error.Text = "";
                }
                catch
                {
                    textBox_error.Text = "Error. Can't evaluate invalid inputs.";
                    textBox_part1operand.Focus();
                }
            }
        }

        public Complex fromListOperand()
        {
            string extra = listboxanswers.SelectedItem.ToString();
            double num1, num2;
            Complex extracomplex = new Complex();

            extra = extra.Replace("(", "");
            extra = extra.Replace(")", "");
            string[] newinput = extra.Split(' ');

            newinput[2] = newinput[2].Replace("j", "");

            textBox_part1operand.Text = newinput[0];
            textBox_part2operand.Text = newinput[2];

            num1 = double.Parse(newinput[0]);
            num2 = double.Parse(newinput[2]);

            if (newinput[1] == "+")
            {
                extracomplex = new Complex(num1, num2);
            }
            else if (newinput[1] == "-")
            {
                num2 = num2 * -1;
                extracomplex = new Complex(num1, num2);
            }
            else if (newinput[1] == "@")
            {
                extracomplex.Magnitude = num1;
                extracomplex.Angle = num2;
            }
            return extracomplex;
        }

        private void instructionsToolStripMenuItem_Click(object sender, RoutedEventArgs e)
        {
            string aboutString =
                    @"      Instructions:
                1.    Enter real numbers into the two text boxes labeled real/magnitude
                            and imaginary/angle.
                2.    Click Enter or hit Enter on your keyboard to switch to the next text 
                            box, or complete the first operand.
                3.    The operation buttons should enable once the first operand 
                            is entered in, click the operation that you would like to 
                            perform:
 
                            (+ for addition, - for subtraction,
                            * for multiplication, and / for division).

                4.    Now enter more numbers into the two text boxes to represent the
                            second operand. Click enter (repeat step 2).
                5.    The calculation will now be stored as the first operand. Go back to
                            step #3 and repeat.

        NOTE: Pressing the ENTER Key on your keyboard while the focus is on a 
            button will activate the button as if you clicked on it. This way you 
            can tab over to the buttons you need and hit enter for keyboard use only.

     Store Button: 
                    Stores the current entries in the textboxes directly to the right of
                    clear and store buttons. They do not store any values in the console
                    window that appears on the top of the application.

     Clear Button: 
                    Clears the console window, as well as the entries in the two text boxes.
                    Will still keep the entries stored from previous uses.

     Set as operand. Button:
                    Once an item in the listbox is selected, this button should become 
                    available. This button will take the item selected and use it as 
                    the second operand in equation, or the first depending on where in 
                    the equation you are.

     Mode:
                    Two radio buttons control whether the input/output is in polar or
                    rectangular format. Click the radio button you want the input/output
                    to be displayed in. It should change the formating of the console
                    window as well. Changing the mode also changes the stored list.

                    Keyboard instructions: You can use the left or right arrow keyboard
                        buttons to switch between modes easily. Also, you can select one
                        by hitting the enter key when the mode has focus.

    Error Text:
                    Any errors you run into should be shown in the textbox at the bottom.
                    ";

            MessageBox.Show(aboutString);
        }

        private void featuresNotImplementedToolStripMenuItem_Click(object sender, RoutedEventArgs e)
        {
            string aboutString =
                    @"      Features Not Implemented:

                        The listbox that stores data doesn't change the look of it's
                        items when the mode is changed, but when doing calculations, the 
                        program will calculate them in the mode that is activated, 
                        regardless of what mode the value was stored in. It won't 
                        affect the calculation.

                        You must scroll down in the console window to see 
                        your current equation.
        
                        SelectionStart for textboxes works differently in XAML and I couldn't
                        figure out how to get it working. This means that trying to insert
                        numbers into the middle of a number that has been typed out will
                        result in an unwanted outcome. Numbers being added will always
                        go to the end of the textbox. This will only do it for clicking 
                        buttons. You can insert numbers using the keyboard.";

            MessageBox.Show(aboutString);
        }

        private void textBox_part1operand_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                textBox_part2operand.Focus();
        }

        private void listboxanswers_SelectedValueChanged(object sender, RoutedEventArgs e)
        {
            button_setprevoperand.IsEnabled = true;
        }

        private void textBox_part1operand_MouseEnter(object sender, MouseEventArgs e)
        {
            index = textBox_part1operand.SelectionStart;
        }

        private void textBox_part2operand_MouseEnter(object sender, MouseEventArgs e)
        {
            index = textBox_part2operand.SelectionStart;
        }

        private void textBox_part2operand_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                if (enterflag == 0)
                {
                    try
                    {
                        if (textboxfocus == 1)
                            textBox_part2operand.Focus();
                        else
                        {
                            if (Complex.mode == MODE.Rectangular)
                            {
                                firstoperand.Real = double.Parse(textBox_part1operand.Text);
                                firstoperand.Imag = double.Parse(textBox_part2operand.Text);
                            }
                            else
                            {
                                if (double.Parse(textBox_part1operand.Text) < 0)
                                    throw new Exception("Magnitude can't be less than 0.");

                                firstoperand.Magnitude = double.Parse(textBox_part1operand.Text);
                                firstoperand.Angle = double.Parse(textBox_part2operand.Text);
                            }

                            textBox_part1operand.Text = firstoperand.Real.ToString("F");
                            textBox_part2operand.Text = firstoperand.Imag.ToString("F");

                            textBox_Console.Items.Add(firstoperand.ToString());
                            enable_opnumpad();
                            disable_numpad();
                            enterflag = 1;
                        }
                        textBox_error.Text = "";
                    }
                    catch
                    {
                        textBox_error.Text = "Error. Can't evaluate invalid inputs.";
                        textBox_part1operand.Focus();
                    }
                }
                else if (enterflag == 1)
                {
                    try
                    {
                        if (textboxfocus == 1)
                            textBox_part2operand.Focus();
                        else
                        {
                            if (Complex.mode == MODE.Rectangular)
                            {
                                secondoperand.Real = double.Parse(textBox_part1operand.Text);
                                secondoperand.Imag = double.Parse(textBox_part2operand.Text);
                            }
                            else
                            {
                                if (double.Parse(textBox_part1operand.Text) < 0)
                                    throw new Exception("Magnitude can't be zero.");

                                secondoperand.Magnitude = double.Parse(textBox_part1operand.Text);
                                secondoperand.Angle = double.Parse(textBox_part2operand.Text);
                            }

                            answer = calculateAnswer();

                            if (Complex.mode == MODE.Rectangular)
                            {
                                textBox_part1operand.Text = answer.Real.ToString("F");
                                textBox_part2operand.Text = answer.Imag.ToString("F");
                            }
                            else
                            {
                                textBox_part1operand.Text = answer.Magnitude.ToString("F");
                                textBox_part2operand.Text = answer.Angle.ToString("F");
                            }

                            textBox_Console.Items[consoleline] = firstoperand.ToString() + " " + displayoperation() + " " + secondoperand.ToString() + " = " + answer.ToString();

                            button_setprevoperand.IsEnabled = true;

                            firstoperand = answer;

                            textBox_Console.Items.Add(firstoperand.ToString());

                            disable_numpad();
                            enable_opnumpad();
                            consoleline++;
                        }
                        textBox_error.Text = "";
                    }
                    catch
                    {
                        textBox_error.Text = "Error. Can't evaluate invalid inputs.";
                        textBox_part1operand.Focus();
                    }
                }
            }
        }

        private void radiopolar_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                radiopolar.IsChecked = true;
                radiorectangular.IsTabStop = true;
            }
            else if (e.Key == Key.Right)
            {
                radiorectangular.IsChecked = true;
                radiorectangular.Focus();
            }
        }

        private void radiorectangular_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                radiorectangular.IsChecked = true;
                radiopolar.IsTabStop = true;
            }
            else if (e.Key == Key.Left)
            {
                radiopolar.IsChecked = true;
                radiopolar.Focus();
            }
        }
    }
}
