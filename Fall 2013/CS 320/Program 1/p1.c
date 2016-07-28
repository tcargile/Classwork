/*CS320 Program1
  Trevor Cargile
  Dr. Carroll
  September 21th, 2013*/

/*Defined constants are below.
  NEWLINE_VALUE represents the value newline is (10)
  DELETE_VALUE represents the value the embedded delete (127)
  MAX_CHAR_LIMIT represents the cap for chars in a single line.*/

#define NEWLINE_VALUE '\n'
#define DELETE_VALUE 127
#define MAX_CHAR_LIMIT 72

#include <stdio.h>

int main(void){

/*inputChar is the character being read from the input.
  outputFlag stores a value if the input changes. It
      will remain 1 unless the input
      differs from the output, otherwise it will turn to 0.
  charAmount stores the amount of characters a line has.*/

int inputChar, outputFlag = 1, charAmount = 0;                                           

/*Main while loop. Continues until the program hits the end of the file.
  Credit to C by Discovery for the concept of the line below.
  Program used - inout2.c*/

    while ((inputChar = getchar()) != EOF){

	/*If there are too many characters in the line, print a newline.
	  If the current char isn't a newline, then go until you find the
	  next newline and flag the output that it differs from input.*/

	if (charAmount == MAX_CHAR_LIMIT){
	    printf("\n");
	    charAmount = 0;

	    if (inputChar != NEWLINE_VALUE){
		outputFlag = 0;
	        while ((inputChar = getchar()) != NEWLINE_VALUE){}
	    }
	}

	/*If there is room for chars, check if the inputChar value
	  represents a non-printing ascii character. If so, check if
	  there is room to print both characters or just the control
	  character. If there is room, first check to see if its a
	  special case and print that value. If it isn't then print
	  the regular control character and its corresponding printed
	  character.*/

	else
	{
       	    if ((inputChar <= 31) || (inputChar == DELETE_VALUE)){
	   	if ((charAmount >= MAX_CHAR_LIMIT-1) && (inputChar != NEWLINE_VALUE)){
		    printf("^\n");
		    charAmount = 0;
		    outputFlag = 0;
		
		    while ((inputChar = getchar()) != NEWLINE_VALUE){}
	    	}
	    	else{
		    if (inputChar == NEWLINE_VALUE){
			printf("$\n");
			charAmount = 0;
		    }
		    else if (inputChar == DELETE_VALUE){
			printf("^?");
			charAmount += 2;
			outputFlag = 0;
		    }

		    /*This is the general algorithm to cover all but
		      two cases for the non-printing ascii characters.
		      Their printing chars correspond to their ascii
		      value plus 64.*/

		    else{
	    	        printf("^%c", inputChar+64);
	    	    	charAmount += 2;
            	    	outputFlag = 0;	
		    }
	    	}
	    }

	    /*If the character read isn't a non-printing ascii char,
	      then check to see if it is a non-ascii character. If it
	      is, then don't print anything, and flag the program 
	      the program that the output differs from input.*/

	    else if ((inputChar >= 128) && (inputChar <= 255))
   	    	outputFlag = 0;

	    /*If the program gets here that means its a regular
              ascii char and can be printed normally, then increase
	      the amount of chars in the line by one.*/

	    else{
	    	putchar(inputChar);
	    	charAmount++;
	    }
    	}
    }
    /*Returns the flag, which indicates if the output differs*/
    return outputFlag;
}
