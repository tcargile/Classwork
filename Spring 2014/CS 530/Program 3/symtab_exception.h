/*	Nathan Purta, Trevor Cargile, Ahmad Algharabally, Mharvinn Calitis
	masc1235
	prog1
	CS530, Spring 2014
*/

#ifndef SYMTAB_EXCEPTION_H
#define SYMTAB_EXCEPTION_H
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

class symtab_exception {

public:
	//Constructor
    symtab_exception(string s) {
        message = s;
    }

    //Implicit constructor
    symtab_exception() {
        message = "An error has occurred";
    }

    //Get message of exception
    string getMessage() {
        return message;
    }



private:
    string message;
};

#endif

