//Trevor Cargile
//813542789
//Lab 2 Program 2

#include <stdio.h>

typedef struct 
{
  int hour;
  int minute;
  int second;
} Time;

void increment(Time* pTime);

int main()
{
  int i;
  Time t = {23,59,57};
  printf("t = %d:%d:%d\n", t.hour, t.minute, t.second);
  printf("Increment t five times\n");
  for (i=0; i<5; i++)
  {
  	increment(&t);
  	printf("%d:%d:%d\n", t.hour, t.minute, t.second);
  }

  return 0;
}

void increment(Time* pTime)
{
  pTime->second++;
  if (pTime->second == 60)
  {
    pTime->second = 0;
    pTime->minute++;
    if (pTime->minute == 60)
    {
      pTime->minute = 0;
      pTime->hour++;
      if (pTime->hour == 24)
        pTime->hour = 0;
    }
  }
}