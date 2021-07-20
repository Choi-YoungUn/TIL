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

////////////////////////////
// 
//   DC Motor PID Position Control
// 
////////////////////////////
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mathext.h"
#include "DcMotor.h"   
#include "DcMotorExtern.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define PID_SUM_TYPE     1
#define PWM_MAX_STEP  10
#define PWM_MIN_POSITIVE 22
#define PWM_MIN_NEGATIVE 22

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim9;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

//형 선언
typedef enum _bool{
  FALSE=0, 
  TRUE=1
} bool;
bool a =TRUE;

struct  {
  float Kp;
  float Ki;
  float Kd;
} PidParam={3,  0.001, 0.005};

enum {
  STATE_IDLE = 0,
  STATE_RUN_SAVE, // 동작 및 저장
  STATE_NORUN_PRINT, // 결과출력
  STATE_RUN_ONLY,  //제어만
} RunState={STATE_RUN_SAVE};

bool flagTim3=FALSE;
int16_t flagUser=0; //user button press 

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM9_Init(void);
static void MX_TIM6_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*
#ifdef __GNUC__
   #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
   #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
   HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1);
   return ch;
}
*/

void  ReadEncoder()
{
      //엔코더 위치 및 샘플링당 엔코더차이(속도) 16bit 계산
      DcMotor1.Encoder16 = DcMotor1ReadEncoder();//TIM4 16비트
      //인터럽트간 엔코더값 차이 계산 => 실제의미는 속도
      DcMotor1.Encoder16Diff= DcMotor1.Encoder16- DcMotor1.Encoder16Old;
      DcMotor1.Encoder16Old = DcMotor1.Encoder16;
            
       //엔코더 위치 및 샘플링당 엔코더차이(속도) 32bit 로 확장
      // TIM4는 16CNT , 모터 8회전하면 오버플로우문제가 발생
      // 현재위치 = 누적합 of 인터럽트간 엔코더값의 변화 
      //x DcMotor1.Encoder32 = DcMotor1.Encoder16;
      DcMotor1.Encoder32 += DcMotor1.Encoder16Diff;
      DcMotor1.Encoder32Diff = DcMotor1.Encoder32- DcMotor1.Encoder32Old;//=DcMotor1.Encoder16Diff
      DcMotor1.Encoder32Old = DcMotor1.Encoder32;    
      
      Controller1.Output32 = DcMotor1.Encoder32;
}

void PidControlInit()
{
  // DC Motor 관련변수 초기화
    DcMotor1.Encoder16Old = 0;
    DcMotor1.Encoder32 = 0 ;
    DcMotor1.Encoder32Old = 0 ;
    DcMotor1.Encoder32Diff = 0;

   // 제어기 관련변수 초기화
	Controller1.Output32 = DcMotor1.Encoder32;
    Controller1.Target32 = 4096;
    Controller1.ErrorOld32 = 0;
    Controller1.ErrorSum32 =0;
    Controller1.loop =0;

    //PWM duty =0
    DcMotor1SetDutyPulse(&htim9, 0);
    
    //htim4->CNT <= 0x0000 (16bit 카운터 clear)
    __HAL_TIM_SET_COUNTER(&htim3,   0x0000); 
}

  float TermKp,TermKi,TermKd; 

void PidControl()
{
   // 목표값과 현재 플랜트 출력의 오차
	Controller1.Error32 = Controller1.Target32- Controller1.Output32; 

#ifdef PID_SUM_TYPE 
   //Euler 적분
	Controller1.ErrorSum32 += Controller1.Error32; //오차의 합(적분값)
#else 
   //사다리꼴 적분 : Tustin's method
	Controller1.ErrorSum32 += (Controller1.Error32+Controller1.ErrorOld32)/2; //오차의 합(적분값)
#endif    

   Controller1.ErrorDiff32 = Controller1.Error32- Controller1.ErrorOld32; // 샘플간 오차의 차이(미분값)
   Controller1.ErrorOld32 = Controller1.Error32;
   
   //ErrorSum 최대값 제한
   #define ERRROR_SUM_MAX  (WHEEL_RESOLUTION*0.5)  
	//	Controller1.ErrorSum32 = LimitFloat(Controller1.ErrorSum32 , ERRROR_SUM_MAX);
   #undef ERRROR_SUM_MAX
    
    TermKp =  PidParam.Kp * Controller1.Error32 ; //비례제어값
    TermKi = PidParam.Ki * Controller1.ErrorSum32 * Tsample; //적분제어값
    TermKd =  PidParam.Kd * Controller1.ErrorDiff32 / Tsample ;//미분제어값
    Controller1.f = TermKp + TermKi + TermKd; 

    //PWM pulse 실수=>+-100이내의 정수값 변환
    Controller1.U = FloatToInt16Limit( Controller1.f ,  U_MAX);
    //PWM dead zone 피하기
    Controller1.U  = AvoidDeadzone(Controller1.U, PWM_MIN_POSITIVE,  PWM_MIN_NEGATIVE);
    //PWM pulse 폭 설정
    DcMotor1SetDutyPulse(&htim9, Controller1.U);    
}  

void PidControlRecord()
{
	Backup1.RecordOutput[Controller1.loop]= Controller1.Output32;//엔코더 값
	Backup1.RecordU[Controller1.loop] = Controller1.U; //PWM 펄스폭
	Backup1.RecordError[Controller1.loop] = Controller1.Error32;  //제어기 오차
	Backup1.RecordErrorSum[Controller1.loop] = Controller1.ErrorSum32; 
	Backup1.RecordErrorDiff[Controller1.loop] = Controller1.ErrorDiff32; 
}

void PidControlResultTransmit()
{
  char string[200];
  HAL_UART_Transmit(&huart1, (uint8_t *)"Record Print\r\n", strlen("Record Print\r\n"), 1000);
  for(int i=0 ; i<RECORD_MAX ; i++ ){
//	printf("%7d, %5d, %6d \r\n", i, Backup1.RecordOutput[i], Backup1.RecordU[i]);
     sprintf(string, "%7d, %5d, %6d \r\n", i, Backup1.RecordOutput[i], Backup1.RecordU[i]);
     HAL_UART_Transmit( &huart1, (uint8_t *)string, strlen(string), 1000);
  }
}

//LCD에 엔코더, U값 출력
void Plot()
{
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  char string[100];
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
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_TIM9_Init();
  MX_TIM6_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  
   PidControlInit();
   HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1 | TIM_CHANNEL_2 );   
   HAL_TIM_Base_Start_IT(&htim6);
   HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        if( flagTim3==TRUE){
			HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin,GPIO_PIN_SET);    
			ReadEncoder();
            switch(RunState){
               case STATE_RUN_SAVE://동작저장 모드
                  if(Controller1.loop< RECORD_MAX){
						PidControl();
						PidControlRecord();
						Plot();
						Controller1.loop++;
                  }else {
                     Controller1.loop = 0;
                   RunState = STATE_NORUN_PRINT;
                    //RunState = STATE_RUN_ONLY;
                  }                  
                  break;
                  
               case STATE_NORUN_PRINT:// 저장된 내용 시리얼 출력
                  //TIM6 interrupt disable
                  HAL_NVIC_DisableIRQ( TIM6_DAC_IRQn);
				  DcMotor1SetDutyPulse(&htim9, 0);
                  PidControlResultTransmit();
                  Controller1.loop = 0;
                 RunState = STATE_RUN_ONLY;
                  //TIM6 interrupt enable
                  HAL_NVIC_EnableIRQ( TIM6_DAC_IRQn);
                  break;
                  
               case STATE_RUN_ONLY:
                 PidControl();
                  break;

            case STATE_IDLE:
                  break;
            }
                    
            flagTim3=FALSE;
            HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin,GPIO_PIN_RESET);
        }
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* EXTI0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
  /* TIM6_DAC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0xFFFF;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 5;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 5;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 84-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000-1;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 84-1;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 100-1;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 10;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */
  HAL_TIM_MspPostInit(&htim9);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, DCMOT1_EN_Pin|DCMOT1_DIR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LD3_Pin|LD4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DCMOT1_EN_Pin DCMOT1_DIR_Pin */
  GPIO_InitStruct.Pin = DCMOT1_EN_Pin|DCMOT1_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : LD3_Pin LD4_Pin */
  GPIO_InitStruct.Pin = LD3_Pin|LD4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin== GPIO_PIN_0){

    flagUser =1;
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if( htim->Instance == TIM6) 
      HAL_GPIO_TogglePin(LD3_GPIO_Port,  LD3_Pin);  
      flagTim3 = TRUE;
	  ReadEncoder();
}
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
