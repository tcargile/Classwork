//Trevor Cargile
//813542789
//CompE361 - Marino
//Project: Conversion Lab 1
//Due Date: September 6th, 2012

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Conversions
{
    class Program
    {
        static void Main(string[] args)
        {
            string type;                            //string variable used for the type of measurement, as well as the units in that type of measurement
            string units = "";                      //the amount of units will be stored in this variable when the user inputs it in
            double value = 0;                       //the value after the string is converted to a float value

            Console.Write("Welcome to the conversion program. Please choose a type of measurement to start. \n" +       
                "Possible options: length, volume, or area.\n" + "Type chosen: ");        //introduction to the program. Asks the user to specify type of measurement.
            type = Console.ReadLine();                                                                  

            if (type == "length")                                      //an if statement sorts the response to either of the three functions to be calculated further
                LengthExtended(value, type, units);                              
            else if (type == "volume")
                VolumeExtended(value, type, units);
            else
                AreaExtended(value, type, units);

            return;        
        }
        static void LengthExtended(double value, string type, string units)         //function to change to other length units
        {
            Console.Write("\nSpecify the units of length wanted: feet, meters, or miles.\n" + "Units choosen: ");
            type = Console.ReadLine();                                              //reads units from user (this process is repeated in the other functions)

            Console.Write("\nSpecify the amount of {0}: ", type);                   //asks for the amount from the user and stores it in value
            units = Console.ReadLine();
            value = float.Parse(units);

            Console.WriteLine("\n\n\nUnits specified: {0} {1}", value, type);
            if (type == "feet")                                                     //converts feet to meters and miles and displays
                Console.WriteLine("\nConversions:\n" + "To meters: {0} meters\n" + 
                    "To miles: {1} miles", value * 0.30480, value * 0.000189394);
            else if (type == "meters")                                              //converts meters to feet and miles and displays
                Console.WriteLine("\nConversions:\n" + "To feet: {0} feet\n" + 
                    "To miles: {1} miles", value * 3.28084, value * 0.000621371);
            else                                                                    //converts miles to feet and meters and displays
                Console.WriteLine("\nConversions:\n" + "To feet: {0} feet\n" + 
                    "To meters: {1} meters", value * 5280, value * 1609.34);

            return;
        }
        static void VolumeExtended(double value, string type, string units)         //function to change to other volume units
        {
            Console.Write("\nSpecify the units of volume wanted: ounces, quarts, or liters.\n" + "Units choosen: ");
            type = Console.ReadLine();

            Console.Write("\nSpecify the amount of {0}: ", type);
            units = Console.ReadLine();
            value = float.Parse(units);

            Console.WriteLine("\n\n\nUnits specified: {0} {1}", value, type);
            if (type == "ounces")                                                   //converts ounces to quarts and liters and displays
                Console.WriteLine("\nConversions:\n" + "To quarts: {0} quarts\n" + 
                    "To liters: {1} liters", value * 0.03125, value * 0.0295735);
            else if (type == "quarts")                                              //converts quarts to ounces and liters and displays
                Console.WriteLine("\nConversions:\n" + "To ounces: {0} ounces\n" +
                    "To liters: {1} liters", value * 32, value * 0.946353);
            else                                                                    //converts liters to ounces and quarts and displays
                Console.WriteLine("\nConversions:\n" + "To ounces: {0} ounces\n" + 
                    "To quarts: {1} quarts", value * 33.814, value * 1.05669);

            return;
        }
        static void AreaExtended(double value, string type, string units)         //function to change to other area units
        {
            Console.Write("\nSpecify the units of area wanted: square feet, sqaure miles, or acres.\n" + "Units chosen: ");
            type = Console.ReadLine();

            Console.Write("\nSpecify the amount of {0}: ", type);
            units = Console.ReadLine();
            value = float.Parse(units);

            Console.WriteLine("\n\n\nUnits specified: {0} {1}", value, type);
            if (type == "square feet")                                             //converts sq. feet to sq. miles and acres and displays
                Console.WriteLine("\nConversions:\n" + "To square miles: {0} square miles\n" + 
                    "To acres: {1} acres", value * 0.0000000358701, value * 0.0000229568);
            else if (type == "square miles")                                       //converts sq. miles to sq. feet and acres and displays
                Console.WriteLine("\nConversions:\n" + "To square feet: {0} square feet\n" + 
                    "To acres: {1} acres", value * 27880000, value * 640);
            else                                                                   //converts acres to sq. feet and sq. miles and displays
                Console.WriteLine("\nConversions:\n" + "To square feet: {0} square feet\n" + 
                    "To square miles: {1} square miles", value * 43560, value * 0.0015625);

            return;
        }
    }
}
