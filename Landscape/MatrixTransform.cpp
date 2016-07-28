/*	Trevor Cargile
	813542789
	MatrixTransformation.cpp		*/

#include "MatrixTransform.h"

using namespace std;

/* Default Constructor when a new node is established with a transformation. */
MatrixTransform::MatrixTransform(){
	//Default the transform to the matrix identity (no transform);
	transform.identity();
}

/* Transform the object with the current world matrix. */
void MatrixTransform::draw(Matrix4 world, int n){
	Matrix4 transform_new = transform * world;
	std::vector<Node*>::iterator itr = children.begin();
	while (itr != children.end()){
		(*itr)->draw(transform_new, n);
		itr++;
	}
}

/* Set the transform that you wan't. */
void MatrixTransform::setTransform(Matrix4 new_transform){
	transform = new_transform;
}

/* Get the transform. */
Matrix4 MatrixTransform::getTransform(){
	return transform;
}