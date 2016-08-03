/*	Trevor Cargile
	813542789
	Robot */

#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <vector>
#include "../Matrix/Vector3.h"
#include "../Matrix/Vector4.h"
#include "../Matrix/Matrix4.h"
#include "../Objects/Square.h"
#include "../Matrix/MatrixTransform.h"
#include "../Objects/Group.h"
#include "../Objects/Geode.h"

class Building{
public:
	Building();
	Building(Vector3, Vector3);

	Vector3 center;
	Vector3 color;
	MatrixTransform top;
	Geode object , WD1 , WD2 , WD3 , WD4 , WD5 , WD6 , WD7 , WD8 , WD9 , WD10 , WD11 , WD12 , WD13 , WD14 , WD15 , WD16;

	Square mainStructure;
	Square window1, window2, window3, window4, window5, window6, window7, window8, window9, window10, window11, window12, window13, window14, window15, window16;
	int outside;
	void culltest();
	Vector4 location;

private:
	int show_spheres;
};

#endif