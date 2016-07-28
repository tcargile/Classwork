// Trevor Cargile
// 813542789
// Project: Textured Cylinder
// Original code by: Professor Jurgen Schulze

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "cylinder.h"
#include "Matrix4.h"
#include "Vector3.h"

using namespace std;

static Cylinder cylinder;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

// Globals to store the window for future use.
int wnew = 512;
int hnew = 512;

// Globals for height/width of txture.
int htext;
int wtext;

/* The colors used to recolor the cube when a key is pressed. */
double r = 1.0, g = 1.0, b = 1.0;

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

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(cylinder.getmatrix(0).getPointer());

	// Call to draw the cylinder with radius and amount of sides.
	cylinder.draw(5.0,32);
  
	glFlush();  
	glutSwapBuffers();
}

Cylinder::Cylinder(){
	matrix.identity();
}

/* Draws a cylinder with the appropriate amount of sides and radius. Height being half of circumference. */
void Cylinder::draw(double rad, int side){
	//Rotation angle calculated from the amount of sides.
	double rotation_angle = 2 * 3.1415926535 / side;
	//Height is half the circumference (or circumference is double height.)
	double height = 3.1415926535 * rad / 2;
	//Start the two coords at 0, with right radius and height
	Vector3 first = Vector3(0, height, rad);
	Vector3 second = Vector3(0, -height, rad);
	//Calculate the next two positions, rotated around the original by the rotation_angle.
	Vector3 tmp = second;
	Vector3 third = Vector3(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), -height, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
	tmp = first;
	Vector3 fourth = Vector3(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), height, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
	Vector3 normal = Vector3(-1.0 * sin(rotation_angle), 0, 1.0 * cos(rotation_angle));

	//Texture Coords that will be used to map each vertex:
	double textwside = 1.0 / side;

	//Vectors to hold the coordinates of the textures (s and t):
	Vector3 tfirst = Vector3(1.0, 1.0, 0);
	Vector3 tsecond = Vector3(1.0, 0.0, 0);
	Vector3 tthird = Vector3(1 - textwside, 0.0, 0);
	Vector3 tfourth = Vector3(1 - textwside, 1.0, 0);

	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	//Draw the sides until the max sides is reached, all while transfering starting points to last sides ending ones, and then rotating them again for the third and fourth.
	for (int i = 0; i < side; i++){
		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2d(tfirst[0],tfirst[1]); glVertex3f(first[0], first[1], first[2]);
		glTexCoord2d(tsecond[0],tsecond[1]); glVertex3f(second[0], second[1], second[2]);
		glTexCoord2d(tthird[0],tthird[1]); glVertex3f(third[0], third[1], third[2]);
		glTexCoord2d(tfourth[0],tfourth[1]); glVertex3f(fourth[0], fourth[1], fourth[2]);

		//Rotate each vertex for next draw.
		first = fourth;
		second = third;
		tmp = third;
		third.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), -height, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
		tmp = fourth;
		fourth.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), height, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
		tmp = normal;
		normal.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), 0, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));

		//Shift textures for next draw:
		tfirst = tfourth;
		tsecond = tthird;
		tthird.set(tthird[0] - textwside, 1.0, 0);
		tfourth.set(tfourth[0] - textwside, 0.0, 0);
	}
	glEnd();

	//Draw top and bottom portions.
	glBegin(GL_POLYGON);
	glNormal3f(0, -1.0, 0);
	Vector3 point = Vector3(0, -height, rad);
	for (int i = 0; i < side; i++){
		glVertex3f(point[0], point[1], point[2]);

		tmp = point;
		point.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), -height, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 1.0, 0);
	point = Vector3(0, height, rad);
	for (int i = 0; i < side; i++){
		glVertex3f(point[0], point[1], point[2]);

		tmp = point;
		point.set(tmp[0] * cos(rotation_angle) - tmp[2] * sin(rotation_angle), height, tmp[0] * sin(rotation_angle) + tmp[2] * cos(rotation_angle));
	}
	glEnd();
}

/* Method used for access the various matrices the cube has. */
Matrix4& Cylinder::getmatrix(int number){
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
void Cylinder::mouse(int button, int state, int x, int y){	
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
void Cylinder::coords(int x, int y){
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

/* Function called to rotate cylinder after 50 milliseconds. */
void rotate_cylinder(int t){
	cylinder.rotate_timer(t);
}

/* Rotate the cylinder so that it will complete one rotation after 10 seconds. */
void Cylinder::rotate_timer(int t){
	rotateM.identity();
	rotateM.rotateY(2.5 * 3.1415926535 / 200);
	matrix.multMM(rotateM);
	//Call TimerFunc again so it will trigger again after 50 milliseconds.
	glutTimerFunc(50, rotate_cylinder, 0);
}

//CREDIT TO PROFESSOR SHULZE FOR THIS METHOD!
/** Load a ppm file from disk.
@input filename The location of the PPM file.  If the file is not found, an error message
will be printed and this function will return 0
@input width This will be modified to contain the width of the loaded image, or 0 if file not found
@input height This will be modified to contain the height of the loaded image, or 0 if file not found
@return Returns the RGB pixel data as interleaved unsigned chars (R0 G0 B0 R1 G1 B1 R2 G2 B2 .... etc) or 0 if an error ocured
**/
unsigned char* loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}

// CREDIT TO PROFESSOR SHULZE FOR THIS METHOD!
// load image file into texture object
void loadTexture()
{
	GLuint texture[1];     // storage for one texture
	int twidth, theight;   // texture width/height [pixels]
	unsigned char* tdata;  // texture pixel data

	// Load image file
	tdata = loadPPM("texture.ppm", twidth, theight);
	if (tdata == NULL) return;

	htext = theight;
	wtext = twidth;

	// Create ID for texture
	glGenTextures(1, &texture[0]);

	// Set this texture to be the one we are working with
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	// Set bi-linear filtering for both minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

/* Function called when the mouse is pressed to be called. */
void mousemove(int button, int state, int x, int y){
	cylinder.mouse(button, state, x, y);
}

/* Function called when the mouse is pressed to be called. */
void mousecoords(int x, int y){
	cylinder.coords(x, y);
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
  cylinder.getmatrix(0).identity();

  // Load the texture file:
  loadTexture();
    
  // Keyboard commands:
  //glutMouseFunc(mousemove);
  //glutMotionFunc(mousecoords);
  glutTimerFunc(50, rotate_cylinder, 0);

  glutMainLoop();
  return 0;
}