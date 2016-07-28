/*	Trevor Cargile
	813542789
	Group.cpp		*/

#include "Group.h"
#include <iostream>

using namespace std;

/* Default constructor that will be called when a new Node is created. */
Group::Group():Node(){}

/* Function to add a child to the list of children. Nodes can't have the same name. */
void Group::addChild(Node &n){
	//Start from the beginning and then go through each vector Node to see if it exists.
	std::vector<Node*>::iterator itr = children.begin();
	while (itr != children.end()){
		//If so, print error because nodes can't be added twice. (disable this to allow double adding).
		if ((*itr) == &n){
			cerr << "Error: Node already exists in list." << endl;
			break;
		}
		itr++;
	}
	children.push_back(&n);
}

/* Function to remove a child to the list of children if it exists. */
void Group::removeChild(Node &n){
	//Start from the beginning and then go through each vector Node to see if it exists.
	std::vector<Node*>::iterator itr = children.begin();
	for (unsigned int i = 0; i < children.size(); i++){
		//If so, erase it.
		if ((*itr) == &n){
			children.erase(children.begin() + i);
			return;
		}
		itr++;
	}
	//Print error if node doesn't exist.
	cerr << "Error: Node doesn't exist in the list." << endl;
}

vector<Node*> Group::getChildren(){
	return children;
}

/* Function to draw, but will affect the children. */
void Group::draw(Matrix4 world, int n){
	std::vector<Node*>::iterator itr = children.begin();
	while (itr != children.end()){
		draw(world, n);
		itr++;
	}
}