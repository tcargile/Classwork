/*CS320 Program1
  Trevor Cargile
  Dr. Carroll
  September 21th, 2013*/

/*Error values:	2 means too many parameters.
		3 means couldn't open file.
		4 means a line couldn't be printed because of too many characters. */

/*Defined constants are below.
  NEWLINE_VALUE represents the value newline is (10)
  DELETE_VALUE represents the value the embedded delete (127) 
  END_ARRAY represents the value of the size of the array being used. 
  MAX_BUFFER represents the limit to how many characters it can process -
	this value was chosen because I felt it was a reasonable number a user could
	have on one line. I estimated around 300 characters for my monitor so considering
	the chance that there could be 2 control characters per character processed
	and someone might put more than 300 characters on one line - 1000 felt good. */

#define NEWLINE_VALUE '\n'
#define DELETE_VALUE 127
#define END_ARRAY 72
#define MAX_BUFFER 1000

#include <stdio.h>

/* Two functions - one to insert characters into the array and another to
   print the array out. */
int insertChar(int charMe);
void printLine(int endFlag);
void printLineReverse(int endFlag);

/* Global array so other functions can access it - 72 elements wide. This
   size was chosen because the contents being printed will always be 72
   elements long. The counter is used as an index in multiple functions and
   the characters variable is used to count how many characters are being processed and
   the program will display an error is this gets too large. */
int arrayString[END_ARRAY];
int counter = 0;
int characters = 0;

/* Credit to Foster for the line below, it matches the book's */
int main(int argc, char *argv[]){

/* outputFlag to be returned by the program to see if the output changed.  
   inputChar takes each char and many tests are used against it. fileContents
   is used to store any parameters passed to the program.  revPar checks to
   see if the output needs to be reversed, which will use printLineReverse if
   it is equal to 1. the fileSlot determines which argument to read from.*/
int outputFlag = 1;
int inputChar;
int revPar = 0;
int fileSlot = 0;
int lengthError = 0;

FILE *fileContents;

    /* If there are more than two arguments, or both aren't -r, or both are -r
       return 2 because nothing was printed to the screen showing that
       the output is different than what is expected. */
    if (argc > 3 || (argc > 2 && (strcmp("-r", argv[1]) != 0 && strcmp("-r", argv[2]) != 0)) || (argc > 2 && (strcmp("-r", argv[1]) == 0 && strcmp("-r", argv[2]) == 0))){
	fprintf(stderr, "USAGE: p4 -r <filename>\nUSAGE: p4 <filename> -r\n");
	return 2;
	}
    /* Check to see which parameter is the reverse one, and which one is the file */
    else if (argc > 2){
	revPar = 1;
	if (strcmp("-r", argv[1]) == 0)
	    fileSlot = 2;
	else
	    fileSlot = 1;
	}
    /* Check to see if there is a reverse argument, if not then read from file. */
    else if (argc == 2){
	if (strcmp("-r", argv[1]) == 0)
	    revPar = 1;
	else
	    fileSlot = 1;
	}
    /* If there is a parameter, open it and scan each characters like you would
       if this was just stdin. Credit to Foster for info on fopen.*/
    if (fileSlot > 0){
	/* If error opening file, prompt user. */
	if ((fileContents = fopen(argv[fileSlot], "r")) == NULL){
	    fprintf(stderr, "ERROR: Couldn't open file.\n"); 
	    return 3;
	    }
	/* Continue until you hit the end of the file */
    	while ((inputChar = getc(fileContents)) != EOF){
	    /* If the end of the line is hit, print the line. */
	    if (inputChar == NEWLINE_VALUE){
	    	if (counter == END_ARRAY)
		    counter = 0;
	    	arrayString[counter++] = '$';
	    	characters++;
		if (revPar == 1)	
	    	    printLineReverse(0);
		else
		    printLine(0);
	    	}
	    else
		/* If the insertChar ever returns a 0, the output has changed. Send
		   the character to be analyzed and input into the array. */
	    	outputFlag *= insertChar(inputChar);

	    /* If there are more characters than what the max buffer allows, its an error. */
	    if (characters > MAX_BUFFER){
		/* In order to print other lines, wait until the next newline is hit or until its EOF. */
                fprintf(stderr, "ERROR: This line contains too many characters in one line.\n");
                while ((inputChar = getc(fileContents)) != EOF && (inputChar != NEWLINE_VALUE)){}

		/* Show that there is an error in length, then reset counter/characters. */
                lengthError = 1;
		counter = 0;
		characters = 0;
                }
	    if (inputChar == EOF)
		break;
	    }
	    fclose(fileContents);
	}
    /* Everything is the same except for stdin being analyzed instead of a file */
    else{
	while ((inputChar = getc(stdin)) != EOF){
            if (inputChar == NEWLINE_VALUE){
                if (counter == END_ARRAY)
                    counter = 0;
                arrayString[counter++] = '$';
                characters++;
		if (revPar == 1)
                    printLineReverse(0);
		else
		    printLine(0);
                }
            else
                outputFlag *= insertChar(inputChar);

            /* If there are more characters than the limit, send error */
            if (characters > MAX_BUFFER){                                                                                  
		/* In order to print other lines, wait until the next newline is hit or until its EOF. */
                fprintf(stderr, "ERROR: This line contains too many characters in one line.\n");
		while ((inputChar = getc(stdin)) != EOF && (inputChar != NEWLINE_VALUE)){}

		/* Mark lengthError flag that there was an error, and reset counter/characters. */
		lengthError = 1;
		counter = 0;
		characters = 0;
                }
	    if (inputChar == EOF)
		break;
            }
	}

    /* Print the last line of the file. */
    if (revPar == 1)
    	printLineReverse(1);
    else
	printLine(1);
    /* Returns the flag, which indicates if the output differs */
    if (lengthError != 0)
	outputFlag = 4;
    return outputFlag;
}

/* Function to analyze each character and either delete it, insert as is,
   or insert control characters. */
int insertChar(int charMe){
    /* If it is between 0 and 31, or the delete value replace with appropriate
       control character (char + 64). */
    if ((charMe <= 31) || (charMe == DELETE_VALUE)){
	if (counter == END_ARRAY)
	    counter = 0;
	arrayString[counter++] = '^';
	if (counter == END_ARRAY)
	    counter = 0;
	if (charMe == DELETE_VALUE)
	    arrayString[counter++] = '?';
	else
	    arrayString[counter++] = (char)(charMe + 64);
	characters += 2;
	return 0;
	}
    /* If the char is in the non-ascii characters then do nothing and skip. */
    else if (charMe >= 128 && charMe <= 255)
	return 0;
    /* Or, just print the char as is. */
    else{
	if (counter == END_ARRAY)
	    counter = 0;
	arrayString[counter++] = charMe;
	characters++;
	return 1;
	}
    }

/* Function used to print the array */
void printLine(int endFlag){
    int charCount = 0;
    /* If there are less than 72 characters, start at front and print until done */
    if (characters < END_ARRAY + 1){
	counter = 0;
    	while (counter < characters){
	    printf("%c", arrayString[counter++]);
	    }
	}
    /* Start where counter left off and print, wrap around until you print 72 characters */
    else{
	while (charCount < END_ARRAY){
	    if (counter == END_ARRAY)
		counter = 0;
	    printf("%c", arrayString[counter++]);
	    charCount++;
	    }
	}
    if (endFlag != 1)
    	printf("\n");
    /* Reset variables for next line. */
    counter = 0;
    characters = 0;
    }

/* Print the line backwards */
void printLineReverse(int endFlag){
    int charCount = 0;
    counter--;
    /* If there are less than 72 characters, start at the control and work backwards until you are at 0. */
    if (characters < END_ARRAY + 1){
        while (counter >= 0){
            printf("%c", arrayString[counter--]);
            }
        }
    /* Start where counter left off and print, wrap around until you print 72 characters */
    else{
        while (charCount < END_ARRAY){
            if (counter < 0)
                counter = END_ARRAY - 1;
            printf("%c", arrayString[counter--]);
            charCount++;
            }
        }
    if (endFlag != 1)
        printf("\n");
    /* Reset variables for next line. */
    counter = 0;
    characters = 0;
    }
