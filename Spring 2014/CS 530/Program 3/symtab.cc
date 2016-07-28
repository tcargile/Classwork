/*  Nathan Purta, Trevor Cargile, Ahmad Algharabally, Mharvinn Calitis
	Team Utah
	masc1235
	prog2
	CS530, Spring 2014 */

#include "symtab.h"
#include "symtab_exception.h"

using namespace std;

symtab::symtab()
{}

void symtab::add_table_entry(string symbol, string value)
{
    sym_iter = symtable.find(symbol);

    if(sym_iter != symtable.end()) //If entry is in table already
        throw symtab_exception("Invalid symbol");
	else
		symtable[symbol] = value;
}

map <string, string> symtab::get_table()
{
    return symtable;
}
