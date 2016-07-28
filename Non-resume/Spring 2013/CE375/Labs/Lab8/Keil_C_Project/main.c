//Trevor Cargile
//813542789
//LAB 5

#include "STM32F0xx.h"

typedef unsigned int uint32_t;

/* Global variable */
volatile uint32_t cycleTime = 1000;
volatile uint32_t btn_pressed = 0;
volatile uint32_t msTicks;             

/* Function declarations */
void BTN_Init(void);
void LED_Init (void);
void delay (uint32_t ms);
uint32_t BTN_Get(void);
void LED_On (uint32_t key);
void LED_Off (uint32_t key);
void SysTick_Handler(void);

/* Main function */
int main(void) {	
	
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	LED_Init();
	BTN_Init();
	
	while(1)
	{
		/* turn blue LED on, then wait cycleTime/2 */
		LED_On(1);
		delay(cycleTime/2);
		
		/* turn blue LED off, then wait cycleTime/2 */
		LED_Off(1);
		delay(cycleTime/2);
	}
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

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
	msTicks++;

	
	/* check to see if USER button is pressed, will return 1 if so */
	if (BTN_Get() == (1UL << 0) && btn_pressed == 0)
	{
		/* turn green LED on */
		LED_On(2);
		
		btn_pressed = 1;
		
		/* decrease cycleTime by 100ms */		
		cycleTime -= 100;
		if (cycleTime < 100)
			cycleTime = 1000;	
	}
	else if (BTN_Get() != (1UL << 0))
	{
		btn_pressed = 0;
		LED_Off(2);
	}
}

/* k = around 4850 for 1ms */
void delay (uint32_t ms) {                                              
  uint32_t curTicks;

  curTicks = 0;
  while (curTicks < 4850*ms)
	{
		curTicks++;
	}
}


uint32_t BTN_Get(void) {
 return (GPIOA->IDR & (1UL << 0));
}


/* Turns Blue/Green LED On and Off. key = 1 for blue, 2 for green*/
void LED_On (uint32_t key) {
	GPIOC->BSRR |= (key << 8);
}

void LED_Off (uint32_t key) {
	GPIOC->BSRR |= (key << 24);
}
