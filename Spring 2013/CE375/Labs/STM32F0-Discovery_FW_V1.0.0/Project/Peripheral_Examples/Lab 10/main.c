/**
  ******************************************************************************
  * @file    TIM_PWM_Output/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

typedef unsigned int uint32_t;

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/** @addtogroup STM32F0_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup TIM_PWM_Output
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t TimerPeriod = 0;
uint32_t msTicks = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;
/* Private function prototypes -----------------------------------------------*/
void TIM_Config(void);

//added functions
void BTN_Init(void);
void LED_Init (void);
uint32_t BTN_Get(void);
uint32_t getKey(void);
void Inputs_Outputs (void);
void SysTick_Handler(void);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	uint32_t scancode = 1;
	uint32_t sound_tracker = 1;
	
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	LED_Init();
	BTN_Init();
	Inputs_Outputs();
	
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */

  /* TIM Configuration */
  TIM_Config();
  
  /* TIM1 Configuration ---------------------------------------------------
   Generate PWM signals with 4 different duty cycles:
   TIM1 input clock (TIM1CLK) is set to APB2 clock (PCLK2)    
    => TIM1CLK = PCLK2 = SystemCoreClock
   TIM1CLK = SystemCoreClock, Prescaler = 48, TIM1 counter clock = SystemCoreClock
   SystemCoreClock is set to 48 MHz for STM32F0xx devices
   
   The objective is to generate 4 PWM signal at 17.57 KHz:
     - TIM1_Period = (SystemCoreClock / 17570) - 1
   The channel 1 and channel 1N duty cycle is set to 50%
   The channel 2 and channel 2N duty cycle is set to 25%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
   
   Note: 
    SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
    Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
    function to update SystemCoreClock variable value. Otherwise, any configuration
    based on this variable will be incorrect. 
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  TimerPeriod = (SystemCoreClock / 17570 ) - 1;
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 */
  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
  /* Compute CCR2 value to generate a duty cycle at 25%  for channel 2 */
  Channel2Pulse = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 1000);
/* Compute CCR3 value to generate a duty cycle at 25%  for channel 3 */
  Channel3Pulse = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 100);
  /* Compute CCR4 value to generate a duty cycle at 12.5%  for channel 4 */
  Channel4Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod- 1)) / 1000);

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 48;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2, 3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	TIM1->ARR = ((SystemCoreClock / TIM_TimeBaseStructure.TIM_Prescaler) / (50));
  /* Infinite loop */
  while (1)
  {
		//Frequency is 50 * the scancode. 1 being keypadnum 1 and 16 being keypadnum D.
		scancode = getKey();
		if (scancode != 0)
		{
			//TIM1->ARR = (1000000 / (scancode * 50));
			TIM1->ARR = ((SystemCoreClock / TIM_TimeBaseStructure.TIM_Prescaler) / (scancode * 50));
		}
		
		//Keeps track of when the user push button is pressed.
		if (BTN_Get() == (1UL << 0))
		{
			sound_tracker++;
			
			if (sound_tracker == 5)
				sound_tracker = 1;
			
			while (BTN_Get() == (1UL << 0))
			{}
		}
		
		//Controls whether speaker A is on (1), speaker B is on (2), both on (3), both off (4).
		if (sound_tracker == 1)
		{
			TIM1->CCR2 = 0;				//Turn off Speaker 2
			TIM1->CCR1 = 500;			//Turn on Speaker 1
		}
		else if (sound_tracker == 2)
		{
			TIM1->CCR2 = 250;			//Turn on Speaker 2
			TIM1->CCR1 = 0;				//Turn off Speaker 1
		}
		else if (sound_tracker == 3)
		{
			TIM1->CCR2 = 250;			//Turn on Speaker 2
			TIM1->CCR1 = 500;			//Turn on Speaker 1
		}
		else if (sound_tracker == 4)
		{
			TIM1->CCR2 = 0;				//Turn off Speaker 2
			TIM1->CCR1 = 0;				//Turn off Speaker 1
		}
	}
}

/**
  * @brief  Configure the TIM1 Pins.
  * @param  None
  * @retval None
  */
void TIM_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOA Clocks enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* GPIOA Configuration: Channel 1, 2, 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_2);

}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

void SysTick_Handler(void) {
	msTicks++;
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

uint32_t BTN_Get(void) {
 return (GPIOA->IDR & (1UL << 0));
}

/* Returns keypad button, scancode = 4*row + col + 1 */
uint32_t getKey(void)
{
 	int i;
	
	GPIOC->BSRR &= 0xFFFF0000;		//Sets all pins to 0
	GPIOC->BSRR |= (1UL << 16);		//Resets pin 0 to 0
	GPIOC->BSRR |= (1UL << 1);		//Sets pin 1 to 1
	GPIOC->BSRR |= (1UL << 2);		//Sets pin 2 to 1
	GPIOC->BSRR |= (1UL << 3);		//Sets pin 3 to 1
	
	for (i = 4; i < 8; i++)
	{
		if ( !(GPIOC->IDR & (1UL << i)) )
			return (i - 3);
	}
	
	GPIOC->BSRR &= 0xFFFF0000;
	GPIOC->BSRR |= (1UL << 0);		//Sets pin 0 to 1
	GPIOC->BSRR |= (1UL << 17);		//Resets pin 1 to 0
	GPIOC->BSRR |= (1UL << 2);		//Sets pin 2 to 1
	GPIOC->BSRR |= (1UL << 3);		//Sets pin 3 to 1
	
	for (i = 4; i < 8; i++)	
	{
		if ( !(GPIOC->IDR & (1UL << i)) )
			return (i + 1);
	}
	
	GPIOC->BSRR &= 0xFFFF0000;
	GPIOC->BSRR |= (1UL << 0);		//Sets pin 0 to 1
	GPIOC->BSRR |= (1UL << 1);		//Sets pin 1 to 1
	GPIOC->BSRR |= (1UL << 18);		//Resets pin 2 to 0
	GPIOC->BSRR |= (1UL << 3);		//Sets pin 3 to 1
	
	for (i = 4; i < 8; i++)	
	{
		if ( !(GPIOC->IDR & (1UL << i)) )
			return (i + 5);
	}
	
	GPIOC->BSRR &= 0xFFFF0000;
	GPIOC->BSRR |= (1UL << 0);		//Sets pin 0 to 1
	GPIOC->BSRR |= (1UL << 1);		//Sets pin 1 to 1
	GPIOC->BSRR |= (1UL << 2);		//Sets pin 2 to 1
	GPIOC->BSRR |= (1UL << 19);		//Resets pin 3 to 0
	
	for (i = 4; i < 8; i++)		
	{
		if ( !(GPIOC->IDR & (1UL << i)) )
			return (i + 9);
	}
	return 0;		//If no button is pressed, return 0
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
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
