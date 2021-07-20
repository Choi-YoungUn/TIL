//***************************************************
//작성자 : 2015132039 최영운
//작성일 : 2019 / 11 / 01

#include "stm32f4xx.h"
#include "GLCD.h"

#define SW0_PUSH        0xFE00  //PH8
#define SW1_PUSH        0xFD00  //PH9
#define SW2_PUSH        0xFB00  //PH10
#define SW3_PUSH        0xF700  //PH11
#define SW4_PUSH        0xEF00  //PH12
#define SW5_PUSH        0xDF00  //PH13
#define SW6_PUSH        0xBF00  //PH14
#define SW7_PUSH        0x7F00  //PH15

void _GPIO_Init(void);
void DisplayTitle(void);
void _ADC_Init(void);

void  TIMER8_Init(void);     //타이머 8 설정
void TIMER14_Init(void);     //타이머 14 설정
void _EXTI_Init(void);

void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

uint16_t KEY_Scan(void);
uint16_t ADC_Value, Voltage, temper, freque, print;  // 순서대로 가변저항 값, 환산전압, 환산온도, 환산 주기, 직사각형길이 변수
uint16_t VSENSE, TEMPER;                             //내부온도 , 환산내부온도
uint8_t str[30];                                     //글자 저장 배열

int main(void)
{
	LCD_Init();	// LCD 구동 함수
	DelayMS(10);	// LCD구동 딜레이
	DisplayTitle();	//LCD 초기화면구동 함수
	_EXTI_Init();  //스위치 인터럽트

	_GPIO_Init();
	_ADC_Init();
	TIMER8_Init();    //타이머 8 설정.
	TIMER14_Init();   // TIM14 Init 

	while (1)
	{

	}
}

void _ADC_Init(void)           //ADC 설정 =여기서 1,3번을 같이 설정해준다.
{   	// ADC1: PA1(pin 41)  가변저항 측정부
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	      // (1<<0) ENABLE GPIOA CLK (stm32f4xx.h 참조)
	GPIOA->MODER |= (3 << 2 * 1);	            	// CONFIG GPIOA PIN1(PA1) TO ANALOG IN MODE

	RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;         	// (1<<10) ENABLE ADC3 CLK (stm32f4xx.h 참조)

	ADC->CCR &= ~(0X1F << 0);		                // MULTI[4:0]: ADC_Mode_Independent
	ADC->CCR |= (1 << 16); 		                    // 0x00010000 ADCPRE:ADC_Prescaler_Div4 (ADC MAX Clock 36MHz, 84Mhz(APB2)/4 = 21MHz)

	ADC3->CR1 |= (1 << 24);	                    	// RES[1:0]=      : 10bit Resolution
	ADC3->CR1 &= ~(1 << 8);		                    // SCAN=0 : ADC_ScanCovMode Disable
	ADC3->CR1 |= (1 << 5);		                    // EOCIE=1: Interrupt enable for EOC

	ADC3->CR2 &= ~(1 << 1);		                    // CONT=0: ADC_Continuous ConvMode Disable
	ADC3->CR2 |= (2 << 28);		                    // EXTEN[1:0]: ADC_ExternalTrigConvEdge_Enable(Falling Edge)
	ADC3->CR2 |= (0x0D << 24);	          // Timer 8 _1CH 에서 신호가 입력 가능하도록 설정.
	ADC3->CR2 &= ~(1 << 11);		               // ALIGN=0: ADC_DataAlign_Right
	ADC3->CR2 &= ~(1 << 10);		               // EOCS=0: The EOC bit is set at the end of each sequence of regular conversions

	ADC3->SQR1 &= ~(0xF << 20);	                 // L[3:0]=0b0000: ADC Regular channel sequece length 
					                                // 0b0000:1 conversion)
	//Channel selection, The Conversion Sequence of PIN1(ADC3_CH1) is first, Config sequence Range is possible from 0 to 17
	ADC3->SQR3 |= (1 << 0);		                       // SQ1[4:0]=0b0001 : CH1
	ADC3->SMPR2 |= (0x7 << (3 * 1));	          // ADC3_CH1 Sample TIme_480Cycles (3*Channel_1)
//Channel selection, The Conversion Sequence of PIN1(ADC1_CH1) is first, Config sequence Range is possible from 0 to 17

	NVIC->ISER[0] |= (1 << 18);	                   // Enable ADC global Interrupt

	ADC3->CR2 |= (1 << 0);		                // ADON: ADC ON


		// ADC1 :내부 16번 채널  내부온도 측정부

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;	// (1<<8) ENABLE ADC1 CLK (stm32f4xx.h 참조)

	ADC->CCR &= ~(0X1F << 0);		// MULTI[4:0]: ADC_Mode_Independent
	ADC->CCR |= (1 << 16); 	       	// 0x00010000 ADCPRE:ADC_Prescaler_Div4 (ADC MAX Clock 36MHz, 84Mhz(APB2)/4 = 21MHz)
	ADC->CCR |= (1 << 23);           //TSVREFE 를 1로 해준다,  Temperature sensor and VREFINT channel enabled

	ADC1->CR1 |= (1 << 24);		// RES[1:0]= 10-bit (13 ADCCLK cycles) 
	ADC1->CR1 |= (1 << 4);		// SCAN=0 : ADC_ScanCovMode Disable
	ADC1->CR1 |= (1 << 5);		// EOCIE=1: Interrupt enable for EOC

	ADC1->CR2 &= ~(1 << 1);		// CONT=0: ADC_Continuous ConvMode Disable
	ADC1->CR2 |= (2 << 28);		// EXTEN[1:0]: ADC_ExternalTrigConvEdge_Enable(Falling Edge)
	ADC1->CR2 |= (0x0D << 24);	         // Timer 8 _1CH 에서 신호가 입력 가능하도록 설정.
	ADC1->CR2 &= ~(1 << 11);		// ALIGN=0: ADC_DataAlign_Right
	ADC1->CR2 &= ~(1 << 10);		// EOCS=0: The EOC bit is set at the end of each sequence of regular conversions

	ADC1->SQR1 &= ~(0xF << 20);	// L[3:0]=0b0000: ADC Regular channel sequece length 
					// 0b0000:1 conversion)
	//Channel selection, The Conversion Sequence of PIN1(ADC1_CH1) is first, Config sequence Range is possible from 0 to 17
	ADC1->SQR1 |= (1 << 15);		// SQ1[4:0]=0b0001 : CH16
	ADC1->SMPR1 |= (0x7 << (18));	// ADC1_CH16 Sample TIme_480Cycles (3*Channel_1)
//Channel selection, The Conversion Sequence of PIN1(ADC1_CH1) is first, Config sequence Range is possible from 0 to 17

		// Enable ADC global Interrupt  위에서 인터럽트를 선언해주었으므로 생략.

	ADC1->CR2 |= (1 << 0);		// ADON: ADC ON
}

void ADC_IRQHandler(void)  //ADC핸들러 부분.
{
	ADC3->SR &= ~(1 << 1);		                     // EOC flag clear 가변저항 측정ADC3 초기화
	ADC1->SR &= ~(1 << 1);		                     // EOC flag clear 내부온도 측정 ADC1 초기화

	ADC_Value = ADC3->DR;		                     // Reading ADC result  ADC3의 데이터 값 => 가변저항값 에 저장
	Voltage = ADC_Value * (3.3 * 100) / 1023;        // 3.3 : 4095 =  Volatge : ADC_Value
													 // 100:  소수점아래 두자리까지 표시하기 위한 값  
	temper = (35 * ((Voltage / 10) * (Voltage / 10))); //가변저항값을 통한 온도 표시하기 위한 함수식.

	LCD_DisplayChar(0, 10, Voltage / 100 + 0x30);    //전압의 10의자리
	LCD_DisplayChar(0, 12, Voltage % 100 / 10 + 0x30); //전압의 1의자리
	LCD_DisplayChar(0, 13, Voltage % 10 + 0x30);      //전압의 0.1의 자리

	temper = temper + 1000;                           //계산된 온도값에 보정값 더하기.

	LCD_DisplayChar(1, 10, temper / 10000 + 0x30);         //온도의 10의자리
	LCD_DisplayChar(1, 11, temper % 10000 / 1000 + 0x30);   //온도의 1의자리
	LCD_DisplayChar(1, 13, temper % 1000 / 100 + 0x30);     //온도의 0.1의 자리

	freque = (temper / 100) * 10;                           //온도값을 통한 주기 변환 계산식

	sprintf(str, "%4d", freque);	                      // ADC result : 12bits (0~4095)
	LCD_DisplayText(2, 7, str);                           // 글자를 표현하기위한 방법
	TIM14->ARR = freque;                                  //타이머 14의 주기ARR을 변경해준다.

	print = freque / 100;                                 //아레 상태 바를 조작하기 위한 변수 계산 후 저장

	LCD_SetBrushColor(RGB_GREEN);                        //브러쉬 색상 초록으로.
	LCD_DrawFillRect(10, 60, 140, 10);                   //상태바의 바탕(직사각형)을 그린다  참고로 디스플레이의 가로는 0~150픽셀이다
	LCD_SetBrushColor(RGB_RED);                          //상태바의 색상 빨강으로 그린다.
	LCD_DrawFillRect(10, 60, 10 + ((((13000 / 39)*print) + 100) / 100), 10);  //왼쪽 10 픽셀 부터 주기로 인한 값을 환산해서 설정. 
														   //단위가 커진 것은 소숫점까지 정확히 계산하여 어긋나는 픽셀의 수를 최소화 해주기 위한것.
	VSENSE = ADC1->DR;                                    //내부온도센서 변수에 ADC1의 데이터 값을 저장

	TEMPER = (((VSENSE - 0.76) / 0.0025) + 25);            //내부온도 측정 계산식

	LCD_DisplayChar(5, 10, TEMPER / 1000 + 0x30);          //내부온도 10의자리
	LCD_DisplayChar(5, 11, TEMPER % 1000 / 100 + 0x30);     //내부온도 1의자리
	LCD_DisplayChar(5, 13, TEMPER % 100 / 10 + 0x30);         //내부온도 0.1의자리
}

void TIMER8_Init(void)  //타이머 8 _채널 1번 고급제어 타이머.
{
	// TIM8_CH1 (PI5) : 150ms 인터럽트 발생
	// Clock Enable : GPIOI & TIMER8
	RCC->AHB1ENR |= (1 << 8);	// GPIOI Enable
	RCC->APB2ENR |= (1 << 1);	// TIMER8 Enable 

// PI5을 출력설정하고 Alternate function(TIM8_CH1)으로 사용 선언 
	GPIOI->MODER |= (2 << 2 * 5);	// PI5 Output Alternate function mode					
	GPIOI->OSPEEDR |= (3 << 2 * 5);	// PI5 Output speed (100MHz High speed)
	GPIOI->OTYPER &= ~(1 << 5);	// PI5 Output type push-pull (reset state)
	GPIOI->AFR[0] |= (3 << 20); 	// AFR[0].: Connect TIM5 pins(PI5) to AF3(TIM8)
					// PI5 ==> TIM8_CH1

	TIM8->BDTR |= (1 << 15);  //고급제어 타이머 1,8을 쓸때 항상 해줘야 하는 것.

	// Assign 'Interrupt Period' and 'Output Pulse Period'
	TIM8->PSC = 1680 - 1;	// Prescaler 168MHz/1680 = 0.1MHz (10us)
	TIM8->ARR = 15000 - 1;	// Auto reload  : 10us * 15K = 150ms(period)

	// CR1 : Up counting
	TIM8->CR1 &= ~(1 << 4);	// DIR=0(Up counter)(reset state)
	TIM8->CR1 &= ~(1 << 1);	// UDIS=0(Update event Enabled): By one of following events
				//	- Counter Overflow/Underflow, 
				// 	- Setting the UG bit Set,
				//	- Update Generation through the slave mode controller 
	TIM8->CR1 &= ~(1 << 2);	// URS=0(Update event source Selection): one of following events
				//	- Counter Overflow/Underflow, 
				// 	- Setting the UG bit Set,
				//	- Update Generation through the slave mode controller 
	TIM8->CR1 &= ~(1 << 3);	// OPM=0(The counter is NOT stopped at update event) (reset state)
	TIM8->CR1 &= ~(1 << 7);	// ARPE=0(ARR is NOT buffered) (reset state)
	TIM8->CR1 &= ~(3 << 8); 	// CKD(Clock division)=00(reset state)
	TIM8->CR1 &= ~(3 << 5); 	// CMS(Center-aligned mode Sel)=00 (Edge-aligned mode) (reset state)
				// Center-aligned mode: The counter counts Up and DOWN alternatively

	// Event & Interrup Enable : UI  
	TIM8->EGR |= (1 << 0);    // UG: Update generation    

	////////////////////////////////
	// Disable Tim8 Update interrupt

	// Define the corresponding pin by 'Output'  
	TIM8->CCER |= (1 << 0);	// CC1E=1: CC1 channel Output Enable
				// OC1(TIM8_CH1) Active: 해당핀을 통해 신호출력
	TIM8->CCER &= ~(1 << 1);	// CC1P=0: CC1 channel Output Polarity (OCPolarity_High : OC1으로 반전없이 출력)  

	// 'Mode' Selection : Output mode, toggle  
	TIM8->CCMR1 &= ~(3 << 0); // CC1S(CC1 channel) = '0b00' : Output 
	TIM8->CCMR1 &= ~(1 << 3); // OC1P=0: Output Compare 3 preload disable
	TIM8->CCMR1 |= (3 << 4);	// OC1M : Output Compare  Mode : toggle
				

	TIM8->CCR1 = 10000;	// TIM8 CCR1 TIM8_Pulse

	TIM8->CR1 |= (1 << 0);	// CEN: Enable the Tim8 Counter  					
}

void TIMER14_Init(void)  //소리 센서를 사용하기 위한 설정타이머
{
	// 핀:PF9(TIM14 CH1)
	// Clock Enable : GPIOF & TIMER14
	RCC->AHB1ENR |= (1 << 5);	// GPIOF Enable
	RCC->APB1ENR |= (1 << 8);	// TIMER14 Enable 

// PF9을 출력설정하고 Alternate function(TIM14_CH1)으로 사용 선언 
	GPIOF->MODER |= (2 << 18);	// PF9 Output Alternate function mode					
	GPIOF->OSPEEDR |= (3 << 18);	// PFP Output speed (100MHz High speed)
	GPIOF->OTYPER &= ~(1 << 9);	// PF9 Output type push-pull (reset state)
	GPIOF->AFR[1] |= (9 << 4); 	// 	(AFR[0].(3~0)=0b0010): Connect AF13


// TIM14 Channel 1 : 
	TIM14->PSC = 840 - 1;	// Prescaler 84,000,000Hz/840 = 100,000 Hz (0.01ms)  (1~65536)
	TIM14->ARR = 80 - 1;	// Auto reload  (0.01ms * 80 = 0.8ms )

	// Define the corresponding pin by 'Output'  
	// CCER(Capture/Compare Enable Register) : Enable "Channel 1" 
	TIM14->CCER |= (1 << 0);	// CC1E=1: OC1(TIM14_CH1) Active(Capture/Compare 1 output enable)
					// 해당핀(40번)을 통해 신호출력
	TIM14->CCER &= ~(1 << 1);	// CC1P=0: CC1 output Polarity High (OC1으로 반전없이 출력)

	GPIOF->MODER |= 0x00020000;   // GPIOF 8 : Output mode (0b01)                  
	GPIOF->OTYPER &= ~0x0100;   // GPIOF 8 : Push-pull     
	GPIOF->OSPEEDR |= 0x00020000;   // GPIOF 8 : Output speed 25MHZ Medium speed 
	// Duty Ratio 
	TIM14->CCR1 = 0;		// CCR1 value

	// 'Mode' Selection : Output Compare mode
	// CCMR1(Capture/Compare Mode Register 1) : Setting the MODE of Ch1 or Ch2
	TIM14->CCMR1 &= ~(3 << 0); 	// CC1S(CC1 channel)='0b00' : Output 
	TIM14->CCMR1 &= ~(1 << 3); 	// OC1PE=0: Output Compare 1 preload disnable
	TIM14->CCMR1 |= (3 << 4);	// OC1M: Output compare 1 mode: oc mode


	// CR1 : Up counting & Counter TIM14 enable
	TIM14->CR1 &= ~(1 << 4);	// DIR: Countermode = Upcounter (reset state)
	TIM14->CR1 &= ~(3 << 8);	// CKD: Clock division = 1 (reset state)
	TIM14->CR1 &= ~(3 << 5); 	// CMS(Center-aligned mode Sel): No(reset state)

	TIM14->CR1 |= (1 << 7);	// ARPE: Auto-reload preload enable

	
}

void _EXTI_Init(void)  //sw7 설정.
{
	RCC->AHB1ENR |= 0x0080;   // RCC_AHB1ENR GPIOH Enable
	RCC->APB2ENR |= 0x4000;   // Enable System Configuration Controller Clock

	GPIOH->MODER &= 0x0000FFFF;   // GPIOH PIN8~PIN15 Input mode (reset state)             

	SYSCFG->EXTICR[3] |= 0x7700;         // EXTI15에 대한 소스 입력은 GPIOF로 설정 

	EXTI->FTSR |= 0x00C000;      // Falling Trigger Enable (EXTI15:PH15)
	EXTI->IMR |= 0x00C000;     // EXTI15인터럽트 mask (Interrupt Enable)

	NVIC->ISER[1] |= (1 << (40 - 32));      // Enable Interrupt EXTI,15 Vector table Position 참조
}

void EXTI15_10_IRQHandler(void)      // EXTI 15~10 인터럽트 핸들러
{
	if (EXTI->PR & 0x8000)       // EXTI15 nterrupt Pending?   
	{
		EXTI->PR |= 0x8000;    // Pending bit Clear
		TIM14->CR1 ^= (1 << 0);	// CEN: Counter TIM14 enable 토글동작.

	}
}

void _GPIO_Init(void)  //부저부분 삭제.
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
	LCD_Clear(RGB_YELLOW);  //배경색 노랑
	LCD_SetFont(&Gulim10);		//폰트 
	LCD_SetBackColor(RGB_YELLOW);	//글자배경색
	LCD_SetTextColor(RGB_BLACK);	//글자색
	LCD_DisplayText(0, 0, "EXT VOL : 0.00V");   //초기화면 설정
	LCD_DisplayText(1, 0, "EXT TMP : 00.0C");
	LCD_DisplayText(2, 0, "FREQ : 0000HZ");
	LCD_DisplayText(5, 0, "INT TMP : 00.0C");

	LCD_SetBrushColor(RGB_GREEN);   //초기 상태 바 색상 녹색
	LCD_DrawFillRect(10, 60, 140, 10);// MAX 픽셀은 X축 150임! 직사각형 막대 생성
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