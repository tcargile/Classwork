/*	Trevor Cargile
	813542789
	Vector3.h		*/

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>
#include <cstdio>
#include <iostream>
#include <iomanip>

class Vector3
{
public:
	Vector3();								//default constructor - will be 0,0,0.
	Vector3(double, double, double);		//constructor with set parameters.
	void set(double, double, double);		//set an existing vector with 3 values.
	double get(int);						//get a value in position 0-2.
	void addV(Vector3);						//add the Vector3 to the existing one.
	void subtractV(Vector3, Vector3);			//subtract the Vector3 from the existing one, int is used to say which vector is being subtracted from what.
	void crossV(Vector3, Vector3);				//perform cross product with the specified vector, int used to specify order.
	double dotV(Vector3);					//perform the dot product with the specified vector.
	void negateV();							//negate the vector.
	void scaleV(double);					//multiply the vector by a scalar.
	double get_mag();						//retrieves the magnitude of the vector.
	void print();							//prints the value of the vector.
	void normalize();						//normalizes the vector.
	
	//Overloaded Operators:
	double operator [] (const int &) const;
	Vector3 operator + (const Vector3 &);
	Vector3 operator - (const Vector3 &);

protected:
	double c[3];							//coordinates (x,y,z)
};

#endif