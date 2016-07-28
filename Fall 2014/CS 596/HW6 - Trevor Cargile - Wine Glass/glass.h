#ifndef _GLASS_H_
#define _GLASS_H_

#include "Matrix4.h"
#include "Vector3.h"

class Glass
{
  protected:
    Matrix4 matrix;                 // model matrix
	Vector3 position;
	Vector3 original_position;

  public:
    Glass();   // Constructor
    Matrix4& getmatrix(int);
	void mouse(int button, int state, int x, int y);
	void coords(int x, int y);
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

