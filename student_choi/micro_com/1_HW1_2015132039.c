//***************************************************
//작성자 : 2015132039 최영운
//작성일 : 2019 / 09 / 18

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
void _EXTI_Init(void);
uint16_t KEY_Scan(void);
void TIMER3_Init(void);   // General-purpose Timer 4 (Output Compare mode)
void TIMER5_Init(void);     //타이머 5에 대한 설정
void DisplayInitScreen(void);

void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);
void BEEP(void);

uint8_t SW1_Flag, SW6_Flag, pm_am = 1;  //스위치와 오전 오후 변수
uint8_t hour_10h = 1, hour_1h = 1, hour_h = 23, hour = 23, min_10m = 5, min_1m = 9, sec_10s = 5, sec_1s = 5, sec_500ms = 0;
uint8_t stop_min_10m = 0, stop_min_1m = 0, stop_sec_10s = 0, stop_sec_1s = 0, stop_sec_100ms = 0;
           //각 시간에 대한 변수 선언


int main(void)
{
	_RCC_Init();
	_GPIO_Init();
	_EXTI_Init();
	LCD_Init();
	DelayMS(10);
	BEEP();
	DisplayInitScreen();   // LCD 초기화면
	GPIOG->ODR &= 0xFF00;   // 초기값: LED0~7 Off

	TIMER3_Init();      // TIM3 Init (Output Compare mode: UI & CCI 발생, )                  
	TIMER5_Init();      //타이머 5 리셋

	GPIOG->ODR |= 0x81;   //LED 0,7 켜기
	while (1)
	{
	}
}

void TIMER3_Init(void)
{
	RCC->APB1ENR |= 0x02;   //RCC_APB1ENR TIMER3 Enable

	NVIC->ISER[0] |= (1 << 29); // Enable Timer3 global Interrupt

	TIM3->PSC = 840 - 1;   // Prescaler 84,000,000Hz/840 = 100,000 Hz (0.01ms)  (1~65536)
	TIM3->ARR = 50000;           // Auto reload  0.01ms * 50000 = 500ms

	TIM3->CR1 |= (1 << 4);   // Downcounter
	TIM3->CR1 &= ~(3 << 8);    // CKD(Clock division)=1(reset state)
	TIM3->CR1 &= ~(3 << 5);    // CMS(Center-aligned mode Sel): No(reset state)

	TIM3->EGR |= (1 << 0);   // Update generation    

	TIM3->DIER |= (1 << 0);   // Enable the Tim3 Update interrupt
	TIM3->CR1 |= (1 << 0);   // Enable the Tim3 Counter    
}

void TIM3_IRQHandler(void)     // 500ms Interrupt
{

	TIM3->SR &= ~(1 << 0);   // Interrupt flag Clear      
	sec_500ms += 5;           //500ms 마다 5씩 상승
	if (sec_500ms >= 10)    //1초가 된다면 
	{
		sec_1s++;           //1초 상승
		sec_500ms = 0;       //500ms는 0으로 초기화
		if (sec_1s >= 10)   //10초가 된다면
		{
			sec_10s++;      //10초 증가
			sec_1s = 0;    //1초는 0으로 초기화
			if (sec_10s >= 6)   //60초가 된다면
			{
				min_1m++;    //1분 증가
				sec_10s = 0;   //10초는 0으로 초기화
				if (min_1m >= 10) //10분이 된다면
				{
					min_10m++;  //10분이 증가
					min_1m = 0;  //10분은 0으로 초기화
					if (min_10m >= 6) //60분이 된다면
					{
						hour_h++;   //1시간 증가
						min_10m = 0;  //60분은 0분으로 초기화
						if (hour_h >= 24)  //hour_h에 시간 저장.  24진수 입력
						{
							hour_h = 0; // 24시간이 될시 0시간으로 초기화
							hour = 0;   //디스플레이할 시간 0으로 초기화
							pm_am = 0;   //오전으로 설정
							LCD_DisplayChar(1, 0, 'A');  //디스플레이 A로 설정
						}
						else if (hour_h >= 12)  //12시이상일시 
						{
							pm_am = 1;   //오후로 설정
							hour = hour_h - 12;  //표시할 시간을 12를 빼준다
							LCD_DisplayChar(1, 0, 'P');  //디스플레이 B로 설정
						}
					}
				}
			}
		}
	}

	switch (hour)
	{
	case 12: hour_10h = 1, hour_1h = 2; break;   //12시간을 디스플레이 하기위한 스위치문
	case 11: hour_10h = 1, hour_1h = 1; break;
	case 10: hour_10h = 1, hour_1h = 0; break;
	case 9: hour_10h = 0, hour_1h = 9; break;
	case 8: hour_10h = 0, hour_1h = 8; break;
	case 7: hour_10h = 0, hour_1h = 7; break;
	case 6: hour_10h = 0, hour_1h = 6; break;
	case 5: hour_10h = 0, hour_1h = 5; break;
	case 4: hour_10h = 0, hour_1h = 4; break;
	case 3: hour_10h = 0, hour_1h = 3; break;
	case 2: hour_10h = 0, hour_1h = 2; break;
	case 1: hour_10h = 0, hour_1h = 1; break;
	case 0: hour_10h = 0, hour_1h = 0; break;
	}

	LCD_DisplayChar(1, 13, sec_500ms + 0x30);  //각 디스플레이에 표시
	LCD_DisplayChar(1, 11, sec_1s + 0x30);
	LCD_DisplayChar(1, 10, sec_10s + 0x30);
	LCD_DisplayChar(1, 8, min_1m + 0x30);
	LCD_DisplayChar(1, 7, min_10m + 0x30);
	LCD_DisplayChar(1, 5, hour_1h + 0x30);
	LCD_DisplayChar(1, 4, hour_10h + 0x30);

}



void TIMER5_Init(void)
{
	// PA3: TIM5_CH4
	// PA3을 출력설정하고 Alternate function(TIM5_CH4)으로 사용 선언
	RCC->AHB1ENR |= (1 << 0);   // 0x01, RCC_AHB1ENR GPIOA Enable 

	GPIOA->MODER |= (2 << 6);   // (MODER.(25,24)=0b10), GPIOA PIN3 Output Alternate function mode                
	GPIOA->OSPEEDR |= (3 << 6);   // (OSPEEDER.(7,6)), GPIOA PIN3 Output speed (100MHz High speed)
	GPIOA->OTYPER &= ~(1 << 3);   // GPIOA PIN3 Output type push-pull (reset state)
	GPIOA->PUPDR |= (1 << 6);    // GPIOA PIN3 Pull-up
	GPIOA->AFR[0] |= (2 << 12);   // (AFR[0]): Connect TIM5 pins(PA3) to AF2(TIM3..5)

 // Timerbase Mode
	RCC->APB1ENR |= (1 << 3);   // 0x08, RCC_APB1ENR TIMER5 Enable

	// Setting CR1 : 0x0000 
	TIM5->CR1 &= ~(1 << 4);   // DIR=0(Up counter)(reset state)
	TIM5->CR1 &= ~(1 << 1);   // UDIS=0(Update event Enabled): By one of following events
			 //   - Counter Overflow/Underflow, 
			 //    - Setting the UG bit Set,
			 //   - Update Generation through the slave mode controller 
	TIM5->CR1 &= ~(1 << 2);   // URS=0(Update event source Selection): one of following events
			 //   - Counter Overflow/Underflow, 
			 //    - Setting the UG bit Set,
			 //   - Update Generation through the slave mode controller 
	TIM5->CR1 &= ~(1 << 3);   // OPM=0(The counter is NOT stopped at update event) (reset state)
	TIM5->CR1 &= ~(1 << 7);   // ARPE=0(ARR is NOT buffered) (reset state)
	TIM5->CR1 &= ~(3 << 8);    // CKD(Clock division)=00(reset state)
	TIM5->CR1 &= ~(3 << 5);    // CMS(Center-aligned mode Sel)=00 (Edge-aligned mode) (reset state)
			 // Center-aligned mode: The counter counts Up and DOWN alternatively

	// Deciding the Period
	TIM5->PSC = 8400 - 1;   // Prescaler=8400, 84MHz/8400 = 10kHz (0.1ms)
	TIM5->ARR = 1000 - 1;   // Auto reload  : 0.1ms * 1K = 100ms(period) : 인터럽트주기나 출력신호의 주기 결정

	// Update(Clear) the Counter
	TIM5->EGR |= (1 << 0);    // UG: Update generation    

	// Setting an UI(UEV) Interrupt 
	NVIC->ISER[1] |= (1 << 50 - 32);   // Enable Timer5 global Interrupt on NVIC
	TIM5->DIER |= (1 << 0);   // UIE: Enable Tim5 Update interrupt

 // Output Compare Mode
	// CCMR1(Capture/Compare Mode Register 1) : Setting the MODE of Ch1 or Ch2
	TIM5->CCMR2 &= ~(3 << 8); // CC4S(CC4 channel) = '0b00' : Output 
	TIM5->CCMR2 &= ~(1 << 10); // OC4FE=0: Output Compare 1 Fast disable 
	TIM5->CCMR2 &= ~(1 << 11); // OC4PE=0: Output Compare 1 preload disable(CCR1에 언제든지 새로운 값을 loading 가능) 
	TIM5->CCMR2 |= (2 << 12);   // OC4M=0b011 (Output Compare 1 Mode : toggle)
			 // OC1REF toggles when CNT = CCR1

	// CCER(Capture/Compare Enable Register) : Enable "Channel 4" 
	TIM5->CCER |= (1 << 12);   // CC4E=1: CC4 channel Output Enable
			 // OC1(TIM5_CH4) Active: 해당핀(100번)을 통해 신호출력
	TIM5->CCER &= ~(1 << 13);   // CC4P=0: CC4channel Output Polarity (OCPolarity_High : OC1으로 반전없이 출력)  

	TIM5->DIER |= (1 << 4);   // CC4IE: Enable the Tim5 CC4 interrupt

	TIM5->CR1 &= ~(1 << 0);   // CEN: Enable the Tim5 Counter                 
}

void TIM5_IRQHandler(void)      //RESET: 0
{
	if ((TIM5->SR & 0x01) != RESET)   // Update interrupt flag (10ms)
	{
		TIM5->SR &= ~(1 << 0);   // Update Interrupt Claer
		LCD_DisplayChar(2, 10, stop_sec_100ms + 0x30);  //STOP WATCH 100MS 디스플레이

		stop_sec_100ms++;  //100ms 증가
		if (stop_sec_100ms >= 10)  // 1초가 될 시
		{
			stop_sec_1s++;   //1초 증가
			stop_sec_100ms = 0;  //100ms는 초기화
			if (stop_sec_1s >= 10)  //10초가 될 시
			{
				stop_sec_10s++;    //10초 증가
				stop_sec_1s = 0;  //10초는 0으로 리셋
				if (stop_sec_10s >= 6)  //60초가 될 시
				{
					stop_min_1m++;   //1분 증가
					stop_sec_10s = 0;   //60초는 0으로 리셋
					if (stop_min_1m >= 10)  //10분이 될시
					{
						stop_min_10m++;   //10분 증가
						stop_min_1m = 0;  //10분은 0으로 리셋
						if (stop_min_10m >= 6) //60분이 될시
						{
							stop_min_10m = 0; //0분으로 리셋
						}
					}
				}
			}
		}
	}
	LCD_DisplayChar(2, 8, stop_sec_1s + 0x30);  //stop watch 디스플레이
	LCD_DisplayChar(2, 7, stop_sec_10s + 0x30);
	LCD_DisplayChar(2, 5, stop_min_1m + 0x30);
	LCD_DisplayChar(2, 4, stop_min_10m + 0x30);
}

void _GPIO_Init(void)
{
	// LED (GPIO G) 설정
	RCC->AHB1ENR |= 0x00000040;   // RCC_AHB1ENR : GPIOG(bit#6) Enable                     
	GPIOG->MODER |= 0x00005555;   // GPIOG 0~7 : Output mode (0b01)                  
	GPIOG->OTYPER &= ~0x00FF;   // GPIOG 0~7 : Push-pull  (GP8~15:reset state)   
	GPIOG->OSPEEDR |= 0x00005555;   // GPIOG 0~7 : Output speed 25MHZ Medium speed 

   // SW (GPIO H) 설정 
	RCC->AHB1ENR |= 0x00000080;   // RCC_AHB1ENR : GPIOH(bit#7) Enable                     
	GPIOH->MODER &= ~0xFFFF0000;   // GPIOH 8~15 : Input mode (reset state)            
	GPIOH->PUPDR &= ~0xFFFF0000;   // GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

	// Buzzer (GPIO F) 설정 
	RCC->AHB1ENR |= 0x00000020; // RCC_AHB1ENR : GPIOF(bit#5) Enable                     
	GPIOF->MODER |= 0x00040000;   // GPIOF 9 : Output mode (0b01)                  
	GPIOF->OTYPER &= ~0x0200;   // GPIOF 9 : Push-pull     
	GPIOF->OSPEEDR |= 0x00040000;   // GPIOF 9 : Output speed 25MHZ Medium speed 
}

void _EXTI_Init(void)
{
	RCC->AHB1ENR |= 0x0080;   // RCC_AHB1ENR GPIOH Enable
	RCC->APB2ENR |= 0x4000;   // Enable System Configuration Controller Clock

	GPIOH->MODER &= 0x0000FFFF;   // GPIOH PIN8~PIN15 Input mode (reset state)             

	SYSCFG->EXTICR[2] |= 0x0077;    // EXTI8,9에 대한 소스 입력은 GPIOH로 설정 (EXTICR3) (reset value: 0x0000)   
	SYSCFG->EXTICR[3] |= 0x7700;         // EXTI14,15에 대한 소스 입력은 GPIOH로 설정 (EXTICR4) (reset value: 0x0000)

	EXTI->FTSR |= 0x00C300;      // Falling Trigger Enable  (EXTI8:PH8)(EXTI9:PH9)(EXTI14:PH14)(EXTI15:PH15)
	EXTI->IMR |= 0x00C300;     // EXTI8,9,14,15인터럽트 mask (Interrupt Enable)

	NVIC->ISER[0] |= (1 << 23);      // Enable Interrupt EXTI8,9 Vector table Position 참조
	NVIC->ISER[1] |= (1 << (40 - 32));      // Enable Interrupt EXTI14,15 Vector table Position 참조
}

void EXTI9_5_IRQHandler(void)      // EXTI 5~9 인터럽트 핸들러
{
	if (EXTI->PR & 0x0100)       // EXTI8 nterrupt Pending?   초기화 시키기
	{
		EXTI->PR |= 0x0100;    // Pending bit Clear
		if (SW1_Flag == 1)   //STOP버튼이 눌렸으면
		{
			GPIOG->ODR |= 0x01;     //LED 0번 ON
			GPIOG->ODR &= ~0x02;    //LED 1번 OFF
			DelayMS(10);
			BEEP();
			sec_500ms = 0;    //모든 현재 시간 초기화
			sec_1s = 0;
			sec_10s = 0;      //00:00:00:0
			min_1m = 0;       //AM
			min_10m = 0;
			hour_1h = 0;
			hour_10h = 0;
			pm_am = 0; 
			SW1_Flag = 0;       //스위치 1번 리셋
			LCD_DisplayChar(1, 0, 'A');
			LCD_DisplayChar(1, 13, sec_500ms + 0x30);  //초기화된 시간 디스플레이
			LCD_DisplayChar(1, 11, sec_1s + 0x30);
			LCD_DisplayChar(1, 10, sec_10s + 0x30);
			LCD_DisplayChar(1, 8, min_1m + 0x30);
			LCD_DisplayChar(1, 7, min_10m + 0x30);
			LCD_DisplayChar(1, 5, hour_1h + 0x30);
			LCD_DisplayChar(1, 4, hour_10h + 0x30);
			TIM3->CR1 |= (1 << 0);  //다시 현재시간 증가 시작   타이머 3 동작시작
		}

	}
	else if (EXTI->PR & 0x0200)    // EXTI9 Interrupt Pending?
	{                            //STOP버튼
		EXTI->PR |= 0x0200;    // Pending bit Clear
		DelayMS(10);
		BEEP();
		if (SW1_Flag == 0)  //안눌려 있었다면
		{
			GPIOG->ODR |= 0x02;   //LED 1번 ON
			GPIOG->ODR &= ~0x01;   // LED 1번 OFF
			SW1_Flag = 1;  
			TIM3->CR1 &= ~(1 << 0); //타이머3 중지
		}
		else if (SW1_Flag == 1) //STOP버튼이 눌려 있었다면
		{
			GPIOG->ODR |= 0x01;   //LED 0번 ON
			GPIOG->ODR &= ~0x02;   // LED 1번 Off
			SW1_Flag = 0;   
			TIM3->CR1 |= (1 << 0); //타이머 3 다시 시작
		}
	}
}
void EXTI15_10_IRQHandler(void)      // EXTI 15~10 인터럽트 핸들러
{
	if (EXTI->PR & 0x8000)       // EXTI15 nterrupt Pending?   STOP_watch리셋버튼이 눌린다면
	{
		DelayMS(10);
		BEEP();
		EXTI->PR |= 0x8000;    // Pending bit Clear
		GPIOG->ODR |= 0x80;    //LED 7번 ON
		GPIOG->ODR &= ~0x40;   //LED 6번 Off
		stop_sec_100ms = 0;   //STOP watch 변수 초기화 0으로
		stop_sec_1s = 0;
		stop_sec_10s = 0;
		stop_min_1m = 0;
		stop_min_10m = 0;
		SW6_Flag = 0;
		LCD_DisplayChar(2, 10, stop_sec_100ms + 0x30);  //stop watch 디스플레이 
		LCD_DisplayChar(2, 8, stop_sec_1s + 0x30);
		LCD_DisplayChar(2, 7, stop_sec_10s + 0x30);
		LCD_DisplayChar(2, 5, stop_min_1m + 0x30);
		LCD_DisplayChar(2, 4, stop_min_10m + 0x30);
		TIM5->CR1 &= ~(1 << 0);  //타이머 5번 중지

	}
	else if (EXTI->PR & 0x4000)    // EXTI14 Interrupt Pending?  stop watch 작동 중지 버튼
	{
		EXTI->PR |= 0x4000;    // Pending bit Clear
		DelayMS(10);
		BEEP();
		if (SW6_Flag == 0) //stop watch 중단상태 였을 시
		{
			SW6_Flag = 1;
			GPIOG->ODR |= 0x40;   //LED6 On
			GPIOG->ODR &= ~0x80;   //LED7 Off
			TIM5->CR1 |= (1 << 0); //타이머 5번 작동 시작
		}
		else if (SW6_Flag == 1) //stop watch 실행 상태 였을시
		{
			SW6_Flag = 0;
			GPIOG->ODR |= 0x80;   //LED7 On
			GPIOG->ODR &= ~0x40;   //LED6 Off
			TIM5->CR1 &= ~(1 << 0);  //타이머5번 작동 중단 
		}


	}
}
void BEEP(void)         // Beep for 20 ms 
{
	GPIOF->ODR |= 0x0200;   // PF9 'H' Buzzer on
	DelayMS(20);      // Delay 20 ms
	GPIOF->ODR &= ~0x0200;   // PF9 'L' Buzzer off
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
	LCD_Clear(RGB_YELLOW);      // 화면 클리어
	LCD_SetFont(&Gulim8);      // 폰트 : 굴림 8
	LCD_SetBackColor(RGB_YELLOW);   // 글자배경색 : Green
	LCD_SetTextColor(RGB_BLACK);   // 글자색 : Black

	LCD_DisplayText(0, 0, "Digital Clock");  // Title

	LCD_DisplayChar(1, 0, 'P');   //초기 디스플래이 작동
	LCD_DisplayChar(1, 1, 'M');
	LCD_DisplayChar(1, 6, ':');
	LCD_DisplayChar(1, 9, ':');
	LCD_DisplayChar(1, 12, ':');
	LCD_DisplayChar(2, 0, 'S');
	LCD_DisplayChar(2, 1, 'W');
	LCD_DisplayChar(2, 6, ':');
	LCD_DisplayChar(2, 9, ':');


}

uint8_t key_flag = 0;
uint16_t KEY_Scan(void)   // input key SW0 - SW7 
{
	uint16_t key;
	key = GPIOH->IDR & 0xFF00;   // any key pressed ?
	if (key == 0xFF00)      // if no key, check key off
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
	else            // if key input, check continuous key
	{
		if (key_flag != 0)   // if continuous key, treat as no key input
			return 0xFF00;
		else         // if new key,delay for debounce
		{
			key_flag = 1;
			DelayMS(10);
			return key;
		}
	}
}

void _RCC_Init(void)
{
	// PLL (clocked by HSE) used as System clock source                    

	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;

	// Enable HSE : 외부 입력 클락주파수: 5MHz(회로도 참조)
	RCC->CR |= 0x00010000;   // Set bit#16 of CR

	// Wait till HSE is ready and if Time out is reached exit 
	do
	{
		HSEStatus = RCC->CR & 0x00020000;   // CHECK bit#17 of CR (HSE RDY?) 
		StartUpCounter++;
	} while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CR & 0x00020000) != RESET)   // CHECK bit#17 of CR (HSE RDY?) // RESET is 0
	{
		HSEStatus = 0x01;   // HSE is Ready!
	}
	else
	{
		HSEStatus = 0x00;   // HSE is NOT Ready!
	}

	if (HSEStatus == 0x01)   // HSE clock Enable
	{
		// HCLK = SYSCLK / 1 (HCLK = 168MHz)
		RCC->CFGR |= 0x00000000;

		// PCLK2 = HCLK / 2  (PCLK2 = 84MHz)
		RCC->CFGR |= 0x00008000;   // PPRE2: APB(Advanced Peripheral Bus)(APB2) High-speed prescaler
					// 100: AHB clock divided by 2 

		// PCLK1 = HCLK / 4  (PCLK1 = 42MHz)
		RCC->CFGR |= 0x00001400;   // PPRE1: APB(Advanced Peripheral Bus)(APB1) Low-speed prescaler
					// 101: AHB clock divided by 4 

			// Configure the main PLL 
		// Reset vlaue: 0x2400 3010 (PPLQ:4, PLLSR:0, PLL_M:16, PLL_N:192, PLL_P: 2(00))
		RCC->PLLCFGR = 0;
		RCC->PLLCFGR |= 8;      // PLL_M(6bits): 8(0b001000): /8
		RCC->PLLCFGR |= (336 << 6);   // PLL_N(9bits): 336 : *336
		RCC->PLLCFGR |= (0 << 16);   // PLL_P(2bits): (2 >> 1) -1=0b00 : 2 : /2 
		RCC->PLLCFGR |= 0x00400000;    // PLL_SR(1bit): 1 : HSE oscillator clock selected as PLL and PLLI2S clock
	 //      RCC->PLLCFGR = 0x24405408;
		// SYSCLK 계산 (HSE 입력클럭주파수: 8MHz)
		// SYSCLK = 8M * 336(N) /8(M) /2(P) = 168MHz   

		// Enable the main PLL 
		RCC->CR |= 0x01000000;   // Set bit#24 of CR : PLL ON

		// Wait till the main PLL is ready 
		while ((RCC->CR & 0x02000000) == 0)   // CHECK bit#25 : PLL RDY?  
		{
		}

		// Configure Flash prefetch, Instruction cache, Data cache and wait state 
		FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

		// Select the main PLL as system clock source 
		// Reset value of RCC->CFGR: 0x0000 0000
		RCC->CFGR &= ~0x00000003;   // clear, (Reset value: HSI) 
		RCC->CFGR |= 0x00000002;   // PLL

		// Wait till the main PLL is used as system clock source 
		while ((RCC->CFGR & 0x0000000C) != 0x00000008);   // CHECK bit#2~3 : PLL as system clock is RDY?  
		{}
	}
	else
	{ // If HSE fails to start-up, the application will have wrong clock
		// configuration. User can add here some code to deal with this error 
	}
}
