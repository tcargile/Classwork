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
    class Program
    {
        static void Main(string[] args)
        {
            Complex.displayMenu();

            ComplexCalc num = new ComplexCalc();
            num.runCalculator();
        }
    }
}