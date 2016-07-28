// Trevor Cargile
// 813542789
// Project: Robot Scene Graph
// Original code by: Professor Jurgen Schulze

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "driver.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Square.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "Robot.h"

using namespace std;

#define ROW_VALUE 20
#define COLUMN_VALUE 20

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

int wnew = 512;
int hnew = 512;
int frameCount = 0;
int currentTime;
int previousTime;
int fps = 0;

int cull_flag = -1;

int rendered = 0;
int culled = 0;

int show_spheres = -1;

vector<Robot*> robots;

double leg_angle = 0.0;
double arm_angle = 0.0;
double head_angle = 0.0;
double increment = 0.04;

Matrix4 translation;
Matrix4 rotation;
Matrix4 transform;
Matrix4 rotateM;
Matrix4 matrix;

Vector3 original_position;
Vector3 position;


/* FPS CALCULATOR - CREDIT GIVEN TO Ali BaderEddin @ mycodelog.com/2010/04/16/fps/ */
void calculateFPS(){
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if (timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
		cout << fps << endl;
		cout << "Rendered: " << rendered << endl;
		cout << "Culled: " << culled << endl;
	}
}

/* Main method to determine which robots are outside the viewing frustum. */
void cull(){
	if (cull_flag > 0){
		std::vector<Robot*>::iterator itr;
		itr = robots.begin();
		for (unsigned int i = 0; i < robots.size(); i++){
			(*itr)->culltest();
			itr++;
		}
	}
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	std::vector<Robot*>::iterator itr;

	leg_angle += increment;
	arm_angle += increment;
	if (leg_angle > 0.5)
		increment *= -1;
	else if (leg_angle < -0.5)
		increment *= -1;

	//Head Transformation
	transform.identity();
	transform.set(Vector4(0, 4.5, 0, 1), 3);
	itr = robots.begin();
	for (unsigned int i = 0; i < robots.size(); i++){
		(*itr)->headrotation.setTransform(transform);
		itr++;
	}

	//Leg 2 Transformation
	itr = robots.begin();
	for (unsigned int i = 0; i < robots.size(); i++){
		rotation.identity();
		transform.identity();
		transform.set(Vector4(0 - (*itr)->center[0], -2.5, 0 - (*itr)->center[2], 1), 3);
		rotation.rotateX(-leg_angle);
		transform.multMM(rotation);
		rotation.identity();
		rotation.set(Vector4(-1.5 + (*itr)->center[0], -2.5, 0 + (*itr)->center[2], 1), 3);
		transform.multMM(rotation);
		(*itr)->leg2rotation.setTransform(transform);
		itr++;
	}

	//Leg 1 Transformation
	itr = robots.begin();
	for (unsigned int i = 0; i < robots.size(); i++){
		rotation.identity();
		transform.identity();
		transform.set(Vector4(0 - (*itr)->center[0], -2.5, 0 - (*itr)->center[2], 1), 3);
		rotation.rotateX(leg_angle);
		transform.multMM(rotation);
		rotation.identity();
		rotation.set(Vector4(1.5 + (*itr)->center[0], -2.5, 0 + (*itr)->center[2], 1), 3);
		transform.multMM(rotation);
		(*itr)->leg1rotation.setTransform(transform);
		itr++;
	}

	//Arm 2 Transformation
	itr = robots.begin();
	for (unsigned int i = 0; i < robots.size(); i++){
		rotation.identity();
		transform.identity();
		transform.set(Vector4(0 - (*itr)->center[0], -2.5, 0 - (*itr)->center[2], 1), 3);
		rotation.rotateX(leg_angle);
		transform.multMM(rotation);
		rotation.identity();
		rotation.set(Vector4(-3.5 + (*itr)->center[0], 2.5, 0 + (*itr)->center[2], 1), 3);
		transform.multMM(rotation);
		(*itr)->arm2rotation.setTransform(transform);
		itr++;
	}

	//Arm 1 Transformation
	itr = robots.begin();
	for (unsigned int i = 0; i < robots.size(); i++){
		rotation.identity();
		transform.identity();
		transform.set(Vector4(0 - (*itr)->center[0], -2.5, 0 - (*itr)->center[2], 1), 3);
		rotation.rotateX(-leg_angle);
		transform.multMM(rotation);
		rotation.identity();
		rotation.set(Vector4(3.5 + (*itr)->center[0], 2.5, 0 + (*itr)->center[2], 1), 3);
		transform.multMM(rotation);
		(*itr)->arm1rotation.setTransform(transform);
		itr++;
	}

	itr = robots.begin();
	for (unsigned int i = 0; i < robots.size(); i++){
		(*itr)->top.setTransform(matrix);
		itr++;
	}

	if (cull_flag > 0){
		cull();
	}

	displayCallback();  // call display routine to re-draw cube
	calculateFPS();
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
	gluPerspective(0, 1, 10, 1000);
	glTranslatef(0, 0, -20);
	glMatrixMode(GL_MODELVIEW);
}

/* Recursively draw the robot. */
void drawRobot(){
	culled = 0;
	rendered = 0;
	std::vector<Robot*>::iterator tmp;
	tmp = robots.begin();
	for (unsigned int i = 0; i < robots.size(); i++){
		if ((*tmp)->outside != 1){
			rendered++;
			(*tmp)->top.draw((*tmp)->top.getTransform(), show_spheres);
		}
		else
			culled++;
		tmp++;
	}
}

/* Checks to see if the spheres need to be drawn. */
void drawSpheres(){
	std::vector<Robot*>::iterator tmp;
	tmp = robots.begin();
	for (unsigned int i = 0; i < robots.size(); i++){
		(*tmp)->location = (*tmp)->object.boundSphere((*tmp)->top.getTransform(), (*tmp)->center, show_spheres);
		tmp++;
	}
}

/* Processes key strokes from the user. */
void processKeys(unsigned char key, int x, int y){
	switch (key){
	case 115:
		show_spheres *= -1;
		break;
	case 99:{
		cull_flag *= -1;
		//Reset each to toggle culling.
		if (cull_flag < 0){
			std::vector<Robot*>::iterator itr;
			itr = robots.begin();
			for (unsigned int i = 0; i < robots.size(); i++){
				(*itr)->outside = 0;
				itr++;
			}
		}
		break;
	}
	case 119:{
		std::vector<Robot*>::iterator itr;
		itr = robots.begin();
		for (unsigned int i = 0; i < robots.size(); i++){
			(*itr)->location.print();
			itr++;
		}
		break;
	}
	default:
		break;;
	}
}

/* Method used when the mouse button is initially clicked. Credit to Roger Crawfis's webpage for help.*/
void mouse(int button, int state, int x, int y){
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
void coords(int x, int y){
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

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);

	cull();

	drawRobot();

	drawSpheres();

	glFlush();
	glutSwapBuffers();
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

  matrix.identity();

  rotateM.identity();

  for (int i = 0; i < ROW_VALUE; i++){
	  for (int j = 0; j < COLUMN_VALUE; j++)
		robots.push_back(new Robot(Vector3(20 * i -20, 0.0, 20 * j -20), Vector3(0.0, 1.0, 0.0)));
  }



  glutMouseFunc(mouse);
  glutMotionFunc(coords);

  // Keyboard commands:
  glutKeyboardFunc(processKeys);

  glutMainLoop();
  return 0;
}