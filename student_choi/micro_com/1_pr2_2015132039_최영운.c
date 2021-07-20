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

void _ADC_Init(void);

void TIMER3_Init(void);     //타이머 3 
void TIMER2_PWM_Init(void);   //타이머 2


void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);
void BEEP(void);



uint16_t KEY_Scan(void);
uint16_t ADC_Value;  //저항값 저장 변수
uint8_t str[20];      //문자 저장 공간

int mode = 0;  // 입력모드 실행모드 선택 변수
int selmode = 0;     //입력모드에서 TE, PR, O2 ,DR을 선택하기 위한 변수
int start = 0;     //시작모드 선택 변수
int stack = 0;     //FRAM에 저장을 하기위한 변수

int te, pr, o2, dr;  //각 항목을 저장하기 위한 변수
int timer = 0;   //타이머 시간을 결정하는 변수
int sw6 = 0;        // 실행완료 후 확실하게 종료해주기 위해 선언하는 변수


int main(void)
{
	LCD_Init();	// LCD 구동 함수
	DelayMS(10);	// LCD구동 딜레이
	DisplayTitle();	//LCD 초기화면구동 함수

	_GPIO_Init();   //입출력 초기화

	TIMER3_Init();    //타이머 3 초기화
	TIMER2_PWM_Init();     //타이머 2 초기화

	_ADC_Init();     //ADC초기화

	Fram_Init();        // FRAM 초기화 
	Fram_Status_Config();

	GPIOG->ODR &= ~(0xFF);   //LED ALL OFF

	GPIOG->ODR |= 0x01;  //LED 0  ON

	te = Fram_Read(1203);   //저장된 값을 변수에 쓰기
	pr = Fram_Read(1204);
	o2 = Fram_Read(1205);
	dr = Fram_Read(1206);
	LCD_SetTextColor(RGB_RED);
	LCD_DisplayChar(2, 5, te / 10 + 0x30);  //저장되어 있던 값 화면에 표시하기.
	LCD_DisplayChar(2, 7, te % 10 + 0x30);
	LCD_DisplayChar(3, 5, pr / 10 + 0x30);
	LCD_DisplayChar(3, 7, pr % 10 + 0x30);
	LCD_DisplayChar(4, 5, o2 / 10 + 0x30);
	LCD_DisplayChar(4, 7, o2 % 10 + 0x30);
	LCD_DisplayChar(5, 5, dr + 0x30);

	while (1)
	{


		switch (KEY_Scan())
		{
		case SW4_PUSH: 		//SW4
                  
                       if(selmode > 0) // 세부 선택 모드시라면.
                       {
			stack = 1;    //저장버튼 누를시 작동
                       }

			break;

		case SW5_PUSH: 		//SW5


			if (mode == 0)      //모드 변경 항목. 입력모드였다면 -> 실행모드
			{
				if (start == 0)   // 시작신호가 없어야 작동한다.
				{
					mode = 1;          // 실행모드
					GPIOG->ODR &= ~(0x01); //LED0 OFF
 					GPIOG->ODR |= (0x02);   //LED1 ON
					LCD_DisplayText(1, 5, "R"); 
				}
			}
			else if (mode == 1)    //모드 변경   실행모드 -> 입력모드
			{
				mode = 0;          // 입력모드
				sw6 = 0;           //실행모드 종료시 발생하는 시그널 초기화
				GPIOG->ODR |= 0x01;    //LED 0 ON
				GPIOG->ODR &= ~(0x02);   //LED1 OFF
				LCD_DisplayText(1, 5, "I");
			}
			break;

		case SW6_PUSH: 		//SW6



			if (start == 0)    //시작상태가 아니었다면
			{
				if (sw6 == 1)    //실행 종료 직후라면
				{
					sw6 = 0;       //초기화
					start = 0; 
				}
				else  //실행 종료 후가 아니라면
				{
					start = 1;           //시작
					GPIOG->ODR |= 0x04;   //LED3 ON
					te = Fram_Read(1203);      //저장된 데이터 읽어오기
					pr = Fram_Read(1204);
					o2 = Fram_Read(1205);
					dr = Fram_Read(1206);
					LCD_SetTextColor(RGB_RED);
					LCD_DisplayChar(2, 5, te / 10 + 0x30);//저장된 데이터 화면에 출력
					LCD_DisplayChar(2, 7, te % 10 + 0x30);
					LCD_DisplayChar(3, 5, pr / 10 + 0x30);
					LCD_DisplayChar(3, 7, pr % 10 + 0x30);
					LCD_DisplayChar(4, 5, o2 / 10 + 0x30);
					LCD_DisplayChar(4, 7, o2 % 10 + 0x30);
					LCD_DisplayChar(5, 5, dr + 0x30);

				}
			}
			else if (start == 1)   //시작 상태였다면
			{
				start = 0;              //시작 종료
				GPIOG->ODR &= ~(0x04);   //LED 2,3,4,5,6 OFF
				GPIOG->ODR &= ~(0x08);
				GPIOG->ODR &= ~(0x10);
				GPIOG->ODR &= ~(0x20);
				GPIOG->ODR &= ~(0x40);
				selmode = 0;              //선택창 초기화
				LCD_DisplayText(2, 0, " ");
				LCD_DisplayText(3, 0, " ");
				LCD_DisplayText(4, 0, " ");
				LCD_DisplayText(5, 0, " ");
                                te = Fram_Read(1203);      //저장된 데이터 읽어오기
				pr = Fram_Read(1204);
				o2 = Fram_Read(1205);
				dr = Fram_Read(1206);
                                LCD_DisplayChar(2, 5, te / 10 + 0x30);//저장된 데이터 화면에 출력
				LCD_DisplayChar(2, 7, te % 10 + 0x30);
				LCD_DisplayChar(3, 5, pr / 10 + 0x30);
				LCD_DisplayChar(3, 7, pr % 10 + 0x30);
				LCD_DisplayChar(4, 5, o2 / 10 + 0x30);
				LCD_DisplayChar(4, 7, o2 % 10 + 0x30);
				LCD_DisplayChar(5, 5, dr + 0x30);



			}

			break;

		case SW7_PUSH: 		//SW7
			if (start == 1)    //시작상태였다면
			{
				if (selmode < 4)   //TE->PR->O2->DR->TE순으로 변경
				{
					selmode++;
				}
				else
				{
					selmode = 1;
				}

			}
			break;



		}
		if (selmode > 0) //세부 선택 모드였다면 ADC1시작
		{
			ADC1->CR2 |= ADC_CR2_SWSTART;  //ADC1 시작
		}

		if (mode == 0)   //입력모드라면
		{
			if (start == 1)  //시작상태라면
			{


				if (selmode == 1) //TE선택 모드라면
				{
					LCD_SetTextColor(RGB_BLACK);
					LCD_DisplayText(2, 0, "*");
					LCD_DisplayText(3, 0, " ");
					LCD_DisplayText(4, 0, " ");
					LCD_DisplayText(5, 0, " ");
					GPIOG->ODR &= ~(0x40);
					GPIOG->ODR |= 0x08;


					if (ADC_Value >= 877)  //읽어온 값을 7등분하여 알맞게 배정함.
					{
						te = 40;
					}
					else if (ADC_Value >= 730)
					{
						te = 35;
					}
					else if (ADC_Value >= 584)
					{
						te = 30;
					}
					else if (ADC_Value >= 439)
					{
						te = 25;
					}
					else if (ADC_Value >= 292)
					{
						te = 20;
					}
					else if (ADC_Value >= 146)
					{
						te = 15;
					}
					else
					{
						te = 10;
					}
					LCD_SetTextColor(RGB_RED);     //읽은 값을 화면에 표시
					LCD_DisplayChar(2, 5, te / 10 + 0x30);
					LCD_DisplayChar(2, 7, te % 10 + 0x30);

					if (stack == 1) //저장신호가 온다면
					{
						Fram_Write(1203, te);  //1203번지에 저장
						stack = 0;
					}
				}

				if (selmode == 2)  //PR상태라면
				{
					LCD_SetTextColor(RGB_BLACK);
					LCD_DisplayText(2, 0, " ");
					LCD_DisplayText(3, 0, "*");
					LCD_DisplayText(4, 0, " ");
					LCD_DisplayText(5, 0, " ");
					GPIOG->ODR &= ~(0x08);
					GPIOG->ODR |= 0x10;

					if (ADC_Value >= 877)  //7등분하여 배분
					{
						pr = 35;
					}
					else if (ADC_Value >= 730)
					{
						pr = 30;
					}
					else if (ADC_Value >= 584)
					{
						pr = 25;
					}
					else if (ADC_Value >= 439)
					{
						pr = 20;
					}
					else if (ADC_Value >= 292)
					{
						pr = 15;
					}
					else if (ADC_Value >= 146)
					{
						pr = 10;
					}
					else
					{
						pr = 5;
					}
					LCD_SetTextColor(RGB_RED);
					LCD_DisplayChar(3, 5, pr / 10 + 0x30);
					LCD_DisplayChar(3, 7, pr % 10 + 0x30);

					if (stack == 1) //저장신호시
					{
						Fram_Write(1204, pr); //1204번지에 저장
						stack = 0;
					}
				}

				if (selmode == 3)  //O2세부선택 상태라면
				{
					LCD_SetTextColor(RGB_BLACK);
					LCD_DisplayText(2, 0, " ");
					LCD_DisplayText(3, 0, " ");
					LCD_DisplayText(4, 0, "*");
					LCD_DisplayText(5, 0, " ");

					GPIOG->ODR &= ~(0x10);
					GPIOG->ODR |= 0x20;


					if (ADC_Value >= 877) //7등분으로 배분
					{
						o2 = 30;
					}
					else if (ADC_Value >= 730)
					{
						o2 = 25;
					}
					else if (ADC_Value >= 584)
					{
						o2 = 20;
					}
					else if (ADC_Value >= 439)
					{
						o2 = 15;
					}
					else if (ADC_Value >= 292)
					{
						o2 = 10;
					}
					else if (ADC_Value >= 146)
					{
						o2 = 5;
					}
					else
					{
						o2 = 0;
					}
					LCD_SetTextColor(RGB_RED);
					LCD_DisplayChar(4, 5, o2 / 10 + 0x30);
					LCD_DisplayChar(4, 7, o2 % 10 + 0x30);

					if (stack == 1)    //저장신호시
					{
						Fram_Write(1205, o2);  //1205번지에 저장
						stack = 0;
					}
				}

				if (selmode == 4)  //DR세부선택 모드시
				{
					LCD_SetTextColor(RGB_BLACK);
					LCD_DisplayText(2, 0, " ");
					LCD_DisplayText(3, 0, " ");
					LCD_DisplayText(4, 0, " ");
					LCD_DisplayText(5, 0, "*");

					GPIOG->ODR &= ~(0x20);
					GPIOG->ODR |= 0x40;

					if (ADC_Value >= 920)  //10등분하여 저장
					{
						dr = 9;
					}
					else if (ADC_Value >= 818)
					{
						dr = 8;
					}
					else if (ADC_Value >= 716)
					{
						dr = 7;
					}
					else if (ADC_Value >= 613)
					{
						dr = 6;
					}
					else if (ADC_Value >= 511)
					{
						dr = 5;
					}
					else if (ADC_Value >= 409)
					{
						dr = 4;
					}
					else if (ADC_Value >= 307)
					{
						dr = 3;
					}
					else if (ADC_Value >= 204)
					{
						dr = 2;
					}
					else if (ADC_Value >= 102)
					{
						dr = 1;
					}
					else
					{
						dr = 0;
					}
					LCD_SetTextColor(RGB_RED);
					LCD_DisplayChar(5, 5, dr + 0x30);
					if (stack == 1)  //저장신호 선택시
					{
						Fram_Write(1206, dr);  //1206번지에 저장
						stack = 0;
					}
				}

			}

		}

		else if (mode == 1) //실행모드
		{
			if (start == 1)  //시작시
			{

				LCD_SetTextColor(RGB_RED);
				LCD_DisplayText(1, 15, "W");
				GPIOG->ODR |= (0x10);

				DelayMS(500);
				LCD_SetTextColor(RGB_BLACK);
				LCD_DisplayText(2, 0, "*");
				TIM3->CR1 |= (1 << 0);   //타이머 작동 시작.
				LCD_SetTextColor(RGB_RED);
				timer = 0;//타이머 0
				te = Fram_Read(1203);//값을 다시 읽어옴
				while (timer <= te) //TE시간까지 타이머 동작
				{
					if (timer > te) //혹시while문에서 오작동할까봐 방지.
					{
						break;
					}
					LCD_DisplayChar(2, 11, timer / 10 + 0x30);
					LCD_DisplayChar(2, 13, timer % 10 + 0x30); //타이머 시간 출력
				}
				LCD_SetTextColor(RGB_BLACK);
				LCD_DisplayText(2, 0, " ");
				GPIOG->ODR &= ~(0x10);


				LCD_DisplayText(3, 0, "*");
				GPIOG->ODR |= (0x20);
				timer = 0;
				pr = Fram_Read(1204);  //
				LCD_SetTextColor(RGB_RED);
	
				while (timer <= pr)// PR시간까지 타이머 작동 시작
				{
					if (timer > pr)//오작동 방지 루프
					{
						break;
					}
					LCD_DisplayChar(3, 11, timer / 10 + 0x30);  //타이머 시간 출력
					LCD_DisplayChar(3, 13, timer % 10 + 0x30);
				}
				LCD_SetTextColor(RGB_BLACK);
				LCD_DisplayText(3, 0, " ");
				GPIOG->ODR &= ~(0x20);

				LCD_DisplayText(4, 0, "*");
				GPIOG->ODR |= (0x40);
				LCD_DisplayText(5, 0, "*");
				GPIOG->ODR |= (0x80);
				timer = 0;
				o2 = Fram_Read(1205);  //데이터 읽어오기
				LCD_SetTextColor(RGB_RED);
				dr = Fram_Read(1206);  //데이터 읽어오기
				if (dr == 9) //DR값에 따라 타이머 2 PWM  조정
				{
					TIM2->CCR3 = 18000;
				}
				else if (dr == 8)
				{
					TIM2->CCR3 = 16000;
				}
				else if (dr == 7)
				{
					TIM2->CCR3 = 14000;
				}
				else if (dr == 6)
				{
					TIM2->CCR3 = 12000;
				}
				else if (dr == 5)
				{
					TIM2->CCR3 = 10000;
				}
				else if (dr == 4)
				{
					TIM2->CCR3 = 8000;
				}
				else if (dr == 3)
				{
					TIM2->CCR3 = 6000;
				}
				else if (dr == 2)
				{
					TIM2->CCR3 = 4000;
				}
				else if (dr == 1)
				{
					TIM2->CCR3 = 2000;
				}
				else
				{
					TIM2->CCR3 = 0;
				}
				TIM2->CR1 |= (1 << 0);
				while (timer <= o2) //O2시간까지 타이머 동작
				{
					if (timer > o2)//오작동 방지 루프
					{
						break;
					}
					LCD_DisplayChar(4, 11, timer / 10 + 0x30);  //화면에 시간 출력
					LCD_DisplayChar(4, 13, timer % 10 + 0x30);
				}
				TIM2->CR1 &= ~(1 << 0);   //타이머 2 작동 중지
				LCD_DisplayChar(5, 5, 0x30);

				LCD_SetTextColor(RGB_BLACK);
				LCD_DisplayText(4, 0, " ");
				LCD_DisplayText(5, 0, " ");
				GPIOG->ODR &= ~(0x40);
				GPIOG->ODR &= ~(0x80);

				DelayMS(500);
				LCD_SetTextColor(RGB_RED);
				LCD_DisplayText(1, 15, "E");
				GPIOG->ODR &= ~(0x04);
				TIM3->CR1 &= ~(1 << 0);   //타이머 작동 종료
				start = 0;  //실행 종료
				sw6 = 1;   //종료 시그널 
			}


		}

	}
}

void _ADC_Init(void)
{   	// ADC1: PA1(pin 41)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	// (1<<0) ENABLE GPIOA CLK (stm32f4xx.h 참조)
	GPIOA->MODER |= (3 << 2 * 1);		// CONFIG GPIOA PIN1(PA1) TO ANALOG IN MODE

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;	// (1<<8) ENABLE ADC1 CLK (stm32f4xx.h 참조)

	ADC->CCR &= ~(0X1F << 0);		// MULTI[4:0]: ADC_Mode_Independent
	ADC->CCR |= (1 << 16); 		// 0x00010000 ADCPRE:ADC_Prescaler_Div4 (ADC MAX Clock 36MHz, 84Mhz(APB2)/4 = 21MHz)

	ADC1->CR1 |= (1 << 24);		// RES[1:0]=      : 10bit Resolution
	ADC1->CR1 &= ~(1 << 8);		// SCAN=0 : ADC_ScanCovMode Disable
	ADC1->CR1 |= (1 << 5);		// EOCIE=1: Interrupt enable for EOC

	ADC1->CR2 &= ~(1 << 1);		// CONT=0: ADC_Continuous ConvMode Disable
	ADC1->CR2 |= (2 << 28);		// EXTEN[1:0]: ADC_ExternalTrigConvEdge_Enable(Falling Edge)
	ADC1->CR2 &= ~(1 << 11);		// ALIGN=0: ADC_DataAlign_Right
	ADC1->CR2 &= ~(1 << 10);		// EOCS=0: The EOC bit is set at the end of each sequence of regular conversions

	ADC1->SQR1 &= ~(0xF << 20);	// L[3:0]=0b0000: ADC Regular channel sequece length 
					// 0b0000:1 conversion)
	//Channel selection, The Conversion Sequence of PIN1(ADC1_CH1) is first, Config sequence Range is possible from 0 to 17
	ADC1->SQR3 |= (1 << 0);		// SQ1[4:0]=0b0001 : CH1
	ADC1->SMPR2 |= (0x7 << (3 * 1));	// ADC1_CH1 Sample TIme_480Cycles (3*Channel_1)
//Channel selection, The Conversion Sequence of PIN1(ADC1_CH1) is first, Config sequence Range is possible from 0 to 17

	NVIC->ISER[0] |= (1 << 18);	// Enable ADC global Interrupt

	ADC1->CR2 |= (1 << 0);		// ADON: ADC ON
}

void ADC_IRQHandler(void)
{

	ADC1->SR &= ~(1 << 1);		// EOC flag clear

	ADC_Value = ADC1->DR;		// Reading ADC result

}

void TIMER3_Init(void)   //범용 타이머  16bit 카운터.  
{
	RCC->APB1ENR |= 0x02;	//RCC_APB1ENR TIMER3 Enable   타이머 3를  EN      RCC 파일 참조.

	NVIC->ISER[0] |= (1 << 29); // Enable Timer3 global Interrupt     
		//  인터럽트 백터 테이블 참조.      29번 인터럽트 이므로    32보다 작기때문에  ISER[0] 이다.

	TIM3->PSC = 8400 - 1;	// Prescaler 84,000,000Hz/8400 = 10,000 Hz (0.1ms)  (1~65536)
	TIM3->ARR = 1000 - 1;	        // Auto reload  0.1ms * 1000 = 100ms  즉  0.1s마다 인터럽트 발생하게 만든다.
		// 

		//CR레지스터 다 0으로 만든다.  안해도  가능하지만  리셋의미에서 해놓은 것이다.
		//타이머 레지스터 파일 참조.

	TIM3->CR1 &= ~(1 << 4);	// Upcounter(reset state)   0이  UP카운터,  1이 DOWN 카운터
	TIM3->CR1 &= ~(3 << 8); 	// CKD(Clock division)=1(reset state)     8번과 9번 bit  를 0으로   내부클럭모드.
	TIM3->CR1 &= ~(3 << 5); 	// CMS(Center-aligned mode Sel): No(reset state)    5번과 6번 을  안쓴다.  엣지 모드

	TIM3->EGR |= (1 << 0);	// Update generation    over or under flow를  이밴트로 사용 하겠다고 선언 .. 0번 비트를 1로 했다.  필수

	TIM3->DIER |= (1 << 0);	// Enable the Tim3 Update interrupt  인터럽트를 쓰겠다.  0번 비트를 1로 선언
}

void TIM3_IRQHandler(void)  	// 1ms Interrupt    
{
	TIM3->SR &= ~(1 << 0);	// Interrupt flag Clear   FLOW발생시 1이 되는 레지스터 이므로  다시 0으로 만들어 준다.

	timer++;

}

void TIMER2_PWM_Init(void)
{
	// Clock Enable : GPIOB & TIMER2
	RCC->AHB1ENR |= (1 << 1);	// GPIOB Enable
	RCC->APB1ENR |= (1 << 0);	// TIMER2 Enable 

// PB10을 출력설정하고 Alternate function(TIM2_CH3)으로 사용 선언 : PWM 출력
	GPIOB->MODER |= (2 << 20);	// PB11 Output Alternate function mode					
	GPIOB->OSPEEDR |= (3 << 20);	// PB11 Output speed (100MHz High speed)
	GPIOB->OTYPER &= ~(1 << 10);	// PB11 Output type push-pull (reset state)
	GPIOB->AFR[1] |= (1 << 8); 	// 0x00000002	(AFR[0].(3~0)=0b0010): PB11 = AFR[1]
// TIM2 Channel 4 : PWM 1 mode
	// Assign 'PWM Pulse Period'
	TIM2->PSC = 8400 - 1;	// Prescaler 84,000,000Hz/8400 = 10,000 Hz(0.1ms)  (1~65536)
	TIM2->ARR = 20000 - 1;	// Auto reload  (0.1ms * 20000 = 2s : PWM Period)

	// Define the corresponding pin by 'Output'  
	// CCER(Capture/Compare Enable Register) : Enable "Channel 1" 
	TIM2->CCER |= (1 << 8);	// CC4E=1: OC4(TIM2_CH4) Active(Capture/Compare 1 output enable)
				// 해당핀(40번)을 통해 신호출력
	TIM2->CCER &= ~(1 << 9);	// CC4P=0: CC4 output Polarity High (OC4으로 반전없이 출력)

	// Duty Ratio 
	TIM2->CCR3 = 0;		// CCR4 value

	// 'Mode' Selection : Output mode, PWM 1
	// CCMR1(Capture/Compare Mode Register 1) : Setting the MODE of Ch1 or Ch2
	TIM2->CCMR2 &= ~(3 << 0); 	// CC4S(CC4 channel)='0b00' : Output 
	TIM2->CCMR2 |= (1 << 2); 	// OC4PE=1: Output Compare 1 preload Enable

	TIM2->CCMR2 |= (6 << 4);	// OC4M: Output compare 1 mode: PWM 1 mode

	// CR1 : Up counting & Counter TIM2 enable
	TIM2->CR1 &= ~(1 << 4);	// DIR: Countermode = Upcounter (reset state)
	TIM2->CR1 &= ~(3 << 8);	// CKD: Clock division = 1 (reset state)
	TIM2->CR1 &= ~(3 << 5); 	// CMS(Center-aligned mode Sel): No(reset state)
	TIM2->CR1 |= (1 << 7);	// ARPE: Auto-reload preload enable
	//시작신호 제거. 
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
	LCD_SetTextColor(RGB_BLUE);	//글자색
	LCD_DisplayText(0, 0, "SPC monitor");      //초기화면 설

	LCD_SetTextColor(RGB_BLACK);	//글자색
	LCD_DisplayText(1, 0, "Mode:");
	LCD_DisplayText(1, 9, "Wafer:");

	LCD_DisplayText(2, 1, "TE:");
	LCD_DisplayText(2, 8, "s");

	LCD_DisplayText(3, 1, "PR:");
	LCD_DisplayText(3, 8, "s");

	LCD_DisplayText(4, 1, "O2:");
	LCD_DisplayText(4, 8, "s");

	LCD_DisplayText(5, 1, "DR:");

	LCD_DisplayText(2, 14, "s");
	LCD_DisplayText(3, 14, "s");
	LCD_DisplayText(4, 14, "s");

	LCD_SetTextColor(RGB_RED);	//글자색
	LCD_DisplayText(1, 5, "I");
	LCD_DisplayText(1, 15, "E");
	LCD_DisplayText(2, 5, "1.0");
	LCD_DisplayText(3, 5, "0.5");
	LCD_DisplayText(4, 5, "0.0");
	LCD_DisplayText(5, 5, "1");

	LCD_DisplayText(2, 11, "0.0");
	LCD_DisplayText(3, 11, "0.0");
	LCD_DisplayText(4, 11, "0.0");

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