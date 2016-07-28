// Trevor Cargile
// 813542789
// Project: Robot Scene Graph
// Original code by: Professor Jurgen Schulze
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "shader.h"
#include <GL/glut.h>
#include "driver.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Square.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "Building.h"
#include "fairy.h"


using namespace std;

#define ROW_VALUE 0
#define COLUMN_VALUE 0

int Window::width  = 1900;   // set window width in pixels here
int Window::height = 1000;   // set window height in pixels here
Vector3 trackposition;
vector<int> posXtracker;
vector<int> posZtracker;

int wnew = 1900;
int hnew = 1000;
int frameCount = 0;
int currentTime;
int previousTime;
int fps = 0;
bool switchScene = false;
bool genCity = false;
double dist = 20;
int cull_flag = -1;

int rendered = 0;
int culled = 0;
static BOOL g_createFullScreen;											// If TRUE, Then Create Fullscreen


//Fairy object. (NOTE: You can specify coordinates by including a Vector3 in the constructor.
Fairy fairy = Fairy();
int show_spheres = -1;


//Mharv stuff
char toon_vert[] = "toon.vert";
char toon_frag[] = "toon.frag";
Shader *shader;
bool toggle_shader = false;
struct Particle {
	Vector3 pos;
	Vector3 vel;
	Vector4 color;
	float rotate;
	float age;
	float lifetime;

	Particle() {
		pos = Vector3(0, 0, 0);
		vel = Vector3(0, 0, 0);
		color = Vector4(1, 1, 1, 1);
		age = 0;
		lifetime = 0;
	}
};
static int num_rain = 1000;
static vector<Particle> rain(num_rain, Particle());
void initializeRain() {

	for (int i = 0; i<num_rain; i++) {
		rain[i].vel = Vector3(0, -0.05, 0);
		rain[i].age = rand() % 100 + 1;
		rain[i].lifetime = rand() % 100 + 1;
		rain[i].pos = Vector3(0.1*(rand() % 201 - 100), 10 - 10 * (rain[i].age / rain[i].lifetime), 0.1*(rand() % 201 - 100));
	}
}

void updateRain() {

	for (int i = 0; i<num_rain; i++) {
		if (rain[i].age > rain[i].lifetime) {
			rain[i].pos = Vector3(0.1*(rand() % 201 - 100), 10, 0.1*(rand() % 201 - 100));
			rain[i].vel = Vector3(0, -0.05, 0);
			rain[i].age = 0;
		}
		else {
			float x = rain[i].pos.get(0);
			float y = rain[i].pos.get(1);
			float z = rain[i].pos.get(2);

			float vy = rain[i].vel.get(1);

			y += vy;

			rain[i].pos = Vector3(x, y, z);
			rain[i].age += 0.1;
		}
	}
}

void drawRain() {
	glPushMatrix();

	//glEnable(GL_POINT_SMOOTH);
	//glPointSize(5);
	glLineWidth(2);

	// translate to center around player
	GLfloat curr[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, curr);
	Matrix4 mv = Matrix4(
		curr[0], curr[1], curr[2], curr[3],
		curr[4], curr[5], curr[6], curr[7],
		curr[8], curr[9], curr[10], curr[11],
		curr[12], curr[13], curr[14], curr[15]
		);

	glBegin(GL_LINES);
	for (int i = 0; i<num_rain; i++) {
		glColor3f(0, 0, 1);
		glVertex3f(rain[i].pos.get(0), rain[i].pos.get(1) - 0.2, rain[i].pos.get(2));
		glVertex3f(rain[i].pos.get(0), rain[i].pos.get(1) + 0.2, rain[i].pos.get(2));
	}
	glEnd();


	glPopMatrix();
}
//ENd Mharv Stuff
vector<Building*> Buildings;
vector<vector<int>> grid(50 , vector<int> (50 , 0));

Matrix4 translation;
Matrix4 rotation;
Matrix4 transform;
Matrix4 rotateM;
Matrix4 matrix;

Vector3 original_position;
Vector3 position;

void cull(){
	if (cull_flag > 0){
		std::vector<Building*>::iterator itr;
		itr = Buildings.begin();
		for (unsigned int i = 0; i < Buildings.size(); i++){
			(*itr)->culltest();
			itr++;
		}
	}
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	std::vector<Building*>::iterator itr;

	itr = Buildings.begin();
	for (unsigned int i = 0; i < Buildings.size(); i++){
		(*itr)->top.setTransform(matrix);
		itr++;
	}

	if (cull_flag > 0){
		cull();
	}

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
	glFrustum(-19.0, 19.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
	gluPerspective(0, 1, 10, 1000);
	glTranslatef(0, 0, -20);
	glMatrixMode(GL_MODELVIEW);
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


/* Draw the buildings. */
void drawBuilding(){
	culled = 0;
	rendered = 0;
	std::vector<Building*>::iterator tmp;
	tmp = Buildings.begin();
	for (unsigned int i = 0; i < Buildings.size(); i++){
		if ((*tmp)->outside != 1){
			rendered++;
			(*tmp)->top.draw((*tmp)->top.getTransform(), show_spheres);
		}
		else
			culled++;
		tmp++;
	}
}

/* Processes key strokes from the user. */
void processKeys(unsigned char key, int x, int y){
	switch (key){
	case 'b':
		/*show_spheres *= -1;
		break;*/
		if (toggle_shader)
		{
			toggle_shader = false;
			shader->unbind();
		}
		else
		{
			toggle_shader = true;
			shader->bind();
		}
		break;
	case 99:{														// c
		cull_flag *= -1;
		//Reset each to toggle culling.
		if (cull_flag < 0){
			std::vector<Building*>::iterator itr;
			itr = Buildings.begin();
			for (unsigned int i = 0; i < Buildings.size(); i++){
				(*itr)->outside = 0;
				itr++;
			}
		}
		break;
	}
	case 'w':
		glMatrixMode(GL_PROJECTION);
		glTranslated(0, 0, dist/2);
		trackposition.addV(Vector3(0, 0, dist / 2));
		break;
	case 'a':
		glMatrixMode(GL_PROJECTION);
		glTranslated(dist/2, 0, 0);
		trackposition.addV(Vector3(-(dist/2), 0, 0));
		break;
	case 's':
		glMatrixMode(GL_PROJECTION);
		glTranslated(0, 0, -dist / 2);
		trackposition.addV(Vector3(0, 0, -dist / 2));
		break;
	case 'd':
		glMatrixMode(GL_PROJECTION);
		glTranslated(-dist / 2, 0, 0);
		trackposition.addV(Vector3(dist / 2, 0, 0));
		break;

	case 't':
		dist = 20;
		glMatrixMode(GL_PROJECTION);
		if (switchScene){
			if (trackposition.get(0) != -0 || trackposition.get(2) != 0){
				glTranslated(trackposition.get(0), trackposition.get(1), trackposition.get(2));
				trackposition.set(-0, 0, 0);
			}
		}
		Buildings.clear();
		posXtracker.clear();
		posZtracker.clear();
		switchScene = !switchScene;
		glMatrixMode(GL_MODELVIEW);
		break;

	case 'g':
		Buildings.clear();
		posXtracker.clear();
		posZtracker.clear();
		dist = 100;
		genCity = !genCity;
		if (genCity == false)
			dist = 20;
		break;

	default:
		break;;
	}
}


//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	if (switchScene){
		glClearColor(0.0, 0.0, 1.0, 1.0);   	      // set clear color to black
		fairy.draw();
		drawRain();
	}
	else{
		glClearColor(0.0, 0.0, 0.0, 1.0);   	      // set clear color to black

		double posX = trackposition.get(0);
		double posZ = trackposition.get(2);
		double tempX, tempZ;
		int height;
		vector<int>::iterator Xit;
		vector<int>::iterator Zit;
		if (genCity){
			if (fmod(posX + 0, dist) == 0 && fmod(-(posZ + 0), dist) == 0){
				tempX = (int)posX;
				tempZ = (int)posZ;
				if (tempX < 0)
					tempX = -tempX;
				if (tempZ < 0)
					tempZ = -tempZ;

				Xit = find(posXtracker.begin(), posXtracker.end(), ((int)posX));
				if (Xit != posXtracker.end()){

					Zit = find(posZtracker.begin(), posZtracker.end(), -((int)posZ + 50));

					if (Zit != posZtracker.end()){


					}
					else{
						for (int i = 0; i < 5; i++){
							for (int j = 0; j < 5; j++){
								height = rand() % 5 + 1;
								cout << height << endl;
								for (int k = 0; k < height; k++){
									Buildings.push_back(new Building(Vector3(j * 20 + posX, 10 * k, -(20 * i + posZ + 50)), Vector3(1.0, 1.0, 1.0)));
									posXtracker.push_back(j * 20 + posX);
									posZtracker.push_back(-(20 * i + posZ + 50));
								}
							}
						}
					}

				}
				else{
					for (int i = 0; i < 5; i++){
						for (int j = 0; j < 5; j++){
							height = rand() % 5 + 1;
							cout << height << endl;
							for (int k = 0; k < height; k++){
								Buildings.push_back(new Building(Vector3(j * 20 + posX, 10 * k, -(20 * i + posZ + 50)), Vector3(1.0, 1.0, 1.0)));
								posXtracker.push_back(j * 20 + posX);
								posZtracker.push_back(-(20 * i + posZ + 50));
							}
						}
					}
				}

			}
		}
		else{
			if (fmod(posX + 0, dist) == 0 && fmod(-(posZ + 0), dist) == 0){
				tempX = (int)posX;
				tempZ = (int)posZ;
				if (tempX < 0)
					tempX = -tempX;
				if (tempZ < 0)
					tempZ = -tempZ;
				height = rand() % 3 + 1;

				Xit = find(posXtracker.begin(), posXtracker.end(), ((int)posX + 0));
				if (Xit != posXtracker.end()){

					Zit = find(posZtracker.begin(), posZtracker.end(), -((int)posZ + 0));

					if (Zit != posZtracker.end()){


					}
					else{
						//dDistX = (int)fmod(dist - tempX, dist);
						//dDistZ = (int)fmod(dist - tempZ, dist);
						//cout << (int)posX + dist << " , " << (int)(-(posZ + dist)) + 0 << endl;
						for (int k = 0; k < height; k++){
							Buildings.push_back(new Building(Vector3(((int)posX + 0 + 0), 10.0*k, (-((int)posZ + 0 + 0))), Vector3(1.0, 1.0, 1.0)));
						}
						posXtracker.push_back(((int)posX + 0));
						posZtracker.push_back(-((int)posZ + 0));
					}

				}
				else{
					//dDistX = (int)fmod(dist - tempX, dist);
					//dDistZ = (int)fmod(dist - tempZ, dist);
					//cout << (int)posX + dist << " , " << (int)(-(posZ + dist)) + 0 << endl;
					for (int k = 0; k < height; k++){
						Buildings.push_back(new Building(Vector3(((int)posX + 0 + 0), 10.0*k, (-((int)posZ + 0 + 0))), Vector3(1.0, 1.0, 1.0)));
					}
					posXtracker.push_back(((int)posX + 0));
					posZtracker.push_back(-((int)posZ + 0));
				}

			}
		}
		drawBuilding();
	}
	updateRain();



	//Was testing my fairy on here and needed to disable this.

	glFlush();
	glutSwapBuffers();
}


void readSpecialKeys(int key, int x, int y){
	switch (key){

		case GLUT_KEY_DOWN:
		dist--;
		break;
	}

}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("Final Project");    	      // open window and set window title
  shader = new Shader(toon_vert, toon_frag, true);

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(1.0, 1.0, 1.0, 1.0);   	      // set clear color to black
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
  
  //Enable alpha.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);

  matrix.identity();

  rotateM.identity();

  for (int i = 0; i < ROW_VALUE; i++){
	  for (int j = 0; j < COLUMN_VALUE; j++)
		  Buildings.push_back(new Building(Vector3(20 * i, 0.0, -20 * j), Vector3(1.0, 1.0, 1.0)));
  }

  trackposition.set(-0, 0, 0);
  glutMouseFunc(mouse);
  glutMotionFunc(coords);

  // Keyboard commands:
  glutKeyboardFunc(processKeys);
  initializeRain();

  glutMainLoop();
  return 0;
}