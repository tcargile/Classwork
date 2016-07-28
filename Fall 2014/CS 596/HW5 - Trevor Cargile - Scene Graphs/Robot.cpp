/*	Trevor Cargile
	813542789
	Robot */

#include "Robot.h"

using namespace std;

/* Default constructor with center at 0,0,0 and white color. */
Robot::Robot(){
	show_spheres = -1;
	outside = 0;
	top = MatrixTransform();
	headrotation = MatrixTransform();
	leg1rotation = MatrixTransform();
	leg2rotation = MatrixTransform();
	arm1rotation = MatrixTransform();
	arm2rotation = MatrixTransform();
	arm2object = Geode();
	arm1object = Geode();
	leg2object = Geode();
	leg1object = Geode();
	headobject = Geode();
	object = Geode();

	center = Vector3(0.0, 0.0, 0.0);
	color = Vector3(0.0, 0.0, 0.0);

	arm2 = Square(Vector3(2.0, 5.0, 2.0), Vector3(1.0, 1.0, 1.0), Vector3(0.0 ,0.0, 0.0), "arm2");
	arm1 = Square(Vector3(2.0, 5.0, 2.0), Vector3(1.0, 1.0, 1.0), Vector3(0.0, 0.0, 0.0), "arm1");
	leg2 = Square(Vector3(2.0, 5.0, 2.0), Vector3(1.0, 1.0, 1.0), Vector3(0.0, 0.0, 0.0), "leg2");
	leg1 = Square(Vector3(2.0, 5.0, 2.0), Vector3(1.0, 1.0, 1.0), Vector3(0.0, 0.0, 0.0), "leg1");
	head = Square(Vector3(4.0, 4.0, 4.0), Vector3(1.0, 1.0, 1.0), Vector3(0.0, 0.0, 0.0), "head");
	torso = Square(Vector3(5.0, 5.0, 5.0), Vector3(1.0, 1.0, 1.0), Vector3(0.0, 0.0, 0.0), "torso");

	object.addObject(torso);
	top.addChild(object);
	headobject.addObject(head);
	headrotation.addChild(headobject);
	top.addChild(headrotation);
	leg1object.addObject(leg1);
	leg1rotation.addChild(leg1object);
	top.addChild(leg1rotation);
	leg2object.addObject(leg2);
	leg2rotation.addChild(leg2object);
	top.addChild(leg2rotation);
	arm1object.addObject(arm1);
	arm1rotation.addChild(arm1object);
	top.addChild(arm1rotation);
	arm2object.addObject(arm2);
	arm2rotation.addChild(arm2object);
	top.addChild(arm2rotation);
}

/* Specified Constructor. */
Robot::Robot(Vector3 cntr, Vector3 clr){
	show_spheres = -1;
	top = MatrixTransform();
	headrotation = MatrixTransform();
	leg1rotation = MatrixTransform();
	leg2rotation = MatrixTransform();
	arm1rotation = MatrixTransform();
	arm2rotation = MatrixTransform();
	arm2object = Geode();
	arm1object = Geode();
	leg2object = Geode();
	leg1object = Geode();
	headobject = Geode();
	object = Geode();

	object.setCenter(cntr);

	center = Vector3(cntr[0], cntr[1], cntr[2]);
	color = Vector3(clr[0], clr[1], clr[2]);

	arm2 = Square(Vector3(2.0, 5.0, 2.0), Vector3(clr[0], clr[1], clr[2]), Vector3(cntr[0], cntr[1], cntr[2]), "arm2");
	arm1 = Square(Vector3(2.0, 5.0, 2.0), Vector3(clr[0], clr[1], clr[2]), Vector3(cntr[0], cntr[1], cntr[2]), "arm1");
	leg2 = Square(Vector3(2.0, 5.0, 2.0), Vector3(clr[0], clr[1], clr[2]), Vector3(cntr[0], cntr[1], cntr[2]), "leg2");
	leg1 = Square(Vector3(2.0, 5.0, 2.0), Vector3(clr[0], clr[1], clr[2]), Vector3(cntr[0], cntr[1], cntr[2]), "leg1");
	head = Square(Vector3(4.0, 4.0, 4.0), Vector3(clr[0], clr[1], clr[2]), Vector3(cntr[0], cntr[1], cntr[2]), "head");
	torso = Square(Vector3(5.0, 5.0, 5.0), Vector3(clr[0], clr[1], clr[2]), Vector3(cntr[0], cntr[1], cntr[2]), "torso");

	object.addObject(torso);
	top.addChild(object);
	headobject.addObject(head);
	headrotation.addChild(headobject);
	top.addChild(headrotation);
	leg1object.addObject(leg1);
	leg1rotation.addChild(leg1object);
	top.addChild(leg1rotation);
	leg2object.addObject(leg2);
	leg2rotation.addChild(leg2object);
	top.addChild(leg2rotation);
	arm1object.addObject(arm1);
	arm1rotation.addChild(arm1object);
	top.addChild(arm1rotation);
	arm2object.addObject(arm2);
	arm2rotation.addChild(arm2object);
	top.addChild(arm2rotation);
}

/* Send info to Geode to see if the bounding sphere is in the view frustum. */
void Robot::culltest(){
	outside = object.culltest(location);
}