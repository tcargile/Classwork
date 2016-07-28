#include <iostream>
#include "sicxe_asm.h"

using namespace std;

sicxe_asm::sicxe_asm(string name)
{
    First_Pass(name);
}

sicxe_asm::~sicxe_asm() {}

void sicxe_asm::First_Pass(string name)
{
    try
    {
        int start = 0;
        file_parser parser(name);

        parser.read_file();

        //line data;
        /*string sizu;
        string temp;
        int pracehorder = 0;*/

        for(int i =0; i < parser.size(); i++)
        {
            table = tab.get_table();

            LineNo.str("");
            LineNo << i + 1;

            data.label = parser.get_token(i,0);
            data.opcode = parser.get_token(i,1);

            //Test opcode goes here

            data.operand = parser.get_token(i,2);
            data.row = i + 1;

            isStart(start);

            if (start == 1)
            {
                process_directives(data.opcode);

                update_address(FirPas[i-1]);
            }


            FirPas.push_back(data);

            //Symbol table
            if (data.label != "")
            {
                if (data.opcode == "EQU")
                {
                    if (hex_to_int(data.operand))
                        tab.add_table_entry(data.label, data.operand);
                    else
                        tab.add_table_entry(data.label, table.find(data.operand)->first);
                }

                else
                {
                    tab.add_table_entry(data.label, data.address);
                }

            }
        }
    }

    catch (file_parse_exception excpt)
    {
        cerr << excpt.getMessage() << endl;
        exit(0);
    }

    catch (opcode_error_exception excpt)
    {
        cerr << excpt.getMessage() << endl;
        exit(0);
    }

    catch (symtab_exception excpt)
    {
        cerr << excpt.getMessage() << endl;
        exit(0);
    }

    catch (const char* excpt)
    {
        cerr << excpt << endl;
        exit(0);
    }

    catch (...)
    {
        cerr << "Line " << LineNo.str() << ": Error" <<endl;
        exit(0);
    }
}

void sicxe_asm::update_address(line last_instr)
{
    last_instr.opcode = to_uppercase(last_instr.opcode);

    if(last_instr.opcode == "START")
        start_address(last_instr.operand);

    else if (last_instr.opcode == "BYTE")
        byte_address(last_instr.operand, last_instr.address);

    else if (last_instr.opcode == "WORD")
    {

    }

    else if (last_instr.opcode == "RESB")
    {

    }

    else if (last_instr.opcode == "RESW")
    {

    }

    else if (last_instr.opcode == "BASE")
    {

    }

    else if (last_instr.opcode == "NOBASE")
    {

    }

    else if (last_instr.opcode == "EQU")
    {
        data.address = last_instr.address;

    }

    if (last_instr.opcode == "END")
        exit(0);

    else if (last_instr.opcode == "")
        data.address = last_instr.address;

    else
        data.address = int_to_hex(hex_to_int(last_instr.address) +
                optab.get_instruction_size(last_instr.opcode), 5);

}
void sicxe_asm::Print()
{

}

void sicxe_asm::isStart(int &start)
{
    string opcode = to_uppercase(data.opcode);

    if (opcode == "START")
    {
        start = 1;
        data.address = "00000";

        if (data.label == "")
            throw "Line " + LineNo.str() + ": Starting address needs a label";

        tab.add_table_entry(data.label, data.address);
    }

    if (start == 0)
        data.address = "00000";
}

int sicxe_asm::string_to_int(string s)
{
    istringstream instr(s);
    int n;
    instr >> n;

    return n;
}

string sicxe_asm::int_to_hex(int num, int width)
{
    stringstream out;
    out << setw(width) << setfill('0') << hex << num;
    return to_uppercase(out.str());
}

int sicxe_asm::hex_to_int(string s)
{
    int value;
    sscanf(s.c_str(),"%x",&value);
    return value;
}

int sicxe_asm::dec_to_int(string s)
{
    int value;
    sscanf(s.c_str(),"%d",&value);
    return value;
}

string sicxe_asm::format_15(int x, int address)
{
    stringstream tmp;
    if (address == 1)
        tmp << hex << setw(5) << setfill('0') << x;
    else
        tmp << hex << setw(8) << setfill('0') << x;
    string xx = tmp.str();
    stringstream tmmp;
    tmmp << setw(15) << xx;
    return tmmp.str();
}

string sicxe_asm::to_uppercase(string s)
{
    transform(s.begin(),s.end(),s.begin(),::toupper);
    return s;
}

void sicxe_asm::process_directives(string opcode)
{
    opcode = to_uppercase(opcode);

    if (opcode == "BYTE")
        process_byte(data.label, data.operand);

    else if (opcode == "WORD")
    {

    }

    else if (opcode == "RESB")
    {

    }

    else if (opcode == "RESW")
    {

    }

    else if (opcode == "BASE")
    {

    }

    else if (opcode == "NOBASE")
    {

    }

    else if (opcode == "EQU")
    {

    }
}

void sicxe_asm::process_byte(string label, string operand)
{
    if (label == "")
        throw "Line " + LineNo.str() + ": Invalid byte label";

    operand = to_uppercase(operand);

    if (operand[0] == 'X')
    {
        operand.erase(0,2);
        operand.erase(operand.end() - 1);

        check_byte_const(operand);

        tab.add_table_entry(label,operand);
    }

    else if (operand[0] == 'C')
    {
        if (operand[1] != '\'')
            throw "Line " + LineNo.str() + ": Invalid byte constant";

        operand.erase(0,2);
        operand.erase(operand.end() - 1);

        tab.add_table_entry(label,operand);
    }

    else
        throw "Line " + LineNo.str() + ": Invalid byte constant type";
}

void sicxe_asm::check_address(string addr, string type)
{
    string::iterator itr;
    if (type == "hex")
        for (itr = addr.begin(); itr != addr.end(); itr++)
            if (!isxdigit(addr[itr - addr.begin()]))
                throw "Line " + LineNo.str() + ": Invalid address";

    if (type == "dec")
        for (itr = addr.begin(); itr != addr.end(); itr++)
            if (!isdigit(addr[itr - addr.begin()]))
                throw "Line " + LineNo.str() + ": Invalid address";
}

void sicxe_asm::check_byte_const(string constant)
{
    string::iterator itr;
    if (constant.size() % 2 != 0)
        throw "Line " + LineNo.str() + ": Invalid byte constant length";

    for (itr = constant.begin(); itr != constant.end(); itr++)
        if (!isxdigit(constant[itr - constant.begin()]))
            throw "Line " + LineNo.str() + ": Invalid byte constant";
}

void sicxe_asm::start_address(string operand)
{
    data.address = operand;
    if (data.address[0] == '$')
    {
        data.address.erase(0,1);
        check_address(data.address, "hex");

        if (hex_to_int(data.address) >= 0x10000)
            throw "Line " + LineNo.str() + ": Negative address";
    }

    else if (isdigit(data.address[0]))
    {
        check_address(data.address, "dec");
        data.address = int_to_hex(dec_to_int(data.address),5);

        if (hex_to_int(data.address) >= 0x10000)
            throw "Line " + LineNo.str() + ": Negative address";
    }

    else
        throw "Line " + LineNo.str() + ": Invalid address";
}

void sicxe_asm::byte_address(string operand, string address)
{
    //Don't forget to add to symbol table in process_directives function
    operand = to_uppercase(operand);
    if (operand[0] == 'X')
    {
        operand.erase(0,2);
        operand.erase(operand.end() - 1);

        check_byte_const(operand);

        data.address = int_to_hex(hex_to_int(address) + (int)(operand.size())/2, 5);
    }

    else if (operand[0] == 'C')
    {
        if (operand[1] != '\'')
            throw "Line " + LineNo.str() + ": Invalid byte constant";

        operand.erase(0,2);
        operand.erase(operand.end() - 1);

        data.address = int_to_hex(hex_to_int(address) + (int)(operand.size()), 5);
    }

    else
        throw "Line " + LineNo.str() + ": Invalid byte constant type";
}


 string sicxe_asm::remove_letters (string s)
 {
    string::iterator itr;

    for (itr = s.begin(); itr != s.end(); itr++)
    {
        if (!isdigit(s[itr - s.begin()]) && isdigit(s[itr - s.begin() - 1]) && isdigit(s[itr - s.begin() + 1]))
            throw file_parse_exception("Line " + LineNo.str() + ": Invalid operand");

        if (!isdigit(s[itr - s.begin()]))
            s.erase(itr - s.begin(),1);
    }

    return s;
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

