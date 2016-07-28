#ifndef _DRIVER_H_
#define _DRIVER_H_

class Window	  // output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
};

#endif

