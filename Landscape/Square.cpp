/*	Trevor Cargile
	813542789
	Square.cpp		*/

#include "Square.h"

using namespace std;

/* Default constructor with default values. */
Square::Square(){
	red = 1.0;
	green = 1.0;
	blue = 1.0;
	center = Vector3(0.0, 0.0, 0.0);
	dimensions = Vector3(1.0, 1.0, 1.0);
	name = "No name";
}

/* Precise constructor with values included. */
Square::Square(Vector3 dim, Vector3 rgb, Vector3 centr, std::string n){
	red = rgb[0];
	green = rgb[1];
	blue = rgb[2];
	name = n;
	dimensions = dim;
	center = Vector3(centr[0], centr[1], centr[2]);
}

/* Function to retrieve name. */
std::string Square::getName(){
	return name;
}

/* Function to retrieve red. */
double Square::gR(){
	return red;
}

/* Function to retrieve green. */
double Square::gG(){
	return green;
}

/* Function to retrieve blue. */
double Square::gB(){
	return blue;
}

/* Function to retrieve center. */
double Square::getCenter(int index){
	return center[index];
}

/* Function to retrieve dimensions. */
double Square::getDim(int index){
	return dimensions[index];
}