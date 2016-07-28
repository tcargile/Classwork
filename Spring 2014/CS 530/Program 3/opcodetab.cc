/*  Nathan Purta, Trevor Cargile, Ahmad Algharabally, Mharvinn Calitis
	Team Utah
	masc1235
	prog2
	CS530, Spring 2014 */

#include "opcodetab.h"
#include "opcode_error_exception.h"

using namespace std;

//Initialize mnemonics array
const string opcodetab::mnem[] = { "ADD","ADDF","ADDR","AND","CLEAR","COMP",
            "COMPF","COMPR","DIV","DIVF","DIVR","FIX","FLOAT","HIO","J","JEQ",
            "JGT","JLT","JSUB","LDA","LDB","LDCH","LDF","LDL","LDS","LDT",
            "LDX","LPS","MUL","MULF","MULR","NORM","OR","RD","RMO","RSUB",
            "SHIFTL","SHIFTR","SIO","SSK","STA","STB","STCH","STF","STI",
            "STL","STS","STSW","STT","STX","SUB","SUBF","SUBR","SVC","TD",
            "TIO","TIX","TIXR","WD" };

//Initialize format array
const int opcodetab::format[] = { 3,3,2,3,2,3,3,2,3,3,2,1,1,1,3,3,3,3,3,3,
            3,3,3,3,3,3,3,3,3,3,2,1,3,3,2,3,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
            2,2,3,1,3,2,3};

//Initialize machine code array
const string opcodetab::opcode[] = { "18","58","90","40","B4","28","88","A0","24","64",
            "9C","C4","C0","F4","3C","30","34","38","48","00","68","50","70","08","6C",
            "74","04","D0","20","60","98","C8","44","D8","AC","4C","A4","A8","F0","EC",
            "0C","78","54","80","D4","14","7C","E8","84","10","1C","5C","94","B0","E0",
            "F8","2C","B8","DC"};

//Constructor
opcodetab::opcodetab()
{
    //Add opcode mnemonic, machine code, and format to map
	for(int i = 0; i < 59; i++)
		op_list[mnem[i]] = pair<string,int>(opcode[i],format[i]);
}

//Get machine code function
string opcodetab::get_machine_code(string s)
{
	s = make_uppercase(s);  //Convert to uppercase only

    //Check if the opcode is extended
	if (s[0] == '+')
		s.erase(0,1);

	op_iter = op_list.find(s);  //Look for it in map

    //If opcode is found, return machine code, else error
	if(op_iter == op_list.end())
        throw opcode_error_exception("Invalid opcode");
	else
		return op_iter->second.first;
}

//Get format size function
int opcodetab::get_instruction_size(string s)
{
	int isExt = 0;  //Flag for extended instructions

	s = make_uppercase(s);  //Convert to uppercase

    //Check for extended instruction
	if (s[0] == '+')
	{
		isExt = 1;
		s.erase(0,1);
	}

	//Look up opcode
    op_iter = op_list.find(s);

    //Check if the opcode is valid
    if(op_iter == op_list.end())
        throw opcode_error_exception("Invalid opcode");

    //Check if the opcode is extended and not format 3/4
    else if (op_iter->second.second != 3 && isExt == 1)
        throw opcode_error_exception("Opcode cannot be extended, format not 3/4");

    //Return size if opcode is found, else throw error
	else
		return op_iter->second.second + isExt;
}

//Convert string to uppercase function
string opcodetab::make_uppercase(string s)
{
    //Convert all characters to uppercase
	for(string::iterator it = s.begin(); it != s.end(); it++)
        s[it - s.begin()] = toupper(s[it - s.begin()]);

	return s;
}








