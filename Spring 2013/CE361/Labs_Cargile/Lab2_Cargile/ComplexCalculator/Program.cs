//Trevor Cargile
//813542789
//CompE361 - Lab 2


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Numerics;

namespace ComplexCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("-----------------------------\n" +
                    "Complex Number Calculator:\n\t(c)\tClear\n\t(+)\tAdd\n\t(-)\tSubtract\n\t(*)" +
                    "\tMultiply\n\t(/)\tDivide\n\t(m)\tMenu\n\t(q)\tQuit\n\n" +
                    "Operation entry: c, +, -, *, /, m. or q\n" +
                    "Operand entry: REAL IMAGINARY\n" +
                    "-----------------------------");

            runCalculator();
        }

        public static int runCalculator()
        {
            string first, operation, second;
            Complex ifirst, isecond;

        Beginning:
            Console.Write("\nEnter first operand: ");
            first = Console.ReadLine();

            if (first == "m")
            {
                displayMenu();
                goto Beginning;
            }
            else if (first == "c")
            {
                Console.WriteLine("Calculator cleared.");
                goto Beginning;
            }
            else if (first == "q")
            {
                Console.WriteLine("Exiting calculator.");
                Environment.Exit(0);
            }

            ifirst = StringToComplex(first);
            Console.WriteLine("operand 1 = {0}", ifirst);

        Continued:
            Console.Write("Enter operation: ");
            operation = Console.ReadLine();

            if (operation == "m")
            {
                displayMenu();
                goto Continued;
            }
            else if (operation == "c")
            {
                Console.WriteLine("Calculator cleared.");
                goto Beginning;
            }
            else if (operation == "q")
            {
                Console.WriteLine("Exiting calculator.");
                Environment.Exit(0);
            }

        Next:
            Console.Write("Enter second operand: ");
            second = Console.ReadLine();

            if (second == "m")
            {
                displayMenu();
                goto Next;
            }
            else if (second == "c")
            {
                Console.WriteLine("Calculator cleared.");
                goto Beginning;
            }
            else if (second == "q")
            {
                Console.WriteLine("Exiting calculator.");
                Environment.Exit(0);
            }

            isecond = StringToComplex(second);

            ifirst = checkOperator(operation, ifirst, isecond);

            Console.WriteLine("operand 1 = {0}", ifirst);
            goto Continued;
        }

        public static void displayMenu()
        {
            Console.WriteLine("-----------------------------\n" +
                    "Complex Number Calculator:\n\t(c)\tClear\n\t(+)\tAdd\n\t(-)\tSubtract\n\t(*)" +
                    "\tMultiply\n\t(/)\tDivide\n\t(m)\tMenu\n\t(q)\tQuit\n\n" +
                    "Operation entry: c, +, -, *, /, m. or q\n" +
                    "Operand entry: REAL IMAGINARY\n" +
                    "-----------------------------");
        }

        public static Complex checkOperator(string operation, Complex first, Complex second)
        {
            Complex combined = new Complex();
            if (operation == "+")
                combined = addComplex(first, second);
            else if (operation == "-")
                combined = subComplex(first, second);
            else if (operation == "*")
                combined = mulComplex(first, second);
            else if (operation == "/")
                combined = divComplex(first, second);

            Console.WriteLine("{0} {1} {2} = {3}", first, operation, second, combined);

            return combined;
        }

        public static Complex StringToComplex(string input)
        {
            double num1, num2;
            string[] newinput = input.Split(' ');

            num1 = double.Parse(newinput[0]);
            num2 = double.Parse(newinput[1]);

            Complex converted = new Complex(num1, num2);

            return converted;
        }

        public static Complex addComplex(Complex first, Complex second)
        {
            Complex sum;
            sum = Complex.Add(first, second);
            return sum;
        }

        public static Complex subComplex(Complex first, Complex second)
        {
            Complex sub;
            sub = Complex.Subtract(first, second);
            return sub;
        }

        public static Complex mulComplex(Complex first, Complex second)
        {
            Complex mul;
            mul = Complex.Multiply(first, second);
            return mul;
        }

        public static Complex divComplex(Complex first, Complex second)
        {
            Complex div;
            div = Complex.Divide(first, second);
            return div;
        }
    }
}
