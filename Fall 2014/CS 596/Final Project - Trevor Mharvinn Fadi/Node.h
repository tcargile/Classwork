/*	Trevor Cargile
	813542789
	Homework 5 - Node.h		*/

#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <string>
#include "Matrix4.h"

class Node{
private:
	Node * parent;

public:
	Node();
	void setParent(Node&);
	virtual void draw(Matrix4, int);
};

#endif