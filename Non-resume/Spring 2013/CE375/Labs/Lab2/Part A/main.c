//Trevor Cargile
//813542789
//Lab 2 Program 1

#include <stdio.h>
typedef unsigned int uint;
typedef unsigned char uchar;

uint setHexDigit(uint hexNumber, uchar hexDigit, uchar hexPosition);
int main()
{
	uint i;
	uint x = 0xA4B09F2C;
	
	printf("%X\n", x);
	for (i=0; i<8; i++)
		printf("%X\n", setHexDigit(x, i, i));
	
  return 0;
}

uint setHexDigit(uint hexNumber, uchar hexDigit, uchar hexPosition)
{
  char xfer[8];
  sprintf(xfer, "%X", hexNumber);
  
  xfer[7 - hexPosition] = hexDigit + 48;
  
  sscanf(xfer, "%X", &hexNumber);
  
  return hexNumber;
}
