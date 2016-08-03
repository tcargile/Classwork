/*	Trevor Cargile
	813542789
	Node.cpp		*/

#include "Node.h"

using namespace std;

/* Default Constructor when a new node is established. */
Node::Node(){}

/* Set the parent pointer. */
void Node::setParent(Node &p){
	parent = &p;
}

/* Base class draw. */
void Node::draw(Matrix4 matrix, int n){
	cout << "I SHOULDN'T BE HERE!" << endl;
}
