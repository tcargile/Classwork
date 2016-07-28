//Trevor Cargile
//813542789
//LAB 3 - CompE361
//Dr. Marino

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ComplexNumbers
{
    class ComplexCalc : Complex
    {
        public void runCalculator()
        {
            string input = "", operation;
            double real = 0, imag = 0;
            int x = 0, time = 0;

            Complex first = new Complex(), second = new Complex(), combined = new Complex();

        start:
            while (true)
            {
                time = 0;
                input = "";

                Console.WriteLine("Enter operand1: ");
                if (mode == MODE.Rectangular)
                {
                    try
                    {
                        Console.Write("\treal part: ");
                        input = Console.ReadLine();

                        real = double.Parse(input);

                        Console.Write("\timaginary part: ");
                        input = Console.ReadLine();

                        imag = double.Parse(input);
                    }
                    catch
                    {
                        if (input == "M" || input == "A" || input == "R" || input == "I")
                        {
                            Console.WriteLine("Operation not valid until operand 1 is made.\n" +
                                                    "Please enter a number.");
                            goto start;
                        }
                        else
                        {
                            x = inputCheck(input, first, time);
                            if (x == 0)
                                Environment.Exit(0);
                            else
                                goto start;
                        }
                    }

                    first = new Complex(real, imag);
                    Console.WriteLine("operand1: {0}", first);
                }
                else
                {
                    try
                    {
                        Console.Write("\tmagnitude: ");
                        input = Console.ReadLine();

                        first.Magnitude = double.Parse(input);

                        Console.Write("\tangle: ");
                        input = Console.ReadLine();

                        first.Angle = double.Parse(input);
                    }
                    catch
                    {
                        if (input == "M" || input == "A" || input == "R" || input == "I")
                        {
                            Console.WriteLine("Operation not valid until operand 1 is made.\n" +
                                                    "Please enter a number.");
                            goto start;
                        }
                        else
                        {
                            x = inputCheck(input, first, time);
                            if (x == 0)
                                Environment.Exit(0);
                            else
                                goto start;
                        }
                    }

                    Console.WriteLine("operand1: {0}", first);
                }

            operation:
                time = 1;

                Console.Write("Operation: ");
                operation = Console.ReadLine();

                try
                {
                    if (operation != "+" && operation != "-" && operation != "*" && operation != "/")
                        throw new Exception("Operation is not one of four, needs further testing.");
                }
                catch
                {
                    if (operation == "c" || operation == "q" || operation == "m" || operation == "p" || operation == "r")
                    {
                        x = inputCheck(operation, first, time);
                        if (x == 1)
                            goto start;
                        else
                            goto operation;
                    }
                    else
                        alterCheck(operation, first);

                    goto operation;
                }

            operand2:
                input = "";

                Console.WriteLine("Enter operand2: ");
                if (mode == MODE.Rectangular)
                {
                    try
                    {
                        Console.Write("\treal part: ");
                        input = Console.ReadLine();

                        real = double.Parse(input);

                        Console.Write("\timaginary part: ");
                        input = Console.ReadLine();

                        imag = double.Parse(input);
                    }

                    catch
                    {
                        if (input == "M" || input == "A" || input == "R" || input == "I")
                        {
                            Console.WriteLine("Operation not valid for operand2.");
                            goto operand2;
                        }
                        else
                        {
                            x = inputCheck(input, first, time);
                            if (x == 1)
                                goto start;
                            else
                                goto operand2;
                        }
                    }

                    second = new Complex(real, imag);
                }
                else
                {
                    try
                    {
                        Console.Write("\tmagnitude: ");
                        input = Console.ReadLine();

                        second.Magnitude = double.Parse(input);

                        Console.Write("\tangle: ");
                        input = Console.ReadLine();

                        second.Angle = double.Parse(input);
                    }

                    catch
                    {
                        if (input == "M" || input == "A" || input == "R" || input == "I")
                        {
                            Console.WriteLine("Operation not valid for operand2.");
                            goto operand2;
                        }
                        else
                        {
                            x = inputCheck(input, second, time);
                            if (x == 1)
                                goto start;
                            else
                                goto operand2;
                        }
                    }
                }

                if (operation == "+")
                {
                    combined = first + second;
                    Console.WriteLine("({0}) + ({1}) = ({2})", first, second, combined);

                    first = combined;
                    Console.WriteLine("operand1: {0}", first);
                    goto operation;
                }
                else if (operation == "-")
                {
                    combined = first - second;
                    Console.WriteLine("({0}) - ({1}) = ({2})", first, second, combined);

                    first = combined;
                    Console.WriteLine("operand1: {0}", first);
                    goto operation;
                }
                else if (operation == "*")
                {
                    combined = first * second;
                    Console.WriteLine("({0}) * ({1}) = ({2})", first, second, combined);

                    first = combined;
                    Console.WriteLine("operand1: {0}", first);
                    goto operation;
                }
                else
                {
                    combined = first / second;
                    Console.WriteLine("({0}) / ({1}) = ({2})", first, second, combined);

                    first = combined;
                    Console.WriteLine("operand1: {0}", first);
                    goto operation;
                }
            }
        }

        private static int inputCheck(string input, Complex num, int time)
        {
            if (input == "c")
            {
                Console.WriteLine("Calculator cleared.");
                return 1;
            }
            else if (input == "q")
            {
                Console.WriteLine("Exiting the calculator.");
                Environment.Exit(0);
                return 0;
            }
            else if (input == "m")
            {
                Complex.displayMenu();
                return 2;
            }
            else if (input == "p")
            {
                if (mode == MODE.Polar)
                    Console.WriteLine("Calculator already in Polar mode.");
                else
                {
                    Console.WriteLine("Calculator changed to Polar mode.");
                    mode = MODE.Polar;
                }

                if (time != 0)
                    Console.WriteLine("operand1: {0}", num);
                return 2;
            }
            else if (input == "r")
            {
                if (mode == MODE.Rectangular)
                    Console.WriteLine("Calculator already in Rectangular mode.");
                else
                {
                    Console.WriteLine("Calculator changed to Rectangular mode.");
                    mode = MODE.Rectangular;
                }

                if (time != 0)
                    Console.WriteLine("operand1: {0}", num);
                return 2;
            }
            else
            {
                Console.WriteLine("Error: Enter a number.");
                return 2;
            }
        }

        private static void alterCheck(string input, Complex num)
        {
            if (input == "M")
            {
                Console.Write("{0} : ", num.Magnitude);
                input = Console.ReadLine();

                if (input == "")
                {
                    Console.WriteLine("operand1: {0}", num);
                }
                else
                {
                    try
                    {
                        num.Magnitude = double.Parse(input);
                        Console.WriteLine("operand1: {0}", num);
                    }
                    catch
                    {
                        Console.WriteLine("Error: Invalid Input.");
                    }
                }
            }
            else if (input == "A")
            {
                Console.Write("{0} : ", num.Angle);
                input = Console.ReadLine();

                if (input == "")
                {
                    Console.WriteLine("operand1: {0}", num);
                }
                else
                {
                    try
                    {
                        num.Angle = double.Parse(input);
                        Console.WriteLine("operand1: {0}", num);
                    }
                    catch
                    {
                        Console.WriteLine("Error: Invalid Input.");
                    }
                }
            }
            else if (input == "R")
            {
                Console.Write("{0} : ", num.Real);
                input = Console.ReadLine();

                if (input == "")
                {
                    Console.WriteLine("operand1: {0}", num);
                }
                else
                {
                    try
                    {
                        num.Real = double.Parse(input);
                        Console.WriteLine("operand1: {0}", num);
                    }
                    catch
                    {
                        Console.WriteLine("Error: Invalid Input.");
                    }
                }
            }
            else if (input == "I")
            {
                Console.Write("{0} : ", num.Imag);
                input = Console.ReadLine();

                if (input == "")
                {
                    Console.WriteLine("operand1: {0}", num);
                }
                else
                {
                    try
                    {
                        num.Imag = double.Parse(input);
                        Console.WriteLine("operand1: {0}", num);
                    }
                    catch
                    {
                        Console.WriteLine("Error: Invalid Input.");
                    }
                }
            }
            else
            {
                Console.WriteLine("Error! Enter an operation.\n" +
                            "Options are: c, +, -, *, /, p, r, m, q, M, A, R, I");
                Console.WriteLine("operand1 : {0}", num);
            }
        }
    }
}
