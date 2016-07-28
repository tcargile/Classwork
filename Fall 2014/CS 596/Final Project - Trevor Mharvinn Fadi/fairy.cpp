// Trevor Cargile
// 813542789
// Project: Wine Glass with B Curves
// Original code by: Professor Jurgen Schulze

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "fairy.h"
#include "Matrix4.h"
#include "Vector3.h"

using namespace std;

//int Window::width  = 512;   // set window width in pixels here
//int Window::height = 512;   // set window height in pixels here

////----------------------------------------------------------------------------
//// Callback method called when system is idle.
//void Window::idleCallback(void)
//{
//	displayCallback();  // call display routine to re-draw cube
//}

////----------------------------------------------------------------------------
//// Callback method called when window is resized.
//void Window::reshapeCallback(int w, int h)
//{
//	width = w;
//	height = h;
//	wnew = w;
//	hnew = h;
//	glViewport(0, 0, w, h);  // set new viewport size
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
//	glTranslatef(0, 0, -20);
//	glMatrixMode(GL_MODELVIEW);
//}

double getX(double t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3){
	return ((1 - t) * (1 - t) * (1 - t)) * p0[0] + (3 * t * ((1 - t) * (1 - t))) * p1[0] + (3 * t * t * (1 - t)) * p2[0] + (t * t * t) * p3[0];
}

double getZ(double t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3){
	return ((1 - t) * (1 - t) * (1 - t)) * p0[2] + (3 * t * ((1 - t) * (1 - t))) * p1[2] + (3 * t * t * (1 - t)) * p2[2] + (t * t * t) * p3[2];
}

/* Method to get the vectors for drawing inside the wine glass. */
void Fairy::draw(){
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;
	Vector3 p3;

	//Determine where on the path the orb should be.
	switch (chunk){
	case 0:
		p0 = path[0];
		p1 = path[1];
		p2 = path[2];
		p3 = path[3];
		break;
	case 1:
		p0 = path[3];
		p1 = path[4];
		p2 = path[5];
		p3 = path[6];
		break;
	case 2:
		p0 = path[6];
		p1 = path[7];
		p2 = path[8];
		p3 = path[9];
		break;
	case 3:
		p0 = path[9];
		p1 = path[10];
		p2 = path[11];
		p3 = path[12];
		break;
	case 4:
		p0 = path[12];
		p1 = path[13];
		p2 = path[14];
		p3 = path[15];
		break;
	case 5:
		p0 = path[15];
		p1 = path[16];
		p2 = path[17];
		p3 = path[18];
		break;
	default:
		break;
	}
	
	//Scale the path if needed:
	p0 = Vector3(p0[0] * 4, p0[1] * 4, p0[2] * 4);
	p1 = Vector3(p1[0] * 4, p1[1] * 4, p1[2] * 4);
	p2 = Vector3(p2[0] * 4, p2[1] * 4, p2[2] * 4);
	p3 = Vector3(p3[0] * 4, p3[1] * 4, p3[2] * 4);

	position = Vector3(getX(tpos, p0, p1, p2, p3) + center[0], 0 + center[1], getZ(tpos, p0, p1, p2, p3) + center[2]);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	glDisable(GL_LIGHTING);
	glutSolidSphere(2.0, 100, 100);

	//glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
	glutSolidSphere(2.1, 100, 100);
	glColor4f(1.0f, 1.0f, 0.0f, 0.295f);
	glutSolidSphere(2.2, 100, 100);
	glColor4f(1.0f, 1.0f, 0.0f, 0.26f);
	glutSolidSphere(2.3, 100, 100);
	glColor4f(1.0f, 1.0f, 0.0f, 0.225f);
	glutSolidSphere(2.4, 100, 100);
	glColor4f(1.0f, 1.0f, 0.0f, 0.19f);
	glutSolidSphere(2.6, 100, 100);
	glColor4f(1.0f, 1.0f, 0.0f, 0.155f);
	glutSolidSphere(2.8, 100, 100);
	glColor4f(1.0f, 1.0f, 0.0f, 0.14f);
	glutSolidSphere(3.0, 100, 100);
	glColor4f(1.0f, 1.0f, 0.0f, 0.13f);
	glutSolidSphere(3.2, 100, 100);
	glEnable(GL_LIGHTING);

	float light2_position[] = { position[0], position[1], position[2], 1.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glPopMatrix();

	tpos += increment;
	if (tpos > 1.0){
		tpos = 0;
		chunk++;
	}
	if (chunk > 5)
		chunk = 0;
}

////POINT LIGHT PUT IN MAIN PROJECT
////Create pointlight:
//float light2_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
//float light2_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//float light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//float light2_position[] = { 0.0, 0.0, 0.0, 1.0 };
//
//glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
//glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
//glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
//glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
//glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0);
//glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.0);
//glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);
//
//glEnable(GL_LIGHT2);

////----------------------------------------------------------------------------
//// Callback method called when window readraw is necessary or
//// when glutPostRedisplay() was called.
//void Window::displayCallback(void)
//{
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffers and stencil
//	//glLoadMatrixd(fairy.getmatrix().getPointer());
//
//	fairy.draw();
//}

/* Default constructor with the center at 0,0,0. */
Fairy::Fairy(){
	matrix.identity();

	//Input the coords into the Vector3 array.
	path[0] = Vector3(0, 0, 0);
	path[1] = Vector3(2.28, 0, -0.30);
	path[2] = Vector3(3.94, 0, -1.70);
	path[3] = Vector3(4.48, 0, -3.44);
	path[4] = Vector3(4.70, 0, -5.46);
	path[5] = Vector3(4.16, 0, -7.40);
	path[6] = Vector3(3.00, 0, -7.98);
	path[7] = Vector3(1.64, 0, -8.36);
	path[8] = Vector3(-0.46, 0, -8.18);
	path[9] = Vector3(-1.72, 0, -6.66);
	path[10] = Vector3(-3.02, 0, -4.80);
	path[11] = Vector3(-1.72, 0, -4.54);
	path[12] = Vector3(-0.12, 0, -4.36);
	path[13] = Vector3(2.00, 0, -4.24);
	path[14] = Vector3(0.58, 0, -3.20);
	path[15] = Vector3(-1.38, 0, -1.90);
	path[16] = Vector3(-4.20, 0, 0.24);
	path[17] = Vector3(-1.16, 0, 0.26);
	path[18] = Vector3(0, 0, 0);

	center = Vector3(0, 0, 0);
	chunk = 1;
	tpos = 0;

	increment = 0.005;
}

/* Constuctor to specify where the fairy should start. */
Fairy::Fairy(Vector3 cntr){
	matrix.identity();

	//Input the coords into the Vector3 array.
	path[0] = Vector3(0, 0, 0);
	path[1] = Vector3(2.28, 0, -0.30);
	path[2] = Vector3(3.94, 0, -1.70);
	path[3] = Vector3(4.48, 0, -3.44);
	path[4] = Vector3(4.70, 0, -5.46);
	path[5] = Vector3(4.16, 0, -7.40);
	path[6] = Vector3(3.00, 0, -7.98);
	path[7] = Vector3(1.64, 0, -8.36);
	path[8] = Vector3(-0.46, 0, -8.18);
	path[9] = Vector3(-1.72, 0, -6.66);
	path[10] = Vector3(-3.02, 0, -4.80);
	path[11] = Vector3(-1.72, 0, -4.54);
	path[12] = Vector3(-0.12, 0, -4.36);
	path[13] = Vector3(2.00, 0, -4.24);
	path[14] = Vector3(0.58, 0, -3.20);
	path[15] = Vector3(-1.38, 0, -1.90);
	path[16] = Vector3(-4.20, 0, 0.24);
	path[17] = Vector3(-1.16, 0, 0.26);
	path[18] = Vector3(0, 0, 0);

	center = Vector3(cntr[0], cntr[1], cntr[2]);
	chunk = 1;
	tpos = 0;

	increment = 0.005;
}

/* Method used for access the various matrices the cube has. */
Matrix4& Fairy ::getmatrix(){
	return matrix;
}

//int main(int argc, char *argv[])
//{
//  float specular[]  = {1.0, 1.0, 1.0, 1.0};
//  float shininess[] = {100.0};
//  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
//  
//  glutInit(&argc, argv);      	      	      // initialize GLUT
//  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
//  glutInitWindowSize(Window::width, Window::height);      // set initial window size
//  glutCreateWindow("OpenGL Model Viewer");    	      // open window and set window title
//
//  // Enable texturing:
//  glEnable(GL_TEXTURE_2D);
//
//  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
//  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
//  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
//  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
//  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
//  glMatrixMode(GL_PROJECTION); 
//  glEnable(GL_NORMALIZE);
//  
//  // Generate material properties:
//  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
//  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
//  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//  glEnable(GL_COLOR_MATERIAL);
//
//  // Generate light source:
//  glLightfv(GL_LIGHT0, GL_POSITION, position);
//  glEnable(GL_LIGHTING);
//  //glEnable(GL_LIGHT0);
//  
//  // Install callback functions:
//  glutDisplayFunc(Window::displayCallback);
//  glutReshapeFunc(Window::reshapeCallback);
//  glutIdleFunc(Window::idleCallback);
//    
//  // Initialize cube matrix:
//  fairy.getmatrix().identity();
//    
//  //POINT LIGHT PUT IN MAIN PROJECT
//  //Create pointlight:
//  float light2_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
//  float light2_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//  float light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//  float light2_position[] = { 0.0, 0.0, 0.0, 1.0 };
//
//  glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
//  glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
//  glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
//  glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
//  glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0);
//  glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.0);
//  glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);
//
//  glEnable(GL_LIGHT2);
//
//  // Keyboard commands:
//  //glutMouseFunc(mousemove);
//  //glutMotionFunc(mousecoords);
//
//  glutMainLoop();
//  return 0;
//}