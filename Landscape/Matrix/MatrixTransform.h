/*	Trevor Cargile
	813542789
	Homework 5 - MatrixTransform.h		*/

#ifndef _MATRIXTRANSFORM_H_
#define _MATRIXTRANSFORM_H_

#include <vector>
#include "../Objects/Group.h"
#include "Matrix4.h"

class MatrixTransform : public Group{
public:
	MatrixTransform();
	void draw(Matrix4, int);				//NOT IMPLEMENTED
	void setTransform(Matrix4);
	Matrix4 getTransform();

private:
	Matrix4 transform;
};

#endif