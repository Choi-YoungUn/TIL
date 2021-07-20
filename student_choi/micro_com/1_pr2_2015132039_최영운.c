//***************************************************
//�ۼ��� : 2015132039 �ֿ���
//�ۼ��� : 2019 / 12 / 03
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

void TIMER3_Init(void);     //Ÿ�̸� 3 
void TIMER2_PWM_Init(void);   //Ÿ�̸� 2


void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);
void BEEP(void);



uint16_t KEY_Scan(void);
uint16_t ADC_Value;  //���װ� ���� ����
uint8_t str[20];      //���� ���� ����

int mode = 0;  // �Է¸�� ������ ���� ����
int selmode = 0;     //�Է¸�忡�� TE, PR, O2 ,DR�� �����ϱ� ���� ����
int start = 0;     //���۸�� ���� ����
int stack = 0;     //FRAM�� ������ �ϱ����� ����

int te, pr, o2, dr;  //�� �׸��� �����ϱ� ���� ����
int timer = 0;   //Ÿ�̸� �ð��� �����ϴ� ����
int sw6 = 0;        // ����Ϸ� �� Ȯ���ϰ� �������ֱ� ���� �����ϴ� ����


int main(void)
{
	LCD_Init();	// LCD ���� �Լ�
	DelayMS(10);	// LCD���� ������
	DisplayTitle();	//LCD �ʱ�ȭ�鱸�� �Լ�

	_GPIO_Init();   //����� �ʱ�ȭ

	TIMER3_Init();    //Ÿ�̸� 3 �ʱ�ȭ
	TIMER2_PWM_Init();     //Ÿ�̸� 2 �ʱ�ȭ

	_ADC_Init();     //ADC�ʱ�ȭ

	Fram_Init();        // FRAM �ʱ�ȭ 
	Fram_Status_Config();

	GPIOG->ODR &= ~(0xFF);   //LED ALL OFF

	GPIOG->ODR |= 0x01;  //LED 0  ON

	te = Fram_Read(1203);   //����� ���� ������ ����
	pr = Fram_Read(1204);
	o2 = Fram_Read(1205);
	dr = Fram_Read(1206);
	LCD_SetTextColor(RGB_RED);
	LCD_DisplayChar(2, 5, te / 10 + 0x30);  //����Ǿ� �ִ� �� ȭ�鿡 ǥ���ϱ�.
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
                  
                       if(selmode > 0) // ���� ���� ���ö��.
                       {
			stack = 1;    //�����ư ������ �۵�
                       }

			break;

		case SW5_PUSH: 		//SW5


			if (mode == 0)      //��� ���� �׸�. �Է¸�忴�ٸ� -> ������
			{
				if (start == 0)   // ���۽�ȣ�� ����� �۵��Ѵ�.
				{
					mode = 1;          // ������
					GPIOG->ODR &= ~(0x01); //LED0 OFF
 					GPIOG->ODR |= (0x02);   //LED1 ON
					LCD_DisplayText(1, 5, "R"); 
				}
			}
			else if (mode == 1)    //��� ����   ������ -> �Է¸��
			{
				mode = 0;          // �Է¸��
				sw6 = 0;           //������ ����� �߻��ϴ� �ñ׳� �ʱ�ȭ
				GPIOG->ODR |= 0x01;    //LED 0 ON
				GPIOG->ODR &= ~(0x02);   //LED1 OFF
				LCD_DisplayText(1, 5, "I");
			}
			break;

		case SW6_PUSH: 		//SW6



			if (start == 0)    //���ۻ��°� �ƴϾ��ٸ�
			{
				if (sw6 == 1)    //���� ���� ���Ķ��
				{
					sw6 = 0;       //�ʱ�ȭ
					start = 0; 
				}
				else  //���� ���� �İ� �ƴ϶��
				{
					start = 1;           //����
					GPIOG->ODR |= 0x04;   //LED3 ON
					te = Fram_Read(1203);      //����� ������ �о����
					pr = Fram_Read(1204);
					o2 = Fram_Read(1205);
					dr = Fram_Read(1206);
					LCD_SetTextColor(RGB_RED);
					LCD_DisplayChar(2, 5, te / 10 + 0x30);//����� ������ ȭ�鿡 ���
					LCD_DisplayChar(2, 7, te % 10 + 0x30);
					LCD_DisplayChar(3, 5, pr / 10 + 0x30);
					LCD_DisplayChar(3, 7, pr % 10 + 0x30);
					LCD_DisplayChar(4, 5, o2 / 10 + 0x30);
					LCD_DisplayChar(4, 7, o2 % 10 + 0x30);
					LCD_DisplayChar(5, 5, dr + 0x30);

				}
			}
			else if (start == 1)   //���� ���¿��ٸ�
			{
				start = 0;              //���� ����
				GPIOG->ODR &= ~(0x04);   //LED 2,3,4,5,6 OFF
				GPIOG->ODR &= ~(0x08);
				GPIOG->ODR &= ~(0x10);
				GPIOG->ODR &= ~(0x20);
				GPIOG->ODR &= ~(0x40);
				selmode = 0;              //����â �ʱ�ȭ
				LCD_DisplayText(2, 0, " ");
				LCD_DisplayText(3, 0, " ");
				LCD_DisplayText(4, 0, " ");
				LCD_DisplayText(5, 0, " ");
                                te = Fram_Read(1203);      //����� ������ �о����
				pr = Fram_Read(1204);
				o2 = Fram_Read(1205);
				dr = Fram_Read(1206);
                                LCD_DisplayChar(2, 5, te / 10 + 0x30);//����� ������ ȭ�鿡 ���
				LCD_DisplayChar(2, 7, te % 10 + 0x30);
				LCD_DisplayChar(3, 5, pr / 10 + 0x30);
				LCD_DisplayChar(3, 7, pr % 10 + 0x30);
				LCD_DisplayChar(4, 5, o2 / 10 + 0x30);
				LCD_DisplayChar(4, 7, o2 % 10 + 0x30);
				LCD_DisplayChar(5, 5, dr + 0x30);



			}

			break;

		case SW7_PUSH: 		//SW7
			if (start == 1)    //���ۻ��¿��ٸ�
			{
				if (selmode < 4)   //TE->PR->O2->DR->TE������ ����
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
		if (selmode > 0) //���� ���� ��忴�ٸ� ADC1����
		{
			ADC1->CR2 |= ADC_CR2_SWSTART;  //ADC1 ����
		}

		if (mode == 0)   //�Է¸����
		{
			if (start == 1)  //���ۻ��¶��
			{


				if (selmode == 1) //TE���� �����
				{
					LCD_SetTextColor(RGB_BLACK);
					LCD_DisplayText(2, 0, "*");
					LCD_DisplayText(3, 0, " ");
					LCD_DisplayText(4, 0, " ");
					LCD_DisplayText(5, 0, " ");
					GPIOG->ODR &= ~(0x40);
					GPIOG->ODR |= 0x08;


					if (ADC_Value >= 877)  //�о�� ���� 7����Ͽ� �˸°� ������.
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
					LCD_SetTextColor(RGB_RED);     //���� ���� ȭ�鿡 ǥ��
					LCD_DisplayChar(2, 5, te / 10 + 0x30);
					LCD_DisplayChar(2, 7, te % 10 + 0x30);

					if (stack == 1) //�����ȣ�� �´ٸ�
					{
						Fram_Write(1203, te);  //1203������ ����
						stack = 0;
					}
				}

				if (selmode == 2)  //PR���¶��
				{
					LCD_SetTextColor(RGB_BLACK);
					LCD_DisplayText(2, 0, " ");
					LCD_DisplayText(3, 0, "*");
					LCD_DisplayText(4, 0, " ");
					LCD_DisplayText(5, 0, " ");
					GPIOG->ODR &= ~(0x08);
					GPIOG->ODR |= 0x10;

					if (ADC_Value >= 877)  //7����Ͽ� ���
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

					if (stack == 1) //�����ȣ��
					{
						Fram_Write(1204, pr); //1204������ ����
						stack = 0;
					}
				}

				if (selmode == 3)  //O2���μ��� ���¶��
				{
					LCD_SetTextColor(RGB_BLACK);
					LCD_DisplayText(2, 0, " ");
					LCD_DisplayText(3, 0, " ");
					LCD_DisplayText(4, 0, "*");
					LCD_DisplayText(5, 0, " ");

					GPIOG->ODR &= ~(0x10);
					GPIOG->ODR |= 0x20;


					if (ADC_Value >= 877) //7������� ���
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

					if (stack == 1)    //�����ȣ��
					{
						Fram_Write(1205, o2);  //1205������ ����
						stack = 0;
					}
				}

				if (selmode == 4)  //DR���μ��� ����
				{
					LCD_SetTextColor(RGB_BLACK);
					LCD_DisplayText(2, 0, " ");
					LCD_DisplayText(3, 0, " ");
					LCD_DisplayText(4, 0, " ");
					LCD_DisplayText(5, 0, "*");

					GPIOG->ODR &= ~(0x20);
					GPIOG->ODR |= 0x40;

					if (ADC_Value >= 920)  //10����Ͽ� ����
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
					if (stack == 1)  //�����ȣ ���ý�
					{
						Fram_Write(1206, dr);  //1206������ ����
						stack = 0;
					}
				}

			}

		}

		else if (mode == 1) //������
		{
			if (start == 1)  //���۽�
			{

				LCD_SetTextColor(RGB_RED);
				LCD_DisplayText(1, 15, "W");
				GPIOG->ODR |= (0x10);

				DelayMS(500);
				LCD_SetTextColor(RGB_BLACK);
				LCD_DisplayText(2, 0, "*");
				TIM3->CR1 |= (1 << 0);   //Ÿ�̸� �۵� ����.
				LCD_SetTextColor(RGB_RED);
				timer = 0;//Ÿ�̸� 0
				te = Fram_Read(1203);//���� �ٽ� �о��
				while (timer <= te) //TE�ð����� Ÿ�̸� ����
				{
					if (timer > te) //Ȥ��while������ ���۵��ұ�� ����.
					{
						break;
					}
					LCD_DisplayChar(2, 11, timer / 10 + 0x30);
					LCD_DisplayChar(2, 13, timer % 10 + 0x30); //Ÿ�̸� �ð� ���
				}
				LCD_SetTextColor(RGB_BLACK);
				LCD_DisplayText(2, 0, " ");
				GPIOG->ODR &= ~(0x10);


				LCD_DisplayText(3, 0, "*");
				GPIOG->ODR |= (0x20);
				timer = 0;
				pr = Fram_Read(1204);  //
				LCD_SetTextColor(RGB_RED);
	
				while (timer <= pr)// PR�ð����� Ÿ�̸� �۵� ����
				{
					if (timer > pr)//���۵� ���� ����
					{
						break;
					}
					LCD_DisplayChar(3, 11, timer / 10 + 0x30);  //Ÿ�̸� �ð� ���
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
				o2 = Fram_Read(1205);  //������ �о����
				LCD_SetTextColor(RGB_RED);
				dr = Fram_Read(1206);  //������ �о����
				if (dr == 9) //DR���� ���� Ÿ�̸� 2 PWM  ����
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
				while (timer <= o2) //O2�ð����� Ÿ�̸� ����
				{
					if (timer > o2)//���۵� ���� ����
					{
						break;
					}
					LCD_DisplayChar(4, 11, timer / 10 + 0x30);  //ȭ�鿡 �ð� ���
					LCD_DisplayChar(4, 13, timer % 10 + 0x30);
				}
				TIM2->CR1 &= ~(1 << 0);   //Ÿ�̸� 2 �۵� ����
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
				TIM3->CR1 &= ~(1 << 0);   //Ÿ�̸� �۵� ����
				start = 0;  //���� ����
				sw6 = 1;   //���� �ñ׳� 
			}


		}

	}
}

void _ADC_Init(void)
{   	// ADC1: PA1(pin 41)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	// (1<<0) ENABLE GPIOA CLK (stm32f4xx.h ����)
	GPIOA->MODER |= (3 << 2 * 1);		// CONFIG GPIOA PIN1(PA1) TO ANALOG IN MODE

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;	// (1<<8) ENABLE ADC1 CLK (stm32f4xx.h ����)

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

void TIMER3_Init(void)   //���� Ÿ�̸�  16bit ī����.  
{
	RCC->APB1ENR |= 0x02;	//RCC_APB1ENR TIMER3 Enable   Ÿ�̸� 3��  EN      RCC ���� ����.

	NVIC->ISER[0] |= (1 << 29); // Enable Timer3 global Interrupt     
		//  ���ͷ�Ʈ ���� ���̺� ����.      29�� ���ͷ�Ʈ �̹Ƿ�    32���� �۱⶧����  ISER[0] �̴�.

	TIM3->PSC = 8400 - 1;	// Prescaler 84,000,000Hz/8400 = 10,000 Hz (0.1ms)  (1~65536)
	TIM3->ARR = 1000 - 1;	        // Auto reload  0.1ms * 1000 = 100ms  ��  0.1s���� ���ͷ�Ʈ �߻��ϰ� �����.
		// 

		//CR�������� �� 0���� �����.  ���ص�  ����������  �����ǹ̿��� �س��� ���̴�.
		//Ÿ�̸� �������� ���� ����.

	TIM3->CR1 &= ~(1 << 4);	// Upcounter(reset state)   0��  UPī����,  1�� DOWN ī����
	TIM3->CR1 &= ~(3 << 8); 	// CKD(Clock division)=1(reset state)     8���� 9�� bit  �� 0����   ����Ŭ�����.
	TIM3->CR1 &= ~(3 << 5); 	// CMS(Center-aligned mode Sel): No(reset state)    5���� 6�� ��  �Ⱦ���.  ���� ���

	TIM3->EGR |= (1 << 0);	// Update generation    over or under flow��  �̹�Ʈ�� ��� �ϰڴٰ� ���� .. 0�� ��Ʈ�� 1�� �ߴ�.  �ʼ�

	TIM3->DIER |= (1 << 0);	// Enable the Tim3 Update interrupt  ���ͷ�Ʈ�� ���ڴ�.  0�� ��Ʈ�� 1�� ����
}

void TIM3_IRQHandler(void)  	// 1ms Interrupt    
{
	TIM3->SR &= ~(1 << 0);	// Interrupt flag Clear   FLOW�߻��� 1�� �Ǵ� �������� �̹Ƿ�  �ٽ� 0���� ����� �ش�.

	timer++;

}

void TIMER2_PWM_Init(void)
{
	// Clock Enable : GPIOB & TIMER2
	RCC->AHB1ENR |= (1 << 1);	// GPIOB Enable
	RCC->APB1ENR |= (1 << 0);	// TIMER2 Enable 

// PB10�� ��¼����ϰ� Alternate function(TIM2_CH3)���� ��� ���� : PWM ���
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
				// �ش���(40��)�� ���� ��ȣ���
	TIM2->CCER &= ~(1 << 9);	// CC4P=0: CC4 output Polarity High (OC4���� �������� ���)

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
	//���۽�ȣ ����. 
}

void _GPIO_Init(void)
{
	// LED (GPIO G) ����
	RCC->AHB1ENR |= 0x00000040;	// RCC_AHB1ENR : GPIOG(bit#6) Enable							
	GPIOG->MODER |= 0x00005555;	// GPIOG 0~7 : Output mode (0b01)						
	GPIOG->OTYPER &= ~0x00FF;	// GPIOG 0~7 : Push-pull  (GP8~15:reset state)	
	GPIOG->OSPEEDR |= 0x00005555;	// GPIOG 0~7 : Output speed 25MHZ Medium speed 

	// SW (GPIO H) ���� 
	RCC->AHB1ENR |= 0x00000080;	// RCC_AHB1ENR : GPIOH(bit#7) Enable							
	GPIOH->MODER &= ~0xFFFF0000;	// GPIOH 8~15 : Input mode (reset state)				
	GPIOH->PUPDR &= ~0xFFFF0000;	// GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

	// Buzzer (GPIO F) ���� 
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
	LCD_SetFont(&Gulim10);		//��Ʈ 
	LCD_SetBackColor(RGB_YELLOW);	//���ڹ���
	LCD_SetTextColor(RGB_BLUE);	//���ڻ�
	LCD_DisplayText(0, 0, "SPC monitor");      //�ʱ�ȭ�� ��

	LCD_SetTextColor(RGB_BLACK);	//���ڻ�
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

	LCD_SetTextColor(RGB_RED);	//���ڻ�
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