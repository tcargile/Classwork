/*  Nathan Purta, Trevor Cargile, Ahmad Algharabally, Mharvinn Calitis
	Team Utah
	masc1235
	prog2
	CS530, Spring 2014 */

#ifndef OPCODETAB_H
#define OPCODETAB_H

#include <cstdlib>
#include <string>
#include <map>
#include <cctype>
#include <iostream>

using namespace std;

class opcodetab {
    public:
        // ctor
        // creates a new dictionary structure and loads all of the opcodes for
        // the SIC/XE architecture into the table.  Use the STL map for this.
        opcodetab();

        // takes a SIC/XE opcode and returns the machine code
        // equivalent as a two byte string in hexadecimal.
        // Example:  get_machine_code("ADD") returns the value 18
        // Note that opcodes may be prepended with a '+'.
        // throws an opcode_error_exception if the opcode is not
        // found in the table.
        string get_machine_code(string);

        // takes a SIC/XE opcode and returns the number of bytes
        // needed to encode the instruction, which is an int in
        // the range 1..4.
        // NOTE: the opcode must be prepended with a '+' for format 4.
        // throws an opcode_error_exception if the opcode is not
        // found in the table.
        int get_instruction_size(string);

    private:
		const static string mnem[];    //Holds opcode mnemonics
		const static int format[];      //Holds opcode format size
		const static string opcode[];   //Holds opcode machine code

		//Map to store opcode information
        map <string, pair<string,int> > op_list;

        //Iterator to step through opcode map
        map <string, pair<string,int> >::iterator op_iter;

        string make_uppercase(string);  //Converts opcode to all uppercase
};

#endif

