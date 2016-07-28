//Trevor Cargile
//813542789
//CompE375 - Lab 1 Program 1

#include <stdio.h>

int main()
{
  int sum = 0;
  
  for(int i = 1; i <= 1000; i++)
  {
    if (i % 2 != 0)
      sum += i;
  }
  
  printf("The sum of odd numbers between 1 - 1000 = %d\n", sum);
  return 0;
}
