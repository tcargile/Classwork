//Trevor Cargile
//813542789
//LAB 7

#include "STM32F0xx.h"

typedef unsigned int uint32_t;

/* Global variable */
volatile uint32_t cycleTime_BLUE = 800;
volatile uint32_t cycleTime_GREEN = 50;
volatile uint32_t msTicks_BLUE = 0;
volatile uint32_t msTicks_GREEN = 0;

/* Function declarations */
void Initialize (void);
void LED_On (uint32_t key);
void LED_Off (uint32_t key);
void SysTick_Handler (void);
uint32_t getKey (void);

/* Main function */
int main(void) {	
	uint32_t BLUE_ON = 0;
	uint32_t GREEN_ON = 0;
	
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	Initialize();
	
	while(1)
	{	
		/* Control if the new cycletime goes below what msTicks is currently at */
		while (msTicks_BLUE > (cycleTime_BLUE / 2))
			msTicks_BLUE = (cycleTime_BLUE / 2);;
		while (msTicks_GREEN > (cycleTime_GREEN / 2))
			msTicks_GREEN = (cycleTime_GREEN / 2);
		
		/* If statement to control blue LED */
		if (msTicks_BLUE == (cycleTime_BLUE / 2))
		{
			if (BLUE_ON == 1)
			{
				LED_Off(1);
				BLUE_ON = 0;
			}
			else
			{
				LED_On(1);
				BLUE_ON = 1;
			}
			
			msTicks_BLUE = 0;
		}
		
		/* If statement to control green LED */
		if (msTicks_GREEN == (cycleTime_GREEN / 2))
		{
			if (GREEN_ON == 1)
			{
				LED_Off(2);
				GREEN_ON = 0;
			}
			else
			{
				LED_On(2);
				GREEN_ON = 1;
			}
			
			msTicks_GREEN = 0;
		}	
	}
}






/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  uint32_t key_pressed = 0;
	msTicks_BLUE++;
	msTicks_GREEN++;

	/* Monitor the output of PA1 */
	ADC1->CR |= (1UL << 2);
	cycleTime_GREEN = (ADC1->DR / 40 * 9.5 + 50);
	ADC1->CR &= ~(1UL << 2);
	
	/* check to see if keypad button is pressed, will return scancode if so */
	key_pressed = getKey();
	if (key_pressed != 0)
	{
		cycleTime_BLUE = key_pressed * 50;
	}
}


/* Turns Blue/Green LED On and Off. key = 1 for blue, 2 for green*/
void LED_On (uint32_t key) {
	GPIOC->BSRR |= (key << 8);
}


void LED_Off (uint32_t key) {
	GPIOC->BSRR |= (key << 24);
}


/* Returns keypad button, scancode = 4*row + col + 1 */
uint32_t getKey(void)
{
	int i, y;
	for(y = 0; y < 4; y++)
	{
		if (y == 0)	/* row 0 */
		{
			GPIOC->BSRR &= 0xFFFF0000;		/* Sets all pins to 0 */
			GPIOC->BSRR |= (1UL << 16);		/* Resets pin 0 to 0 */
			GPIOC->BSRR |= (1UL << 1);		/* Sets pin 1 to 1 */
			GPIOC->BSRR |= (1UL << 2);		/* Sets pin 2 to 1 */
			GPIOC->BSRR |= (1UL << 3);		/* Sets pin 3 to 1 */
		}
		else if (y == 1) /* row 1 */
		{
			GPIOC->BSRR &= 0xFFFF0000;
			GPIOC->BSRR |= (1UL << 0);		/* Sets pin 0 to 1 */
			GPIOC->BSRR |= (1UL << 17);		/* Resets pin 1 to 0 */
			GPIOC->BSRR |= (1UL << 2);		/* Sets pin 2 to 1 */
			GPIOC->BSRR |= (1UL << 3);		/* Sets pin 3 to 1 */
		}
		else if (y == 2) /* row 2 */
		{
			GPIOC->BSRR &= 0xFFFF0000;
			GPIOC->BSRR |= (1UL << 0);		/* Sets pin 0 to 1 */
			GPIOC->BSRR |= (1UL << 1);		/* Sets pin 1 to 1 */
			GPIOC->BSRR |= (1UL << 18);		/* Resets pin 2 to 0 */
			GPIOC->BSRR |= (1UL << 3);		/* Sets pin 3 to 1 */
		}
		else /* row 3 */
		{
			GPIOC->BSRR &= 0xFFFF0000;
			GPIOC->BSRR |= (1UL << 0);		/* Sets pin 0 to 1 */
			GPIOC->BSRR |= (1UL << 1);		/* Sets pin 1 to 1 */
			GPIOC->BSRR |= (1UL << 2);		/* Sets pin 2 to 1 */
			GPIOC->BSRR |= (1UL << 19);		/* Resets pin 3 to 0 */
		}
		
		/* Checks each column in the selected row for a 0 */
		for (i = 4; i < 8; i++)
		{
			if ( !(GPIOC->IDR & (1UL << i)) )
				return (i - 3 + 4 * y);		/* keypad_button 1 will return 1, keypad_button D will return 16 */
		}
	}
	return 0;		/* If no button is pressed, return 0 */
}


/* Function that initializes many things. */
void Initialize (void)
{
	/******** PARTS OF LED INIT ********/
	/* Enable clock for GPIOC */
  RCC->AHBENR |= (1UL << 19);

  /* Configure LED (PC.8..9) pins as push-pull outputs */
  GPIOC->MODER  &= ~((3UL << 2 * 8) | (3UL << 2 * 9));
  GPIOC->MODER  |=  ((1UL << 2 * 8) | (1UL << 2 * 9));
  GPIOC->OTYPER &= ~((1UL <<     8) | (1UL <<     9));
	
	
	/******** PARTS OF INPUTS OUTPUTS ********/	
	/* Sets pins 7 - 4 as inputs (input mode - 00). Represent Columns 3 - 0 */
	GPIOC->MODER &= ~((3UL << 14));
	GPIOC->MODER &= ~((3UL << 12));
	GPIOC->MODER &= ~((3UL << 10));
	GPIOC->MODER &= ~((3UL << 8));
	
	/* Sets pins 3 - 0 as outputs (output mode - 01). Represent Rows 3 - 0 */
	GPIOC->MODER |= (1UL << 6);
	GPIOC->MODER |= (1UL << 4);	
	GPIOC->MODER |= (1UL << 2);
	GPIOC->MODER |= (1UL << 0);

	/* Sets pins 7 - 4 as pull up - which is 01 */	
	GPIOC->PUPDR |= (1UL << 14);
	GPIOC->PUPDR |= (1UL << 12);
	GPIOC->PUPDR |= (1UL << 10);
	GPIOC->PUPDR |= (1UL << 8);
	
	
	/******** CONFIG PA1 ********/
	/* Enable GPIOA clock         */
	RCC->AHBENR  |= (1UL << 17);
	/* Enabled ADC clock */
	RCC->APB2ENR |= (1UL << 9);
	
	/* Set PA1 as Analog mode */
	GPIOA->MODER |= (3UL << 2);
	
	/* Enable ADC */
	ADC1->CR |= (1UL << 0);
	
	/* Configure ADC registers for Channel 1*/
	ADC1->CHSELR &= 0;
	ADC1->CHSELR |= (1UL << 1);
	
	/* ADC analog input Channel 1 monitored by AWD */
	ADC1->CFGR1 &= ~(31UL << 26);
	ADC1->CFGR1 |= (1UL << 26);
	
	/* Set sample time of register */
	ADC1->SMPR |= (0UL << 0);
}
