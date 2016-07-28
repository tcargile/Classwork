/*  Nathan Purta, Trevor Cargile, Ahmad Algharabally, Mharvinn Calitis
	Team Utah
	masc1235
	prog2
	CS530, Spring 2014 */

#ifndef SYMTAB_H
#define SYMTAB_H

#include <cstdlib>
#include <string>
#include <map>
#include <cctype>
#include <iostream>

using namespace std;

class symtab {
    public:

        symtab();

        void add_table_entry(string, string);

        map <string, string> get_table();

    private:
		//Map to store opcode information
        map <string, string> symtable;
        map <string, string>::iterator sym_iter;
};

#endif


