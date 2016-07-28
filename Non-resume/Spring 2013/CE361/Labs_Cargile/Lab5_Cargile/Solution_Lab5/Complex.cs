//Trevor Cargile
//813542789
//LAB 5 - CompE361
//Dr. Marino

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
    public enum MODE { Rectangular, Polar }

    public class Complex : Form
    {
        private double real;
        private double imag;

        public static MODE mode = MODE.Rectangular;

        public Complex(double re, double im)
        {
            real = re;
            imag = im;
        }

        public Complex()
        {
            real = 0;
            imag = 0;
        }

        public double Real
        {
            get { return real; }
            set { real = value; }
        }

        public double Imag
        {
            get { return imag; }
            set { imag = value; }
        }

        public double Magnitude
        {
            get { return Math.Sqrt(imag * imag + real * real); }
            set
            {
                if (value < 0)
                    Console.WriteLine("Magnitude can't be a negative number.");
                else
                {
                    double angle = Angle;
                    real = value * Math.Cos(angle * Math.PI / 180);
                    imag = value * Math.Sin(angle * Math.PI / 180);
                }
            }
        }

        public double Angle //Sets or returns the angle part of a Complex variable
        {
            get	//returns angle in degrees, between -180 and +180
            {
                double angle = Math.Atan2(imag, real); // Angle in radians, between -pi and +pi

                return angle * 180 / Math.PI;   // Convert to degrees
            }
            set	// assumes value is in degrees
            {
                double magnitude = Magnitude;
                real = Math.Sqrt(magnitude * magnitude / (1 + Math.Tan(value * Math.PI / 180) * Math.Tan(value * Math.PI / 180)));
                imag = Math.Sqrt(magnitude * magnitude * Math.Tan(value * Math.PI / 180) * Math.Tan(value * Math.PI / 180) / (1 + Math.Tan(value * Math.PI / 180) * Math.Tan(value * Math.PI / 180)));

                while (value >= 360)    //Keeps the angle entered below or at 360 degrees if greater than 360 degrees
                    value -= 360;

                while (value <= -360)   //Keeps the angle entered above or at -360 degrees if less than -360 degrees
                    value += 360;

                if ((value < 0 && value > -180) || (value > 180 && value < 360))    //Checks if the imaginary part should be negative
                    imag = -imag;
                if (value > 90 && value < 270 || value < -90 && value > -270)       //Checks if the real part should be negative
                    real = -real;
            }
        }


        public override string ToString()
        {
            if (mode == MODE.Rectangular)
            {
                if (imag < 0)
                    return String.Format("({0:F2} - j{1:F2})", real, -imag);
                else
                    return String.Format("({0:F2} + j{1:F2})", real, imag);
            }
            else
            {
                return String.Format("({0:F2} @ {1:F2})", Magnitude, Angle);
            }
        }

        public static Complex operator +(Complex x, Complex y)
        {
            return new Complex(x.real + y.real, x.imag + y.imag);
        }

        public static Complex operator -(Complex x, Complex y)
        {
            return new Complex(x.real - y.real, x.imag - y.imag);
        }

        public static Complex operator *(Complex x, Complex y)
        {
            return new Complex((x.real * y.real) - (x.imag * y.imag), (x.real * y.imag) + (x.imag * y.real));
        }

        public static Complex operator /(Complex x, Complex y)
        {
            Complex conjugate = new Complex(y.real, -y.imag);

            x = x * conjugate;
            y = y * conjugate;

            return new Complex(x.real / y.real, x.imag / y.real);
        }

        //public static void displayMenu()
        //{
        //    Console.WriteLine("-----------------------------\n" +
        //            "Complex Number Calculator:\n\t(c)\tClear\n\t(+)\tAdd\n\t(-)\tSubtract\n\t(*)" +
        //            "\tMultiply\n\t(/)\tDivide\n\t(p)\tPolar\n\t(r)\tRectangular\n\t(m)\tMenu\n\t(q)" +
        //            "\tQuit\n\t(M)\tMagnitude\n\t(A)\tAngle\n\t(R)\tReal\n\t(I)\tImaginary\n" +
        //            "-----------------------------");
        //}

    }   // end class Complex

}   // end namespace ComplexClass