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
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)		/* for printf */
#define RxBufferSize  0xFF
uint8_t RxBuffer[RxBufferSize]; 
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int pulse = 1825;
int start_sen = 0;
int canger =1;
int p0 = 0;
int p1 =0;
int p2 =0;
int psum = 0;
int num = 0;
int nums = 0;
int count = 0;
char full_ch[50];
char full_ch1[50];
int point = 0;
TIM_OC_InitTypeDef sConfigOC = {0};
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_TIM4_Init(void);
static void MX_UART4_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


PUTCHAR_PROTOTYPE			// For printf Function
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart4, (uint8_t *)&ch, 1, 0xFFFF);   // USB
	return ch;
}
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
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM4_Init();
  MX_UART4_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
   HAL_TIM_Base_Start_IT(&htim3);
   HAL_TIM_Base_Start_IT(&htim4);
   HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1); 
   HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
   HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
   
   p0 = pulse;
   p1 = pulse;
   p2 = pulse;
   psum = (p0+ p1) /2;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    
     HAL_UART_Receive_IT(&huart4, (uint8_t*)RxBuffer,1);
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
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

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
  /* TIM3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
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

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 840-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 2000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1825-1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 8400-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED_0_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin 
                          |LED_4_Pin|LED_5_Pin|LED_6_Pin|LED_7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
  GPIO_InitStruct.Pin = RMII_MDC_Pin|RMII_RXD0_Pin|RMII_RXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_REF_CLK_Pin RMII_MDIO_Pin */
  GPIO_InitStruct.Pin = RMII_REF_CLK_Pin|RMII_MDIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SW_0_Pin SW_1_Pin SW_2_Pin SW_3_Pin */
  GPIO_InitStruct.Pin = SW_0_Pin|SW_1_Pin|SW_2_Pin|SW_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : RMII_TXD1_Pin */
  GPIO_InitStruct.Pin = RMII_TXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(RMII_TXD1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_0_Pin LED_1_Pin LED_2_Pin LED_3_Pin 
                           LED_4_Pin LED_5_Pin LED_6_Pin LED_7_Pin */
  GPIO_InitStruct.Pin = LED_0_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin 
                          |LED_4_Pin|LED_5_Pin|LED_6_Pin|LED_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_TX_EN_Pin RMII_TXD0_Pin */
  GPIO_InitStruct.Pin = RMII_TX_EN_Pin|RMII_TXD0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}

/* USER CODE BEGIN 4 */
  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
  {
    if( htim->Instance == TIM3 )
    {
    HAL_GPIO_WritePin(GPIOD, LED_0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, LED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, LED_2_Pin, GPIO_PIN_RESET);
    nums++;
    if(nums >= 3) //0.1초
    {
                    if( start_sen == 1)
                      {
                        if((full_ch[6]& 0x2D) == 0x2D) //-    x축 왼쪽이 아래로
                        {
                          if( (p1 >= 1850) && (p0 <= 1800))
                          {
                            
                          }
                          else if( p1 >= 1850)
                          {
                            
                            p0 = p0 - canger;
                            sConfigOC.Pulse = p0;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);                        
                          }
                          else if(p0 <= 1800)
                          {
                            
                            p1 = p1 + canger;
                            sConfigOC.Pulse = p1;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
                          }
                          else if((1850 - p1) >= (p0 - 1800))
                          {
                            
                            p1 = p1 + canger;
                            sConfigOC.Pulse = p1;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
                          }
                          else if((1850 - p1) < (p0 - 1800))
                          {
                            
                            p0 = p0 - canger;
                            sConfigOC.Pulse = p0;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
                          }
                          
                          
                        }if((full_ch[6]& 0x30) == 0x30) // 0
                        {
                        
                        }
                        
                        if(((full_ch[6]& 0x31) == 0x31)||((full_ch[6]& 0x32) == 0x32)||((full_ch[6]& 0x33) == 0x33)
                           ||((full_ch[6]& 0x34) == 0x34) ||((full_ch[6]& 0x35) == 0x35)||((full_ch[6]& 0x36) == 0x36)
                             ||((full_ch[6]& 0x37) == 0x37)||((full_ch[6]& 0x38) == 0x38)||((full_ch[6]& 0x39) == 0x39))
                        { //x축 오른쪽이 아래로
                       
                          if( (p0 >= 1850) && (p1 <= 1800))
                          {
                            HAL_GPIO_WritePin(GPIOD, LED_5_Pin, GPIO_PIN_SET);
                          }
                          else if( p0 >= 1850)
                          {
                           
                            p1 = p1 - canger;
                            sConfigOC.Pulse = p1;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);                        
                          }
                          else if(p1 <= 1800)
                          {
                            
                            p0 = p0 +canger;
                            sConfigOC.Pulse = p0;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
                          }
                          else if((1850 - p0) >= (p1 - 1800))
                          {
                            
                            p0 = p0 +canger;
                            sConfigOC.Pulse = p0;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
                          }
                          else if((1850 - p0) < (p1 - 1800))
                          {
                            
                            p1 = p1 - canger;
                            sConfigOC.Pulse = p1;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
                          }
                        }
                       
                        if((full_ch1[4]& 0x2D) == 0x2D) // y축 위가 아래로
                        {
                            HAL_GPIO_WritePin(GPIOD, LED_5_Pin, GPIO_PIN_SET);
                            HAL_GPIO_WritePin(GPIOD, LED_6_Pin, GPIO_PIN_RESET);
                            HAL_GPIO_WritePin(GPIOD, LED_7_Pin, GPIO_PIN_RESET);
                          if(1800 >= p2)
                          {
                            p2 = 1800;
                          }
                          else
                          {
                            p2 = p2 - canger;
                          }
                          if((1850 <= p0) ||(1850 <= p1))
                          {
                            
                          }
                          else
                          {
                            p0 = p0+canger;
                            p1 = p1+canger;
                          }
                          sConfigOC.Pulse = p0;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
                            
                            sConfigOC.Pulse = p1;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
                          
                          sConfigOC.Pulse = p2;
                             
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
                        }
                        
                        if((full_ch1[4]& 0x30) == 0x30)
                        {
                          HAL_GPIO_WritePin(GPIOD, LED_5_Pin, GPIO_PIN_RESET);
                            HAL_GPIO_WritePin(GPIOD, LED_6_Pin, GPIO_PIN_SET);
                            HAL_GPIO_WritePin(GPIOD, LED_7_Pin, GPIO_PIN_RESET);
                        }
                        
                        if(((full_ch1[4]& 0x31) == 0x31)||((full_ch1[4]& 0x32) == 0x32)||((full_ch1[4]& 0x33) == 0x33)
                           ||((full_ch1[4]& 0x34) == 0x34)||((full_ch1[4]& 0x35) == 0x35)||((full_ch1[4]& 0x36) == 0x36)
                             ||((full_ch1[4]& 0x37) == 0x37)||((full_ch1[4]& 0x38) == 0x38)||((full_ch1[4]& 0x39) == 0x39))
                        {
                          HAL_GPIO_WritePin(GPIOD, LED_5_Pin, GPIO_PIN_RESET);
                            HAL_GPIO_WritePin(GPIOD, LED_6_Pin, GPIO_PIN_RESET);
                            HAL_GPIO_WritePin(GPIOD, LED_7_Pin, GPIO_PIN_SET);
                          
                          if(1850 <= p2)
                          {
                            p2 = 1850;
                          }
                          else
                          {
                            p2 = p2 + canger;
                          }
                          if ((p0 <= 1800) || (p1 <= 1800))
                          {
                            
                          }
                          else
                          {
                            p0 = p0 -canger;
                            p1 = p1 -canger;
                          }
                          sConfigOC.Pulse = p0;
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
                            
                            sConfigOC.Pulse = p1;
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
                            
                          sConfigOC.Pulse = p2;
                             if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
                            {
                              Error_Handler();
                            }
                            HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
                        }
                  }
   nums = 0;
    }
    }
    
    
     
/*// printf("@mode,BC*6E\r\n);   @mode,BC*6E\r\n
@bin_out,QUATERNION,IMU*45\r\n
@asc_out,RPY*77\r\n
@mode,A*2E\r\n
@divider,50*0D\r\n
@mode*43\r\n
@bin_out*14\r\n
@set_offset*70\r\n
@version*3A\r\n
@id*4D\r\n
@sn*5D\r\n
@sensitivity*2D\r\n
@baudrate*50\r\n
@calib,A*48\r\n
@calib,G*4E\r\n
@calib,M*44\r\n
@mode,C*2C\r\n*/
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  
    char ch;  
    ch = (uint16_t)(UART4->DR & (uint16_t)0x01FF);	// 수신된 문자 저장
    full_ch[count] = ch;
    
    count ++;               
                if(point == 0)
                {
                 if((ch & 0x2E) == 0x2E)
                 {
                   point = 1;
                 }
                }
                
                if(point == 1)
                {
                  full_ch1[num] = ch;
                     num++;
                }
                
                if((ch & 0x52) == 0x52)
                {
                  
                  count = 0;
                  num = 0;
                  point = 0;
                  
                }
}

  void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
  {
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
       HAL_GPIO_WritePin(GPIOD, LED_0_Pin, GPIO_PIN_SET);
    }
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
    {
    HAL_GPIO_WritePin(GPIOD, LED_1_Pin, GPIO_PIN_SET);
    }
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
    {
    HAL_GPIO_WritePin(GPIOD, LED_2_Pin, GPIO_PIN_SET);
    }
  }

  void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)   //switch
  {
    //최소 1775
    //최대 1950
    
    switch(GPIO_Pin)
    {
     case SW_0_Pin:
    {
      //pulse = pulse + 5;
      
      start_sen = 1;
      break;
    }
    case SW_1_Pin:
    {
      // pulse = pulse - 5;
      start_sen = 0;
      break;
    }
    case SW_2_Pin:
    {
    //  pulse = 1850-1;
      
      break;
    }
    case SW_3_Pin:
    {
      pulse = 1800-1;
      sConfigOC.Pulse = pulse;
   
   if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
      p0 = 1;
      break;
    }
    }
    
    if(pulse >= 1850)
    {
      pulse = 1850 -1;
    }
    else if(pulse <= 1800)
    {
      pulse = 1800 - 1;
    }
    
  
    
    HAL_GPIO_WritePin(GPIOD, LED_7_Pin, GPIO_PIN_RESET);
   HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1); 
   HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
   HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
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
