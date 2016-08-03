/*	Trevor Cargile
	813542789
	Matrix4.h		*/

#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include <math.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include "Vector4.h"
#include "Vector3.h"

class Matrix4{   
	public:
		Matrix4();        //default constructor.
		Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
		double* getPointer();		//return pointer to matrix elements.
		void identity();			//create identity matrix.
		void multMM(Matrix4);		//multiply the matrix by the one specified.  
		Vector4 multMV(Vector4);		//multiply the maxtrix by a vector.			
		void rotateX(double);		//rotation about x axis.
		void rotateY(double);		//rotation about y axis.
		void rotateZ(double);		//rotation about z axis.
		void rotateA(double,Vector3);		//rotate around an arbitrary axis.		
		void scaleM(double);						//scale the matrix.
		void non_scaleM(double, double, double, double);	//non-uniform scaling.
		void transpose();			//transpose the matrix.
		static Matrix4 translation(Vector4);			//creates a translation matrix by making the last column of an identity matrix the vector.
		void set(Vector4, int);			//set a row to the vector.
		double get(int, int);		//returns one matrix element at that location.
		void print();				//print the matrix components in a neat format.

		//Overloaded operators.
		Matrix4 operator * (const Matrix4 &);

	protected:
		double m[4][4];   //matrix elements
};

#endif