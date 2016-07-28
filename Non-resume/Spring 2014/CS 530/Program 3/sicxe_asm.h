#ifndef SICXE_ASM_H
#define SICXE_ASM_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>

#include "file_parser.h"
#include "file_parse_exception.h"
#include "opcodetab.h"
#include "opcode_error_exception.h"
#include "symtab.h"
#include "symtab_exception.h"

using namespace std;

class sicxe_asm {
struct line{
        string row;
        string address;
        string label;
        string opcode;
        string operand;
    };

public :

        sicxe_asm(string);
        ~sicxe_asm();
        void First_Pass(string);
        void Print();
        void isStart(int&);
        int string_to_int(string);
        string int_to_hex(int, int);
        int hex_to_int(string);
        int dec_to_int(string);
        string to_uppercase(string);
        void process_directives(string);
        void process_byte(string, string);
        void update_address(line);
        void check_address(string, string);
        void check_byte_const(string);
        void start_address(string);
        void byte_address(string, string);
        string format_15(int, int);


private :

    string filename;

    line data;
    opcodetab optab;
    symtab tab;
    map <string, string> table;
    vector<line> FirPas;
    stringstream LineNo;

    string remove_letters (string);

};

#endif

