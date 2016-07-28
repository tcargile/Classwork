/*	Nathan Purta, Trevor Cargile, Ahmad Algharabally, Mharvinn Calitis
	masc1235
	prog1
	CS530, Spring 2014
*/

#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

//Constructor
file_parser::file_parser(string name) {
	filename = name;
}

//Destructor
file_parser::~file_parser() {}

//File reader function
void file_parser::read_file() {
	int row = 0, pos = 0, tokenCount = 0, isApos = 0, AposCount;
	string Line;			//Holds a line in the file
	ifstream infile;
	string::iterator itr_line;
	line info;

	infile.open(filename.c_str(), ios::in);	//Open file

	if(!infile)	//If file doesn't exist
		throw file_parse_exception("Filename not valid");

	while(!infile.eof()) //While not at end of file
	{
		tokenCount = 0;			//Counter for the number of tokens
		pos = 0;				//Position counter for the line in the file
		ErrorLine.str("");		//Reset line number
		ErrorLine << row + 1;	//Store current line number

		getline(infile,Line);	//Store one line of the file

		//Check if the line is empty or holds only a comment
		if (!Line.empty() && Line[0] != '.')
		{
			//Check if the first letter of the label is not a letter
			if (!isalpha(Line[0]) && !isspace(Line[0]) && Line[0] != '.' && !Line.empty())
				throw file_parse_exception("Line " + ErrorLine.str() + ": First character of label is not a letter");

			//Line.push_back('\0');

			tokenCount++;	//Assume there is a label even if there isn't
			pos++;			//Move to next character in line to prevent access to index -1 in Line

			AposCount = 0;

			//Read through the line until you reach the end
			//or until you started reading a comment to check for number of tokens
			for (itr_line = Line.begin(); itr_line != Line.end() && (Line[pos-1] != '.' || isApos == -1); itr_line++ )
            {
                //Check for apostrophe
				if(Line[pos] == '\'')
				{
					if (AposCount > 0 && isalnum(Line[pos+1]) && isalnum(Line[pos-1]))
						 throw file_parse_exception("Line " + ErrorLine.str() + ": Apostrophes in the middle of operand");

					isApos = ~isApos;
					AposCount++;
				}

				if(!isspace(Line[pos]) && isspace(Line[pos-1]) && isApos == 0 && itr_line + 1 != Line.end())
					tokenCount++;

				pos++;
            }

			pos = 0;

			if (AposCount != 2 && AposCount != 0)
				throw file_parse_exception("Line " + ErrorLine.str() + ": Number of Apostrophes is not 2");

			//Check if the amount of tokens is greater than 4
			if (tokenCount > 4)
				throw file_parse_exception("Line " + ErrorLine.str() + ": Too many tokens");




			//Run through label, if there is one, to see if there is a non-alphanumeric character
            for (itr_line = Line.begin(); itr_line != Line.end() && !isspace(Line[pos]) && isalnum(Line[pos]); itr_line++)
                pos++;

			if (!isalnum(Line[pos]) && !isspace(Line[pos]) && Line[pos] != '.')
				throw file_parse_exception("Line " + ErrorLine.str() + ": Label has non-alphanumeric character");


		}

		pos = 0;

		//Get line tokens
		if (!Line.empty())
        {
            info.label = get_label(Line, pos);
            info.opcode = get_opcode(Line, pos);
            info.operand = get_operand(Line, pos);
            info.comment = get_comments(Line, pos);

            lineTable.push_back(info);	//If no errors, add the line to the vector
        }

        else
        {
            info.label = "";
            info.opcode = "";
            info.operand = "";
            info.comment = "";

            lineTable.push_back(info);	//If no errors, add blank tokens
        }
		row++;
	}

	infile.close();

}

//Get token function
string file_parser::get_token(unsigned int row, unsigned int col) {

    if (col == 0)
        return lineTable[row].label;	//Return label
    else if (col == 1)
        return lineTable[row].opcode;	//Return opcode
    else if (col == 2)
        return lineTable[row].operand;	//Return operand
    else if (col == 3)
        return lineTable[row].comment;	//Return comment
    else
        throw file_parse_exception("Invalid column");
}

//File print function
void file_parser::print_file() {

	//Print the titles for each column
	cout<<left<<setw(10)<<"Label"<<setw(15)<<"Opcode"<<setw(20)<<"Operand"<<"Comments"<<endl;

	//Print each token
	for (unsigned int i = 0; i < lineTable.size(); i++)
		cout<<left<<setw(10)<<get_token(i,0)<<setw(15)<<get_token(i,1)<<setw(20)<<get_token(i,2)<<get_token(i,3)<<endl;

}

//Get size of file function
int file_parser::size() {
	return (int)lineTable.size();
}

//Get label function
string file_parser::get_label(string s, int &pos)
{
    string::iterator itr_line;
	string label = "";

    for (itr_line = s.begin(); itr_line != s.end() && !isspace(s[pos]) && isalnum(s[pos]) && pos < 8; itr_line++)
    {
        label += s[pos];
		pos++;
    }
	while (!isspace(s[pos]) && s[pos] != '.')	//Ignore rest of label
		pos++;

	while(isspace(s[pos]))	//Move to next token
		pos++;

	return label;
}

//Get opcode function
string file_parser::get_opcode(string s, int &pos)
{
    string::iterator itr_line;
    string opcode = "";

	//Run through characters until first white space or .
	for (itr_line = s.begin() + pos; itr_line != s.end() && !isspace(s[pos]) && s[pos] != '.'; itr_line++ )
	{
		//If there is a ', store everything until the ending '
		if (s[pos] == '\'')
		{
			do
			{
				opcode += s[pos];
				pos++;
			}
			while (s[pos] != '\'');

		}
		opcode += s[pos];
		pos++;
	}
	while(isspace(s[pos]))
		pos++;

	return opcode;
}

//Get operand function
string file_parser::get_operand(string s, int &pos)
{
	string operand = "";
    string::iterator itr_line;

	//Run through characters until first white space or .
	for(itr_line = s.begin() + pos; itr_line != s.end() && !isspace(s[pos]) && s[pos] != '.'; itr_line++)
	{
		if (s[pos] == '\'')
		{
		    operand += s[pos];
            pos++;
            for (itr_line = s.begin() + pos; s[pos] != '\''; itr_line++)
            {
                operand += s[pos];
                pos++;
            }
		}


		operand += s[pos];
		pos++;
	}
	while(isspace(s[pos]))
		pos++;

	return operand;
}

//Get comments function
string file_parser::get_comments(string s, int &pos)
{
	string comments = "";
    string::iterator itr_line;

    if (s[pos] != '.' && s.begin() + pos != s.end())
        throw file_parse_exception("Line " + ErrorLine.str() + ": Invalid token");

	//If current position in line is a period, then return rest of line
	if (s[pos] == '.')
		for (itr_line = s.begin() + pos; itr_line != s.end(); itr_line++ )
		{
			comments += s[pos];
			pos++;
		}


	return comments;
}
