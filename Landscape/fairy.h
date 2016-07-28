#ifndef _FAIRY_H_
#define _FAIRY_H_

#include "Matrix4.h"
#include "Vector3.h"

class Fairy
{
  protected:
    Matrix4 matrix;                 // model matrix
	Vector3 path[19];
	Vector3 center;
	Vector3 position;
	double tpos;
	double increment;
	int chunk;

  public:
    Fairy();   // Constructor
	Fairy(Vector3);
    Matrix4& getmatrix();
	void draw();
};

//class Window	  // output window related routines
//{
//  public:
//    static int width, height; 	            // window size
//
//    static void idleCallback(void);
//    static void reshapeCallback(int, int);
//    static void displayCallback(void);
//};

#endif

