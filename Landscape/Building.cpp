#include "Building.h"
#include <time.h>       /* time */

using namespace std;

/* Default constructor with center at 0,0,0 and white color. */
Building::Building(){
	show_spheres = -1;
	outside = 0;
	top = MatrixTransform();
	object = Geode();

	center = Vector3(0.0, 0.0, 0.0);
	color = Vector3(0.0, 0.0, 0.0);

	mainStructure = Square(Vector3(10.0, 10.0, 10.0), Vector3(1.0, 1.0, 1.0), Vector3(0.0, 0.0, 0.0), "torso");

	object.addObject(mainStructure);
	top.addChild(object);
}

/* Specified Constructor. */
Building::Building(Vector3 cntr, Vector3 clr){
	show_spheres = -1;
	top = MatrixTransform();
	object = Geode(); 

	WD1 = Geode(); WD2 = Geode(); WD3 = Geode(); WD4 = Geode(); 
	WD5 = Geode(); WD6 = Geode(); WD7 = Geode(); WD8 = Geode();
	WD9 = Geode(); WD10 = Geode(); WD11 = Geode(); WD12 = Geode();
	WD13 = Geode(); WD14 = Geode(); WD15 = Geode(); WD16 = Geode();

	int bCount = 0; int clrY;
	double offset = 2.5;
	object.setCenter(cntr);

	center = Vector3(cntr[0], cntr[1], cntr[2]);
	color = Vector3(clr[0], clr[1], clr[2]);

	mainStructure = Square(Vector3(10.0, 10.0, 10.0), Vector3(clr[0], clr[1], clr[2]), Vector3(cntr[0], cntr[1], cntr[2]), "mainStruc");

	object.addObject(mainStructure);
	top.addChild(object);

	clrY = rand() % 2;
	window1 = Square(Vector3(3.8, 3.8, 0.5), Vector3(clrY, clrY, 0), Vector3(cntr[0] - offset, cntr[1] + offset, cntr[2] + 4.9), "window1");
	clrY = rand() % 2;
	window2 = Square(Vector3(3.8, 3.8, 0.5), Vector3(clrY, clrY, 0), Vector3(cntr[0] + offset, cntr[1] + offset, cntr[2] + 4.9), "window2");
	clrY = rand() % 2;
	window3 = Square(Vector3(3.8, 3.8, 0.5), Vector3(clrY, clrY, 0), Vector3(cntr[0] - offset, cntr[1] - offset, cntr[2] + 4.9), "window3");
	clrY = rand() % 2;
	window4 = Square(Vector3(3.8, 3.8, 0.5), Vector3(clrY, clrY, 0), Vector3(cntr[0] + offset, cntr[1] - offset, cntr[2] + 4.9), "window4");

	clrY = rand() % 2;
	window5 = Square(Vector3(0.5, 3.8, 3.8), Vector3(clrY, clrY, 0), Vector3(cntr[0] - 4.9, cntr[1] + offset, cntr[2] - offset), "window5");
	clrY = rand() % 2;
	window6 = Square(Vector3(0.5, 3.8, 3.8), Vector3(clrY, clrY, 0), Vector3(cntr[0] - 4.9, cntr[1] + offset, cntr[2] + offset), "window6");
	clrY = rand() % 2;
	window7 = Square(Vector3(0.5, 3.8, 3.8), Vector3(clrY, clrY, 0), Vector3(cntr[0] - 4.9, cntr[1] - offset, cntr[2] - offset), "window7");
	clrY = rand() % 2;
	window8 = Square(Vector3(0.5, 3.8, 3.8), Vector3(clrY, clrY, 0), Vector3(cntr[0] - 4.9, cntr[1] - offset, cntr[2] + offset), "window8");

	clrY = rand() % 2;
	window9 = Square(Vector3(0.5, 3.8, 3.8), Vector3(clrY, clrY, 0), Vector3(cntr[0] + 4.9, cntr[1] + offset, cntr[2] - offset), "window9");
	clrY = rand() % 2;
	window10 = Square(Vector3(0.5, 3.8, 3.8), Vector3(clrY, clrY, 0), Vector3(cntr[0] + 4.9, cntr[1] + offset, cntr[2] + offset), "window10");
	clrY = rand() % 2;
	window11 = Square(Vector3(0.5, 3.8, 3.8), Vector3(clrY, clrY, 0), Vector3(cntr[0] + 4.9, cntr[1] - offset, cntr[2] - offset), "window11");
	clrY = rand() % 2;
	window12 = Square(Vector3(0.5, 3.8, 3.8), Vector3(clrY, clrY, 0), Vector3(cntr[0] + 4.9, cntr[1] - offset, cntr[2] + offset), "window12");

	clrY = rand() % 2;
	window13 = Square(Vector3(3.8, 3.8, 0.5), Vector3(clrY, clrY, 0), Vector3(cntr[0] - offset, cntr[1] + offset, cntr[2] - 4.9), "window13");
	clrY = rand() % 2;
	window14 = Square(Vector3(3.8, 3.8, 0.5), Vector3(clrY, clrY, 0), Vector3(cntr[0] + offset, cntr[1] + offset, cntr[2] - 4.9), "window14");
	clrY = rand() % 2;
	window15 = Square(Vector3(3.8, 3.8, 0.5), Vector3(clrY, clrY, 0), Vector3(cntr[0] - offset, cntr[1] - offset, cntr[2] - 4.9), "window15");
	clrY = rand() % 2;
	window16 = Square(Vector3(3.8, 3.8, 0.5), Vector3(clrY, clrY, 0), Vector3(cntr[0] + offset, cntr[1] - offset, cntr[2] - 4.9), "window16");

	WD1.addObject(window1); WD2.addObject(window2); WD3.addObject(window3); WD4.addObject(window4);
	WD5.addObject(window5); WD6.addObject(window6); WD7.addObject(window7); WD8.addObject(window8);
	WD9.addObject(window9); WD10.addObject(window10); WD11.addObject(window11); WD12.addObject(window12);
	WD13.addObject(window13); WD14.addObject(window14); WD15.addObject(window15); WD16.addObject(window16);

	top.addChild(WD1); top.addChild(WD2); top.addChild(WD3); top.addChild(WD4);
	top.addChild(WD5); top.addChild(WD6); top.addChild(WD7); top.addChild(WD8);
	top.addChild(WD9); top.addChild(WD10); top.addChild(WD11); top.addChild(WD12);
	top.addChild(WD13); top.addChild(WD14); top.addChild(WD15); top.addChild(WD16);

}

/* Send info to Geode to see if the bounding sphere is in the view frustum. */
void Building::culltest(){
	outside = object.culltest(location);
}