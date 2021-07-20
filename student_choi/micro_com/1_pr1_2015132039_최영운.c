//***************************************************
//작성자 : 2015132039 최영운
//작성일 : 2019 / 12 / 03
//////////////////////////////////////////////////////////////////////////
#include "stm32f4xx.h"
#include "GLCD.h"
#include "ACC.h"
#include "FRAM.h"

#define SW0_PUSH        0xFE00  //PH8
#define SW1_PUSH        0xFD00  //PH9
#define SW2_PUSH        0xFB00  //PH10
#define SW3_PUSH        0xF700  //PH11
#define SW4_PUSH        0xEF00  //PH12
#define SW5_PUSH        0xDF00  //PH13
#define SW6_PUSH        0xBF00  //PH14
#define SW7_PUSH        0x7F00  //PH15

void DisplayTitle(void);
void _GPIO_Init(void);
void _EXTI_Init(void);
void _ADC_Init(void);

void TIMER1_Init(void);     //타이머 1 
void TIMER2_PWM_Init(void);   //타이머 2

void USART1_Init(void);      //uart1
void USART_BRR_Configuration(uint32_t USART_BaudRate);

void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);
void BEEP(void);

void SerialSendChar(uint8_t c);
void SerialSendString(char *s);

uint16_t KEY_Scan(void);
uint16_t ADC_Value, Voltage;  //저항값 and 전압값 저장 변수
uint8_t str[20];      //문자 저장 공간

int move;           //자동차 시동

int main(void)
{
	LCD_Init();	// LCD 구동 함수
	DelayMS(10);	// LCD구동 딜레이
	DisplayTitle();	//LCD 초기화면구동 함수
	_EXTI_Init();
	_GPIO_Init();

	TIMER1_Init();
	TIMER2_PWM_Init();

	_ADC_Init();
	USART1_Init();     //uart통신 초기화

	Fram_Init();        // FRAM 초기화 
	Fram_Status_Config();

	if ((Fram_Read(1126) & 0x53) == 0x53)   //1126번지에 저장된 값이 S라면
	{
		move = 0;                     //시동 OFF
		TIM2->CR1 &= ~(1 << 0);       //출력 파형 OFF
	}
	else if ((Fram_Read(1126) & 0x4D) == 0x4D)   //1126번지에 저장된 값이 M이라면
	{
		move = 1;                       //시동 ON
		TIM2->CR1 |= (1 << 0);          //출력 파형 ON
	}

	while (1)
	{
		switch (KEY_Scan())
		{
		case SW0_PUSH: 		//SW0

			move = 1;         //시동 ON
			TIM2->CR1 |= (1 << 0);   //출력파형 ON
			Fram_Write(1126, 0x4D);   //1126번지에 M 저장
			break;


		}
	}
}

void _ADC_Init(void)
{   	// ADC2: PA1(pin 41)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	// (1<<0) ENABLE GPIOA CLK (stm32f4xx.h 참조)
	GPIOA->MODER |= (3 << 2 * 1);		// CONFIG GPIOA PIN1(PA1) TO ANALOG IN MODE

	RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;	// (1<<8) ENABLE ADC1 CLK (stm32f4xx.h 참조)

	ADC->CCR &= ~(0X1F << 0);		// MULTI[4:0]: ADC_Mode_Independent
	ADC->CCR |= (1 << 16); 		// 0x00010000 ADCPRE:ADC_Prescaler_Div4 (ADC MAX Clock 36MHz, 84Mhz(APB2)/4 = 21MHz)

	ADC2->CR1 |= (1 << 24);		// RES[1:0]=      : 10bit Resolution
	ADC2->CR1 &= ~(1 << 8);		// SCAN=0 : ADC_ScanCovMode Disable
	ADC2->CR1 |= (1 << 5);		// EOCIE=1: Interrupt enable for EOC

	ADC2->CR2 &= ~(1 << 1);		// CONT=0: ADC_Continuous ConvMode Disable
	ADC2->CR2 |= (2 << 28);		// EXTEN[1:0]: ADC_ExternalTrigConvEdge_Enable(Falling Edge)
	ADC2->CR2 |= (2 << 24);	         // Timer 1 _3CH 에서 신호가 입력 가능하도록 설정.
	ADC2->CR2 &= ~(1 << 11);		// ALIGN=0: ADC_DataAlign_Right
	ADC2->CR2 &= ~(1 << 10);		// EOCS=0: The EOC bit is set at the end of each sequence of regular conversions

	ADC2->SQR1 &= ~(0xF << 20);	// L[3:0]=0b0000: ADC Regular channel sequece length 
					// 0b0000:1 conversion)
	//Channel selection, The Conversion Sequence of PIN1(ADC1_CH1) is first, Config sequence Range is possible from 0 to 17
	ADC2->SQR3 |= (1 << 0);		// SQ1[4:0]=0b0001 : CH1
	ADC2->SMPR2 |= (0x7 << (3 * 1));	// ADC1_CH1 Sample TIme_480Cycles (3*Channel_1)
//Channel selection, The Conversion Sequence of PIN1(ADC1_CH1) is first, Config sequence Range is possible from 0 to 17

	NVIC->ISER[0] |= (1 << 18);	// Enable ADC global Interrupt

	ADC2->CR2 |= (1 << 0);		// ADON: ADC ON
}

void ADC_IRQHandler(void)
{
	int range = 0;
	ADC2->SR &= ~(1 << 1);		// EOC flag clear

	ADC_Value = ADC2->DR;		// Reading ADC result

	Voltage = ADC_Value * (3.3 * 100) / 1023;   // 3.3 : 4095 =  Volatge : ADC_Value 
													// 100:  소수점아래 두자리까지 표시하기 위한 값  


	if (move == 1)
	{
		range = (Voltage * 10 + 500) / 100;   //차동차 간의 거리 표시
		sprintf(str, "%4d", range);	// ADC result : 12bits (0~4095)
		LCD_DisplayText(1, 14, str);    //화면에 띄우기

		LCD_SetBrushColor(RGB_YELLOW);
		LCD_DrawFillRect(15, 22, 95, 8);             // 막대바 리셋
		LCD_SetBrushColor(RGB_RED);
		LCD_DrawFillRect(15, 22, 2.5*range, 8);  //빨간 막대바 그리기

		LCD_DisplayText(2, 14, "M");    // 주행 상태 화면에 표시

		if (range >= 37)        //거리가 37 이상이라면
		{
			TIM2->CCR4 = 9000;		// CCR4 value
			LCD_DisplayText(2, 7, "90%");
		}
		else if (range >= 33) //거리가 33 이상이라면
		{
			TIM2->CCR4 = 8000;		// CCR4 value
			LCD_DisplayText(2, 7, "80%");
		}
		else if (range >= 29) //거리가 29 이상이라면
		{
			TIM2->CCR4 = 7000;		// CCR4 value
			LCD_DisplayText(2, 7, "70%");
		}
		else if (range >= 25) //거리가 25 이상이라면
		{
			TIM2->CCR4 = 6000;		// CCR4 value
			LCD_DisplayText(2, 7, "60%");
		}
		else if (range >= 21) //거리가 21 이상이라면
		{
			TIM2->CCR4 = 5000;		// CCR4 value
			LCD_DisplayText(2, 7, "50%");
		}
		else if (range >= 17) //거리가 17 이상이라면
		{
			TIM2->CCR4 = 4000;		// CCR4 value
			LCD_DisplayText(2, 7, "40%");
		}
		else if (range >= 13) //거리가 13 이상이라면
		{
			TIM2->CCR4 = 3000;		// CCR4 value
			LCD_DisplayText(2, 7, "30%");
		}
		else if (range >= 9) //거리가 9 이상이라면
		{
			TIM2->CCR4 = 2000;		// CCR4 value
			LCD_DisplayText(2, 7, "20%");
		}
		else if (range >= 5) //거리가 5 이상이라면
		{
			TIM2->CCR4 = 1000;		// CCR4 value
			LCD_DisplayText(2, 7, "10%");
		}
		SerialSendString(str);
		SerialSendString("M ");
	}
	else
	{                  //시동이 꺼져 있다면 MOVE = 0
		range = 0;     //거리 0
		TIM2->CCR4 = 0;  //CCR4 0
		LCD_DisplayText(2, 0, "S(DR): 00%");
		sprintf(str, "%4d", range);	// ADC result : 12bits (0~4095)
		LCD_DisplayText(1, 14, str);
		LCD_SetBrushColor(RGB_YELLOW);
		LCD_DrawFillRect(15, 22, 95, 8);
		LCD_DisplayText(2, 14, "S");          //화면 초기화
	}

}

void TIMER1_Init(void)
{
	// PE13: TIM1_CH3
	// PE13을 출력설정하고 Alternate function(TIM1_CH3)으로 사용 선언
	RCC->AHB1ENR |= (1 << 4);   //  RCC_AHB1ENR GPIOE Enable 

	GPIOE->MODER |= (2 << 26);   // (MODER.(27,26)=0b10), GPIOE PIN13 Output Alternate function mode                
	GPIOE->OSPEEDR |= (3 << 26);   // (OSPEEDER.(27,26)), GPIOe PIN13 Output speed (100MHz High speed)
	GPIOE->OTYPER &= ~(1 << 13);   // GPIOE PIN13 Output type push-pull (reset state)
	GPIOE->PUPDR |= (1 << 26);    // GPIOE PIN13 Pull-up
	GPIOE->AFR[1] |= (1 << 20);   // (AFR[1]): Connect TIM1 pins(PF1) to AF1(TIM1)



 // Timerbase Mode
	RCC->APB2ENR |= (1 << 0);   // RCC_APB2ENR TIMER1 Enable

	// Setting CR1 : 0x0000 
	TIM1->CR1 &= ~(1 << 4);   // DIR=0(Up counter)(reset state)
	TIM1->CR1 &= ~(1 << 1);   // UDIS=0(Update event Enabled): By one of following events
			 //   - Counter Overflow/Underflow, 
			 //    - Setting the UG bit Set,
			 //   - Update Generation through the slave mode controller 
	TIM1->CR1 &= ~(1 << 2);   // URS=0(Update event source Selection): one of following events
			 //   - Counter Overflow/Underflow, 
			 //    - Setting the UG bit Set,
			 //   - Update Generation through the slave mode controller 
	TIM1->CR1 &= ~(1 << 3);   // OPM=0(The counter is NOT stopped at update event) (reset state)
	TIM1->CR1 &= ~(1 << 7);   // ARPE=0(ARR is NOT buffered) (reset state)
	TIM1->CR1 &= ~(3 << 8);    // CKD(Clock division)=00(reset state)
	TIM1->CR1 &= ~(3 << 5);    // CMS(Center-aligned mode Sel)=00 (Edge-aligned mode) (reset state)
			 // Center-aligned mode: The counter counts Up and DOWN alternatively

	// Deciding the Period
	TIM1->PSC = 16800 - 1;   // Prescaler=8400, 168MHz/16800 = 10kHz (0.1ms)
	TIM1->ARR = 3000 - 1;   // Auto reload  : 0.1ms * 3K = 300ms(period) : 인터럽트주기나 출력신호의 주기 결정

	// Update(Clear) the Counter
	TIM1->EGR |= (1 << 0);    // UG: Update generation    

	// Setting an UI(UEV) Interrupt 
	NVIC->ISER[0] |= (1 << 27);   // Enable Timer1 global Interrupt on NVIC
	TIM1->DIER |= (1 << 0);   // UIE: Enable Tim1 Update interrupt

 // Output Compare Mode
	TIM1->CCMR2 &= ~(3 << 0); // CC3S(CC3 channel) = '0b00' : Output 
	TIM1->CCMR2 &= ~(1 << 2); // OC3FE=0: Output Compare 1 Fast disable 
	TIM1->CCMR2 &= ~(1 << 3); // OC3PE=0: Output Compare 1 preload disable(CCR1에 언제든지 새로운 값을 loading 가능) 
	TIM1->CCMR2 |= (3 << 4);   // OC3M (Output Compare 1 Mode : toggle)

	// CCER(Capture/Compare Enable Register) : Enable "Channel 3" 
	TIM1->CCER |= (1 << 8);   // CC3E=1: CC3 channel Output Enable
			 // OC1(TIM1_CH3) Active: 해당핀을 통해 신호출력
	TIM1->CCER &= ~(1 << 9);   // CC3P=0: CC3channel Output Polarity (OCPolarity_High : OC1으로 반전없이 출력)  
	TIM1->CCR3 = 2000 - 1;
	TIM1->DIER |= (1 << 3);   // CC3IE: Enable the Tim1 CC3 interrupt
	TIM1->BDTR |= (1 << 15); // 타이머1 , 8 시 써줘야함
	TIM1->CR1 |= (1 << 0);   //타이머 작동 시작.
}

void TIM1_CC_IRQHandler(void)  	// 300ms Interrupt  ADC에 이유는 모르겠으나 직접 시작이 되지 않아 사용.   
{
	if ((TIM1->SR & 0x08) != RESET)   // Update interrupt flag 
	{
		TIM1->SR &= ~(1 << 3);   // Update Interrupt Claer

		ADC2->CR2 |= ADC_CR2_SWSTART;  //ADC2 시작
	}

}

void TIMER2_PWM_Init(void)
{
	// Clock Enable : GPIOB & TIMER2
	RCC->AHB1ENR |= (1 << 1);	// GPIOB Enable
	RCC->APB1ENR |= (1 << 0);	// TIMER2 Enable 

// PB11을 출력설정하고 Alternate function(TIM2_CH4)으로 사용 선언 : PWM 출력
	GPIOB->MODER |= (2 << 22);	// PB11 Output Alternate function mode					
	GPIOB->OSPEEDR |= (3 << 22);	// PB11 Output speed (100MHz High speed)
	GPIOB->OTYPER &= ~(1 << 11);	// PB11 Output type push-pull (reset state)
	GPIOB->AFR[1] |= (1 << 12); 	// 0x00000002	(AFR[0].(3~0)=0b0010): PB11 = AFR[1]
// TIM2 Channel 4 : PWM 1 mode
	// Assign 'PWM Pulse Period'
	TIM2->PSC = 42000 - 1;	// Prescaler 84,000,000Hz/42000 = 20,000 Hz(0.5ms)  (1~65536)
	TIM2->ARR = 10000 - 1;	// Auto reload  (0.1ms * 10000 = 5s : PWM Period)

	// Define the corresponding pin by 'Output'  
	// CCER(Capture/Compare Enable Register) : Enable "Channel 1" 
	TIM2->CCER |= (1 << 12);	// CC4E=1: OC4(TIM2_CH4) Active(Capture/Compare 1 output enable)
				// 해당핀(40번)을 통해 신호출력
	TIM2->CCER &= ~(1 << 13);	// CC4P=0: CC4 output Polarity High (OC4으로 반전없이 출력)

	// Duty Ratio 
	TIM2->CCR4 = 0;		// CCR4 value

	// 'Mode' Selection : Output mode, PWM 1
	// CCMR1(Capture/Compare Mode Register 1) : Setting the MODE of Ch1 or Ch2
	TIM2->CCMR2 &= ~(3 << 8); 	// CC4S(CC4 channel)='0b00' : Output 
	TIM2->CCMR2 |= (1 << 11); 	// OC4PE=1: Output Compare 1 preload Enable

	TIM2->CCMR2 |= (6 << 12);	// OC4M: Output compare 1 mode: PWM 1 mode

	// CR1 : Up counting & Counter TIM2 enable
	TIM2->CR1 &= ~(1 << 4);	// DIR: Countermode = Upcounter (reset state)
	TIM2->CR1 &= ~(3 << 8);	// CKD: Clock division = 1 (reset state)
	TIM2->CR1 &= ~(3 << 5); 	// CMS(Center-aligned mode Sel): No(reset state)
	TIM2->CR1 |= (1 << 7);	// ARPE: Auto-reload preload enable
	//시작신호 제거. 
}

void USART1_Init(void)
{
	// USART1 : TX(PA9)
	RCC->AHB1ENR |= (1 << 0);	// RCC_AHB1ENR GPIOA Enable
	GPIOA->MODER |= (2 << 2 * 9);	// GPIOB PIN9 Output Alternate function mode					
	GPIOA->OSPEEDR |= (3 << 2 * 9);	// GPIOB PIN9 Output speed (100MHz Very High speed)
	GPIOA->AFR[1] |= (7 << 4);	// Connect GPIOA pin9 to AF7(USART1)

	// USART1 : RX(PA10)
	GPIOA->MODER |= (2 << 2 * 10);	// GPIOA PIN10 Output Alternate function mode
	GPIOA->OSPEEDR |= (3 << 2 * 10);	// GPIOA PIN10 Output speed (100MHz Very High speed
	GPIOA->AFR[1] |= (7 << 8);	// Connect GPIOA pin10 to AF7(USART1)

	RCC->APB2ENR |= (1 << 4);	// RCC_APB2ENR USART1 Enable

	USART_BRR_Configuration(9600); // USART Baud rate Configuration

	USART1->CR1 |= 1 << 12;	// USART_WordLength 8 Data bit  보내는 데이터의 길이 설정

	USART1->CR1 |= 1 << 10;	// USART_Parity
	USART1->CR1 |= 1 << 9;  //홀수 페리티 설정

	USART1->CR1 |= 1 << 8; //페리티 인터럽트 발생.

	USART1->CR1 |= (1 << 2);	// 0x0004, USART_Mode_RX Enable
	USART1->CR1 |= (1 << 3);	// 0x0008, USART_Mode_Tx Enable
	USART1->CR2 &= ~(3 << 12);	// 0b00, USART_StopBits_1
	USART1->CR3 = 0x0000;	// No HardwareFlowControl, No DMA

	USART1->CR1 |= (1 << 5);	// 0x0020, RXNE interrupt Enable
	NVIC->ISER[1] |= (1 << (37 - 32));// Enable Interrupt USART1 (NVIC 37번)
	USART1->CR1 |= (1 << 13);	//  0x2000, USART1 Enable
}

void USART1_IRQHandler(void)	//모든 인터럽트시 핸들러.
{

	if ((USART1->SR & USART_SR_RXNE)) 	// USART_SR_RXNE=(1<<5) 
	{
		uint16_t ch;

		ch = (uint16_t)(USART1->DR & (uint16_t)0x01FF);	// 수신된 문자 저장
		if ((ch & 0x4D) == 0x4D)      //M 이 수신된다면
		{
			move = 1;               //시동 ON
			TIM2->CR1 |= (1 << 0);	// CEN: Counter TIM2 enable
		}
		if ((ch & 0X53) == 0x53)     //S 이 수신된다면
		{
			move = 0;         //시동 OFF
			TIM2->CR1 &= ~(1 << 0);	// CEN: Counter TIM2 enable
		}
		Fram_Write(1126, ch);  //1126번지에 저장

	}
	// DR 을 읽으면 SR.RXNE bit(flag bit)는 clear 된다. 즉 clear 할 필요없음 

	if ((USART1->SR & USART_SR_PE)) 	// USART_SR_PE=(1<<0)   페리티 인터럽트만 검출  (0x0001)
	{
		SerialSendString("error!!");
	}
}

void USART_BRR_Configuration(uint32_t USART_BaudRate)//소숫점을 살리기 위해 최대한 한것.
{
	uint32_t tmpreg = 0x00;
	uint32_t APB2clock = 84000000;	//PCLK2_Frequency
	uint32_t integerdivider = 0x00;
	uint32_t fractionaldivider = 0x00;

	// Determine the integer part 
	if ((USART1->CR1 & USART_CR1_OVER8) != 0) // USART_CR1_OVER8=(1<<15)
	{                                         // USART1->CR1.OVER8 = 1 (8 oversampling)
	// Computing 'Integer part' when the oversampling mode is 8 Samples 
		integerdivider = ((25 * APB2clock) / (2 * USART_BaudRate));
	}
	else  // USART1->CR1.OVER8 = 0 (16 oversampling)
	{	// Computing 'Integer part' when the oversampling mode is 16 Samples 
		integerdivider = ((25 * APB2clock) / (4 * USART_BaudRate));
	}
	tmpreg = (integerdivider / 100) << 4;

	// Determine the fractional part 
	fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

	// Implement the fractional part in the register 
	if ((USART1->CR1 & USART_CR1_OVER8) != 0)	// 8 oversampling
	{
		tmpreg |= (((fractionaldivider * 8) + 50) / 100) & (0x07);
	}
	else 						// 16 oversampling
	{
		tmpreg |= (((fractionaldivider * 16) + 50) / 100) & (0x0F);
	}

	// Write to USART BRR register
	USART1->BRR = (uint16_t)tmpreg;
}

void SerialSendChar(uint8_t Ch) // 1문자 보내기 함수
{
	while ((USART1->SR & USART_SR_TXE) == RESET); // USART_SR_TXE=(1<<7), 송신 가능한 상태까지 대기

	USART1->DR = (Ch & 0x01FF);	// 전송 (최대 9bit 이므로 0x01FF과 masking)
}

void SerialSendString(char *str) // 여러문자 보내기 함수
{
	while (*str != '\0') // 종결문자가 나오기 전까지 구동, 종결문자가 나온후에도 구동시 메모리 오류 발생가능성 있음.
	{
		SerialSendChar(*str);	// 포인터가 가르키는 곳의 데이터를 송신
		str++; 			// 포인터 수치 증가
	}
}

void _GPIO_Init(void)
{
	// LED (GPIO G) 설정
	RCC->AHB1ENR |= 0x00000040;	// RCC_AHB1ENR : GPIOG(bit#6) Enable							
	GPIOG->MODER |= 0x00005555;	// GPIOG 0~7 : Output mode (0b01)						
	GPIOG->OTYPER &= ~0x00FF;	// GPIOG 0~7 : Push-pull  (GP8~15:reset state)	
	GPIOG->OSPEEDR |= 0x00005555;	// GPIOG 0~7 : Output speed 25MHZ Medium speed 

	// SW (GPIO H) 설정 
	RCC->AHB1ENR |= 0x00000080;	// RCC_AHB1ENR : GPIOH(bit#7) Enable							
	GPIOH->MODER &= ~0xFFFF0000;	// GPIOH 8~15 : Input mode (reset state)				
	GPIOH->PUPDR &= ~0xFFFF0000;	// GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

	// Buzzer (GPIO F) 설정 
	RCC->AHB1ENR |= 0x00000020; // RCC_AHB1ENR : GPIOF(bit#5) Enable							
	GPIOF->MODER |= 0x00040000;	// GPIOF 9 : Output mode (0b01)						
	GPIOF->OTYPER &= ~0x0200;	// GPIOF 9 : Push-pull  	
	GPIOF->OSPEEDR |= 0x00040000;	// GPIOF 9 : Output speed 25MHZ Medium speed 

}

void _EXTI_Init(void)
{
	RCC->AHB1ENR |= 0x00000080;   // RCC_AHB1ENR GPIOH Enable
	RCC->APB2ENR |= 0x00004000;   // Enable System Configuration Controller Clock
	GPIOH->MODER &= 0x0000FFFF;   // GPIOH PIN8~PIN15 Input mode (reset state)            
	SYSCFG->EXTICR[3] |= 0x7700;   //EXTI 14,15에 대한 입력을 GPIOH로 설정  EXTICR4 이므로 [3]을 설정

	EXTI->FTSR |= 0x0000C000;              //눌릴시 EXTI15 작동
	EXTI->IMR |= 0x0000C000;         //EXTI 14,15 인터럽트 마스크 벗김

	NVIC->ISER[1] |= (1 << (40 - 32));  //백터 테이블에 해당하는 번호를 찾아서 설정해준다.
}

void EXTI15_10_IRQHandler(void)      //EXTI15_10핸들러를 설정해준다
{


	if (EXTI->PR & 0x8000)              //EXTI15 입력시 
	{

		EXTI->PR |= 0x8000;            //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
		move = 0;                     //시동 OFF
		TIM2->CR1 &= ~(1 << 0);          //출력 파형 OFF
		Fram_Write(1126, 0x53);              //1126번지에 저장
	}
}
void BEEP(void)			// Beep for 20 ms 
{
	GPIOF->ODR |= (1 << 9);	// PF9 'H' Buzzer on
	DelayMS(20);		// Delay 20 ms
	GPIOF->ODR &= ~(1 << 9);	// PF9 'L' Buzzer off
}

void DelayMS(unsigned short wMS)
{
	register unsigned short i;
	for (i = 0; i < wMS; i++)
		DelayUS(1000);   // 1000us => 1ms
}

void DelayUS(unsigned short wUS)
{
	volatile int Dly = (int)wUS * 17;
	for (; Dly; Dly--);
}

void DisplayTitle(void)
{
	LCD_Clear(RGB_YELLOW);
	LCD_SetFont(&Gulim10);		//폰트 
	LCD_SetBackColor(RGB_YELLOW);	//글자배경색
	LCD_SetTextColor(RGB_BLACK);	//글자색
	LCD_DisplayText(0, 0, "Tracking Car");      //초기화면 설정
	LCD_DisplayText(1, 0, "D:");
	LCD_DisplayText(2, 0, "S(DR): 00%");


}

uint8_t key_flag = 0;
uint16_t KEY_Scan(void)	// input key SW0 - SW7 
{
	uint16_t key;
	key = GPIOH->IDR & 0xFF00;	// any key pressed ?
	if (key == 0xFF00)		// if no key, check key off
	{
		if (key_flag == 0)
			return key;
		else
		{
			DelayMS(10);
			key_flag = 0;
			return key;
		}
	}
	else				// if key input, check continuous key
	{
		if (key_flag != 0)	// if continuous key, treat as no key input
			return 0xFF00;
		else			// if new key,delay for debounce
		{
			key_flag = 1;
			DelayMS(10);
			return key;
		}
	}
}