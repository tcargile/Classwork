//Trevor Cargile
//813542789
//Lab 3 Program 1

#include <stdio.h>
typedef unsigned int uint;
typedef unsigned char uchar;

uint countOnes(uint hexNumber);
int main()
{
  uint number = 0x12345678;
  
  printf("%X has %d ones in it.", number, countOnes(number));
  return 0;
}

uint countOnes(uint hexNumber)
{
  uint counter = 0;
  uint stored;
  
  for (int i = 0; i < 32; i++)
  {
    stored = (0xFFFFFFFF >> i) & hexNumber;
    stored = stored >> (31 - i);
    
    if (stored == 1)
      counter++;
  }
  
  return counter;
}