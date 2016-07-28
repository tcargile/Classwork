using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApplication4
{
	class Program4
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Enter Main");
			try
			{
				method1();
			}
			//Console.WriteLine("Between try and catch");	// compiler error
			catch (Exception e)
			{
				Console.WriteLine("In Main catch block");
				Console.WriteLine(e.Message);
				Console.WriteLine(e.Source);
			}
			Console.WriteLine("In Main after catch block");
			Console.WriteLine("Exit Main");
		}

		public static void method1()
		{
			Console.WriteLine("Enter method1");
			try
			{
				Console.WriteLine("Enter method1 try block");
				method2();
                Console.WriteLine("Exit method1 try block");
            }
			//Console.WriteLine("between try and finally, method2");	// compiler error
			finally
			{
				Console.WriteLine("In method1 finally block");
			}
			Console.WriteLine("After method1 finally block");
			Console.WriteLine("Exit method1");
		}

		public static void method2()
		{
			Console.WriteLine("Enter method2");
            try
            {
                Console.WriteLine("Enter method2 try block");

                Console.Write("Enter divisor: ");
                int divisor = int.Parse(Console.ReadLine());
                int result = 12 / divisor;

                Console.WriteLine("Exit method2 try block");
            }
            catch (DivideByZeroException e)
            {
                Console.WriteLine("In method2 catch block");
                Console.WriteLine(e.Message);
            }
			finally
			{
				Console.WriteLine("In method2 finally block");
			}
			Console.WriteLine("After method2 finally block");
			Console.WriteLine("Exit method2");
		}
	}
}
