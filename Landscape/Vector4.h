/*	Trevor Cargile
	813542789
	Homework 2 - Vector4.h		*/

#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <math.h>
#include <cstdio>
#include <iostream>
#include <iomanip>

class Vector4{
public:
	Vector4();									//default constructor with everything set to 0.
	Vector4(double, double, double);			//constructor with only 3 parameters for a point vector.
	Vector4(double, double, double, double);	//constructor to set all parameters.
	void set(double, double, double, double);	//set an existing vector with 4 values.
	double get(int);							//get a value in position 0-3.
	void addV(Vector4);						//add the Vector4 to the existing one.
	void subtractV(Vector4, int);			//subtract the Vector4 from the existing one, int is used to say which vector is being subtracted from what.
	void print();								//prints the value of the vector.
	void dehomogenize();						//makes the w coordinate 1.

	//Overloaded Operators:
	double operator [] (const int &) const;
	Vector4 operator + (const Vector4 &);
	Vector4 operator - (const Vector4 &);


protected:
	double c[4];								//coordinates (x,y,z,w).
};

#endif