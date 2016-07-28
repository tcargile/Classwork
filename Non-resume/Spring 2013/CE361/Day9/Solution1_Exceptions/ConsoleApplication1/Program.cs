using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;


namespace ConsoleApplication1
{
	class Program
	{

		static void Main(string[] args)
		{
			/* Main illustrates various error sources.
			 * Uncomment one block at a time and try to build and run.
			 */
			int n;
			string s;


			////////// Assignment error /////////////
            //n = int.MaxValue + 1;

			
			////////// Integer overflow /////////////
            //Integer arithmetic will be checked for overflow in the following block  
            //checked
            //{
            //    n = int.MaxValue;
            //    n += 1;
            //}
            //Console.WriteLine("n = " + n);
			////// There is also a global checked flag:
			////// RtClk Project > Properties > Build > Advanced
			////// Keyword unchecked disables integer overflow checking




			////////// Parse error /////////////////
            //Console.Write("Enter integer n: ");
            //s = Console.ReadLine();
            //n = int.Parse(s);
            //Console.WriteLine("n = " + n);



			/////////// New way to handle parse errors (.NET 2005)
            //// Handled with try-catch in .NET 2000 and .NET 2003
            //Console.Write("Enter integer n: ");
            //s = Console.ReadLine();
            //while (!int.TryParse(s, out n))
            //{
            //    Console.WriteLine("Input error");
            //    Console.Write("Enter integer n: ");
            //    s = Console.ReadLine();
            //}
            //Console.WriteLine("n = " + n);




            ////////// Programmer-defined error /////////////////
            //Console.Write("Enter circle radius: ");
            //double radius = Convert.ToDouble(Console.ReadLine());
            //if (radius < 0)
            //    throw new Exception("Error - negative radius");


            //////////// Array Bounds Error ///////////////
            //int[] x = new int[3];
            //for (int i = 0; i < 4; i++)
            //    Console.WriteLine("x[{0}] = {1}", i, x[i]);



            //////////// Handling errors with try-catch ///////////////
            //////Can handle error as desired and continue with program
            //try
            //{
            //    // Array bounds error
            //    int[] x = new int[3];
            //    for (int i = 0; i < 4; i++)
            //        Console.WriteLine("x[{0}] = {1}", i, x[i]);

            //}
            //catch
            //{
            //    Console.WriteLine("Array bounds error");
            //    Console.WriteLine("Can add code here in catch block to do whatever you want");
            //}





            ////////// try block with multiple error possibilities ///////////
            ////////// All handled by a single catch block ///////////
            //try
            //{
            //    // Possible integer overflow or invalid format error
            //    Console.Write("Enter integer: ");
            //    s = Console.ReadLine();
            //    n = int.Parse(s);
            //    checked
            //    {
            //        n = n * n;
            //    }

            //    ////////// Array Bounds Error ///////////////
            //    int[] x = new int[3];
            //    for (int i = 0; i < 4; i++)
            //        Console.WriteLine("x[{0}] = {1}", i, x[i]);
            //}
            //catch (Exception e)
            //{
            //    Console.WriteLine(e.Message);
            //}



            ////////// try block with multiple error possibilities ////////////////////
            ////////// Multiple catch blocks for different error types //////////////
            ////////// Last catch block is generic - catches any other errors //////////////
            try
            {
                //// Possible integer overflow or invalid format error
                Console.Write("Enter integer: ");
                s = Console.ReadLine();
                n = int.Parse(s);
                Console.WriteLine("n * n = " + n * n);
                checked
                {
                    int m = n * n;
                }
                //// Array bounds error
                int[] x = new int[3];
                for (int i = 0; i < n; i++)
                    Console.WriteLine("x[{0}] = {1}", i, x[i]);

            }	// end try block

            catch (System.IndexOutOfRangeException e)
            {
                Console.WriteLine("INDEX OUT OF RANGE EXCEPTION");
                Console.WriteLine(e.Message);
            }
            catch (System.OverflowException e)
            {
                Console.WriteLine("INTEGER OVERFLOW EXCEPTION");
                Console.WriteLine(e.Message);
            }
            catch (Exception e)
            {
                Console.WriteLine("OTHER EXCEPTION");
                Console.WriteLine(e.Message);
            }

			Console.WriteLine("Program continues.");


		} // end Main
	} // end class Program
} // end namespace 
