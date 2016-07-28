#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"
#include "Vector3.h"

class Cube
{
  protected:
    Matrix4 matrix;                 // model matrix
	Matrix4 frontm;					// matrix with side name then m.
	Matrix4 leftm;
	Matrix4 rightm;
	Matrix4 backm;
	Matrix4 topm;
	Matrix4 bottomm;
	Vector3 center;
    double angle;                   // rotation angle [degrees]
	double angleZ;				// rotation for Z.

  public:
    Cube();   // Constructor
    Matrix4& getmatrix(int);
	double getcenter(int);			// gets the center vector.
    void spin(double, int);      // spin cube [degrees]
	void processKeys(unsigned char, int, int);
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

