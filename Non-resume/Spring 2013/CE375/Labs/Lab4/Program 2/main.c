//Trevor Cargile
//813542789
//Lab 4 - Program 2

#include <STM32F0xx.h>

typedef unsigned int uint;
typedef unsigned char uchar;

uint setHexDigit(uint hexNumber, uchar hexDigit, uchar hexPosition);
int outArray[8];

int main()
{
	uint i;
	uint x = 0x1234ABCD;
	
	for (i = 0; i < 8; i++)
		outArray[i] = setHexDigit(x, i, i);
	
  return 0;
}

uint setHexDigit(uint hexNumber, uchar hexDigit, uchar hexPosition)
{
	hexNumber = (hexDigit << (hexPosition * 4)) | (hexNumber & ~(0xF << (hexPosition * 4)));

	return hexNumber;
}

