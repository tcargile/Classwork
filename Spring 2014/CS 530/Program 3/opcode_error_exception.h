/*	Nathan Purta, Trevor Cargile, Ahmad Algharabally, Mharvinn Calitis
	Team Utah
	masc1235
	prog2
	CS530, Spring 2014 */

#ifndef OPCODE_ERROR_EXCEPTION_H
#define OPCODE_ERROR_EXCEPTION_H
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

class opcode_error_exception {

public:
	//Constructor
    opcode_error_exception(string s) {
        message = s;
    }

    //Get message of exception
    string getMessage() {
        return message;
    }

private:
    string message;
};

#endif

