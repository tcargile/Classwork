/************************************************************
Nathan Purta
CompE375 Midterm
Red ID 814071486

This code turns on the LEDs on the Cortex M0 Discovery Board
and allows them to blink at different speeds, which are 
determined by the number pressed on the keypad in milliseconds.
The push button on the board changes which LED blinks. The blue
LED is initially set to blink whenever the code is first 
executed.
**************************************************************/

#include <STM32F0xx.h>

void delay(uint32_t ms);
uint32_t BTN_Get(void);
void BTN_Init(void);
void LED_Init (void);
void Audio_Init (void);
void Mode_Set (void);
void initTIM1(void);
void  getKey(void);

typedef enum {CH1, CH2, BOTH, NONE} SELECTION;
SELECTION selection;

//uint16_t timerPeriod = 2000;
uint16_t dutyCH1 = 1000;
uint16_t dutyCH2 = 100;
//uint16_t num = 0;
// int i;
int num = 0;

volatile uint32_t cycleTime = 2000;
volatile uint32_t msTicks;

int main()
{	
	//uint16_t TimerPeriod;
	int counter = 3;
	uint32_t nextTicks; //Variable used to keep track of current time
	
	SystemCoreClockUpdate();   									  //Gets core clock frequency
  if (SysTick_Config(SystemCoreClock / 1000)) 	//Creates loop to catch interrupts
    while (1);																	//Captures interrupt imediately
	
	//TimerPeriod = (SystemCoreClock /48 / 500) - 1;
	
	initTIM1();
	Audio_Init();
	BTN_Init();		//Initializes the push button
	LED_Init();		//Initializes the LEDs
	Mode_Set();		//Sets PC<3:0> to output and PC<7:4> to input
	
	while(1)
	{
		if (counter == 1)
		{
			//GPIOC->BSRR &= (15UL << 16);
			GPIOC->BSRR |= (1UL << 8); //Turn on Blue LED
			GPIOC->BSRR |= (1UL << 25); //Turn off Green LED
		}
		
		else if (counter == 2)
		{
			//GPIOC->BSRR &= (15UL << 16);
			GPIOC->BSRR |= (1UL << 24); //Turn off Blue LED
			GPIOC->BSRR |= (1UL << 9); //Turn on Green LED
		}
		
		else if (counter == 3)
		{
			//GPIOC->BSRR &= (15UL << 16);
			GPIOC->BSRR |= (1UL << 8); //Turn on Blue LED
			GPIOC->BSRR |= (1UL << 9); //Turn on Green LED
		}
		
		else
		{
			//GPIOC->BSRR &= (15UL << 16);
			GPIOC->BSRR |= (1UL << 24); //Turn off Blue LED
			GPIOC->BSRR |= (1UL << 25); //Turn off Green LED
		}
		delay(10);
		nextTicks = msTicks + 50;
		while (msTicks < nextTicks)
		{
			if (BTN_Get() == 1)
			{
				delay(1);
				counter++;
				counter = counter % 4; //Keeps counter between 0 and 3
				if (counter == 1)
				{
					//GPIOC->BSRR &= (15UL << 16);
					GPIOC->BSRR |= (1UL << 8); //Turn on Blue LED
					GPIOC->BSRR |= (1UL << 25); //Turn off Green LED
					TIM1->CCR2 = 0;						//Turn off Speaker 2
					TIM1->CCR1 = dutyCH1;			//Turn on Speaker 1
				}
				
				else if (counter == 2)
				{
					//GPIOC->BSRR &= (15UL << 16);
					GPIOC->BSRR |= (1UL << 24); //Turn off Blue LED
					GPIOC->BSRR |= (1UL << 9); //Turn on Green LED
					TIM1->CCR2 = dutyCH2;	//Turn on Speaker 2
					TIM1->CCR1 = 0;				//Turn off Speaker 1
				}
				
				else if (counter == 3)
				{
					//GPIOC->BSRR &= (15UL << 16);
					GPIOC->BSRR |= (1UL << 8); //Turn on Blue LED
					GPIOC->BSRR |= (1UL << 9); //Turn on Green LED
					TIM1->CCR2 = dutyCH2;				//Turn on Speaker 2
					TIM1->CCR1 = dutyCH1;				//Turn on Speaker 1
				}
				
				else
				{
					//GPIOC->BSRR &= (15UL << 16);
					GPIOC->BSRR |= (1UL << 24); //Turn off Blue LED
					GPIOC->BSRR |= (1UL << 25); //Turn off Green LED
					TIM1->CCR2 = 0;				//Turn off Speaker 2
					TIM1->CCR1 = 0;				//Turn off Speaker 1
				}
				
				while (BTN_Get() == 1);
				delay(1);
			}
		}
		
		getKey();
		
		nextTicks = msTicks + 50;
		while (msTicks < nextTicks)
		{
			delay(1);
			if (BTN_Get() == 1)
			{
				counter++;
				counter = counter % 4; //Keeps counter between 0 and 3
				if (counter == 1)
				{
					//GPIOC->BSRR &= (15UL << 16);
					GPIOC->BSRR |= (1UL << 8); //Turn on Blue LED
					GPIOC->BSRR |= (1UL << 25); //Turn off Green LED
					TIM1->CCR2 = 0;						//Turn off Speaker 2
					TIM1->CCR1 = dutyCH1;			//Turn on Speaker 1
				}
				
				else if (counter == 2)
				{
					//GPIOC->BSRR &= (15UL << 16);
					GPIOC->BSRR |= (1UL << 24); //Turn off Blue LED
					GPIOC->BSRR |= (1UL << 9); //Turn on Green LED
					TIM1->CCR2 = dutyCH2;	//Turn on Speaker 2
					TIM1->CCR1 = 0;				//Turn off Speaker 1
				}
				
				else if (counter == 3)
				{
					//GPIOC->BSRR &= (15UL << 16);
					GPIOC->BSRR |= (1UL << 8); //Turn on Blue LED
					GPIOC->BSRR |= (1UL << 9); //Turn on Green LED
					TIM1->CCR2 = dutyCH2;				//Turn on Speaker 2
					TIM1->CCR1 = dutyCH1;				//Turn on Speaker 1
				}
				
				else
				{
					//GPIOC->BSRR &= (15UL << 16);
					GPIOC->BSRR |= (1UL << 24); //Turn off Blue LED
					GPIOC->BSRR |= (1UL << 25); //Turn off Green LED
					TIM1->CCR2 = 0;				//Turn off Speaker 2
					TIM1->CCR1 = 0;				//Turn off Speaker 1
				}
				
				while (BTN_Get() == 1);
				delay(1);
			}
		}
		delay(10);
		
	}
}

//Function that sets the TIM1 registers
void initTIM1(void) 
{
	RCC->APB2ENR = (1UL << 11);
	TIM1->CR1 = 0x00000001;
	TIM1->CR2 = 0x00000500;
	TIM1->ARR = 0x000007D0;
	TIM1->SR = 0x0000001F;
	TIM1->CCMR1 = 0x00006060;
	TIM1->CCER = 0x00000077;
	TIM1->PSC = 0x00000030;
	TIM1->CCR1 = 1000;
	TIM1->CCR2 = 100;
	TIM1->BDTR = 0x00008000;
	TIM1->DMAR = 0x00000001;
}

//Interrupt service routine function
void SysTick_Handler(void)
{
	
	msTicks++;	//Increments clock once every millisecond

}

//Function that returns value of pressed keypad button, if any
void getKey(void)
{
	int i;
	
	uint32_t delayTicks;
	//int num = 0;	//Variable to store the button number
	delay (50);
	
	GPIOC->BSRR &= (15UL << 16);
	GPIOC->BSRR |= (1UL << 16);		//Sets pin 0 to 0
	GPIOC->BSRR |= (1UL << 1);		//Sets pin 1 to 1
	GPIOC->BSRR |= (1UL << 2);		//Sets pin 2 to 1
	GPIOC->BSRR |= (1UL << 3);		//Sets pin 3 to 1
	
	for (i = 4; i < 8; i++)		//Checks each colum in row 1 if there is a 0 bit
	{
		if ( !(GPIOC->IDR & (1UL << i)) && i != 7)
		{
			num = num * 10 + (i - 3);
			while (!(GPIOC->IDR & (1UL << i)) == 1);
		}
		
		else if (!(GPIOC->IDR & (1UL << i)) && i == 7)
		{
			if (dutyCH1 == 2000)
			{
				dutyCH1 = 1000;
				TIM1->CCR1 = dutyCH1;
			}
			
			else
			{
				if (TIM1->CCR1 | 0UL)
				{
					dutyCH1 = dutyCH1 + 50;
					TIM1->CCR1 = dutyCH1;
				}
			}
			
			while (!(GPIOC->IDR & (1UL << i)) == 1);
			//return -1;
		}
		
	}
	
	GPIOC->BSRR &= (15UL << 16);
	GPIOC->BSRR |= (1UL << 0);		//Sets pin 0 to 1
	GPIOC->BSRR |= (1UL << 17);		//Sets pin 1 to 0
	GPIOC->BSRR |= (1UL << 2);		//Sets pin 2 to 1
	GPIOC->BSRR |= (1UL << 3);		//Sets pin 3 to 1
	
	for (i = 4; i < 8; i++)		//Checks each colum in row 2 if there is a 0 bit
	{
		if ( !(GPIOC->IDR & (1UL << i)) && i != 7)
		{
			num = num * 10 + i;
			while (!(GPIOC->IDR & (1UL << i)) == 1);
		}
		
		else if (!(GPIOC->IDR & (1UL << i)) && i == 7)
		{
			if (dutyCH2 == 200)
			{
				dutyCH2 = 100;
				TIM1->CCR2 = dutyCH2;
			}
			
			else
			{
				if (TIM1->CCR2 | 0UL)
				{
					dutyCH2 = dutyCH2 + 5;
					TIM1->CCR2 = dutyCH2;
				}
			}
			
			while (!(GPIOC->IDR & (1UL << i)) == 1);
			//return 0;
		}
			
	}
	
	GPIOC->BSRR &= (15UL << 16);
	GPIOC->BSRR |= (1UL << 0);		//Sets pin 0 to 1
	GPIOC->BSRR |= (1UL << 1);		//Sets pin 1 to 1
	GPIOC->BSRR |= (1UL << 18);		//Sets pin 2 to 0
	GPIOC->BSRR |= (1UL << 3);		//Sets pin 3 to 1
	
	for (i = 4; i < 8; i++)	//Checks each colum in row 3 if there is a 0 bit
	{
		if ( !(GPIOC->IDR & (1UL << i)) && i != 7)
		{
			num = num * 10 + (i + 3);
			while (!(GPIOC->IDR & (1UL << i)) == 1);
		}
		
		else if (!(GPIOC->IDR & (1UL << i)) && i == 7)
		{
			delayTicks = msTicks + 1000;
			while (msTicks < delayTicks)
			{
				GPIOC->BSRR |= ((1UL << 8) | (1UL << 9));
				delay (100);
				GPIOC->BSRR |= ((1UL << 24) | (1UL << 25));
				delay (100);
			}
			num = 0;
			
			while (!(GPIOC->IDR & (1UL << i)) == 1);
			
			//return -1;
		}
	}
	
	GPIOC->BSRR &= (15UL << 16);
	GPIOC->BSRR |= (1UL << 0);		//Sets pin 0 to 1
	GPIOC->BSRR |= (1UL << 1);		//Sets pin 1 to 1
	GPIOC->BSRR |= (1UL << 2);		//Sets pin 2 to 1
	GPIOC->BSRR |= (1UL << 19);		//Sets pin 3 to 0
	
	for (i = 4; i < 8; i++)		//Checks each colum in row 4 if there is a 0 bit
	{
		if ( !(GPIOC->IDR & (1UL << i)) && i == 6)
		{
			if (num > 19 && num <= 20000)
			{
				TIM1->ARR = num;
				dutyCH1 = 500;
				dutyCH2 = 50;
				TIM1->CCR1 = dutyCH1;
				TIM1->CCR2 = dutyCH2;
				num = 0;
				
				while (!(GPIOC->IDR & (1UL << i)) == 1);
				
				//return num;
			}
			
			else
			{
				delayTicks = msTicks + 1000;
				while (msTicks < delayTicks)
				{
					GPIOC->BSRR |= ((1UL << 8) | (1UL << 9));
					delay (100);
					GPIOC->BSRR |= ((1UL << 24) | (1UL << 25));
					delay (100);
				}
				num = 0;
				
				while (!(GPIOC->IDR & (1UL << i)) == 1);
				
				//return -1;
			}
		}
		
		else if (!(GPIOC->IDR & (1UL << i)) && i == 5)
		{
			num = num * 10;
			while (!(GPIOC->IDR & (1UL << i)) == 1);
		}
		
		else if ((!(GPIOC->IDR & (1UL << i)) && (i == 4 || i == 7)))
		{
			delayTicks = msTicks + 1000;
			while (msTicks < delayTicks)
			{
				GPIOC->BSRR |= ((1UL << 8) | (1UL << 9));
				delay (100);
				GPIOC->BSRR |= ((1UL << 24) | (1UL << 25));
				delay (100);
			}
			num = 0;
			
			while (!(GPIOC->IDR & (1UL << i)) == 1);
			
			//return -1;
			
		}
		
	}
	
	delay (50);
 }


//Function that delays code processing for entered amount in milliseconds
void delay(uint32_t dlyTicks)
{
	uint32_t curTicks;

	//Delays the board for the amount of ms that you pass
  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}

//Function that allows the push button to be pressed
void BTN_Init(void) 
{
  RCC->AHBENR  |= ((1UL << 17) );       //Enables clock of port A

  GPIOA->MODER    &= ~((3UL << 0)  );   // Sets pin 0 of A to 00 (Input mode)
  GPIOA->OSPEEDR  &= ~((3UL << 0)  );   // Sets speed of pin 0 of A to 00 (Slow speed)
  GPIOA->PUPDR    &= ~((3UL << 0)  );   // Disables pull up and pull down for pin 0 of A
}

//Functions that allows LEDs to light up
void LED_Init (void) 
{
  //Enable clock for GPIOC
  RCC->AHBENR |= (1UL << 19);	//Clock of port C is bit 19 of AHBENR and is enabled
  GPIOC->MODER  |=  ((1UL << 2 * 8) | (1UL << 2 * 9));	//Sets LEDs to 01 (Output mode)
}

//Function that retrieves the numeric representation of state of the push button
uint32_t BTN_Get(void) 
{
	return (GPIOA->IDR & (1UL << 0));	//Returns the integer value of the button pressed
}

//Function that sets input and output pins
void Mode_Set (void)
{
	GPIOC->MODER |= (1UL << 6);	//Sets pin 3 to output mode (01) (Row 3)
	GPIOC->MODER |= (1UL << 4);	//Sets pin 2 to output mode (01) (Row 2)
	GPIOC->MODER |= (1UL << 2);	//Sets pin 1 to output mode (01) (Row 1)
	GPIOC->MODER |= (1UL << 0);	//Sets pin 0 to output mode (01) (Row 0)
	
	GPIOC->MODER &= ~((3UL << 14));	//Sets pin 7 to input mode (00) (Col 3)
	GPIOC->MODER &= ~((3UL << 12));	//Sets pin 6 to input mode (00) (Col 2)
	GPIOC->MODER &= ~((3UL << 10));	//Sets pin 5 to input mode (00) (Col 1)
	GPIOC->MODER &= ~((3UL << 8));	//Sets pin 4 to input mode (00) (Col 0)
		
	GPIOC->PUPDR |= (1UL << 14);	//Sets pin 7 to pull up (01)
	GPIOC->PUPDR |= (1UL << 12);	//Sets pin 6 to pull up (01)
	GPIOC->PUPDR |= (1UL << 10);	//Sets pin 5 to pull up (01)
	GPIOC->PUPDR |= (1UL << 8);		//Sets pin 4 to pull up (01)
	
	//Sets the AFRH
	GPIOA->AFR[1] &= ~((15UL << 0) | (15UL << 4));	//Sets PA8 and PA9 to 0000 
	GPIOA->AFR[1] |= ((2UL << 0) | (2UL << 4));	//Sets PA8 and PA9 to 0010 
}

void Audio_Init (void) 
{
  //Enable clock for GPIOA
  RCC->AHBENR |= (1UL << 17);	//Clock of port A is bit 17 of AHBENR and is enabled
	
  GPIOA->MODER  |=  ((2UL << 2 * 8) | (2UL << 2 * 9));	//Sets audio to 10 (Output mode)
	GPIOA->OTYPER  &=  ~((1UL << 8) | (1UL << 9));
}
