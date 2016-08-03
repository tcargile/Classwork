/*	Trevor Cargile
	813542789
	Homework 5 - Group.h		*/

#ifndef _GROUP_H_
#define _GROUP_H_

#include <vector>
#include "../Matrix/Matrix4.h"
#include "Node.h"

class Group : public Node{
public:
	Group();
	void addChild(Node&);
	void removeChild(Node&);
	void draw(Matrix4, int);				//NOT IMPLEMENTED
	std::vector<Node*> getChildren();


protected:
	std::vector<Node*> children;
};

#endif