//***************************************************
//작성자 : 2015132039 최영운
//작성일 : 2019 / 10 / 05

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

void _RCC_Init(void);
void _GPIO_Init(void);
uint16_t KEY_Scan(void);
void DisplayInitScreen(void);

void TIMER1_Init(void);
void _EXTI_Init(void);
void TIMER14_PWM_Init(void);

void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);
void BEEP(void);


int speed = 5000;
uint8_t displaypoint = 0;

int main(void)
{
	_RCC_Init();
	_GPIO_Init();
	LCD_Init();		// LCD 구동 함수
	_EXTI_Init();
	DelayMS(10);		// LCD구동 딜레이
	DisplayInitScreen();	// LCD 초기화면구동 함수
	BEEP();

	GPIOG->ODR &= ~0x00FF;	// 초기값: LED0~7 Off

	TIMER1_Init();	     // TIM1 Init 
	TIMER14_PWM_Init();   // TIM1 Init 
	GPIOG->ODR |= 0x01; 	// LED0 ON



	while (1)
	{
		switch (KEY_Scan())
		{
		case SW0_PUSH: 	//SW0
			TIM14->CCR1 = 0;		// DR: 0%	  
			LCD_DisplayChar(4, 14, '0');  //디스플레이
			GPIOG->ODR &= ~0x00FF;		// All LED Off
			GPIOG->ODR |= (1 << 0);		// LED0 ON 
			break;

		case SW1_PUSH: 	//SW1
			TIM14->CCR1 = 10;		// DR: 10%	  
			LCD_DisplayChar(4, 14, '1'); //디스플레이
			GPIOG->ODR &= ~0x00FF;		// All LED Off
			GPIOG->ODR |= (1 << 1);		// LED1 ON 
			break;

		case SW2_PUSH: 	//SW2
			TIM14->CCR1 = 20;	// DR: 20%	  
			LCD_DisplayChar(4, 14, '2'); //디스플레이
			GPIOG->ODR &= ~0x00FF;		// All LED Off
			GPIOG->ODR |= (1 << 2);		// LED2 ON 
			break;

		case SW3_PUSH: 	//SW3
			TIM14->CCR1 = 30;		// DR: 30%	  
			LCD_DisplayChar(4, 14, '3'); //디스플레이
			GPIOG->ODR &= ~0x00FF;		// All LED Off
			GPIOG->ODR |= (1 << 3);		// LED3 ON 
			break;

		case SW4_PUSH: 	//SW4
			TIM14->CCR1 = 40;		// DR: 40%	  
			LCD_DisplayChar(4, 14, '4'); //디스플레이
			GPIOG->ODR &= ~0x00FF;		// All LED Off
			GPIOG->ODR |= (1 << 4);		// LED4 ON 
			break;

		case SW5_PUSH: 	//SW5
			TIM14->CCR1 = 50;		// DR: 50%	  
			LCD_DisplayChar(4, 14, '5'); //디스플레이
			GPIOG->ODR &= ~0x00FF;		// All LED Off
			GPIOG->ODR |= (1 << 5);		// LED5 ON 
			break;

		}
	}
}

void TIMER1_Init(void)
{
	// PE13: TIM1_CH3
	// PF13을 출력설정하고 Alternate function(TIM1_CH3)으로 사용 선언
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
	TIM1->PSC = 8400 - 1;   // Prescaler=8400, 84MHz/8400 = 10kHz (0.1ms)
	TIM1->ARR = 5000 - 1;   // Auto reload  : 0.1ms * 1K = 500ms(period) : 인터럽트주기나 출력신호의 주기 결정

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
	TIM1->CCR3 = 5000 - 1;
	TIM1->DIER |= (1 << 3);   // CC3IE: Enable the Tim1 CC3 interrupt

	TIM1->CR1 |= (1 << 0);   //타이머 작동 시작.
}


void TIM1_CC_IRQHandler(void)  	// 1ms Interrupt    
{
	if ((TIM1->SR & 0x08) != RESET)   // Update interrupt flag 
	{
		TIM1->SR &= ~(1 << 3);   // Update Interrupt Claer
		GPIOG->ODR ^= (1 << 7);		// LED7 ON  and  OFF      첫 인트럽트 발생시   ON  (홀수)        짝수시   OFF
	}

}

void TIMER14_PWM_Init(void)
{
	// 모터펄스(PWM)핀:PF9(TIM14 CH1)
	// Clock Enable : GPIOF & TIMER14
	RCC->AHB1ENR |= (1 << 5);	// GPIOF Enable
	RCC->APB1ENR |= (1 << 8);	// TIMER14 Enable 

// PF13을 출력설정하고 Alternate function(TIM14_CH1)으로 사용 선언 : PWM 출력
	GPIOF->MODER |= (2 << 18);	// PF9 Output Alternate function mode					
	GPIOF->OSPEEDR |= (3 << 18);	// PFP Output speed (100MHz High speed)
	GPIOF->OTYPER &= ~(1 << 9);	// PF9 Output type push-pull (reset state)
	GPIOF->AFR[1] |= (9 << 4); 	// 	(AFR[0].(3~0)=0b0010): Connect AF13
					             

// TIM5 Channel 1 : PWM 1 mode
	// Assign 'PWM Pulse Period'
	TIM14->PSC = 420;	// Prescaler 84,000,000Hz/420 = 200,000 Hz(5us)  (1~65536)
	TIM14->ARR = 80;	// Auto reload  (5us * 80 = 400us : PWM Period)

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

	// 'Mode' Selection : Output mode, PWM 1
	// CCMR1(Capture/Compare Mode Register 1) : Setting the MODE of Ch1 or Ch2
	TIM14->CCMR1 &= ~(3 << 0); 	// CC1S(CC1 channel)='0b00' : Output 
	TIM14->CCMR1 |= (1 << 3); 	// OC1PE=1: Output Compare 1 preload Enable

	TIM14->CCMR1 |= (6 << 4);	// OC1M: Output compare 1 mode: PWM 1 mode
	TIM14->CCMR1 |= (1 << 3);	// OC1CE: Output compare 1 Clear enable

	// CR1 : Up counting & Counter TIM14 enable
	TIM14->CR1 &= ~(1 << 4);	// DIR: Countermode = Upcounter (reset state)
	TIM14->CR1 &= ~(3 << 8);	// CKD: Clock division = 1 (reset state)
	TIM14->CR1 &= ~(3 << 5); 	// CMS(Center-aligned mode Sel): No(reset state)
	TIM14->CR1 |= (1 << 7);	// ARPE: Auto-reload preload enable
	TIM14->CR1 |= (1 << 0);	// CEN: Counter TIM14 enable
}


void EXTI15_10_IRQHandler(void)      // EXTI 15~10 인터럽트 핸들러
{
	if (EXTI->PR & 0x8000)       // EXTI15 nterrupt Pending?   
	{
		EXTI->PR |= 0x8000;    // Pending bit Clear
		if (speed < 50000)   // 스피드가 50000보다 작다면 (5sec)
		{
			speed = speed + 5000; //기존 스피드에 5000을 더해서 0.5sec추가
			displaypoint++;    //디스플레이에 숫자를 표시하기 위한 변수
		}
		else if (speed >= 50000)//스피드가 50000 이상이라면(5sec)
		{
			speed = 5000;  //스피드 리셋
			displaypoint = 0;  //디스플레이 다시 0으로
		}
		TIM1->ARR = (speed - 1);  //ARR변경
		TIM1->CCR3 = (speed - 1); //ARR과 CCR을 같게 하여 동시에 동작하게 하기위함. 
		LCD_DisplayChar(2, 13, displaypoint + 0x30); //디스플레이 표시
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
}

void _EXTI_Init(void)
{
	RCC->AHB1ENR |= 0x0080;   // RCC_AHB1ENR GPIOH Enable
	RCC->APB2ENR |= 0x4000;   // Enable System Configuration Controller Clock

	GPIOH->MODER &= 0x0000FFFF;   // GPIOH PIN8~PIN15 Input mode (reset state)             

	SYSCFG->EXTICR[3] |= 0x7700;         // EXTI15에 대한 소스 입력은 GPIOF로 설정 

	EXTI->FTSR |= 0x00C000;      // Falling Trigger Enable (EXTI15:PH15)
	EXTI->IMR |= 0x00C000;     // EXTI15인터럽트 mask (Interrupt Enable)

	NVIC->ISER[1] |= (1 << (40 - 32));      // Enable Interrupt EXTI,15 Vector table Position 참조
}



void BEEP(void)			// Beep for 20 ms  9번핀을 pwm으로 사용해서 8번핀으로 버퍼를 옮김
{
	GPIOF->ODR |= 0x0100;	// PF8 'H' Buzzer on
	DelayMS(20);		// Delay 20 ms
	GPIOF->ODR &= ~0x0100;	// PF8 'L' Buzzer off
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

void DisplayInitScreen(void)
{
	LCD_Clear(RGB_YELLOW);		// 화면 클리어
	LCD_SetFont(&Gulim8);		// 폰트 : 굴림 8
	LCD_SetBackColor(RGB_BLACK);	// 글자배경색 : 검정
	LCD_SetTextColor(RGB_WHITE);	// 글자색 : 흰색
	LCD_DisplayText(0, 0, "Moter Control");  // Title

	LCD_SetBackColor(RGB_YELLOW);	// 글자배경색 : 노랑
	LCD_SetTextColor(RGB_BLUE);	// 글자색 : 파랑
	LCD_DisplayText(1, 0, "<Step Moter>");
	LCD_DisplayText(3, 0, "<DC Moter>");

	LCD_SetTextColor(RGB_BLACK);	// 글자색 :검정
	LCD_DisplayText(2, 0, "*Speed Level:0");
	LCD_DisplayText(4, 0, "*Torque Level:0");
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

/******************************************************************************/
/*     RCC Set up                                                             */
/******************************************************************************/
void _RCC_Init(void)
{
	// PLL (clocked by HSE) used as System clock source                    

	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;

	// Enable HSE : 외부 입력 클락주파수: 5MHz(회로도 참조)
	RCC->CR |= 0x00010000;	// Set bit#16 of CR

	// Wait till HSE is ready and if Time out is reached exit 
	do
	{
		HSEStatus = RCC->CR & 0x00020000;	// CHECK bit#17 of CR (HSE RDY?) 
		StartUpCounter++;
	} while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CR & 0x00020000) != RESET)	// CHECK bit#17 of CR (HSE RDY?) // RESET is 0
	{
		HSEStatus = 0x01;	// HSE is Ready!
	}
	else
	{
		HSEStatus = 0x00;	// HSE is NOT Ready!
	}

	if (HSEStatus == 0x01)	// HSE clock Enable
	{
		// HCLK = SYSCLK / 1 (HCLK = 168MHz)
		RCC->CFGR |= 0x00000000;

		// PCLK2 = HCLK / 2  (PCLK2 = 84MHz)
		RCC->CFGR |= 0x00008000;	// PPRE2: APB(Advanced Peripheral Bus)(APB2) High-speed prescaler
						// 100: AHB clock divided by 2 

		// PCLK1 = HCLK / 4  (PCLK1 = 42MHz)
		RCC->CFGR |= 0x00001400;	// PPRE1: APB(Advanced Peripheral Bus)(APB1) Low-speed prescaler
						// 101: AHB clock divided by 4 

			// Configure the main PLL 
		// Reset vlaue: 0x2400 3010 (PPLQ:4, PLLSR:0, PLL_M:16, PLL_N:192, PLL_P: 2(00))
		RCC->PLLCFGR = 0;
		RCC->PLLCFGR |= 8;		// PLL_M(6bits): 8(0b001000): /8
		RCC->PLLCFGR |= (336 << 6);	// PLL_N(9bits): 336 : *336
		RCC->PLLCFGR |= (0 << 16);	// PLL_P(2bits): (2 >> 1) -1=0b00 : 2 : /2 
		RCC->PLLCFGR |= 0x00400000; 	// PLL_SR(1bit): 1 : HSE oscillator clock selected as PLL and PLLI2S clock
	//      RCC->PLLCFGR = 0x24405408;
		// SYSCLK 계산 (HSE 입력클럭주파수: 8MHz)
		// SYSCLK = 8M * 336(N) /8(M) /2(P) = 168MHz	

		// Enable the main PLL 
		RCC->CR |= 0x01000000;	// Set bit#24 of CR : PLL ON

		// Wait till the main PLL is ready 
		while ((RCC->CR & 0x02000000) == 0)	// CHECK bit#25 : PLL RDY?  
		{
		}

		// Configure Flash prefetch, Instruction cache, Data cache and wait state 
		FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

		// Select the main PLL as system clock source 
		// Reset value of RCC->CFGR: 0x0000 0000
		RCC->CFGR &= ~0x00000003;	// clear, (Reset value: HSI) 
		RCC->CFGR |= 0x00000002;	// PLL

		// Wait till the main PLL is used as system clock source 
		while ((RCC->CFGR & 0x0000000C) != 0x00000008);	// CHECK bit#2~3 : PLL as system clock is RDY?  
		{}
	}
	else
	{ // If HSE fails to start-up, the application will have wrong clock
		// configuration. User can add here some code to deal with this error 
	}
}