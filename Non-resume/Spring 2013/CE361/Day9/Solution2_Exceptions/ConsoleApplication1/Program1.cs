using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApplication1
{
	class Program1
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Enter Main");

			method1();

			Console.WriteLine("Exit Main");
		}

		public static void method1()
		{
			Console.WriteLine("Enter method1");

			method2();

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

/***************** Sample run without exception *******************************
Enter Main
Enter method1
Enter method2
Enter divisor: 2
Exit method2
Exit method1
Exit Main
Press any key to continue . . .
*****************************************************************************/

/***************** Sample run with exception *******************************
Enter Main
Enter method1
Enter method2
Enter divisor: 0

Unhandled Exception: System.DivideByZeroException: Attempted to divide by zero.
   at ConsoleApplication1.Program.method2() in K:\Courses\CompE361\S07\Progs\Prep\Day8\Solution2_Day
8\ConsoleApplication1\Program.cs:line 33
   at ConsoleApplication1.Program.method1() in K:\Courses\CompE361\S07\Progs\Prep\Day8\Solution2_Day
8\ConsoleApplication1\Program.cs:line 22
   at ConsoleApplication1.Program.Main(String[] args) in K:\Courses\CompE361\S07\Progs\Prep\Day8\Sol
ution2_Day8\ConsoleApplication1\Program.cs:line 13
Press any key to continue . . .
*****************************************************************************/
