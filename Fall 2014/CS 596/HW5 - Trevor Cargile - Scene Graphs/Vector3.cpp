/*	Trevor Cargile
	813542789
	Vector3.cpp		*/

#include "Vector3.h"

using namespace std;

/* Default constructor - Defaults the x, y, and z coordinate to 0. */
Vector3::Vector3(){
	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
}

/* Constructor. - Passes the x, y, and z values to the vector being created. */
Vector3::Vector3(double x_value, double y_value, double z_value){
	c[0] = x_value;
	c[1] = y_value;
	c[2] = z_value;
}

/* Set a vector already created to the x, y, and z values passed to the method. */
void Vector3::set(double x_value, double y_value, double z_value){
	c[0] = x_value;
	c[1] = y_value;
	c[2] = z_value;
}

/* Retrieves the index specified by the user. The numbers can range from 0-2. */
double Vector3::get(int index){
	if (index > -1 && index < 3)
		return c[index];
	else
		return NULL;
}

/* Adds two vectors together. The original vector plus the one passed to the method. */
void Vector3::addV(Vector3 vector){
	c[0] += vector.c[0];
	c[1] += vector.c[1];
	c[2] += vector.c[2];
}

/* Subtracts two vectors. If the user passes a 0 argument the method will perform:
		original - vector passed
   If the user passes anything other than a 0, the method will flip the argument and perform:
		vector passed - original
   The result is then stored in the original vector that is passed. */
void Vector3::subtractV(Vector3 vector, Vector3 vector2){
	c[0] = vector.c[0] - vector2.c[0];
	c[1] = vector.c[1] - vector2.c[1];
	c[2] = vector.c[2] - vector2.c[2];
}

/* Performs the cross products for two vectors and stores the result in the original vector.
   If the user specifies 0 the method will perform (original x vector passed). If not, then
   the method will perform the opposite. */
void Vector3::crossV(Vector3 tmp, Vector3 vector){
	c[0] = tmp.c[1] * vector.c[2] - vector.c[1] * tmp.c[2];
	c[1] = tmp.c[2] * vector.c[0] - tmp.c[0] * vector.c[2];
	c[2] = tmp.c[0] * vector.c[1] - vector.c[0] * tmp.c[1];
}

/* Returns the dot product of the two vectors. */
double Vector3::dotV(Vector3 vector){
	return (c[0] * vector.c[0] + c[1] * vector.c[1] + c[2] * vector.c[2]);
}

/* Negates the vector, multiplying all values by -1. */
void Vector3::negateV(){
	c[0] *= -1;
	c[1] *= -1;
	c[2] *= -1;
}

/* Scales the vector by the scalar passed to the method. */
void Vector3::scaleV(double scalar){
	c[0] *= scalar;
	c[1] *= scalar;
	c[2] *= scalar;
}

/* Retrieves the magnitude of the vector. */
double Vector3::get_mag(){
	return sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
}

/* Prints the coordinates of the vector. */
void Vector3::print(){
	cout << "[ " << setw(6) << c[0] << " " << setw(6) << c[1] << " " << setw(6) << c[2] << " ]" << endl;
}

/* Normalic[2]e a vector. */
void Vector3::normalize(){
	double magnitude = sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
	c[0] /= magnitude;
	c[1] /= magnitude;
	c[2] /= magnitude;
}

/* Operator [] overloaded to retrieve the x, y, or z coordinate. */
double Vector3::operator[] (const int &index) const{
	if (index > -1 && index < 3)
		return c[index];
	else
		return NULL;
}

/* Operator + overloaded to allow adding two 3D vectors together with +. */
Vector3 Vector3::operator+ (const Vector3 &vector){
	c[0] += vector.c[0];
	c[1] += vector.c[1];
	c[2] += vector.c[2];
	return Vector3(c[0], c[1], c[2]);
}

/* Operator - overloaded to allow subtracting two 3D vectors together with -. */
Vector3 Vector3::operator- (const Vector3 &vector){
	c[0] -= vector.c[0];
	c[1] -= vector.c[1];
	c[2] -= vector.c[2];
	return Vector3(c[0], c[1], c[2]);
}