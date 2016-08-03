/*	Trevor Cargile
	813542789
	Square - MatrixTransform.h		*/

#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <vector>
#include "../Matrix/Matrix4.h"

class Square{
public:
	Square();
	Square(Vector3, Vector3, Vector3, std::string);
	std::string getName();
	double gR();
	double gG();
	double gB();
	double getCenter(int);
	double getDim(int);

private:
	Vector3 dimensions;
	Vector3 center;
	double red, green, blue;
	std::string name;
};

#endif