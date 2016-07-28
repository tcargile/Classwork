/*	Nathan Purta, Trevor Cargile, Ahmad Algharabally, Mharvinn Calitis
	masc1235
	prog1
	CS530, Spring 2014
*/

#ifndef FILE_PARSE_EXCEPTION_H
#define FILE_PARSE_EXCEPTION_H
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

class file_parse_exception {

public:
	//Constructor
    file_parse_exception(string s) {
        message = s;        
    }
    
    //Implicit constructor
    file_parse_exception() {
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
