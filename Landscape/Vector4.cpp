/*	Trevor Cargile
	813542789
	Vector4.cpp		*/

#include "Vector4.h"

using namespace std;

/* Default vector constructor. Will set the x, y, and z values but default w to 0. */
Vector4::Vector4(){
	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	c[3] = 0;
}

/* Point vector constructor. Will set the x, y, and z values but default w to 1 because its a point. */
Vector4::Vector4(double x_value, double y_value, double z_value){
	c[0] = x_value;
	c[1] = y_value;
	c[2] = z_value;
	c[3] = 1;
}

/* Constructor. - Passes the x, y, z, and w values to the vector being created. */
Vector4::Vector4(double x_value, double y_value, double z_value, double w_value){
	c[0] = x_value;
	c[1] = y_value;
	c[2] = z_value;
	c[3] = w_value;
}

/* Set a vector already created to the x, y, z, and w values passed to the method. */
void Vector4::set(double x_value, double y_value, double z_value, double w_value){
	c[0] = x_value;
	c[1] = y_value;
	c[2] = z_value;
	c[3] = w_value;
}

/* Retrieves the index specified by the user. The numbers can range from 0-3. */
double Vector4::get(int index){
	if (index > -1 && index < 4)
		return c[index];
	else
		return NULL;
}

/* Adds two vectors together. The original vector plus the one passed to the method. */
void Vector4::addV(Vector4 vector){
	c[0] += vector.c[0];
	c[1] += vector.c[1];
	c[2] += vector.c[2];
	c[3] += vector.c[3];
}

/* Subtracts two vectors. If the user passes a 0 argument the method will perform:
original - vector passed
If the user passes anything other than a 0, the method will flip the argument and perform:
vector passed - original
The result is then stored in the original vector that is passed. */
void Vector4::subtractV(Vector4 vector, int direction){
	if (direction == 0){
		c[0] -= vector.c[0];
		c[1] -= vector.c[1];
		c[2] -= vector.c[2];
		c[3] -= vector.c[3];
	}
	else{
		c[0] = vector.c[0] - c[0];
		c[1] = vector.c[1] - c[1];
		c[2] = vector.c[2] - c[2];
		c[2] = vector.c[3] - c[3];
	}
}

/* Prints the coordinates of the 4D vector. */
void Vector4::print(){
	cout << "[ " << setw(6) << c[0] << " " << setw(6) << c[1] << " " << setw(6) << c[2] << " " << setw(6) << c[3] << " ]" << endl;
}

/* Dehomogenizes the vector to make the w coordinate 1 by divinding everything by value of w. */
void Vector4::dehomogenize(){
	c[0] /= c[3];
	c[1] /= c[3];
	c[2] /= c[3];
	c[3] /= c[3];
}

/* Operator [] overloaded to retrieve the x, y, z, or w coordinate. */
double Vector4::operator[] (const int &index) const{
	if (index > -1 && index < 4)
		return c[index];
	else
		return NULL;
}

/* Operator + overloaded to allow adding two 4D vectors together with +. */
Vector4 Vector4::operator+ (const Vector4 &vector){
	c[0] += vector.c[0];
	c[1] += vector.c[1];
	c[2] += vector.c[2];
	c[3] += vector.c[3];
	return Vector4(c[0], c[1], c[2], c[3]);
}

/* Operator - overloaded to allow subtracting two 4D vectors together with -. */
Vector4 Vector4::operator- (const Vector4 &vector){
	c[0] -= vector.c[0];
	c[1] -= vector.c[1];
	c[2] -= vector.c[2];
	c[3] -= vector.c[3];
	return Vector4(c[0], c[1], c[2], c[3]);
}