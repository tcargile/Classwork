using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApplication2
{
	class Program2
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Enter Main");
			try
			{
                Console.WriteLine("Enter Main try block");
                method1();
                Console.WriteLine("Exit Main try block");
			}
			//Console.WriteLine("Between try and catch");	// compiler error
			catch
			{
				Console.WriteLine("In Main catch block");
			}
			Console.WriteLine("Exit Main");
		}

		public static void method1()
		{
			Console.WriteLine("Enter method1");

            //method2();
            try
            {
                Console.WriteLine("Enter method1 try block");
                method2();
                Console.WriteLine("Exit method1 try block");
            }
            //Console.WriteLine("Between try and catch");	// compiler error
            catch
            {
                Console.WriteLine("In method1 catch block");
            }

			Console.WriteLine("Exit method1");
		}

		public static void method2()
		{
			Console.WriteLine("Enter method2");

			Console.Write("Enter divisor: ");
			int divisor = int.Parse(Console.ReadLine());
			int result = 12 / divisor;

			Console.WriteLine("Exit method2");
		}
	}
}
