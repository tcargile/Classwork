//Trevor Cargile
//813542789
//CompE375 - Lab 1 Program 2

#include <stdio.h>

int evenSum(int x[], int size);
int oddSum(int x[], int size);

int main()
{
  int xxx[] = {77, -66, 55, -11, 22, 99, -33, 44, -88};
  int size = 9;
  
  int even = evenSum(xxx, size);
  int odd = oddSum(xxx, size);
  
  printf("The sum of odd numbers = %d\nThe sum of even numbers = %d", odd, even);
  return 0;
}

int evenSum(int x[], int size)
{
  int sum = 0;
  
  for(int i = 0; i < size; i++)
    if (x[i] % 2 == 0)
      sum += x[i];
  
  return sum;
}

int oddSum(int x[], int size)
{
  int sum = 0;
  
  for(int i = 0; i < size; i++)
    if (x[i] % 2 != 0)
      sum += x[i];
  
  return sum;
}