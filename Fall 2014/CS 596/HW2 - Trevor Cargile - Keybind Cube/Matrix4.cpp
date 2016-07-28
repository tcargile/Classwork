/*	Trevor Cargile
	813542789
	Homework 2 - Matrix4.cpp		*/

#include "Matrix4.h"

using namespace std;

/* Default constructor. Will default all items to 0 in the 4x4 matrix.*/
Matrix4::Matrix4(){
	for (int i=0; i<4; ++i){
		for (int j=0; j<4; ++j)
			m[i][j] = 0;
		}
} 

/* Constructor used when default values are specified by the user. */
Matrix4::Matrix4(double m00, double m01, double m02, double m03,
				 double m10, double m11, double m12, double m13,
				 double m20, double m21, double m22, double m23,
				 double m30, double m31, double m32, double m33 ){
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;
	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;
	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;
	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

/* Retrieves a pointer to the item located in that matrix spot. */
double* Matrix4::getPointer(){
	return &m[0][0];
}

void Matrix4::identity(){
  double ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}

/* Multiplies two 4x4 matrices together. */
void Matrix4::multMM(Matrix4 matrix){
	Matrix4 mt = Matrix4(m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
	m[0][0] = mt.m[0][0] * matrix.m[0][0] + mt.m[0][1] * matrix.m[1][0] + mt.m[0][2] * matrix.m[2][0] + mt.m[0][3] * matrix.m[3][0];
	m[0][1] = mt.m[0][0] * matrix.m[0][1] + mt.m[0][1] * matrix.m[1][1] + mt.m[0][2] * matrix.m[2][1] + mt.m[0][3] * matrix.m[3][1];
	m[0][2] = mt.m[0][0] * matrix.m[0][2] + mt.m[0][1] * matrix.m[1][2] + mt.m[0][2] * matrix.m[2][2] + mt.m[0][3] * matrix.m[3][2];
	m[0][3] = mt.m[0][0] * matrix.m[0][3] + mt.m[0][1] * matrix.m[1][3] + mt.m[0][2] * matrix.m[2][3] + mt.m[0][3] * matrix.m[3][3];

	m[1][0] = mt.m[1][0] * matrix.m[0][0] + mt.m[1][1] * matrix.m[1][0] + mt.m[1][2] * matrix.m[2][0] + mt.m[1][3] * matrix.m[3][0];
	m[1][1] = mt.m[1][0] * matrix.m[0][1] + mt.m[1][1] * matrix.m[1][1] + mt.m[1][2] * matrix.m[2][1] + mt.m[1][3] * matrix.m[3][1];
	m[1][2] = mt.m[1][0] * matrix.m[0][2] + mt.m[1][1] * matrix.m[1][2] + mt.m[1][2] * matrix.m[2][2] + mt.m[1][3] * matrix.m[3][2];
	m[1][3] = mt.m[1][0] * matrix.m[0][3] + mt.m[1][1] * matrix.m[1][3] + mt.m[1][2] * matrix.m[2][3] + mt.m[1][3] * matrix.m[3][3];

	m[2][0] = mt.m[2][0] * matrix.m[0][0] + mt.m[2][1] * matrix.m[1][0] + mt.m[2][2] * matrix.m[2][0] + mt.m[2][3] * matrix.m[3][0];
	m[2][1] = mt.m[2][0] * matrix.m[0][1] + mt.m[2][1] * matrix.m[1][1] + mt.m[2][2] * matrix.m[2][1] + mt.m[2][3] * matrix.m[3][1];
	m[2][2] = mt.m[2][0] * matrix.m[0][2] + mt.m[2][1] * matrix.m[1][2] + mt.m[2][2] * matrix.m[2][2] + mt.m[2][3] * matrix.m[3][2];
	m[2][3] = mt.m[2][0] * matrix.m[0][3] + mt.m[2][1] * matrix.m[1][3] + mt.m[2][2] * matrix.m[2][3] + mt.m[2][3] * matrix.m[3][3];

	m[3][0] = mt.m[3][0] * matrix.m[0][0] + mt.m[3][1] * matrix.m[1][0] + mt.m[3][2] * matrix.m[2][0] + mt.m[3][3] * matrix.m[3][0];
	m[3][1] = mt.m[3][0] * matrix.m[0][1] + mt.m[3][1] * matrix.m[1][1] + mt.m[3][2] * matrix.m[2][1] + mt.m[3][3] * matrix.m[3][1];
	m[3][2] = mt.m[3][0] * matrix.m[0][2] + mt.m[3][1] * matrix.m[1][2] + mt.m[3][2] * matrix.m[2][2] + mt.m[3][3] * matrix.m[3][2];
	m[3][3] = mt.m[3][0] * matrix.m[0][3] + mt.m[3][1] * matrix.m[1][3] + mt.m[3][2] * matrix.m[2][3] + mt.m[3][3] * matrix.m[3][3];
}

/* Multiplies a 4x4 matrix with a 4x1 vector and returns the resulting vector.*/
Vector4 Matrix4::multMV(Vector4 vector){
	double c0, c1, c2, c3;
	c0 = m[0][0] * vector.get(0) + m[0][1] * vector.get(1) + m[0][2] * vector.get(2) + m[0][3] * vector.get(3);
	c1 = m[1][0] * vector.get(0) + m[1][1] * vector.get(1) + m[1][2] * vector.get(2) + m[1][3] * vector.get(3);
	c2 = m[2][0] * vector.get(0) + m[2][1] * vector.get(1) + m[2][2] * vector.get(2) + m[2][3] * vector.get(3);
	c3 = m[3][0] * vector.get(0) + m[3][1] * vector.get(1) + m[3][2] * vector.get(2) + m[3][3] * vector.get(3);

	Vector4 newvec = Vector4(c0, c1, c2, c3);

	return newvec;
}

/* Rotates the matrix around the X axis specified by the angle in radians. */
void Matrix4::rotateX(double angle){
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

/* Rotates the matrix around the Y axis specified by the angle in radians. */
void Matrix4::rotateY(double angle){
	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = sin(angle);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = -sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

/* Rotates the matrix around the Z axis specified by the angle in radians. */
void Matrix4::rotateZ(double angle){
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

/* Rotates the matrix around an arbitrary axis defined by the vector passed to the method. The angle is also to be specified by the user. */
void Matrix4::rotateA(double angle, Vector4 vector){
	m[0][0] = vector.get(0) * vector.get(0) + cos(angle) * (1 - vector.get(0) * vector.get(0));
	m[0][1] = vector.get(0) * vector.get(1) * (1 - cos(angle)) - vector.get(2) * sin(angle);
	m[0][2] = vector.get(0) * vector.get(2) * (1 - cos(angle)) + vector.get(1) * sin(angle);
	m[0][3] = 0;
	m[1][0] = vector.get(0) * vector.get(1) * (1 - cos(angle)) + vector.get(2) * sin(angle);
	m[1][1] = vector.get(1) * vector.get(1) + cos(angle) * (1 - vector.get(1) * vector.get(1));
	m[1][2] = vector.get(1) * vector.get(2) * (1 - cos(angle)) - vector.get(0) * sin(angle);
	m[1][3] = 0;
	m[2][0] = vector.get(0) * vector.get(2) * (1 - cos(angle)) - vector.get(1) * sin(angle);
	m[2][1] = vector.get(1) * vector.get(2) * (1 - cos(angle)) + vector.get(0) * sin(angle);
	m[2][2] = vector.get(2) * vector.get(2) + cos(angle) * (1 - vector.get(2) * vector.get(2));
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

/* Scales the matrix with the given scalar. */
void Matrix4::scaleM(double scalar){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			m[i][j] *= scalar;
	}
}

/* Scales the matrix with the given scalar values. Each one could be different. */
void Matrix4::non_scaleM(double x, double y, double z, double w){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			switch (j){
			case 0:
				m[i][j] *= x;
			case 1:
				m[i][j] *= y;
			case 2:
				m[i][j] *= z;
			case 3:
				m[i][j] *= w;
			}
		}
	}
}

/* Transposes the matrix (making columns into rows and rows into columns. */
void Matrix4::transpose(){
	Matrix4 tmp = Matrix4(m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
	m[0][0] = tmp.m[0][0];
	m[0][1] = tmp.m[1][0];
	m[0][2] = tmp.m[2][0];
	m[0][3] = tmp.m[3][0];
	m[1][0] = tmp.m[0][1];
	m[1][1] = tmp.m[1][1];
	m[1][2] = tmp.m[2][1];
	m[1][3] = tmp.m[3][1];
	m[2][0] = tmp.m[0][2];
	m[2][1] = tmp.m[1][2];
	m[2][2] = tmp.m[2][2];
	m[2][3] = tmp.m[3][2];
	m[3][0] = tmp.m[0][3];
	m[3][1] = tmp.m[1][3];
	m[3][2] = tmp.m[2][3];
	m[3][3] = tmp.m[3][3];
}

/* Translates the matrix if the ordering is row major form.*/
Matrix4 Matrix4::translation(Vector4 vector){
	Matrix4 translate = Matrix4();
	translate.identity();
	for (int i = 0; i < 3; i++)
		translate.m[i][3] += vector.get(i);

	return translate;
}

/* Set the values of the row located in that position in the matrix. */
void Matrix4::set(Vector4 vector, int row){
	for (int i = 0; i < 4; i++)
		m[row][i] = vector[i];
}

/* Retrieves the value of the item located in that position in the matrix. */
double Matrix4::get(int i, int j){
	if (i > -1 && i < 4 && j > -1 && j < 4)
		return m[i][j];
	else
		return NULL;
}

/* Prints the contents of the matrix in a neat format. */
void Matrix4::print(){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			cout << setw(10) << m[i][j] << "  ";
		cout << endl;
	}
}