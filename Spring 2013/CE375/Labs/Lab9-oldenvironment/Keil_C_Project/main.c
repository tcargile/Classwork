//Trevor Cargile
//813542789
//LAB 7

#include "STM32F0xx.h"

typedef unsigned int uint32_t;

/* Global variable */
volatile uint32_t msTicks; 
volatile uint32_t pattern = 0;

/* Function declarations */
void BTN_Init(void);
void delay (uint32_t ms);
void Inputs_Outputs(void);
void SysTick_Handler(void);
uint32_t getKey(void);
void LED_Init (void);

/* Main function */
int main(void) {	
	int temp;
	
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	LED_Init();
	BTN_Init();
	Inputs_Outputs();
	
	while(1)
	{
		if (pattern != 0) temp = pattern;
		pattern = getKey();
		
		if (pattern == 0)
		{
			if (temp == 1)
			{
				GPIOA->BSRR |= (1UL << 25);
				GPIOA->BSRR |= (1UL << 8);
				delay(2);
				GPIOA->BSRR |= (1UL << 24);
				delay(2);
			}
			else if (temp == 2)
			{
				GPIOA->BSRR |= (1UL << 24);
				GPIOA->BSRR |= (1UL << 9);
				delay(3);
				GPIOA->BSRR |= (1UL << 25);
				delay(3);
			}
			else if (temp == 3)
			{
				GPIOA->BSRR |= (1UL << 9);
				GPIOA->BSRR |= (1UL << 8);
				delay(2);
				GPIOA->BSRR |= (1UL << 24);
				delay(1);
				GPIOA->BSRR |= (1UL << 25);
				delay(1);
				GPIOA->BSRR |= (1UL << 8);
				delay(2);
				GPIOA->BSRR |= (1UL << 24);
				GPIOA->BSRR |= (1UL << 9);
				delay(2);
				GPIOA->BSRR |= (1UL << 8);
				delay(1);
				GPIOA->BSRR |= (1UL << 25);
				delay(1);
				GPIOA->BSRR |= (1UL << 24);
				delay(2);
			}
			else if (temp == 4)
			{
				GPIOA->BSRR |= (1UL << 24);
				GPIOA->BSRR |= (1UL << 25);
			}
		}
		else
		{			
			if (pattern == 1)
			{
				GPIOA->BSRR |= (1UL << 25);
				GPIOA->BSRR |= (1UL << 8);
				delay(2);
				GPIOA->BSRR |= (1UL << 24);
				delay(2);
			}
			else if (pattern == 2)
			{
				GPIOA->BSRR |= (1UL << 24);
				GPIOA->BSRR |= (1UL << 9);
				delay(3);
				GPIOA->BSRR |= (1UL << 25);
				delay(3);
			}
			else if (pattern == 3)
			{
				GPIOA->BSRR |= (1UL << 9);
				GPIOA->BSRR |= (1UL << 8);
				delay(2);
				GPIOA->BSRR |= (1UL << 24);
				delay(1);
				GPIOA->BSRR |= (1UL << 25);
				delay(1);
				GPIOA->BSRR |= (1UL << 8);
				delay(2);
				GPIOA->BSRR |= (1UL << 24);
				GPIOA->BSRR |= (1UL << 9);
				delay(2);
				GPIOA->BSRR |= (1UL << 8);
				delay(1);
				GPIOA->BSRR |= (1UL << 25);
				delay(1);
				GPIOA->BSRR |= (1UL << 24);
				delay(2);			
			}
			else if (pattern == 4)
			{
				GPIOA->BSRR |= (1UL << 24);
				GPIOA->BSRR |= (1UL << 25);
			}
		}
	}
}


/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
	msTicks++;
}


void delay(uint32_t ms)
{
	uint32_t curTicks;

	//Delays the board for the amount of ms that you pass
  curTicks = msTicks;
  while ((msTicks - curTicks) < ms);
}

/* Returns keypad button, scancode = 4*row + col + 1 */
uint32_t getKey(void)
{
	int i;
	
	GPIOC->BSRR &= 0xFFFF0000;		/* Sets all pins to 0 */
	GPIOC->BSRR |= (1UL << 16);		/* Resets pin 0 to 0 */
	GPIOC->BSRR |= (1UL << 1);		/* Sets pin 1 to 1 */
	GPIOC->BSRR |= (1UL << 2);		/* Sets pin 2 to 1 */
	GPIOC->BSRR |= (1UL << 3);		/* Sets pin 3 to 1 */
		
		
	/* Checks each column in the selected row for a 0 */
	for (i = 4; i < 8; i++)
	{
		if ( !(GPIOC->IDR & (1UL << i)) )
			return (i - 3);		/* keypad_button 1 will return 1, keypad_button A will return 3 */
	}

	return 0;		/* If no button is pressed, return 0 */
}

/* Initialize buttons */
void BTN_Init(void) {
  RCC->AHBENR  |= ((1UL << 17) );               /* Enable GPIOA clock         */

  GPIOA->MODER    &= ~((3UL << 2*0)  );         /* PA.0 is input              */
  GPIOA->OSPEEDR  &= ~((3UL << 2*0)  );         /* PA.0 is Low Speed          */
  GPIOA->PUPDR    &= ~((3UL << 2*0)  );         /* PA.0 is no Pull up         */
}


void LED_Init (void) {
  /* Enable clock for GPIOC                                                   */
  RCC->AHBENR |= (1UL << 19);

  /* Configure LED (PC.8..9) pins as push-pull outputs */
  GPIOC->MODER  &= ~((3UL << 2 * 8) | (3UL << 2 * 9));
  GPIOC->MODER  |=  ((1UL << 2 * 8) | (1UL << 2 * 9));
  GPIOC->OTYPER &= ~((1UL <<     8) | (1UL <<     9));

}

/* Function that sets input and output pins */
void Inputs_Outputs (void)
{
	GPIOC->MODER |= (1UL << 6);	/* Sets pin 3 to output mode (01) (Row 3) */
	GPIOC->MODER |= (1UL << 4);	/* Sets pin 2 to output mode (01) (Row 2) */
	GPIOC->MODER |= (1UL << 2);	/* Sets pin 1 to output mode (01) (Row 1) */
	GPIOC->MODER |= (1UL << 0);	/* Sets pin 0 to output mode (01) (Row 0) */
	
	GPIOC->MODER &= ~((3UL << 14));	/* Sets pin 7 to input mode (00) (Col 3) */
	GPIOC->MODER &= ~((3UL << 12));	/* Sets pin 6 to input mode (00) (Col 2) */
	GPIOC->MODER &= ~((3UL << 10));	/* Sets pin 5 to input mode (00) (Col 1) */
	GPIOC->MODER &= ~((3UL << 8));	/* Sets pin 4 to input mode (00) (Col 0) */
		
	GPIOC->PUPDR |= (1UL << 14);	/* Sets pin 7 to pull up (01) */
	GPIOC->PUPDR |= (1UL << 12);	/* Sets pin 6 to pull up (01) */
	GPIOC->PUPDR |= (1UL << 10);	/* Sets pin 5 to pull up (01) */
	GPIOC->PUPDR |= (1UL << 8);		/* Sets pin 4 to pull up (01) */
	
	/* Audio */
  RCC->AHBENR |= (1UL << 17);	//Clock of port A is bit 17 of AHBENR and is enabled
	
	GPIOA->MODER |= (1UL << 16);	//Sets pin 8 to general purpose output mode (01)
	GPIOA->MODER |= (1UL << 18);	//Sets pin 9 to general purpose output mode (01)
}
