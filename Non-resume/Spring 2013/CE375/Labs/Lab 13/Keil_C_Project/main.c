/***************************************************************** 
 *  MDK-ARM Template for a Simple Discovery Board C Project
 *
 *****************************************************************/
#include <STM32F0xx.h>
#include <math.h>

/*typedef to store starttime, stoptime, number pressed */
typedef struct {
  uint8_t number;  /* scancode */
  uint32_t startTime;
  uint32_t stopTime;
} NOTE;


/* noteNumber[i] is the MIDI note for scancode i. */
uint8_t noteNumber[17] = {0, 60, 62, 64, 65, 67, 69, 71, 0, 72, 74, 76, 77, 79, 81, 83, 84};  
/* frequency[i] is the frequency in Hertz of noteNumber */
float frequency[17]; 
/*	period for ARR register. */	
uint16_t period[17];
/* Array to keep at least 100 notes played */
NOTE Song[100];

volatile uint32_t msTicks;
volatile uint32_t msTicks_SOUND;
volatile uint32_t msTicks_LED;
volatile uint32_t cycleTime = 125;
volatile uint32_t scancode = 0;
volatile uint32_t volume = 500;
volatile uint32_t controlInAction = 0;
	
uint32_t getKey(void);	
void SysTick_Handler(void);
void reorder_frequency (void);
void Initialize (void);
void LED_On (uint32_t key);
void LED_Off (uint32_t key);
void delay(uint32_t ms);
void control_function(void);
void record_function(void);
void playback_function(void);

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

	/* Set first NOTE to 0 if user playbacks nothing it won't do anything */
	Song[0].number = 0;
	
	while(1)
	{
		LED_On(1);
		LED_Off(2);
		
		/* check if button is being pressed */
		scancode = getKey();
		if (scancode != 0)
		{
			/* set frequency of the current button being clicked */
			TIM1->ARR = period[scancode];
			/* set volume of speakers */
			TIM1->CCR1 = volume;
			TIM1->CCR2 = volume;
		}
		
		/* wait for the button to be unpressed. */
		delay(5);
		while (scancode != 0)
		{
			scancode = getKey();
			TIM1->CCR1 = volume;
			TIM1->CCR2 = volume;
		}
				
		/* once the button is unpressed, turn off speakers. */
		TIM1->CCR1 = 0;
		TIM1->CCR2 = 0;
	}
}





/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
	msTicks_LED++;
	msTicks++;
	msTicks_SOUND++;


	/* Monitor the output of PA1 */
	ADC1->CR |= (1UL << 2);
	volume = (ADC1->DR / 40 * 9);
	ADC1->CR &= ~(1UL << 2);
}


/* Function that initializes many things. */
void Initialize (void)
{
	/******** PARTS OF BTN INIT ********/
	/* Enable GPIOA clock         */
	RCC->AHBENR  |= ((1UL << 17) );               

	/* PA.0 is input              */
  GPIOA->MODER    &= ~((3UL << 2*0)  ); 
	/* PA.0 is Low Speed          */
  GPIOA->OSPEEDR  &= ~((3UL << 2*0)  ); 
	/* PA.0 is no Pull up         */
  GPIOA->PUPDR    &= ~((3UL << 2*0)  );         
	
	
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
	
	
	/******** INIT TIMER CONFIG ********/
	RCC->APB2ENR = (1UL << 11);
	/* Shuts off with period of 0 */
	TIM1->ARR = 0;
	/* Sets Channel 1 and Channel 2 to PWM mode, making them active as long as CNT<CRR. */
	TIM1->CCMR1 = 0x00006060;
	/* Channel 1 and 2 is output based on BDTR register. MOE is set to 1, which makes it main output enabled */
	TIM1->CCER = 0x00000077;
	/* Prescaler = 48 */
	TIM1->PSC = 48;
	/* Shuts off speaker 1 and 2 with duty cycles of 0 */
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	/* Enables main output when its set in CCER register */
	TIM1->BDTR = 0x00008000;
	
	/* Registers that weren't required in lab, but it made it work. */
	/* Enables the counter */
	TIM1->CR1 = 0x00000001;
	/* Dead-lock when MOE = 0, but its set to 1 in the BDTR register */
	TIM1->CR2 = 0x00000500;
	
	
	/******** SOUND OUTPUT ********/
	/* Resets AFRH register, then sets PA8 and PA9 to 0010 so it can be controlled by alternate function */
	/* The pins were set to alternate function in the MODER register below. */
	GPIOA->AFR[1] &= ~((15UL << 0) | (15UL << 4));	
	GPIOA->AFR[1] |= ((2UL << 0) | (2UL << 4));	

	/* Enables clock */
	RCC->AHBENR |= (1UL << 17);		
	/* Sets pins 8 and 9 to alternate function to be controlled (10) */
	GPIOA->MODER |= (1UL << 17);	
	GPIOA->MODER |= (1UL << 19);
	
	
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


/* Turns Blue/Green LED On and Off. key = 1 for blue, 2 for green*/
void LED_On (uint32_t key) {
	GPIOC->BSRR |= (key << 8);
}


void LED_Off (uint32_t key) {
	GPIOC->BSRR |= (key << 24);
}


/* Delay function to help with keybounce */
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
			if ((i == 7) && (controlInAction == 0))
			{
				controlInAction = 1;
				control_function();
				controlInAction = 0;
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

void control_function (void)
{
	int temp;
	int pressed = 0;
	int LED_isOn = 1;
	
	LED_On(1);
	LED_On(2);
	/* reset msTicks_LED timer */
	msTicks_LED = 0;
	
	temp = getKey();
	delay(5);
	while(temp != 0)
		temp = getKey();
	
	/* wait for the button to be pressed. */
	scancode = getKey();
	while (pressed == 0)
	{
		if (msTicks_LED > cycleTime)
			msTicks_LED = cycleTime;
		
		scancode = getKey();
		if (scancode == 1)
		{
			pressed = 1;
			while (getKey() != 0){}
		}
		else if (scancode == 2)
			record_function();
		else if (scancode == 3)
			playback_function();
		
		if (msTicks_LED == cycleTime)
		{
			if (LED_isOn == 1)
			{
				LED_Off(1);
				LED_Off(2);
				msTicks_LED = 0;
				LED_isOn = 0;
			}
			else
			{
				LED_On(1);
				LED_On(2);
				msTicks_LED = 0;
				LED_isOn = 1;
			}
		}
	}
	
	return;
}

void record_function (void)
{
	int temp;
	int scancode_new;
	int numberOfKeysPressed = 0;
	
	LED_On(2);
	LED_Off(1);
	
	/* Wait for the 2 key to be released so it doesn't affect number */
	temp = getKey();
	delay(5);
	while(temp != 0)
		temp = getKey();
	
	while(1)
	{
		if (getKey() != 0)
		{
			/* check if button is being pressed */
			scancode_new = getKey();
			if (scancode_new != 0)
			{
				if (scancode_new == 8)
				{
					/* If B is pressed, mark the current entry with 0 so that I know its the end of the stream of keys */
					Song[numberOfKeysPressed].number = 0;
					/* Go back to control */
					return;
				}
				else
				{
					/* set frequency of the current button being clicked */
					TIM1->ARR = period[scancode_new];
					/*set volume of speakers */
					TIM1->CCR1 = volume;
					TIM1->CCR2 = volume;
					/* set current Song entry with its MIDI number and startTime of msTicks_SOUND */
					Song[numberOfKeysPressed].number = scancode_new;
					Song[numberOfKeysPressed].startTime = msTicks_SOUND;
				}
			}
		
			/* wait for the button to be unpressed. */
			while(getKey() != 0)
			{
				TIM1->CCR1 = volume;
				TIM1->CCR2 = volume;
			}
			delay(2);
				
			/* once the button is unpressed, turn off speakers. */
			TIM1->CCR1 = 0;
			TIM1->CCR2 = 0;
			Song[numberOfKeysPressed].stopTime = msTicks_SOUND;
			numberOfKeysPressed++;
		}
	}
}

void playback_function (void)
{
	int keyToPlay = 0;
	/* reset msTicks_SOUND to the first startTime */
	msTicks_SOUND = Song[0].startTime - 50;
	
	LED_On(1);
	LED_On(2);
	
	while(1)
	{
		if (getKey() == 8)
		{
			TIM1->CCR1 = 0;
			TIM1->CCR2 = 0;
			return;
		}

		if (Song[keyToPlay].number == 0)
		{
			keyToPlay = 0;
			msTicks_SOUND = Song[0].startTime - 50;
		}
		else if (msTicks_SOUND == Song[keyToPlay].startTime)
		{
			/* If the starttime matches where msTicks is, turn speakers on with current note */
			TIM1->ARR = period[Song[keyToPlay].number];
			TIM1->CCR1 = volume;
			TIM1->CCR2 = volume;
			
			while (msTicks_SOUND != Song[keyToPlay].stopTime)
			{
				if (getKey() == 8)
				{
					TIM1->CCR1 = 0;
					TIM1->CCR2 = 0;
					return;
				}
			}
				
			/* turn the speakers off, because the stopTime has been reached. */	
			TIM1->CCR1 = 0;
			TIM1->CCR2 = 0;
				
			keyToPlay++;
		}
	}
}
