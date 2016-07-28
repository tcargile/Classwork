using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ComplexCalculator
{
    public partial class Calculator : Complex
    {
        int textboxfocus = 1;
        int operation = 0;
        int enterflag;
        int consoleline = 0;
        int index;
        Complex firstoperand = new Complex();
        Complex secondoperand = new Complex();
        Complex answer = new Complex();
        Complex storedopearnd = new Complex();

        public Calculator()
        {
            InitializeComponent();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            Part1AnswerTypeLabel.Text = "Magnitude";
            Part2AnswerTypeLabel.Text = "Angle";

            mode = MODE.Polar;

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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            Part1AnswerTypeLabel.Text = "Real";
            Part2AnswerTypeLabel.Text = "Imaginary";

            mode = MODE.Rectangular;

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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;
        }

        private void textBox_GotFocus(object sender, EventArgs e)
        {
            if (sender.Equals(textBox_part1operand))
                textboxfocus = 1;
            else if (sender.Equals(textBox_part2operand))
                textboxfocus = 2;
        }

        private void operationbuttonadd_Click(object sender, EventArgs e)
        {
            operation = 1;
            textBox_Console.Items[consoleline] = textBox_Console.Items[consoleline] + " + ";
            disable_opnumpad();
            enable_numpad();

            textBox_part1operand.Focus();
            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void operationbuttonsub_Click(object sender, EventArgs e)
        {
            operation = 2;
            textBox_Console.Items[consoleline] = textBox_Console.Items[consoleline] + " - ";
            disable_opnumpad();
            enable_numpad();

            textBox_part1operand.Focus();
            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void operationbuttonmul_Click(object sender, EventArgs e)
        {
            operation = 3;
            textBox_Console.Items[consoleline] = textBox_Console.Items[consoleline] + " * ";
            disable_opnumpad();
            enable_numpad();

            textBox_part1operand.Focus();
            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void operationbuttondiv_Click(object sender, EventArgs e)
        {
            operation = 4;
            textBox_Console.Items[consoleline] = textBox_Console.Items[consoleline] + " / ";
            disable_opnumpad();
            enable_numpad();

            textBox_part1operand.Focus();
            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void numberbuttondot_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbuttonneg_Click(object sender, EventArgs e)
        {
            if (textboxfocus == 1)
            {
                if (textBox_part1operand.Text.Contains('-'))
                    textBox_part1operand.Text = textBox_part1operand.Text.Replace("-", "");
                else
                    textBox_part1operand.Text = "-" + textBox_part1operand.Text;
            }
            else if (textboxfocus == 2)
            {
                if (textBox_part2operand.Text.Contains('-'))
                    textBox_part2operand.Text = textBox_part2operand.Text.Replace("-", "");
                else
                    textBox_part2operand.Text = "-" + textBox_part2operand.Text;
            }

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
        }

        private void numberbutton1_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton2_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton3_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton4_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton5_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton6_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton7_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton8_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton9_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void numberbutton0_Click(object sender, EventArgs e)
        {
            if (textBox_part1operand.SelectionLength == textBox_part1operand.TextLength && textboxfocus == 1 && textBox_part1operand.TextLength != 0)
            {
                textBox_part1operand.Text = "";
                index = 0;
            }
            else if (textBox_part2operand.SelectionLength == textBox_part2operand.TextLength && textboxfocus == 2 && textBox_part2operand.TextLength != 0)
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

            if (consoleline > 2)
                textBox_Console.TopIndex = consoleline - 1;

            textBox_error.Text = "";
            index++;
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            textBox_part1operand.Text = "";
            textBox_part2operand.Text = "";
            textBox_Console.Items.Clear();

            enterflag = 0;

            enable_numpad();
            disable_opnumpad();

            consoleline = 0;
            textBox_part1operand.Focus();
            textBox_Console.TopIndex = consoleline;
            textBox_error.Text = "";
            operation = 0;
        }

        private void buttonStore_Click(object sender, EventArgs e)
        {
            try
            {
                if (mode == MODE.Rectangular)
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

                if (consoleline > 2)
                    textBox_Console.TopIndex = consoleline - 1;
                textBox_error.Text = "";
            }
            catch
            {
                textBox_error.Text = "Error. Can't store invalid inputs.";
                textBox_part1operand.Focus();
            }
        }

        private void buttonEnter_Click(object sender, EventArgs e)
        {
            if (enterflag == 0)
            {
                try
                {
                    if (textboxfocus == 1)
                    {
                        textBox_part2operand.Focus();
                        index = textBox_part2operand.TextLength;
                    }
                    else
                    {
                        if (mode == MODE.Rectangular)
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
                        if (mode == MODE.Rectangular)
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

                        if (mode == MODE.Rectangular)
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

                        button_setprevoperand.Enabled = true;

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
            textBox_part1operand.Enabled = false;
            textBox_part2operand.Enabled = false;
            button_setprevoperand.Enabled = false;
            numberbuttonneg.Enabled = false;
            numberbutton0.Enabled = false;
            numberbutton1.Enabled = false;
            numberbutton2.Enabled = false;
            numberbutton3.Enabled = false;
            numberbutton4.Enabled = false;
            numberbutton5.Enabled = false;
            numberbutton6.Enabled = false;
            numberbutton7.Enabled = false;
            numberbutton8.Enabled = false;
            numberbutton9.Enabled = false;
            numberbuttondot.Enabled = false;
            buttonEnter.Enabled = false;
        }

        private void enable_numpad()
        {
            textBox_part1operand.Enabled = true;
            textBox_part2operand.Enabled = true;
            button_setprevoperand.Enabled = true;
            numberbuttonneg.Enabled = true;
            numberbutton0.Enabled = true;
            numberbutton1.Enabled = true;
            numberbutton2.Enabled = true;
            numberbutton3.Enabled = true;
            numberbutton4.Enabled = true;
            numberbutton5.Enabled = true;
            numberbutton6.Enabled = true;
            numberbutton7.Enabled = true;
            numberbutton8.Enabled = true;
            numberbutton9.Enabled = true;
            numberbuttondot.Enabled = true;
            buttonEnter.Enabled = true;
        }

        private void disable_opnumpad()
        {
            operationbuttonadd.Enabled = false;
            operationbuttondiv.Enabled = false;
            operationbuttonmul.Enabled = false;
            operationbuttonsub.Enabled = false;
        }

        private void enable_opnumpad()
        {
            operationbuttonadd.Enabled = true;
            operationbuttondiv.Enabled = true;
            operationbuttonmul.Enabled = true;
            operationbuttonsub.Enabled = true;
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

        private void button_setprevoperand_Click(object sender, EventArgs e)
        {
            if (enterflag == 0)
            {
                try
                {
                    firstoperand = fromListOperand();

                    if (mode == MODE.Rectangular)
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

                    button_setprevoperand.Enabled = true;

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

                    if (mode == MODE.Rectangular)
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

        private void instructionsToolStripMenuItem_Click(object sender, EventArgs e)
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
                    If you run into any problems, the text box at the bottom of the
                    application should prompt you with an error message.
                    ";

            MessageBox.Show(aboutString);
        }

        private void featuresNotImplementedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string aboutString =
                    @"      Features Not Implemented:
                        The listbox that stores data doesn't change the look of it's
                        items when the mode is changed, but when doing calculations, the 
                        program will calculate them in the mode that is activated, 
                        regardless of what mode the value was stored in. It won't 
                        affect the calculation.";

            MessageBox.Show(aboutString);
        }

        private void textBox_part1operand_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                textBox_part2operand.Focus();
        }

        private void listboxanswers_SelectedValueChanged(object sender, EventArgs e)
        {
            button_setprevoperand.Enabled = true;
        }

        private void textBox_part1operand_MouseClick(object sender, MouseEventArgs e)
        {
            index = textBox_part1operand.SelectionStart;
        }

        private void textBox_part2operand_MouseClick(object sender, MouseEventArgs e)
        {
            index = textBox_part2operand.SelectionStart;
        }

        private void textBox_part2operand_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (enterflag == 0)
                {
                    try
                    {
                        if (textboxfocus == 1)
                            textBox_part2operand.Focus();
                        else
                        {
                            if (mode == MODE.Rectangular)
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
                            if (mode == MODE.Rectangular)
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

                            if (mode == MODE.Rectangular)
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

                            button_setprevoperand.Enabled = true;

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
            if (e.KeyCode == Keys.Enter)
            {
                radiopolar.Checked = true;
                radiorectangular.TabStop = true;
            }
            else if (e.KeyCode == Keys.Right)
            {
                radiorectangular.Checked = true;
                radiorectangular.Focus();
            }
        }

        private void radiorectangular_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                radiorectangular.Checked = true;
                radiopolar.TabStop = true;
            }
            else if (e.KeyCode == Keys.Left)
            {
                radiopolar.Checked = true;
                radiopolar.Focus();
            }
        }
    }
}
