// Trevor Cargile
// 813542789
// Project: Edited Spinning Cube with keybinds.
// Original code by: Professor Jurgen Schulze

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "cube.h"
#include "Matrix4.h"
#include "Vector3.h"

using namespace std;

static Cube cube;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

/* The colors used to recolor the cube when a key is pressed. */
double r = 0.0, g = 1.0, b = 0.0;
double speed = 0.01;

/* Translation vector that will be used for translating a matrix. */
Vector4 translation = Vector4();
/* Matrix used for the z rotation. */
Matrix4 rotateM = Matrix4();

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	cube.spin(speed, 0);     // rotate cube; if it spins too fast try smaller values
	displayCallback();  // call display routine to re-draw cube
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
	glTranslatef(0, 0, -20);
	glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(cube.getmatrix(0).getPointer());

  // Draw sides of cube in object coordinate system:
  glBegin(GL_QUADS);

	glColor3f(r, g, b);		// Front face rgb defined by the global variables.

	// Draw front face:
    glNormal3f(0.0, 0.0, 1.0);   
	glVertex3f(cube.getmatrix(1).get(0, 0), cube.getmatrix(1).get(0, 1), cube.getmatrix(1).get(0, 2));
	glVertex3f(cube.getmatrix(1).get(1, 0), cube.getmatrix(1).get(1, 1), cube.getmatrix(1).get(1, 2));
	glVertex3f(cube.getmatrix(1).get(2, 0), cube.getmatrix(1).get(2, 1), cube.getmatrix(1).get(2, 2));
	glVertex3f(cube.getmatrix(1).get(3, 0), cube.getmatrix(1).get(3, 1), cube.getmatrix(1).get(3, 2));

    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(cube.getmatrix(3).get(0, 0), cube.getmatrix(3).get(0, 1), cube.getmatrix(3).get(0, 2));
	glVertex3f(cube.getmatrix(3).get(1, 0), cube.getmatrix(3).get(1, 1), cube.getmatrix(3).get(1, 2));
	glVertex3f(cube.getmatrix(3).get(2, 0), cube.getmatrix(3).get(2, 1), cube.getmatrix(3).get(2, 2));
	glVertex3f(cube.getmatrix(3).get(3, 0), cube.getmatrix(3).get(3, 1), cube.getmatrix(3).get(3, 2));

    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(cube.getmatrix(4).get(0, 0), cube.getmatrix(4).get(0, 1), cube.getmatrix(4).get(0, 2));
	glVertex3f(cube.getmatrix(4).get(1, 0), cube.getmatrix(4).get(1, 1), cube.getmatrix(4).get(1, 2));
	glVertex3f(cube.getmatrix(4).get(2, 0), cube.getmatrix(4).get(2, 1), cube.getmatrix(4).get(2, 2));
	glVertex3f(cube.getmatrix(4).get(3, 0), cube.getmatrix(4).get(3, 1), cube.getmatrix(4).get(3, 2));

    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(cube.getmatrix(2).get(0, 0), cube.getmatrix(2).get(0, 1), cube.getmatrix(2).get(0, 2));
	glVertex3f(cube.getmatrix(2).get(1, 0), cube.getmatrix(2).get(1, 1), cube.getmatrix(2).get(1, 2));
	glVertex3f(cube.getmatrix(2).get(2, 0), cube.getmatrix(2).get(2, 1), cube.getmatrix(2).get(2, 2));
	glVertex3f(cube.getmatrix(2).get(3, 0), cube.getmatrix(2).get(3, 1), cube.getmatrix(2).get(3, 2));

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(cube.getmatrix(5).get(0, 0), cube.getmatrix(5).get(0, 1), cube.getmatrix(5).get(0, 2));
	glVertex3f(cube.getmatrix(5).get(1, 0), cube.getmatrix(5).get(1, 1), cube.getmatrix(5).get(1, 2));
	glVertex3f(cube.getmatrix(5).get(2, 0), cube.getmatrix(5).get(2, 1), cube.getmatrix(5).get(2, 2));
	glVertex3f(cube.getmatrix(5).get(3, 0), cube.getmatrix(5).get(3, 1), cube.getmatrix(5).get(3, 2));

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(cube.getmatrix(6).get(0, 0), cube.getmatrix(6).get(0, 1), cube.getmatrix(6).get(0, 2));
	glVertex3f(cube.getmatrix(6).get(1, 0), cube.getmatrix(6).get(1, 1), cube.getmatrix(6).get(1, 2));
	glVertex3f(cube.getmatrix(6).get(2, 0), cube.getmatrix(6).get(2, 1), cube.getmatrix(6).get(2, 2));
	glVertex3f(cube.getmatrix(6).get(3, 0), cube.getmatrix(6).get(3, 1), cube.getmatrix(6).get(3, 2));
	glEnd(); 
  
	glFlush();  
	glutSwapBuffers();
}

Cube::Cube(){
	/* Initialize both angles to 0 to start. */
	angle = 0.0;
	angleZ = 0.0;
	/* These 6 matrices hold the values of the faces of the cube. Used for scaling. */
	frontm = Matrix4(-5.0, 5.0, 5.0, 0, 5.0, 5.0, 5.0, 0, 5.0, -5.0, 5.0, 0, -5.0, -5.0, 5.0, 1);
	backm = Matrix4(-5.0, 5.0, -5.0, 0, 5.0, 5.0, -5.0, 0, 5.0, -5.0, -5.0, 0, -5.0, -5.0, -5.0, 1);
	leftm = Matrix4(-5.0, 5.0, 5.0, 0, -5.0, 5.0, -5.0, 0, -5.0, -5.0, -5.0, 0, -5.0, -5.0, 5.0, 1);
	rightm = Matrix4(5.0, 5.0, 5.0, 0, 5.0, 5.0, -5.0, 0, 5.0, -5.0, -5.0, 0, 5.0, -5.0, 5.0, 1);
	topm = Matrix4(-5.0, 5.0, 5.0, 0, 5.0, 5.0, 5.0, 0, 5.0, 5.0, -5.0, 0, -5.0, 5.0, -5.0, 1);
	bottomm = Matrix4(-5.0, -5.0, -5.0, 0, 5.0, -5.0, -5.0, 0, 5.0, -5.0, 5.0, 0, -5.0, -5.0, 5.0, 1);
	/* Where the center of the cube should be. Used for translating. */
	center = Vector3(0, 0, 0);
}

/* Method used for access the various matrices the cube has. */
Matrix4& Cube::getmatrix(int number){
	switch (number){
	case 0:
		return matrix;
		break;
	case 1:
		return frontm;
		break;
	case 2:
		return backm;
		break;
	case 3:
		return leftm;
		break;
	case 4:
		return rightm;
		break;
	case 5:
		return topm;
		break;
	case 6:
		return bottomm;
		break;
	default:
		return matrix;
		break;
	}
}

void Cube::spin(double deg, int direction){
	double holderY = angle;
	double holderZ = angleZ;
	/* If the idle calls spin, increment the Y angle up. */
	if (direction == 0)
		angle += deg;
	else
		angleZ += deg;
	if (angle > 360.0 || angle < -360.0) angle = 0.0;
	if (angleZ > 360.0 || angleZ < -360.0) angleZ = 0.0;

	/*  In order for the matrix to rotate around its own center, move cube to origin of coordinates,
		rotate around Z first (if there is any degrees to rotate around) then multiply with the rotation around Y, then move back to center of the cube.
		It's important to store the position of the original matrix so you need to keep multiplying the matrix by new transofmations. This means that
		we need to store the difference in rotation angles from the previous rotation so it's just an updated move.*/
	matrix.set(Vector4(0, 0, 0, 1), 3);
	rotateM.rotateZ(angleZ - holderZ);
	matrix.multMM(rotateM);
	rotateM.rotateY(angle - holderY);
	matrix.multMM(rotateM);
	matrix.set(Vector4(center.get(0), center.get(1), center.get(2), 1), 3);
}

/* Returns the index for the center matrix. */
double Cube::getcenter(int index){
	return center[index];
}

/* Processes key strokes from the user. */
void Cube::processKeys(unsigned char key, int x, int y){
	switch (key){
	/* Make the cube spin in the opposite direction. (c) */
	case 99:{
		speed *= -1;
		center.print();
		break;
	}
	/* Change the cube to red. (1) */
	case 49:
		r = 1.0;
		g = 0.0;
		b = 0.0;
		center.print();
		break;
	/* Change the cube to green. (2) */
	case 50:
		r = 0.0;
		g = 1.0;
		b = 0.0;
		center.print();
		break;
	/* Change the cube to blue. (3) */
	case 51:
		r = 0.0;
		g = 0.0;
		b = 1.0;
		center.print();
		break;
	/* Change the cube to yellow. (4) */
	case 52:
		r = 1.0;
		g = 1.0;
		b = 0.0;
		center.print();
		break;
	/* Reset the cube position. (i) */
	case 105:
		/* Reset color to green. */
		r = 0.0;
		g = 1.0;
		b = 0.0;
		/* Reset angles to 0, and go back to original direction. */
		speed = 0.01;
		angle = 0.0;
		angleZ = 0.0;
		/* Default the matrix to 0, and rescale the sides to their original values. */
		matrix.identity();
		frontm = Matrix4(-5.0, 5.0, 5.0, 0, 5.0, 5.0, 5.0, 0, 5.0, -5.0, 5.0, 0, -5.0, -5.0, 5.0, 1);
		backm = Matrix4(-5.0, 5.0, -5.0, 0, 5.0, 5.0, -5.0, 0, 5.0, -5.0, -5.0, 0, -5.0, -5.0, -5.0, 1);
		leftm = Matrix4(-5.0, 5.0, 5.0, 0, -5.0, 5.0, -5.0, 0, -5.0, -5.0, -5.0, 0, -5.0, -5.0, 5.0, 1);
		rightm = Matrix4(5.0, 5.0, 5.0, 0, 5.0, 5.0, -5.0, 0, 5.0, -5.0, -5.0, 0, 5.0, -5.0, 5.0, 1);
		topm = Matrix4(-5.0, 5.0, 5.0, 0, 5.0, 5.0, 5.0, 0, 5.0, 5.0, -5.0, 0, -5.0, 5.0, -5.0, 1);
		bottomm = Matrix4(-5.0, -5.0, -5.0, 0, 5.0, -5.0, -5.0, 0, 5.0, -5.0, 5.0, 0, -5.0, -5.0, 5.0, 1);
		/* Reoriginate the center of the cube to 0, 0, 0 (the origin)*/
		center.set(0, 0, 0);
		/* Print the location of the center of the cube. */
		center.print();
	/* Scale the cube up. (S) */
	case 83:
		/* Multiply each face by the scalar to scale it up. */
		cube.frontm.scaleM(1.05);
		cube.backm.scaleM(1.05);
		cube.topm.scaleM(1.05);
		cube.bottomm.scaleM(1.05);
		cube.leftm.scaleM(1.05);
		cube.rightm.scaleM(1.05);
		/* Print the location of the center of the cube. */
		center.print();
		break;
	/* Scale the cube down. (s) */
	case 115:
		/* Multiply each face by the scalar to scale it down. */
		cube.frontm.scaleM(0.95);
		cube.backm.scaleM(0.95);
		cube.topm.scaleM(0.95);
		cube.bottomm.scaleM(0.95);
		cube.leftm.scaleM(0.95);
		cube.rightm.scaleM(0.95);
		/* Print the location of the center of the cube. */
		center.print();
		break;
	/* Move the cube to the left. (x) */
	case 120:
		/* Move the center by how much you are moving. */
		translation.set(-0.2, 0, 0, 0);	
		center.set(translation.get(0) + cube.center.get(0), translation.get(1) + cube.center.get(1), translation.get(2) + cube.center.get(2));
		/* Print the location of the center of the cube. */
		center.print();
		break;
	/* Move the cube to the right. (X) */
	case 88:
		translation.set(0.2, 0, 0, 0);
		cube.center.set(translation.get(0) + cube.center.get(0), translation.get(1) + cube.center.get(1), translation.get(2) + cube.center.get(2));
		center.print();
		break;
	/* Move the cube down. (y) */
	case 121:
		translation.set(0, -0.2, 0, 0);
		cube.center.set(translation.get(0) + cube.center.get(0), translation.get(1) + cube.center.get(1), translation.get(2) + cube.center.get(2));
		center.print();
		break;
	/* Move the cube up. (Y) */
	case 89:
		translation.set(0, 0.2, 0, 0);
		cube.center.set(translation.get(0) + cube.center.get(0), translation.get(1) + cube.center.get(1), translation.get(2) + cube.center.get(2));
		center.print();
		break;
	/* Move the cube forward. (z) */
	case 122:
		translation.set(0, 0, 0.4, 0);
		cube.center.set(translation.get(0) + cube.center.get(0), translation.get(1) + cube.center.get(1), translation.get(2) + cube.center.get(2));
		center.print();
		break;
	/* Move the cube back. (Z) */
	case 90:
		translation.set(0, 0, -0.4, 0);
		cube.center.set(translation.get(0) + cube.center.get(0), translation.get(1) + cube.center.get(1), translation.get(2) + cube.center.get(2));
		center.print();
		break;
	/* Rotate around z axis 10 degrees counterclockwise. (r) */
	case 114:
		/* Subtract some degrees to the Z angle. */
		cube.spin(-0.1, 1);
		center.print();
		break;
	/* Rotate around z axis 10 degrees clockwise. (R) */
	case 82:
		/* Add some degrees to the Z angle. */
		cube.spin(0.1, 1);
		center.print();
		break;
	/* If keystroke isn't recognized do nothing. */
	default:
		break;
	}
}

/* Function called when a key is pressed, transfers keystroke to a cube method to process the cube. */
void terminal(unsigned char key, int x, int y){
	cube.processKeys(key, x, y);
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube");    	      // open window and set window title

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
  cube.getmatrix(0).identity();
    
  // Keyboard commands:
  glutKeyboardFunc(terminal);

  glutMainLoop();
  return 0;
}