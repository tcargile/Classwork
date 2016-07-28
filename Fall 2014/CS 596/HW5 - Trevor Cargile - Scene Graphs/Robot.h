/*	Trevor Cargile
	813542789
	Robot */

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <vector>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Square.h"
#include "MatrixTransform.h"
#include "Group.h"
#include "Geode.h"

class Robot{
public:
	Robot();
	Robot(Vector3, Vector3);

	Vector3 center;
	Vector3 color;
	MatrixTransform top;
	MatrixTransform headrotation;
	MatrixTransform leg1rotation;
	MatrixTransform leg2rotation;
	MatrixTransform arm1rotation;
	MatrixTransform arm2rotation;
	Geode arm2object;
	Geode arm1object;
	Geode leg2object;
	Geode leg1object;
	Geode headobject;
	Geode object;
	Square arm2;
	Square arm1;
	Square leg2;
	Square leg1;
	Square head;
	Square torso;
	int outside;
	void culltest();
	Vector4 location;

private:
	int show_spheres;
};

#endif