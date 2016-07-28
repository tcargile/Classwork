/*	Trevor Cargile
	813542789
	Geode.cpp		*/

#include "Geode.h"
#include <math.h>
#include <GL/glut.h>

using namespace std;

/* Default constructor that is empty. */
Geode::Geode(){}

void Geode::addObject(Square sq){
	//Start from the beginning and then go through each vector Square to see if it exists.
	std::vector<Square>::iterator itr = objects.begin();
	while (itr != objects.end()){
		//If so, print error because squares can't be added twice. (disable this to allow double adding).
		if (itr->getName() == sq.getName()){
			cerr << "Error: Square already exists in the list." << endl;
			break;
		}
		itr++;
	}
	objects.push_back(sq);
}

/* Function to remove a child to the list of children if it exists. */
void Geode::removeObject(std::string sq){
	//Start from the beginning and then go through each vector Node to see if it exists.
	std::vector<Square>::iterator itr = objects.begin();
	for (unsigned int i = 0; i < objects.size(); i++){
		//If so, erase it.
		if (itr->getName() == sq){
			objects.erase(objects.begin() + i);
			return;
		}
		itr++;
	}
	//Print error if node doesn't exist.
	cerr << "Error: Square doesn't exist in object list." << endl;
}

/* Function to draw all objects tied to this node. */
void Geode::draw(Matrix4 world, int spheres){
	glLoadMatrixd(world.getPointer());
	glBegin(GL_QUADS);

	std::vector<Square>::iterator itr = objects.begin();

	for (unsigned int i = 0; i < objects.size(); i++){
		glColor3f(itr->gR(), itr->gG(), itr->gB());
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);

		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);

		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);

		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);

		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) - itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);

		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) - itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) + itr->getDim(2) / 2);
		glVertex3f(itr->getCenter(0) + itr->getDim(0) / 2, itr->getCenter(1) + itr->getDim(1) / 2, itr->getCenter(2) - itr->getDim(2) / 2);
	}
	glEnd();
}

/* Specify the bounding spheres. */
Vector4 Geode::boundSphere(Matrix4 world, Vector3 center, int draw){
	Matrix4 transform;
	transform.identity();
	transform.set(Vector4(center[0], center[1] - 0.5, center[2], 1), 3);
	transform.multMM(world);
	transform.multMM(world);

	if (draw > 0){
		glLoadMatrixd(transform.getPointer());
		glColor3f(1.0, 1.0, 1.0);
		glutWireSphere(7.75, 10, 10);
	}

	return Vector4(transform.get(3, 0), transform.get(3, 1), transform.get(3, 2), transform.get(3, 3));
}

/* Set the center. */
void Geode::setCenter(Vector3 cent){
	center = cent;
	transform.identity();
	transform.set(Vector4(center[0], center[1], center[2], 1), 3);
}

/* Test to see if the sphere is outside the frustum. */
/* Inspiration taken from www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-extracting-the-planes/*/
int Geode::culltest(Vector4 loc){
	Vector3 farlength = Vector3(0, 0, -1);
	farlength.scaleV(1000);
	farlength.addV(Vector3(0, 0, -20));

	Vector3 tmp = Vector3(0, 1, 0);
	tmp.scaleV(1000);
	Vector3 tmp2 = Vector3(1, 0, 0);
	tmp2.scaleV(1000);
	Vector3 farTL = farlength + tmp - tmp2;
	Vector3 farTR = farlength + tmp + tmp2;
	Vector3	farBL = farlength - tmp - tmp2;
	Vector3 farBR = farlength - tmp + tmp2;

	Vector3 nearlength = Vector3(0, 0, -1);
	nearlength.scaleV(10);
	nearlength.addV(Vector3(0, 0, -20));

	tmp = Vector3(0, 1, 0);
	tmp.scaleV(10);
	tmp2 = Vector3(1, 0, 0);
	tmp2.scaleV(10);

	Vector3 nearTL = nearlength + tmp - tmp2;
	Vector3 nearTR = nearlength + tmp + tmp2;
	Vector3 nearBL = nearlength - tmp - tmp2;
	Vector3 nearBR = nearlength - tmp + tmp2;

	Vector3 aT = (nearlength + Vector3(0, 10, 0)) - Vector3(0, 0, -20);
	Vector3 aB = (nearlength + Vector3(0, -10, 0)) - Vector3(0, 0, -20);
	Vector3 aL = (nearlength + Vector3(-10, 0, 0)) - Vector3(0, 0, -20);
	Vector3 aR = (nearlength + Vector3(10, 0, 0)) - Vector3(0, 0, -20);

	aT.normalize();
	aB.normalize();
	aL.normalize();
	aR.normalize();

	Vector3 RN;
	RN.crossV(Vector3(1, 0, 0), aR);
	Vector3 LN;
	LN.crossV(Vector3(-1, 0, 0), aL);
	Vector3 TN;
	TN.crossV(Vector3(0, 1, 0), aT);
	Vector3 BN;
	BN.crossV(Vector3(0, -1, 0), aB);

	//float distance;
	
	/*distance = RN.get_mag();
	if (distance < -7.75)
		return 0;
	else if (distance < 7.75)
		return 0;

	distance = LN.get_mag();
	if (distance < -7.75)
		return 0;
	else if (distance < 7.75)
		return 0;

	distance = TN.get_mag();
	if (distance < -7.75)
		return 0;
	else if (distance < 7.75)
		return 0;

	distance = BN.get_mag();
	if (distance < -7.75)
		return 0;
	else if (distance < 7.75)
		return 0;*/

	int ratio = abs(loc[0] / loc[2]);

	if (ratio > 2 && abs(loc[0]) > 40)
		return 1;
	else if (ratio > 5 && abs(loc[0]) > 30)
		return 1;
	else if (ratio > 50 && (abs(loc[0]) - abs(loc[2])) > 30)
		return 1;
	else if (loc[2] < -1000)
		return 1;
	else if (loc[2] > 10)
		return 1;
	
	ratio = abs(loc[1] / loc[2]);
	if (ratio > 1 && abs(loc[0]) > 20)
		return 1;
	else if (ratio > 5 && abs(loc[0]) > 20)
		return 1;
	else if (ratio > 10 && (abs(loc[1]) - abs(loc[2])) > 30)
		return 1;
	else
		return 0;
}