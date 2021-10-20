/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#include "stm32f4xx.h"
#include "Legacy/stm32_hal_legacy.h"
#include <stddef.h>
#include "stm32f4xx_hal.h"
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// -- <3-1> Nucleo_F429 BoardAC LEDAC Æ÷Æ®, CE ¹øE￡¸| A¤AC 
#define GPIONucleo					GPIOB 
#define GPIOExt									GPIOD
#define GPIO_PIN_Led1		GPIO_PIN_0
#define GPIO_PIN_Led2		GPIO_PIN_1
#define GPIO_PIN_Led3		GPIO_PIN_2
#define GPIO_PIN_Led4		GPIO_PIN_3
#define GPIO_PIN_Led5		GPIO_PIN_4
#define GPIO_PIN_Led6		GPIO_PIN_5
#define GPIO_PIN_Led7		GPIO_PIN_6
#define GPIO_PIN_Led8		GPIO_PIN_7
#define GPIO_PIN_LedAll		GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7

// -- <3-2> Nucleo_F429 BoardAC SwitchAC  Æ÷Æ®, CE ¹øE￡¸| A¤AC
#define GPIOSwNucleo							GPIOC
#define GPIOSw1				GPIOG
#define GPIOSw2				GPIOG
#define GPIOSw3				GPIOG
#define GPIOSw4				GPIOG
#define GPIO_PIN_Nucleo_Sw		GPIO_PIN_13
#define GPIO_PIN_Sw1		GPIO_PIN_0
#define GPIO_PIN_Sw2		GPIO_PIN_1
#define GPIO_PIN_Sw3		GPIO_PIN_2
#define GPIO_PIN_Sw4		GPIO_PIN_3


// -- <3-3> Nucleo_F429.c ¿¡¼­ ≫c¿eCI´A CO¼oAC ¼±¾ð
void SystemClock_Config(void);
void LED_Config(void);
void Sw_Config(void);
void SwEXTI_Config(void);
void TIM2_Config(int prescaler_value, int period_value);
void TIM3_Config(int prescaler_value, int period_value);
void TIM_OC_Config(int pulse_value);
void TIM_PWM_Poll_Config(int pwm_value);
void TIM_PWM_IT_Config(int pwm_value);
void UART3_Config(void);
void ADC1_Polling_Config(void);
void ADC1_Interrupt_Config(void);
void DAC_Config(void);
void LED_OnOff(int, int); 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern TIM_HandleTypeDef TimHandle;    
extern TIM_OC_InitTypeDef TIM_OCInit; 
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
GPIO_InitTypeDef		    						GPIO_Init_Struct; 					    // GPIOAC AE±aE­¿e ±¸A¶A¼ º?¼o 
TIM_HandleTypeDef								TimHandle;											// A¸AI¸OAC AE±aE­¿e ±¸A¶A¼ º?¼o
TIM_OC_InitTypeDef								TIM_OCInit;												// A¸AI¸O Channel(OC)AC AE±aE­¿e ±¸A¶A¼ º?¼o
UART_HandleTypeDef						UartHandle;											// UARTAC AE±aE­¿e ±¸A¶A¼ º?¼o 		
ADC_HandleTypeDef							AdcHandler;											// ADCAC AE±aE­¿e ±¸A¶A¼ º?¼o
ADC_ChannelConfTypeDef   	Adc_sConfig; 									// ADC ChannelAC AE±aE­¿e ±¸A¶A¼ º?¼o
DAC_HandleTypeDef							DacHandler;										// DACAC AE±aE­¿e ±¸A¶A¼ º?¼o
DAC_ChannelConfTypeDef			Dac_sConfig;										// DAC ChannelAC AE±aE­¿e ±¸A¶A¼ º?¼o
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

		
		LED_Config();

		// -- <1> TimerAC AE±a¼³A¤¿e CO¼o¸| E￡Aa	
		TIM2_Config(8999,1999);
		
		
    
	LED_OnOff(GPIO_PIN_LedAll, 500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    
#if 0
    //PG13,14 LED를 0.5초 간격으로 점멸
    GPIOG->ODR = GPIOG->ODR | (0x6000);
    HAL_Delay(500-1);
    GPIOG->ODR = GPIOG->ODR & ~(0x6000);
    HAL_Delay(500-1);
  
#endif
  
#if 1
  HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin|LD4_Pin,GPIO_PIN_SET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin|LD4_Pin,GPIO_PIN_RESET);
  HAL_Delay(500);
  
#endif
  
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		// -- <3-1> TIM AIAI·´Æ®°¡ ¹ß≫yCI¸e LED¸| ¸ðμI Toggle ½AA²´U.
		HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll); 
  	HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
	  
}

void LED_Config(void)
{
		// -- Nucleo Board LED GPIO (PB0, PB7)¼³A¤
		// -- <5-1> GPIOBAC A￢·°A≫ enable	
		__HAL_RCC_GPIOB_CLK_ENABLE();

		// -- <5-2> LEDAC μ¿AU A¶°CA≫ ¼³A¤
		GPIO_Init_Struct.Pin = GPIO_PIN_0 | GPIO_PIN_7;		// GPIO¿¡¼­ ≫c¿eCO PIN ¼³A¤
		GPIO_Init_Struct.Mode  = GPIO_MODE_OUTPUT_PP; 		// Output Push-Pull ¸ðμa
		GPIO_Init_Struct.Pull     = GPIO_PULLUP; 						// Pull Up ¸ðμa
		GPIO_Init_Struct.Speed = GPIO_SPEED_FREQ_HIGH; 		// μ¿AU¼Oμμ¸| HIGH·I 	
		
		// -- <5-3> GPIO_Init_Struct¿¡ ¼³A¤μE A¶°CA¸·I AE±aE­CO
		HAL_GPIO_Init(GPIOB, &GPIO_Init_Struct);
		
		// -- E®Aa IO Board LED GPIO (PD0 ~ PD7)¼³A¤
		// -- <5-4> GPIODAC A￢·°A≫ enable	
		__HAL_RCC_GPIOD_CLK_ENABLE();

		// -- <5-5> LED1~8AC μ¿AU A¶°CA≫ ¼³A¤
		GPIO_Init_Struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | 
								 GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;	
																	// GPIO¿¡¼­ ≫c¿eCO PIN ¼³A¤
		GPIO_Init_Struct.Mode  = GPIO_MODE_OUTPUT_PP; 		// Output Push-Pull ¸ðμa
		GPIO_Init_Struct.Pull     = GPIO_PULLUP; 						// Pull Up ¸ðμa
		GPIO_Init_Struct.Speed = GPIO_SPEED_FREQ_HIGH; 		// μ¿AU¼Oμμ¸| HIGH·I 	
		
		// -- <5-6> GPIOLed¸| GPIO_Init_Struct¿¡ ¼³A¤μE A¶°CA¸·I AE±aE­CO
		HAL_GPIO_Init(GPIOD, &GPIO_Init_Struct); 
}


// -------------------------------------------------------------------------------- //
// -- <6> Nucleo_F429 º¸μaAC  SwitchAC GPIO (PG0, PG1, PG2, PG3)AC AE±a¼³A¤A≫ CO 
//				* AI CO¼o´A SW¸| GPIO AO·AA¸·I ¹Þ´A CO¼oAI´U.

void Sw_Config(void)
{
		// -- Nucleo Board Switch (PC13)¼³A¤
		// -- <6-1> GPIOCAC A￢·°A≫ enable		
		__HAL_RCC_GPIOC_CLK_ENABLE();	

		// -- <6-2> SW1AC μ¿AU A¶°CA≫ GPIO AO·AA¸·I ¼³A¤
		GPIO_Init_Struct.Pin 		= GPIO_PIN_13;	// GPIO¿¡¼­ ≫c¿eCO PIN ¼³A¤
		GPIO_Init_Struct.Mode 	= GPIO_MODE_INPUT; 				// Input Floating ¸ðμa
		GPIO_Init_Struct.Pull 		= GPIO_PULLDOWN; 						// Pull Down ¸ðμa
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// μ¿AU¼Oμμ¸| HIGH·I 

		// -- <6-3> GPIOC¸| GPIO_Init_Struct¿¡ ¼³A¤μE A¶°CA¸·I AE±aE­CO	
		HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);    

		// -- E®Aa IO Board Switch (PG0, PG1, PG2, PG3)AC AE±a¼³A¤
		// -- <6-4> GPIOGAC A￢·°A≫ enable		
		__HAL_RCC_GPIOG_CLK_ENABLE();	

		// -- <6-5>  SW1 ~ SW4¿e μ¿AU A¶°CA≫ GPIO AO·AA¸·I ¼³A¤
		GPIO_Init_Struct.Pin 		= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;	// GPIO¿¡¼­ ≫c¿eCO PIN ¼³A¤
		GPIO_Init_Struct.Mode 	= GPIO_MODE_INPUT; 				// Input Floating ¸ðμa
		GPIO_Init_Struct.Pull 		= GPIO_PULLUP; 						// Pull Up ¸ðμa
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// μ¿AU¼Oμμ¸| HIGH·I 

		// -- <6-6> GPIOG¸| GPIO_Init_Struct¿¡ ¼³A¤μE A¶°CA¸·I AE±aE­CO	
		HAL_GPIO_Init(GPIOG, &GPIO_Init_Struct);      		
}

// -------------------------------------------------------------------------------- //
// -- <7> Nucleo_F429 º¸μaAC  SwitchAC GPIO (PG0, PG1, PG2, PG3)AC AE±a¼³A¤A≫ CO 
//				* AI CO¼o´A SW¸| ´ⓒ¸￡¸e EXTI°¡ ¹ß≫yCIμμ·I ¼³A¤CN´U.

void SwEXTI_Config(void)
{
		// -- Nucleo Board Switch (PC13)¼³A¤
		// -- <7-1> GPIOCAC A￢·°A≫ enable		
		__HAL_RCC_GPIOC_CLK_ENABLE();	

		// -- <7-2> SW1AC μ¿AU A¶°CA≫ GPIO AO·AA¸·I ¼³A¤
		GPIO_Init_Struct.Pin 		= GPIO_PIN_13;	// GPIO¿¡¼­ ≫c¿eCO PIN ¼³A¤
		GPIO_Init_Struct.Mode 	= GPIO_MODE_IT_FALLING; 				// Input Floating ¸ðμa
		GPIO_Init_Struct.Pull 		= GPIO_NOPULL; 						// Pull Up / Pull Down ºnE°¼ºE­
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// μ¿AU¼Oμμ¸| HIGH·I 

		// -- <7-3> GPIOC¸| GPIO_Init_Struct¿¡ ¼³A¤μE A¶°CA¸·I AE±aE­CO	
		HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);

		// -- E®Aa IO Board Switch (PG0, PG1, PG2, PG3)AC AE±a¼³A¤
		// -- <7-4> GPIOGAC A￢·°A≫ enable			
		__HAL_RCC_GPIOG_CLK_ENABLE();	

		// -- <7-5>  SW1 ~ SW4¿e μ¿AU A¶°CA≫ GPIO AO·AA¸·I ¼³A¤
		GPIO_Init_Struct.Pin 		= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;	// GPIO¿¡¼­ ≫c¿eCO PIN ¼³A¤
		GPIO_Init_Struct.Mode 	= GPIO_MODE_IT_FALLING;				// Falling edge¿¡¼­ Interrupt ¹ß≫y
		GPIO_Init_Struct.Pull 		= GPIO_NOPULL; 						// Pull Up / Pull Down ºnE°¼ºE­
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// μ¿AU¼Oμμ¸| HIGH·I  	

		// -- <7-6>  Nucleo SW, SW1 ~ SW4¸| GPIO_Init_Struct¿¡ ¼³A¤μE A¶°CA¸·I AE±aE­CO	
		HAL_GPIO_Init(GPIOG, &GPIO_Init_Struct);    

		// -- <7-7> SW1 ~ SW4AC EXTI¿¡ ´eCN AIAI·´Æ®AC ¿i¼±¼øA§¸| ¼³A¤CI°i, AIAI·´Æ®¸| enableCO
		HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);					//  EXTI AC priority¸| ¼³A¤	
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);								//  EXTI AIAI·´Æ®¸| enable
	
	  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);					//  EXTI AC priority¸| ¼³A¤	
		HAL_NVIC_EnableIRQ(EXTI1_IRQn);								//  EXTI AIAI·´Æ®¸| enable
	
	  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);					//  EXTI AC priority¸| ¼³A¤	
		HAL_NVIC_EnableIRQ(EXTI2_IRQn);								//  EXTI AIAI·´Æ®¸| enable
		
		HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);					//  EXTI AC priority¸| ¼³A¤	
		HAL_NVIC_EnableIRQ(EXTI3_IRQn);								//  EXTI AIAI·´Æ®¸| enable
		
		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);					//  EXTI AC priority¸| ¼³A¤	
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);								//  EXTI AIAI·´Æ®¸| enable
}

// -------------------------------------------------------------------------------- //
// -- <8> TimerAC AE±a¼³A¤A≫ A§CN CO¼o
//			  * TIM2¸| Up couting ¸ðμa·I μ¿AU½AAN 1AE¿¡ 1¹ø¾¿ ¹ß≫yCIμμ·I AOÆA¼o¸| 1 Hz·I ¼³A¤CN´U.

void TIM2_Config(int prescaler_value, int period_value)
{

		// -- <8-1> TIM2AC clockA≫ enable
		__HAL_RCC_TIM2_CLK_ENABLE();
		
		// -- <8-2> TIMAC μ¿AU A¶°C ¼³A¤ (AIAI·´Æ®°¡ 1AE¿¡ 1¹ø¾¿ ¹ß≫yCIμμ·I AOÆA¼o¸| 1 Hz·I ¼³A¤)
		TimHandle.Instance = TIM2;											// TIM2 ≫c¿e
		TimHandle.Init.CounterMode = TIM_COUNTERMODE_DOWN;	//	Up Counter ¸ðμa ¼³A¤
		TimHandle.Init.Prescaler = prescaler_value;								// Prescaler =8999·I ¼³A¤
		TimHandle.Init.Period = period_value;						// ¾÷μ￥AIÆ® AIº￥Æ® ¹ß≫y½A Auto-Reload ·¹Ao½ºAI = 9999·I ¼³A¤
		TimHandle.Init.ClockDivision = 0;								// Clock Division ¼³A¤
		//TimHandle.Init.RepetitionCounter = 0;	// Repetition Counter °ªA≫  ¼³A¤ (TIM1¸¸ CØ´c)

		// -- <8-3> TIM2¸| TimHandle¿¡ ¼³A¤μE °ªA¸·I AE±aE­CI°i TIM¸| μ¿AUCO
		HAL_TIM_Base_Init(&TimHandle);	
		HAL_TIM_Base_Start_IT(&TimHandle);	
		
		// -- <8-4> A¸AI¸O AIAI·´Æ® ¿i¼±¼øA§ ¼³A¤ ¹× ENABLE
		HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);		// º°μμ·I ¼³A¤CIAo ¾EA¸¸e μðÆuÆ®·I ¼³A¤μE
		HAL_NVIC_EnableIRQ(TIM2_IRQn);	
}

// -------------------------------------------------------------------------------- //
// -- <9> TimerAC AE±a¼³A¤A≫ A§CN CO¼o
//			  * TIM3¸| Down couting ¸ðμa·I μ¿AU½AAN 1AE¿¡ 1¹ø¾¿ ¹ß≫yCIμμ·I AOÆA¼o¸| 1 Hz·I ¼³A¤CN´U.

void TIM3_Config(int prescaler_value, int period_value)
{

		// -- <9-1> TIM2AC clockA≫ enable
		__HAL_RCC_TIM3_CLK_ENABLE();
		
		// -- <9-2> TIMAC μ¿AU A¶°C ¼³A¤ (AIAI·´Æ®°¡ 1AE¿¡ 1¹ø¾¿ ¹ß≫yCIμμ·I AOÆA¼o¸| 1 Hz·I ¼³A¤)
		TimHandle.Instance = TIM3;								// TIM3 ≫c¿e
		TimHandle.Init.CounterMode = TIM_COUNTERMODE_DOWN;	//	Down Counter ¸ðμa ¼³A¤
		TimHandle.Init.Prescaler = prescaler_value;					// Prescaler =6399·I ¼³A¤
		TimHandle.Init.Period = period_value;							// ¾÷μ￥AIÆ® AIº￥Æ® ¹ß≫y½A Auto-Reload ·¹Ao½ºAI = 9999·I ¼³A¤
		TimHandle.Init.ClockDivision = 0;					// Clock Division ¼³A¤
		//TimHandle.Init.RepetitionCounter = 0;		// Repetition Counter °ªA≫  ¼³A¤ (TIM1¸¸ CØ´c)

		// -- <9-3> TIM3¸| TimHandle¿¡ ¼³A¤μE °ªA¸·I AE±aE­CI°i TIM¸| μ¿AU
		HAL_TIM_Base_Init(&TimHandle);	
		HAL_TIM_Base_Start_IT(&TimHandle);	
		
		// -- <9-4> A¸AI¸O AIAI·´Æ® ¿i¼±¼øA§ ¼³A¤ ¹× ENABLE
		HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);		// º°μμ·I ¼³A¤CIAo ¾EA¸¸e μðÆuÆ®·I ¼³A¤μE
		HAL_NVIC_EnableIRQ(TIM3_IRQn);		
}

// -------------------------------------------------------------------------------- //
// -- <10> TimerAC Output Compare μ¿AU AE±a¼³A¤A≫ A§CN CO¼o

void TIM_OC_Config(int pulse_value)
{

		// -- <10-1> TIMAC OC μ¿AUA¶°C ¼³A¤
		TIM_OCInit.OCMode = TIM_OCMODE_TIMING;					// Output Compare μ¿AU¸ðμa ¼³A¤
		TIM_OCInit.Pulse = pulse_value;											// Capture/Compare Register(CCR)AC ¼³A¤°ª
		TIM_OCInit.OCPolarity = TIM_OCPOLARITY_HIGH;			// OC Aa·AA≫ High·I ¼³A¤
		TIM_OCInit.OCFastMode = TIM_OCFAST_DISABLE; 		// TIM Output Compare Fast¸| Disable

		// -- <10-2> TIM OC¸| TimHandle¿¡ ¼³A¤μE °ªA¸·I AE±aE­CO  	
		HAL_TIM_OC_Init(&TimHandle);
		// -- <10-3> TIM OCAC ChannelA≫ TIM_OCInit¿¡ ¼³A¤μE °ªA¸·I AE±aE­CO 
		HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
		HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		// -- <10-4> TIM OC¸| μ¿AUCO
		HAL_TIM_OC_Start_IT(&TimHandle,TIM_CHANNEL_1);
		HAL_TIM_OC_Start_IT(&TimHandle,TIM_CHANNEL_2);
}

// -------------------------------------------------------------------------------- //
// -- <11> TimerAC PWM μ¿AU AE±a¼³A¤A≫ A§CN CO¼o

void TIM_PWM_IT_Config(int pwm_value)
{

		// -- <11-1> TIMAC OC μ¿AUA¶°C¼³A¤
		TIM_OCInit.OCMode = TIM_OCMODE_PWM1;					
		TIM_OCInit.Pulse = pwm_value;											
		TIM_OCInit.OCPolarity = TIM_OCPOLARITY_HIGH;						

		// -- <11-2> TIM PWM¸| TimHandle¿¡ ¼³A¤μE °ªA¸·I AE±aE­ CO 	
		HAL_TIM_PWM_Init(&TimHandle);

		// -- <11-3> TIM PWMAC ChannelA≫ TIM_OCInit¿¡ ¼³A¤μE °ªA¸·I AE±aE­ CO
 		HAL_TIM_PWM_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);

		// -- <11-4> TIM PWM¸| μ¿AUCO
		HAL_TIM_PWM_Start_IT(&TimHandle,TIM_CHANNEL_1);
}

// -------------------------------------------------------------------------------- //
// -- <12> TimerAC PWM μ¿AU AE±a¼³A¤A≫ A§CN CO¼o

void TIM_PWM_Poll_Config(int pwm_value)
{

		// -- <12-1> TIMAC OC μ¿AUA¶°C¼³A¤
		TIM_OCInit.OCMode = TIM_OCMODE_PWM1;					
		TIM_OCInit.Pulse = pwm_value;											
		TIM_OCInit.OCPolarity = TIM_OCPOLARITY_HIGH;						

		// -- <12-2> TIM PWM¸| TimHandle¿¡ ¼³A¤μE °ªA¸·I AE±aE­ CO 	
		HAL_TIM_PWM_Init(&TimHandle);

		// -- <12-3> TIM PWMAC ChannelA≫ TIM_OCInit¿¡ ¼³A¤μE °ªA¸·I AE±aE­ CO
 		HAL_TIM_PWM_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);

		// -- <12-4> TIM PWM¸| μ¿AUCO
		HAL_TIM_PWM_Start(&TimHandle,TIM_CHANNEL_1);
}

// -------------------------------------------------------------------------------- //
// -- <13> UARTAC AE±a¼³A¤A≫ A§CN CO¼o 
void UART3_Config(void)
{
	// -- <13-1> UARTAC A￢·°A≫ E°¼ºE­ 
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_USART3_CLK_ENABLE();

	// -- <13-2> GPIO DÆ÷Æ® 8¹ø CEA≫ UART Tx·I ¼³A¤
	GPIO_Init_Struct.Pin	= GPIO_PIN_8;
	GPIO_Init_Struct.Mode	= GPIO_MODE_AF_PP;
	GPIO_Init_Struct.Pull	= GPIO_PULLUP;
	GPIO_Init_Struct.Speed	= GPIO_SPEED_FREQ_HIGH;
	GPIO_Init_Struct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_Init_Struct);

	// -- <13-3> GPIO DÆ÷Æ® 3¹ø CEA≫ UART Rx·I ¼³A¤
	GPIO_Init_Struct.Pin	= GPIO_PIN_9;
	GPIO_Init_Struct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_Init_Struct);	

	// -- <13-4> UARTAC μ¿AU A¶°C ¼³A¤ 
	UartHandle.Instance	= USART3;  
	UartHandle.Init.BaudRate	= 9600;
	UartHandle.Init.WordLength	= UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits	= UART_STOPBITS_1;
	UartHandle.Init.Parity	= UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl	= UART_HWCONTROL_NONE;
	UartHandle.Init.Mode	= UART_MODE_TX_RX;
	
	// -- <13-5> UART ±¸¼ºA¤º¸¸| UartHandle¿¡ ¼³A¤μE °ªA¸·I AE±aE­ CO 
	HAL_UART_Init(&UartHandle);
	
	// -- <13-6> UART AIAI·´Æ® ¿i¼±¼øA§ ¼³A¤ ¹× E°¼ºE­
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);	
	HAL_NVIC_EnableIRQ(USART3_IRQn); 
}

// -------------------------------------------------------------------------------- //
// -- <14> ADCAC Polling¿e AE±a¼³A¤A≫ A§CN CO¼o 
void ADC1_Polling_Config(void)
{	  
    // -- <14-1> ADCAC clockA≫ E°¼ºE­ 
    __HAL_RCC_GPIOC_CLK_ENABLE();	
    __HAL_RCC_ADC1_CLK_ENABLE();
	
    GPIO_Init_Struct.Mode  = GPIO_MODE_ANALOG;
    GPIO_Init_Struct.Pin 	= GPIO_PIN_0;
		GPIO_Init_Struct.Pull = GPIO_NOPULL;	
    HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);	

    // -- <14-2> ADCAC μ¿AU A¶°C ¼³A¤
		AdcHandler.Instance = ADC1;
		AdcHandler.Init.ScanConvMode = DISABLE;
		AdcHandler.Init.ContinuousConvMode = ENABLE;
		AdcHandler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		AdcHandler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		AdcHandler.Init.NbrOfConversion = 1;
	
    // -- <14-3> ADC¸| AdcHandler¿¡ ¼³A¤μE °ªA¸·I AE±aE­ CO 	
    HAL_ADC_Init(&AdcHandler);

    // -- <14-4> ADC Channelμ¿AUA¶°C ¼³A¤	
    Adc_sConfig.Channel	= ADC_CHANNEL_10;
    Adc_sConfig.Rank         	= 1;
    Adc_sConfig.SamplingTime 	= ADC_SAMPLETIME_3CYCLES;

		// -- <14-5> ¼³A¤μE sConfig¿I AdcHandler¸| ¿￢°uAo¾i AE±aE­ CO
		HAL_ADC_ConfigChannel(&AdcHandler, &Adc_sConfig);

		// -- <14-6> ADC¸| μ¿AU½AA´
		HAL_ADC_Start(&AdcHandler);
						
		// -- <14-7> º?E?AI ¿I·aμE ¶§±iAo ´e±a
		HAL_ADC_PollForConversion(&AdcHandler, 10);	

}

// -------------------------------------------------------------------------------- //
// -- <15> ADCAC Interrupt¿e AE±a¼³A¤A≫ A§CN CO¼o 
void ADC1_Interrupt_Config(void)
{	  
    // -- <15-1> ADCAC clockA≫ E°¼ºE­ 
    __HAL_RCC_GPIOC_CLK_ENABLE();	
    __HAL_RCC_ADC1_CLK_ENABLE();
	
    GPIO_Init_Struct.Mode  = GPIO_MODE_ANALOG;
    GPIO_Init_Struct.Pin 	= GPIO_PIN_0;
		GPIO_Init_Struct.Pull = GPIO_NOPULL;	
    HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);	

    // -- <15-2> ADCAC μ¿AU A¶°C ¼³A¤
		AdcHandler.Instance = ADC1;
		AdcHandler.Init.ScanConvMode = DISABLE;
		AdcHandler.Init.ContinuousConvMode = ENABLE;
		AdcHandler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		AdcHandler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		AdcHandler.Init.NbrOfConversion = 1;
	
    // -- <15-3> ADC¸| AdcHandler¿¡ ¼³A¤μE °ªA¸·I AE±aE­ CO 	
    HAL_ADC_Init(&AdcHandler);

    // -- <15-4> ADC Channelμ¿AUA¶°C ¼³A¤	
    Adc_sConfig.Channel	= ADC_CHANNEL_10;
    Adc_sConfig.Rank         	= 1;
    Adc_sConfig.SamplingTime 	= ADC_SAMPLETIME_3CYCLES;

		// -- <15-5> ¼³A¤μE sConfig¿I AdcHandler¸| ¿￢°uAo¾i AE±aE­ CO
		HAL_ADC_ConfigChannel(&AdcHandler, &Adc_sConfig);

		// -- <15-6> ADC¸| μ¿AU½AA´
		HAL_ADC_Start_IT(&AdcHandler);
	
    // -- <15-7> ADC AIAI·´Æ® ¿i¼±¼øA§ ¼³A¤ ¹× E°¼ºE­ 
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0); 
    HAL_NVIC_EnableIRQ(ADC_IRQn);

}

// -------------------------------------------------------------------------------- //
// -- <16> DACAC AE±a¼³A¤A≫ A§CN CO¼o 
void DAC_Config(void)
{
    // -- <16-1> DACAC clock ¹× LED CE clockA≫ E°¼ºE­ 
    __HAL_RCC_DAC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
	
    // -- <16-2> Aß°¡ LED μ¿AU A¶°CA≫ ¼³A¤
    GPIO_Init_Struct.Pin 	= GPIO_PIN_4;
    GPIO_Init_Struct.Mode 	= GPIO_MODE_ANALOG;
    GPIO_Init_Struct.Pull 	= GPIO_NOPULL;

    // -- <16-3> GPIOA¸| GPIO_Init_Struct¿¡ ¼³A¤μE A¶°CA¸·I AE±aE­CO
    HAL_GPIO_Init(GPIOA, &GPIO_Init_Struct);
	
    // -- <16-4> DACAC μ¿AU A¶°C ¼³A¤ 
    DacHandler.Instance 		= DAC;
    Dac_sConfig.DAC_Trigger 		= DAC_TRIGGER_NONE;
    Dac_sConfig.DAC_OutputBuffer 	= DAC_OUTPUTBUFFER_DISABLE;

    // -- <16-5> DacHandler¿¡ ¼³A¤μE °ªA¸·I AE±aE­ CO 	
    HAL_DAC_Init(&DacHandler);

    // -- <16-6> DACAC Channel 1A≫ sConfig¿¡ ¼³A¤μE °ªA¸·I AE±aE­ CO
    HAL_DAC_ConfigChannel(&DacHandler, &Dac_sConfig, DAC_CHANNEL_1);

    // -- <16-7> DAC Channel 1¹ø¿¡ ±¸A¼AuAI μ￥AIAI ·¹Ao½ºAI °ªA≫ ¼³A¤
    HAL_DAC_SetValue(&DacHandler, DAC_CHANNEL_1, DAC_ALIGN_8B_R, 0xff);

    // -- <16-8> DAC¸| E°¼ºE­CI°i º?E?A≫ ½AAU
    HAL_DAC_Start(&DacHandler, DAC_CHANNEL_1);

}

// -------------------------------------------------------------------------------- //
// -- <17> ½C½Aº¸μaAC  LED¸| ON½AA°°i AIA¤ ½A°￡EA¿¡ ´U½A OFF ½AA°´A CO¼o

void LED_OnOff(int led, int interval) 
{
		// -- <17-1> GPIOLed Æ÷Æ®¿¡ AO´A led¸| ON CO
		HAL_GPIO_WritePin(GPIONucleo, led, GPIO_PIN_SET );
		HAL_GPIO_WritePin(GPIOExt, led, GPIO_PIN_SET );		
		// -- <17-2> interval (msec) ½A°￡¸¸A­ ½A°￡ Ao¿￢A≫ CO
		HAL_Delay(interval);
		// -- <17-3> GPIOLed Æ÷Æ®¿¡ AO´A led¸| OFF CO
		HAL_GPIO_WritePin(GPIONucleo, led, GPIO_PIN_RESET );	
		HAL_GPIO_WritePin(GPIOExt, led, GPIO_PIN_RESET );	
}


// -------------------------------------------------------------------------------- //
//   --  <18>  System Clock A≫ ¼³A¤CØAO´A CO¼o
/*				- A￢·°Aº ´UA½°u °°AI ¼³A¤μE´U.

  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  */
// -------------------------------------------------------------------------------- //

void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
  }
	
}

// -------------------------------------------------------------------------------- //
//   --  <19>  Clock ¼³A¤½A ¿¡·?°¡ ¹ß≫yCI¸e A³¸®CØAO´A CO¼o

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
	while (1)   {
	}	
}
#endif
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
