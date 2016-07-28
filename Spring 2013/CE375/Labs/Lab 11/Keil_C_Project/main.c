/***************************************************************** 
 *  MDK-ARM Template for a Simple Discovery Board C Project
 *
 *****************************************************************/
#include <STM32F0xx.h>
#include <math.h>

/* noteNumber[i] is the MIDI note for scancode i. */
uint8_t noteNumber[17] = {0, 60, 62, 64, 65, 67, 69, 71, 0, 72, 74, 76, 77, 79, 81, 83, 84};  
/* frequency[i] is the frequency in Hertz of noteNumber */
float frequency[17]; 
/*	period for ARR register. */	
uint16_t period[17];     
	
/* tests to see if new MIDI value is being determined. */	
uint32_t new_value_process = 0;		
volatile uint32_t msTicks;
/* Global variable to represent the scancode from the keypad */
int scancode = 0;
/* Global variable to represent an error */
/* 1 = too small, 2 = too big, 3 = not a number, 0 = no error. MIDI numbers range from 21 to 108 */
int error = 0;

uint32_t getKey(void);
void reorder_frequency (void);
void new_MIDI_value (void);
void new_MIDI (int num);
void SysTick_Handler(void);
void delay(uint32_t ms);
void Initialize (void);

int main(void)
{	
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }

	/* Initialize all registers */
	Initialize();
	
	/* Initialize the global arrays with default values */
	reorder_frequency();
	
	while(1)
	{
		/* check if button is being pressed */
		scancode = getKey();
		if (scancode != 0)
		{
			/* set frequency of the current button being clicked */
			TIM1->ARR = period[scancode];
			
			/*turn both speakers on */
			TIM1->CCR1 = 500;
			TIM1->CCR2 = 500;
		}
		
		/* wait for the button to be unpressed. */
		delay(5);
		while (scancode != 0)
			scancode = getKey();
				
		/* once the button is unpressed, turn off speakers. */
		TIM1->CCR1 = 0;
		TIM1->CCR2 = 0;
	}
}



/*** Functions ***/

void SysTick_Handler(void) {
	msTicks++;}

/* Initialize buttons */
void BTN_Init(void) {

}

/*Initialize LEDs */
void LED_Init (void) {
  /* Enable clock for GPIOC                                                   */
  RCC->AHBENR |= (1UL << 19);

  /* Configure LED (PC.8..9) pins as push-pull outputs */
  GPIOC->MODER  &= ~((3UL << 2 * 8) | (3UL << 2 * 9));
  GPIOC->MODER  |=  ((1UL << 2 * 8) | (1UL << 2 * 9));
  GPIOC->OTYPER &= ~((1UL <<     8) | (1UL <<     9));
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
	
	for (i = 4; i < 8; i++)
	{
		if ( !(GPIOC->IDR & (1UL << i)) )
			return (i - 3);
	}
	
	GPIOC->BSRR &= 0xFFFF0000;
	GPIOC->BSRR |= (1UL << 0);		/* Sets pin 0 to 1 */
	GPIOC->BSRR |= (1UL << 17);		/* Resets pin 1 to 0 */
	GPIOC->BSRR |= (1UL << 2);		/* Sets pin 2 to 1 */
	GPIOC->BSRR |= (1UL << 3);		/* Sets pin 3 to 1 */
	
	for (i = 4; i < 8; i++)	
	{
		if ( !(GPIOC->IDR & (1UL << i)) )
		{
			/* If B is pressed and not in new MIDI mode, enter new MIDI mode */
			if ((i == 7) && (new_value_process != 1))
			{
				new_value_process = 1;
				new_MIDI_value();
				new_value_process = 0;
				return 0;
			}
			else
				return (i + 1);
		}
	}
	
	GPIOC->BSRR &= 0xFFFF0000;
	GPIOC->BSRR |= (1UL << 0);		/* Sets pin 0 to 1 */
	GPIOC->BSRR |= (1UL << 1);		/* Sets pin 1 to 1 */
	GPIOC->BSRR |= (1UL << 18);		/* Resets pin 2 to 0 */
	GPIOC->BSRR |= (1UL << 3);		/* Sets pin 3 to 1 */
	
	for (i = 4; i < 8; i++)	
	{
		if ( !(GPIOC->IDR & (1UL << i)) )
			return (i + 5);
	}
	
	GPIOC->BSRR &= 0xFFFF0000;
	GPIOC->BSRR |= (1UL << 0);		/* Sets pin 0 to 1 */
	GPIOC->BSRR |= (1UL << 1);		/* Sets pin 1 to 1 */
	GPIOC->BSRR |= (1UL << 2);		/* Sets pin 2 to 1 */
	GPIOC->BSRR |= (1UL << 19);		/* Resets pin 3 to 0 */
	
	for (i = 4; i < 8; i++)		
	{
		if ( !(GPIOC->IDR & (1UL << i)) )
				return (i + 9);
	}
	return 0;		/* If no button is pressed, return 0 */
}

/* Delay function to help with keybounce */
void delay(uint32_t ms)
{
	uint32_t curTicks;

	//Delays the board for the amount of ms that you pass
  curTicks = msTicks;
  while ((msTicks - curTicks) < ms);
}

/* Function to change the frequency and period arrays based on a change in the noteNumber */
void reorder_frequency (void)
{
	int i;
	for (i = 0; i < 17; i++)
	{
		if (noteNumber[i] != 0)
		{
			/* Equation in manual to get frequency of piano key */
			frequency[i] = 27.5 * (float)pow(2, (float)(noteNumber[i] - 21)/12);
			/* Equation is 1 MHz / frequency */
			period[i] = (1000000) / (frequency[i]);
		}
	}
}

/* Scans the keypad after B is pressed to see what the starting MIDI value is */
void new_MIDI_value (void)
{
	int num = 0;
	int temp = 0;
	int pound = 0;
	error = 0;
	
	/* Wait for the B key to be released so it doesn't affect number */
	temp = getKey();
	delay(5);
	while(temp != 0)
		temp = getKey();
	
	/* Continue loop until the pound key is pressed */
	while (pound != 1)
	{
		temp = getKey();
		/* Pound key */
		if (temp == 15)
			pound = 1;
		/* Multiple non-numerical buttons */
		else if (temp  == 4)
			num = -1;			
		else if (temp == 13)
			num = -1;			
		else if (temp == 8) 
			num = -1;
		else if (temp == 12)
			num = -1;			
		else if (temp == 16)
			num = -1;
		/* If actual number */
		else if (temp != 0)
		{
			/* Even if its an actual number, if the number is already an error, do nothing. */
			if (num != -1)
			{
				/* Changes the scancode to be based on the keypad visual number */
				if (temp == 5)
					num = 10*num + 4;
				else if (temp == 6)
					num = 10*num + 5;
				else if (temp == 7)
					num = 10*num + 6;
				else if (temp == 9)
					num = 10*num + 7;
				else if (temp == 10)
					num = 10*num + 8;
				else if (temp == 11)
					num = 10*num + 9;
				else if (temp == 14)
					num = 10*num;
				else
					num = 10*num + temp;
			}
		}
	
		/* wait for release */
		delay(5);
		while(temp != 0)
			temp = getKey();
	}
	
	/* If number is error, do nothing and change error to 1. */
  if ((num < 21))
		error = 1;
	else if (num > 108)
		error = 2;
	else if (num == -1)
		error = 3;
	else
		new_MIDI(num);
}

/* Changes noteNumber based on the first new MIDI number from the previous function */
void new_MIDI (int num)
{
	int i;
	for (i = 1; i < 17; i++)
	{
		/* Do nothing for values of 0. */
		if (noteNumber[i] != 0)
			noteNumber[i] = num;
		
		/* set values for alternating 3, 4, 3, 4 */
		if (i == 3)
			num++;
		else if (i == 7)
			num++;
		else if (i == 11)
			num++;
		else if (i == 15)
			num++;
		else if (noteNumber[i] == 0)
		{}
		else
			num = num + 2;
	}
	
	/* Now redo the frequencies with the new MIDI number */
	reorder_frequency();
}
