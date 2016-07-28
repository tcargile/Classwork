// Trevor Cargile
// 813542789
// Project: Models with Mousetrack movement.
// Original code by: Professor Jurgen Schulze

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "cube.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "objreader.h"

using namespace std;

static Cube cube;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

// Globals to store the window for future use.
int wnew = 512;
int hnew = 512;

/* The colors used to recolor the cube when a key is pressed. */
double r = 0.0, g = 1.0, b = 0.0;

/* Global scalar to fit to window. */
double scalar = 1;
Vector3 center_object;

/* Constant to tell if displaying a unique object. */
int unique = 0;

/* Matrix used for the z rotation. */
Matrix4 rotateM = Matrix4();

/* Object values to be sent to the object reader. */
int nVerts;      // number of vertices in file
float *vertices; // pointer to list of vertices
float *normals;  // pointer to list of normals (number of normals equals number of vertices)
int nIndices;    // number of indices for vertices
int *indices;    // pointer to list of indices

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

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(cube.getmatrix(0).getPointer());

	// Unique isn't on, thus draw the original cube.
	if (unique == 0){
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
	}
	// Unique mode is now on, draw triangles.
	else if (unique == 1){
		glBegin(GL_TRIANGLES);

		glColor3f(r, g, b);		// Don't really need this, just in case we need to start changing the colors later.
		Vector3 coordinates;

		// Continuously loop through the vertices until there are no more. This will load the vertices to be viewed.
		int i = 0;
		int count = 0;
		while (count < nVerts){
			coordinates.set(vertices[i], vertices[i + 1], vertices[i + 2]);
			coordinates.scaleV(scalar);

			//Scan for the coordinates of the normals and the vectors.
			glNormal3f(normals[i], normals[i + 1], normals[i + 2]);
			//Translate the object to the center of the screen.
			glVertex3f(coordinates.get(0) - center_object.get(0) * scalar, coordinates.get(1) - center_object.get(1) * scalar, coordinates.get(2) - center_object.get(2) * scalar);
			i = i + 3;
			count++;
		}
		glEnd();
	}
  
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
	center.set(0, 0, 0);
	center_object.set(0, 0, 0);
	rotation_angle = 0;
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

/* Returns the index for the center matrix. */
double Cube::getcenter(int index){
	return center[index];
}

/* Method used when the mouse button is initially clicked. Credit to Roger Crawfis's webpage for help.*/
void Cube::mouse(int button, int state, int x, int y){	
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
void Cube::coords(int x, int y){
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

// Controls what objects need to be present in the scene. (With F1 - F4)
void Cube::objectloader(int key, int x, int y){
	if (key == GLUT_KEY_F1)
		unique = 0;
	else if (key == GLUT_KEY_F2 || key == GLUT_KEY_F3 || key == GLUT_KEY_F4){
		unique = 1;
		if (key == GLUT_KEY_F2)
			ObjReader::readObj("teddy.obj", nVerts, &vertices, &normals, nIndices, &indices);
		else if (key == GLUT_KEY_F3)
			ObjReader::readObj("bunny.obj", nVerts, &vertices, &normals, nIndices, &indices);
		else
			ObjReader::readObj("dragon.obj", nVerts, &vertices, &normals, nIndices, &indices);

		// Variables to store the min and max values in.
		double xMAX = -DBL_MAX;
		double xMIN = DBL_MAX;
		double yMAX = -DBL_MAX;
		double yMIN = DBL_MAX;
		double zMAX = -DBL_MAX;
		double zMIN = DBL_MAX;

		int count = 0;

		// Loop to find the min and max x values.
		for (count = 0; count < nVerts * 3; count += 3){
			if (vertices[count] < xMIN)
				xMIN = vertices[count];
			if (vertices[count] > xMAX)
				xMAX = vertices[count];
		}
		// Loop to find the min and max y values.
		for (count = 1; count < nVerts * 3; count += 3){
			if (vertices[count] < yMIN)
				yMIN = vertices[count];
			if (vertices[count] > yMAX)
				yMAX = vertices[count];
		}
		// Loop to find the min and max z values.
		for (count = 2; count < nVerts * 3; count += 3){
			if (vertices[count] < zMIN)
				zMIN = vertices[count];
			if (vertices[count] > zMAX)
				zMAX = vertices[count];
		}

		//cout << xMAX << " " << xMIN << " " << yMAX << " " << yMIN << " " << zMAX << " " << zMIN << endl;

		center_object.set((xMIN + xMAX) / 2, (yMIN + yMAX) / 2, (zMIN + zMAX) / 2);
		cout << "Offset required: " << (xMIN + xMAX) / 2 << '\t' << (yMIN + yMAX) / 2 << '\t' << (zMIN + zMAX) / 2 << endl;

		//Figure out the scale of the object.
		double sx = xMAX - xMIN;
		double sy = yMAX - yMIN;
		double sz = zMAX - zMIN;
		double d = sqrt(sx * sx + sy * sy + sz * sz);

		//Calculate the scalar value based on the size of the window.
		scalar = (sqrt(wnew * wnew + hnew * hnew) / 20) / d;
		cout << "Scale factor: " << scalar << endl;
	}
}

/* Function called when the mouse is pressed to be called. */
void mousemove(int button, int state, int x, int y){
	cube.mouse(button, state, x, y);
}

/* Function called when the mouse is pressed to be called. */
void mousecoords(int x, int y){
	cube.coords(x, y);
}

/* Function called when the mouse is pressed to be called. */
void functionhelper(int key, int x, int y){
	cube.objectloader(key, x, y);
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
    
  // Initialize cube matrix:
  cube.getmatrix(0).identity();
    
  // Keyboard commands:
  glutMouseFunc(mousemove);
  glutMotionFunc(mousecoords);
  glutSpecialFunc(functionhelper);

  glutMainLoop();
  return 0;
}