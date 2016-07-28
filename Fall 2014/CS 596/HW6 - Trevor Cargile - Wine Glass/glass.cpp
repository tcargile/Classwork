// Trevor Cargile
// 813542789
// Project: Wine Glass with B Curves
// Original code by: Professor Jurgen Schulze

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "glass.h"
#include "Matrix4.h"
#include "Vector3.h"
#include <vector>

using namespace std;

static Glass wine;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

// Globals to store the window for future use.
int wnew = 512;
int hnew = 512;

/* The colors used to recolor the cube when a key is pressed. */
double r = 1.0, g = 1.0, b = 1.0;

vector<Vector3> vertices;
vector<Vector3> normals;

int offsetx = 377;
int offsety = 265;

/* Matrix used for the z rotation. */
Matrix4 rotateM = Matrix4();


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	displayCallback();  // call display routine to re-draw cube
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
	width = w;
	height = h;
	wnew = w;
	hnew = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
	glTranslatef(0, 0, -20);
	glMatrixMode(GL_MODELVIEW);
}

double getX(double t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3){
	return ((1 - t) * (1 - t) * (1 - t)) * p0[0] + (3 * t * ((1 - t) * (1 - t))) * p1[0] + (3 * t * t * (1 - t)) * p2[0] + (t * t * t) * p3[0];
}

double getY(double t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3){
	return ((1 - t) * (1 - t) * (1 - t)) * p0[1] + (3 * t * ((1 - t) * (1 - t))) * p1[1] + (3 * t * t * (1 - t)) * p2[1] + (t * t * t) * p3[1];
}

double getdX(double t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3){
	return (-3 * (t * t) + 6 * t - 3) * p0[0] + (9 * (t * t) - 12 * t + 3) * p1[0] + (-9 * (t * t) + 6 * t) * p2[0] + (3 * (t * t)) * p3[0];
}

double getdY(double t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3){
	return (-3 * (t * t) + 6 * t - 3) * p0[1] + (9 * (t * t) - 12 * t + 3) * p1[1] + (-9 * (t * t) + 6 * t) * p2[1] + (3 * (t * t)) * p3[1];
}

/* Method to get the vectors for drawing inside the wine glass. */
void getVectors(int points, int sides, double rotation_angle){
	vector<Vector3> vertices;
	vector<Vector3> normals;

	double increment = 1 / (points - 1);
	double t = 0;

	//Inside of the glass.
	Vector3 p0 = Vector3(0, 0, 0);
	Vector3 p1 = Vector3(0.78, 0.17, 0);
	Vector3 p2 = Vector3(1.44, 0.72, 0);
	Vector3 p3 = Vector3(1.56, 1.79, 0);

	//Outside of the glass.
	Vector3 p4 = Vector3(1.56, 1.79, 0);
	Vector3 p5 = Vector3(1.63, 0.72, 0);
	Vector3 p6 = Vector3(0.96, 0, 0);
	Vector3 p7 = Vector3(0.20, -0.14, 0);

	//Wine glass stem.
	Vector3 p8 = Vector3(0.20, -0.14, 0);
	Vector3 p9 = Vector3(0.13, -0.89, 0);
	Vector3 p10 = Vector3(0.12, -1.65, 0);
	Vector3 p11 = Vector3(0.13, -2.51, 0);

	//Wine glass bottom.
	Vector3 p12 = Vector3(0.13, -2.51, 0);
	Vector3 p13 = Vector3(1.02, -2.61, 0);
	Vector3 p14 = Vector3(1.39, -2.79, 0);
	Vector3 p15 = Vector3(0, -2.79, 0);

	//Iterator to go through entries.
	vector<Vector3>::iterator itr;
	vector<Vector3>::iterator nitr;

	Vector3 first = Vector3(getX(0, p0, p1, p2, p3), getY(0, p0, p1, p2, p3), 0);
	Vector3 second = Vector3(getX(0.25, p0, p1, p2, p3), getY(0.25, p0, p1, p2, p3), 0);
	Vector3 third = Vector3(getX(0.50, p0, p1, p2, p3), getY(0.5, p0, p1, p2, p3), 0);
	Vector3 fourth = Vector3(getX(0.75, p0, p1, p2, p3), getY(0.75, p0, p1, p2, p3), 0);
	Vector3 fifth = Vector3(getX(1.0, p0, p1, p2, p3), getY(1.0, p0, p1, p2, p3), 0);
	Vector3 normal = Vector3(-getdY(0, p0, p1, p2, p3), getdX(0, p0, p1, p2, p3), 0);

	//Establish rotation points.
	for (int j = 0; j < sides + 1; j++){
		vertices.push_back(first);
		vertices.push_back(second);
		vertices.push_back(third);
		vertices.push_back(fourth);
		vertices.push_back(fifth);

		//Rotate each vertex for next draw.
		first.set(first[0] * cos(rotation_angle) - first[2] * sin(rotation_angle), first[1], first[0] * sin(rotation_angle) + first[2] * cos(rotation_angle));
		second.set(second[0] * cos(rotation_angle) - second[2] * sin(rotation_angle), second[1], second[0] * sin(rotation_angle) + second[2] * cos(rotation_angle));
		third.set(third[0] * cos(rotation_angle) - third[2] * sin(rotation_angle), third[1], third[0] * sin(rotation_angle) + third[2] * cos(rotation_angle));
		fourth.set(fourth[0] * cos(rotation_angle) - fourth[2] * sin(rotation_angle), fourth[1], fourth[0] * sin(rotation_angle) + fourth[2] * cos(rotation_angle));
		fifth.set(fifth[0] * cos(rotation_angle) - fifth[2] * sin(rotation_angle), fifth[1], fifth[0] * sin(rotation_angle) + fifth[2] * cos(rotation_angle));
	}

	for (int k = 0; k < points; k++){
		normal = Vector3(-getdY((double)k / points, p0, p1, p2, p3), getdX((double)k / points, p0, p1, p2, p3), 0);
		normal.normalize();
		for (int i = 0; i < sides; i++){
			normals.push_back(normal);
			normal.set(normal[0] * cos(rotation_angle) - normal[2] * sin(rotation_angle), normal[1], normal[0] * sin(rotation_angle) + normal[2] * cos(rotation_angle));
		}
	}

	/*
	itr = vertices.begin();
	cout << "START" << endl;
	for (int i = 0; i < points * 4; i++){
		itr->print();
		itr++;
	}*/

	//vector<Vector3>::iterator nitr = normals.begin();
	itr = vertices.begin();
	nitr = normals.begin();

	//Draw the part 1 of the inside glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 1;
	nitr = normals.begin() + sides;

	//Draw the part 2 of the inside glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 2;
	nitr = normals.begin() + sides * 2;

	//Draw the part 3 of the inside glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 3;
	nitr = normals.begin() + sides * 3;

	//Draw the part 4 of the inside glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();
}

/* Method to get the vectors for drawing outside wine glass. */
void getVectors2(int points, int sides, double rotation_angle){
	vector<Vector3> vertices;
	vector<Vector3> normals;

	double increment = 1 / (points - 1);
	double t = 0;

	//Outside of the glass.
	Vector3 p0 = Vector3(1.56, 1.79, 0);
	Vector3 p1 = Vector3(1.63, 0.72, 0);
	Vector3 p2 = Vector3(0.96, 0, 0);
	Vector3 p3 = Vector3(0.20, -0.14, 0);

	//Iterator to go through entries.
	vector<Vector3>::iterator itr;
	vector<Vector3>::iterator nitr;

	Vector3 first = Vector3(getX(0, p0, p1, p2, p3), getY(0, p0, p1, p2, p3), 0);
	Vector3 second = Vector3(getX(0.25, p0, p1, p2, p3), getY(0.25, p0, p1, p2, p3), 0);
	Vector3 third = Vector3(getX(0.50, p0, p1, p2, p3), getY(0.5, p0, p1, p2, p3), 0);
	Vector3 fourth = Vector3(getX(0.75, p0, p1, p2, p3), getY(0.75, p0, p1, p2, p3), 0);
	Vector3 fifth = Vector3(getX(1.0, p0, p1, p2, p3), getY(1.0, p0, p1, p2, p3), 0);
	Vector3 normal = Vector3(-getdY(0, p0, p1, p2, p3), getdX(0, p0, p1, p2, p3), 0);

	//Establish rotation points.
	for (int j = 0; j < sides + 1; j++){
		vertices.push_back(first);
		vertices.push_back(second);
		vertices.push_back(third);
		vertices.push_back(fourth);
		vertices.push_back(fifth);

		//Rotate each vertex for next draw.
		first.set(first[0] * cos(rotation_angle) - first[2] * sin(rotation_angle), first[1], first[0] * sin(rotation_angle) + first[2] * cos(rotation_angle));
		second.set(second[0] * cos(rotation_angle) - second[2] * sin(rotation_angle), second[1], second[0] * sin(rotation_angle) + second[2] * cos(rotation_angle));
		third.set(third[0] * cos(rotation_angle) - third[2] * sin(rotation_angle), third[1], third[0] * sin(rotation_angle) + third[2] * cos(rotation_angle));
		fourth.set(fourth[0] * cos(rotation_angle) - fourth[2] * sin(rotation_angle), fourth[1], fourth[0] * sin(rotation_angle) + fourth[2] * cos(rotation_angle));
		fifth.set(fifth[0] * cos(rotation_angle) - fifth[2] * sin(rotation_angle), fifth[1], fifth[0] * sin(rotation_angle) + fifth[2] * cos(rotation_angle));
	}

	for (int k = 0; k < points; k++){
		normal = Vector3(-getdY((double)k / points, p0, p1, p2, p3), getdX((double)k / points, p0, p1, p2, p3), 0);
		normal.normalize();
		for (int i = 0; i < sides; i++){
			normals.push_back(normal);
			normal.set(normal[0] * cos(rotation_angle) - normal[2] * sin(rotation_angle), normal[1], normal[0] * sin(rotation_angle) + normal[2] * cos(rotation_angle));
		}
	}

	itr = vertices.begin();
	nitr = normals.begin();

	//Draw the part 1 of the outside glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 1;
	nitr = normals.begin() + sides;

	//Draw the part 2 of the outside glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 2;
	nitr = normals.begin() + sides * 2;

	//Draw the part 3 of the outside glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 3;
	nitr = normals.begin() + sides * 3;

	//Draw the part 4 of the outside glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();
}

/* Method to get the vectors for drawing the stem of the wine glass. */
void getVectors3(int points, int sides, double rotation_angle){
	vector<Vector3> vertices;
	vector<Vector3> normals;

	double increment = 1 / (points - 1);
	double t = 0;

	//Wine glass stem.
	Vector3 p0 = Vector3(0.20, -0.14, 0);
	Vector3 p1 = Vector3(0.13, -0.89, 0);
	Vector3 p2 = Vector3(0.12, -1.65, 0);
	Vector3 p3 = Vector3(0.13, -2.51, 0);

	//Iterator to go through entries.
	vector<Vector3>::iterator itr;
	vector<Vector3>::iterator nitr;

	Vector3 first = Vector3(getX(0, p0, p1, p2, p3), getY(0, p0, p1, p2, p3), 0);
	Vector3 second = Vector3(getX(0.25, p0, p1, p2, p3), getY(0.25, p0, p1, p2, p3), 0);
	Vector3 third = Vector3(getX(0.50, p0, p1, p2, p3), getY(0.5, p0, p1, p2, p3), 0);
	Vector3 fourth = Vector3(getX(0.75, p0, p1, p2, p3), getY(0.75, p0, p1, p2, p3), 0);
	Vector3 fifth = Vector3(getX(1.0, p0, p1, p2, p3), getY(1.0, p0, p1, p2, p3), 0);
	Vector3 normal = Vector3(-getdY(0, p0, p1, p2, p3), getdX(0, p0, p1, p2, p3), 0);

	//Establish rotation points.
	for (int j = 0; j < sides + 1; j++){
		vertices.push_back(first);
		vertices.push_back(second);
		vertices.push_back(third);
		vertices.push_back(fourth);
		vertices.push_back(fifth);

		//Rotate each vertex for next draw.
		first.set(first[0] * cos(rotation_angle) - first[2] * sin(rotation_angle), first[1], first[0] * sin(rotation_angle) + first[2] * cos(rotation_angle));
		second.set(second[0] * cos(rotation_angle) - second[2] * sin(rotation_angle), second[1], second[0] * sin(rotation_angle) + second[2] * cos(rotation_angle));
		third.set(third[0] * cos(rotation_angle) - third[2] * sin(rotation_angle), third[1], third[0] * sin(rotation_angle) + third[2] * cos(rotation_angle));
		fourth.set(fourth[0] * cos(rotation_angle) - fourth[2] * sin(rotation_angle), fourth[1], fourth[0] * sin(rotation_angle) + fourth[2] * cos(rotation_angle));
		fifth.set(fifth[0] * cos(rotation_angle) - fifth[2] * sin(rotation_angle), fifth[1], fifth[0] * sin(rotation_angle) + fifth[2] * cos(rotation_angle));
	}

	for (int k = 0; k < points; k++){
		normal = Vector3(-getdY((double)k / points, p0, p1, p2, p3), getdX((double)k / points, p0, p1, p2, p3), 0);
		normal.normalize();
		for (int i = 0; i < sides; i++){
			normals.push_back(normal);
			normal.set(normal[0] * cos(rotation_angle) - normal[2] * sin(rotation_angle), normal[1], normal[0] * sin(rotation_angle) + normal[2] * cos(rotation_angle));
		}
	}

	itr = vertices.begin();
	nitr = normals.begin();

	//Draw the part 1 of the stem for glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 1;
	nitr = normals.begin() + sides;

	//Draw the part 2 of the stem for glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 2;
	nitr = normals.begin() + sides * 2;

	//Draw the part 3 of the stem for glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 3;
	nitr = normals.begin() + sides * 3;

	//Draw the part 4 of the stem for glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();
}

/* Method to get the vectors for drawing the bottom of the wine glass. */
void getVectors4(int points, int sides, double rotation_angle){
	vector<Vector3> vertices;
	vector<Vector3> normals;

	double increment = 1 / (points - 1);
	double t = 0;

	//Wine glass bottom.
	Vector3 p0 = Vector3(0.13, -2.51, 0);
	Vector3 p1 = Vector3(1.02, -2.61, 0);
	Vector3 p2 = Vector3(1.39, -2.79, 0);
	Vector3 p3 = Vector3(0, -2.79, 0);

	//Iterator to go through entries.
	vector<Vector3>::iterator itr;
	vector<Vector3>::iterator nitr;

	Vector3 first = Vector3(getX(0, p0, p1, p2, p3), getY(0, p0, p1, p2, p3), 0);
	Vector3 second = Vector3(getX(0.25, p0, p1, p2, p3), getY(0.25, p0, p1, p2, p3), 0);
	Vector3 third = Vector3(getX(0.50, p0, p1, p2, p3), getY(0.5, p0, p1, p2, p3), 0);
	Vector3 fourth = Vector3(getX(0.75, p0, p1, p2, p3), getY(0.75, p0, p1, p2, p3), 0);
	Vector3 fifth = Vector3(getX(1.0, p0, p1, p2, p3), getY(1.0, p0, p1, p2, p3), 0);
	Vector3 normal = Vector3(-getdY(0, p0, p1, p2, p3), getdX(0, p0, p1, p2, p3), 0);

	//Establish rotation points.
	for (int j = 0; j < sides + 1; j++){
		vertices.push_back(first);
		vertices.push_back(second);
		vertices.push_back(third);
		vertices.push_back(fourth);
		vertices.push_back(fifth);

		//Rotate each vertex for next draw.
		first.set(first[0] * cos(rotation_angle) - first[2] * sin(rotation_angle), first[1], first[0] * sin(rotation_angle) + first[2] * cos(rotation_angle));
		second.set(second[0] * cos(rotation_angle) - second[2] * sin(rotation_angle), second[1], second[0] * sin(rotation_angle) + second[2] * cos(rotation_angle));
		third.set(third[0] * cos(rotation_angle) - third[2] * sin(rotation_angle), third[1], third[0] * sin(rotation_angle) + third[2] * cos(rotation_angle));
		fourth.set(fourth[0] * cos(rotation_angle) - fourth[2] * sin(rotation_angle), fourth[1], fourth[0] * sin(rotation_angle) + fourth[2] * cos(rotation_angle));
		fifth.set(fifth[0] * cos(rotation_angle) - fifth[2] * sin(rotation_angle), fifth[1], fifth[0] * sin(rotation_angle) + fifth[2] * cos(rotation_angle));
	}

	for (int k = 0; k < points; k++){
		normal = Vector3(-getdY((double)k / points, p0, p1, p2, p3), getdX((double)k / points, p0, p1, p2, p3), 0);
		normal.normalize();
		for (int i = 0; i < sides; i++){
			normals.push_back(normal);
			normal.set(normal[0] * cos(rotation_angle) - normal[2] * sin(rotation_angle), normal[1], normal[0] * sin(rotation_angle) + normal[2] * cos(rotation_angle));
		}
	}

	itr = vertices.begin();
	nitr = normals.begin();

	//Draw the part 1 of the bottom of glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 1;
	nitr = normals.begin() + sides;

	//Draw the part 2 of the bottom of glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 2;
	nitr = normals.begin() + sides * 2;

	//Draw the part 3 of the bottom of glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(-nitr->get(0), -nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();

	itr = vertices.begin() + 3;
	nitr = normals.begin() + sides * 3;

	//Draw the part 4 of the bottom of glass.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < sides; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr++;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr += points;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		itr--;
		glVertex3f(3 * itr->get(0), 3 * itr->get(1), 3 * itr->get(2));
		nitr++;
	}
	glEnd();
}

/* Method to draw the stick of the flag. */
void drawStick(){
	double side = 15;
	double rad = 0.15;
	//Rotation angle calculated from the amount of sides.
	double rotation_angle = 2 * 3.1415926535 / side;
	//Height
	double height = 5;
	double moveup = 6;
	//Start the two coords at 0, with right radius and height
	Vector3 first = Vector3(0, height + moveup, rad);
	Vector3 second = Vector3(0, -height + moveup, rad);
	//Calculate the next two positions, rotated around the original by the rotation_angle.
	Vector3 tmp = second;
	Vector3 third = Vector3(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), -height + moveup, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
	tmp = first;
	Vector3 fourth = Vector3(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), height + moveup, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
	Vector3 normal = Vector3(-1.0 * sin(rotation_angle), 0, 1.0 * cos(rotation_angle));

	//Establish the location of the stick.
	Matrix4 rotation = Matrix4();
	Matrix4 translation = Matrix4();
	rotation.identity();

	rotation.rotateZ(10.2);

	translation.identity();
	translation.set(Vector4(7, 8, 0, 1), 3);

	rotation.multMM(translation);

	rotation.multMM(wine.getmatrix(0));

	//Load the matrix for drawing.
	glLoadMatrixd(rotation.getPointer());


	glBegin(GL_QUADS);

	glColor3f(1.0, 0.75, 0.50);
	//Draw the sides until the max sides is reached, all while transfering starting points to last sides ending ones, and then rotating them again for the third and fourth.
	for (int i = 0; i < side; i++){
		glNormal3f(normal[0], normal[1], normal[2]);
		glVertex3f(first[0], first[1], first[2]);
		glVertex3f(second[0], second[1], second[2]);
		glVertex3f(third[0], third[1], third[2]);
		glVertex3f(fourth[0], fourth[1], fourth[2]);

		//Rotate each vertex for next draw.
		first = fourth;
		second = third;
		tmp = third;
		third.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), -height + moveup, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
		tmp = fourth;
		fourth.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), height + moveup, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
		tmp = normal;
		normal.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), 0, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
	}
	glEnd();

	//Draw top and bottom portions.
	glBegin(GL_POLYGON);
	glNormal3f(0, -1.0, 0);
	Vector3 point = Vector3(0, -height + moveup, rad);
	for (int i = 0; i < side; i++){
		glVertex3f(point[0], point[1], point[2]);

		tmp = point;
		point.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), -height + moveup, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 1.0, 0);
	point = Vector3(0, height + moveup, rad);
	for (int i = 0; i < side; i++){
		glVertex3f(point[0], point[1], point[2]);

		tmp = point;
		point.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), height + moveup, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
	}
	glEnd();
}

/* Method to draw the flag itself (part1). */
void drawFlag(){
	vector<Vector3> vertices;
	vector<Vector3> normals;

	//Control points.
	Vector3 p0 = Vector3(0, 0, 0);
	Vector3 p1 = Vector3(0.31, 0.25, 0);
	Vector3 p2 = Vector3(0.57, 0.11, 0);
	Vector3 p3 = Vector3(0.77, 0, 0);

	double index = 0;
	double inc = 0.1;

	//Establish points.
	for (int i = 0; i < 11; i++){
		vertices.push_back(Vector3(getX(index, p0, p1, p2, p3), getY(index, p0, p1, p2, p3), 0));
		index += inc;
	}
	
	//Establish normals of those points.
	index = 0;
	for (int i = 0; i < 11; i++){
		normals.push_back(Vector3(-getdY(index, p0, p1, p2, p3), getdX(index, p0, p1, p2, p3), 0));
		index += inc;
	}

	/* PART 2 STARTS HERE OF THE FLAG. */

	p0 = Vector3(0.77, 0, 0);
	p1 = Vector3(1.11, -0.19, 0);
	p2 = Vector3(1.42, 0, 0);
	p3 = Vector3(1.51, 0.13, 0);

	index = 0;

	//Establish points.
	for (int i = 0; i < 11; i++){
		vertices.push_back(Vector3(getX(index, p0, p1, p2, p3), getY(index, p0, p1, p2, p3), 0));
		index += inc;
	}

	//Establish normals of those points.
	index = 0;
	for (int i = 0; i < 11; i++){
		normals.push_back(Vector3(-getdY(index, p0, p1, p2, p3), getdX(index, p0, p1, p2, p3), 0));
		index += inc;
	}

	//Iterator to go through entries.
	vector<Vector3>::iterator itr;
	vector<Vector3>::iterator nitr;

	double scale = 1.0;
	double length = 1.75;

	itr = vertices.begin();
	nitr = normals.begin();

	//Establish the location of the flag.
	Matrix4 rotation = Matrix4();
	Matrix4 tmp = Matrix4();
	Matrix4 translation = Matrix4();
	rotation.identity();

	rotation.rotateY(3.1415926535 / 2);

	tmp.identity();
	tmp.rotateZ(-3.1415926535 / 4);

	rotation.multMM(tmp);

	translation.identity();
	translation.set(Vector4(5, 6, 0, 1), 3);

	rotation.multMM(translation);

	rotation.multMM(wine.getmatrix(0));

	//Load the matrix for drawing.
	glLoadMatrixd(rotation.getPointer());

	//Draw part 1 of flag.
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 1.0);
	for (int i = 0; i < 20; i++){
		glNormal3f(nitr->get(0), nitr->get(1), nitr->get(2));
		glVertex3f(scale * itr->get(0), scale * itr->get(1), scale * itr->get(2));
		itr++;
		glVertex3f(scale * itr->get(0), scale * itr->get(1), scale * itr->get(2));
		glVertex3f(scale * itr->get(0), scale * itr->get(1), scale * itr->get(2) - length);
		itr--;
		glVertex3f(scale * itr->get(0), scale * itr->get(1), scale * itr->get(2) - length);
		nitr++;
		itr++;
	}
	glEnd();

	p0 = Vector3(1.04, 0.06, 0);
	p1 = Vector3(1.38, -0.26, 0);
	p2 = Vector3(1.75, -0.20, 0);
	p3 = Vector3(2.08, 0.19, 0);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(wine.getmatrix(0).getPointer());

	getVectors(5, 10, 2 * 3.1415926535 / 10);
	getVectors2(5, 10, 2 * 3.1415926535 / 10);
	getVectors3(5, 10, 2 * 3.1415926535 / 10);
	getVectors4(5, 10, 2 * 3.1415926535 / 10);

	drawStick();
	drawFlag();
  
	glFlush();  
	glutSwapBuffers();
}

Glass::Glass(){
	matrix.identity();
}

/* Method used for access the various matrices the cube has. */
Matrix4& Glass ::getmatrix(int number){
	switch (number){
	case 0:
		return matrix;
		break;
	default:
		return matrix;
		break;
	}
}

/* Method used when the mouse button is initially clicked. Credit to Roger Crawfis's webpage for help.*/
void Glass::mouse(int button, int state, int x, int y){	
	// If the left/right mouse button is being pressed down, find the starting position in the window.
	if (state == 0){
		// Scale the position to a sphere coordinate system.
		original_position.set((2.0*x - wnew) / wnew, (hnew - 2.0*y) / hnew, 0);
		double mag = original_position.get_mag();
		mag = (mag < 1.0) ? mag : 1.0;
		// Set the "Z" value to one that is plausible.
		original_position.set(original_position[0], original_position[1], sqrt(1.001 - mag * mag));
		// Normalize for smaller numbers.
		original_position.normalize();
	}
}

/* Method used when the mouse button is being held down and moved. Credit to Roger Crawfis's webpage for help.*/
void Glass::coords(int x, int y){
	//Convert the position vector to coordinates on the "sphere".
	position.set((2.0*x - wnew) / wnew, (hnew - 2.0*y) / hnew, 0);
	double length = position.get_mag();
	length = (length < 1.0) ? length : 1.0;
	position.set(position.get(0), position.get(1), sqrt(1.001 - length * length));
	position.normalize();

	Vector3 difference;
	difference.subtractV(original_position, position);
	// Error sometimes occur when points are too close, so make sure the difference is big enough.
	if (difference.get_mag() > 0.001){
		// Create the rotation vector by finding the cross product of the starting point and current point.
		Vector3 rotation = Vector3();
		rotation.crossV(original_position, position);
		// Normalize rotation matrix. IMPORTANT!!!
		rotation.normalize();

		// Get the dot product in prep for rotation angle calculation.
		double dots = original_position.dotV(position);

		// The angle between the two vectors in radians.
		double rotation_angle = acos(dots / (original_position.get_mag() * position.get_mag()));
		rotation_angle *= 3.1415926535 / 180.00 * 100;

		// Get the rotation matrix by rotating an identity matrix and multiplying it by the current matrix.
		rotateM.identity();
		rotateM.rotateA(-rotation_angle, rotation);
		matrix.multMM(rotateM);

		// Set the current position to the original to compare next point.
		original_position.set(position.get(0), position.get(1), position.get(2));
	}
}

/* Function called when the mouse is pressed to be called. */
void mousemove(int button, int state, int x, int y){
	wine.mouse(button, state, x, y);
}

/* Function called when the mouse is pressed to be called. */
void mousecoords(int x, int y){
	wine.coords(x, y);
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Model Viewer");    	      // open window and set window title

  // Enable texturing:
  glEnable(GL_TEXTURE_2D);

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  glEnable(GL_NORMALIZE);
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
    
  // Initialize cube matrix:
  wine.getmatrix(0).identity();
    
  // Keyboard commands:
  glutMouseFunc(mousemove);
  glutMotionFunc(mousecoords);

  glutMainLoop();
  return 0;
}