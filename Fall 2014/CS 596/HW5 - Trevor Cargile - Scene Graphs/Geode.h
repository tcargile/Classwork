/*	Trevor Cargile
	813542789
	Homework 5 - Geode.h		*/

#ifndef _GEODE_H_
#define _GEODE_H_

#include <vector>
#include "Matrix4.h"
#include "Node.h"
#include "Square.h"

class Geode : public Node{
public:
	Geode();
	void addObject(Square);
	void removeObject(std::string);
	void draw(Matrix4, int);				
	Vector4 boundSphere(Matrix4, Vector3, int);
	void setCenter(Vector3);
	int culltest(Vector4);

protected:
	std::vector<Square> objects;
	Matrix4 transform;
	Vector3 center;
	Matrix4 prev;
	Vector3 RN;
	Vector3 LN;
	Vector3 TN;
	Vector3 BN;
};

#endif