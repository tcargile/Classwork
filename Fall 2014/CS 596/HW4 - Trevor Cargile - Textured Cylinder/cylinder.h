#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "Matrix4.h"
#include "Vector3.h"

class Cylinder
{
  protected:
    Matrix4 matrix;                 // model matrix
	Vector3 position;
	Vector3 original_position;

  public:
    Cylinder();   // Constructor
    Matrix4& getmatrix(int);
	void mouse(int button, int state, int x, int y);
	void coords(int x, int y);
	void draw(double,int);
	void rotate_timer(int);
};

class Window	  // output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
};

#endif

