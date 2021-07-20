//***************************************************
//�ۼ��� : 2015132039 �ֿ���
//�ۼ��� : 2019 / 11 / 01

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

void  TIMER8_Init(void);     //Ÿ�̸� 8 ����
void TIMER14_Init(void);     //Ÿ�̸� 14 ����
void _EXTI_Init(void);

void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

uint16_t KEY_Scan(void);
uint16_t ADC_Value, Voltage, temper, freque, print;  // ������� �������� ��, ȯ������, ȯ��µ�, ȯ�� �ֱ�, ���簢������ ����
uint16_t VSENSE, TEMPER;                             //���οµ� , ȯ�곻�οµ�
uint8_t str[30];                                     //���� ���� �迭

int main(void)
{
	LCD_Init();	// LCD ���� �Լ�
	DelayMS(10);	// LCD���� ������
	DisplayTitle();	//LCD �ʱ�ȭ�鱸�� �Լ�
	_EXTI_Init();  //����ġ ���ͷ�Ʈ

	_GPIO_Init();
	_ADC_Init();
	TIMER8_Init();    //Ÿ�̸� 8 ����.
	TIMER14_Init();   // TIM14 Init 

	while (1)
	{

	}
}

void _ADC_Init(void)           //ADC ���� =���⼭ 1,3���� ���� �������ش�.
{   	// ADC1: PA1(pin 41)  �������� ������
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	      // (1<<0) ENABLE GPIOA CLK (stm32f4xx.h ����)
	GPIOA->MODER |= (3 << 2 * 1);	            	// CONFIG GPIOA PIN1(PA1) TO ANALOG IN MODE

	RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;         	// (1<<10) ENABLE ADC3 CLK (stm32f4xx.h ����)

	ADC->CCR &= ~(0X1F << 0);		                // MULTI[4:0]: ADC_Mode_Independent
	ADC->CCR |= (1 << 16); 		                    // 0x00010000 ADCPRE:ADC_Prescaler_Div4 (ADC MAX Clock 36MHz, 84Mhz(APB2)/4 = 21MHz)

	ADC3->CR1 |= (1 << 24);	                    	// RES[1:0]=      : 10bit Resolution
	ADC3->CR1 &= ~(1 << 8);		                    // SCAN=0 : ADC_ScanCovMode Disable
	ADC3->CR1 |= (1 << 5);		                    // EOCIE=1: Interrupt enable for EOC

	ADC3->CR2 &= ~(1 << 1);		                    // CONT=0: ADC_Continuous ConvMode Disable
	ADC3->CR2 |= (2 << 28);		                    // EXTEN[1:0]: ADC_ExternalTrigConvEdge_Enable(Falling Edge)
	ADC3->CR2 |= (0x0D << 24);	          // Timer 8 _1CH ���� ��ȣ�� �Է� �����ϵ��� ����.
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


		// ADC1 :���� 16�� ä��  ���οµ� ������

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;	// (1<<8) ENABLE ADC1 CLK (stm32f4xx.h ����)

	ADC->CCR &= ~(0X1F << 0);		// MULTI[4:0]: ADC_Mode_Independent
	ADC->CCR |= (1 << 16); 	       	// 0x00010000 ADCPRE:ADC_Prescaler_Div4 (ADC MAX Clock 36MHz, 84Mhz(APB2)/4 = 21MHz)
	ADC->CCR |= (1 << 23);           //TSVREFE �� 1�� ���ش�,  Temperature sensor and VREFINT channel enabled

	ADC1->CR1 |= (1 << 24);		// RES[1:0]= 10-bit (13 ADCCLK cycles) 
	ADC1->CR1 |= (1 << 4);		// SCAN=0 : ADC_ScanCovMode Disable
	ADC1->CR1 |= (1 << 5);		// EOCIE=1: Interrupt enable for EOC

	ADC1->CR2 &= ~(1 << 1);		// CONT=0: ADC_Continuous ConvMode Disable
	ADC1->CR2 |= (2 << 28);		// EXTEN[1:0]: ADC_ExternalTrigConvEdge_Enable(Falling Edge)
	ADC1->CR2 |= (0x0D << 24);	         // Timer 8 _1CH ���� ��ȣ�� �Է� �����ϵ��� ����.
	ADC1->CR2 &= ~(1 << 11);		// ALIGN=0: ADC_DataAlign_Right
	ADC1->CR2 &= ~(1 << 10);		// EOCS=0: The EOC bit is set at the end of each sequence of regular conversions

	ADC1->SQR1 &= ~(0xF << 20);	// L[3:0]=0b0000: ADC Regular channel sequece length 
					// 0b0000:1 conversion)
	//Channel selection, The Conversion Sequence of PIN1(ADC1_CH1) is first, Config sequence Range is possible from 0 to 17
	ADC1->SQR1 |= (1 << 15);		// SQ1[4:0]=0b0001 : CH16
	ADC1->SMPR1 |= (0x7 << (18));	// ADC1_CH16 Sample TIme_480Cycles (3*Channel_1)
//Channel selection, The Conversion Sequence of PIN1(ADC1_CH1) is first, Config sequence Range is possible from 0 to 17

		// Enable ADC global Interrupt  ������ ���ͷ�Ʈ�� �������־����Ƿ� ����.

	ADC1->CR2 |= (1 << 0);		// ADON: ADC ON
}

void ADC_IRQHandler(void)  //ADC�ڵ鷯 �κ�.
{
	ADC3->SR &= ~(1 << 1);		                     // EOC flag clear �������� ����ADC3 �ʱ�ȭ
	ADC1->SR &= ~(1 << 1);		                     // EOC flag clear ���οµ� ���� ADC1 �ʱ�ȭ

	ADC_Value = ADC3->DR;		                     // Reading ADC result  ADC3�� ������ �� => �������װ� �� ����
	Voltage = ADC_Value * (3.3 * 100) / 1023;        // 3.3 : 4095 =  Volatge : ADC_Value
													 // 100:  �Ҽ����Ʒ� ���ڸ����� ǥ���ϱ� ���� ��  
	temper = (35 * ((Voltage / 10) * (Voltage / 10))); //�������װ��� ���� �µ� ǥ���ϱ� ���� �Լ���.

	LCD_DisplayChar(0, 10, Voltage / 100 + 0x30);    //������ 10���ڸ�
	LCD_DisplayChar(0, 12, Voltage % 100 / 10 + 0x30); //������ 1���ڸ�
	LCD_DisplayChar(0, 13, Voltage % 10 + 0x30);      //������ 0.1�� �ڸ�

	temper = temper + 1000;                           //���� �µ����� ������ ���ϱ�.

	LCD_DisplayChar(1, 10, temper / 10000 + 0x30);         //�µ��� 10���ڸ�
	LCD_DisplayChar(1, 11, temper % 10000 / 1000 + 0x30);   //�µ��� 1���ڸ�
	LCD_DisplayChar(1, 13, temper % 1000 / 100 + 0x30);     //�µ��� 0.1�� �ڸ�

	freque = (temper / 100) * 10;                           //�µ����� ���� �ֱ� ��ȯ ����

	sprintf(str, "%4d", freque);	                      // ADC result : 12bits (0~4095)
	LCD_DisplayText(2, 7, str);                           // ���ڸ� ǥ���ϱ����� ���
	TIM14->ARR = freque;                                  //Ÿ�̸� 14�� �ֱ�ARR�� �������ش�.

	print = freque / 100;                                 //�Ʒ� ���� �ٸ� �����ϱ� ���� ���� ��� �� ����

	LCD_SetBrushColor(RGB_GREEN);                        //�귯�� ���� �ʷ�����.
	LCD_DrawFillRect(10, 60, 140, 10);                   //���¹��� ����(���簢��)�� �׸���  ����� ���÷����� ���δ� 0~150�ȼ��̴�
	LCD_SetBrushColor(RGB_RED);                          //���¹��� ���� �������� �׸���.
	LCD_DrawFillRect(10, 60, 10 + ((((13000 / 39)*print) + 100) / 100), 10);  //���� 10 �ȼ� ���� �ֱ�� ���� ���� ȯ���ؼ� ����. 
														   //������ Ŀ�� ���� �Ҽ������� ��Ȯ�� ����Ͽ� ��߳��� �ȼ��� ���� �ּ�ȭ ���ֱ� ���Ѱ�.
	VSENSE = ADC1->DR;                                    //���οµ����� ������ ADC1�� ������ ���� ����

	TEMPER = (((VSENSE - 0.76) / 0.0025) + 25);            //���οµ� ���� ����

	LCD_DisplayChar(5, 10, TEMPER / 1000 + 0x30);          //���οµ� 10���ڸ�
	LCD_DisplayChar(5, 11, TEMPER % 1000 / 100 + 0x30);     //���οµ� 1���ڸ�
	LCD_DisplayChar(5, 13, TEMPER % 100 / 10 + 0x30);         //���οµ� 0.1���ڸ�
}

void TIMER8_Init(void)  //Ÿ�̸� 8 _ä�� 1�� ������� Ÿ�̸�.
{
	// TIM8_CH1 (PI5) : 150ms ���ͷ�Ʈ �߻�
	// Clock Enable : GPIOI & TIMER8
	RCC->AHB1ENR |= (1 << 8);	// GPIOI Enable
	RCC->APB2ENR |= (1 << 1);	// TIMER8 Enable 

// PI5�� ��¼����ϰ� Alternate function(TIM8_CH1)���� ��� ���� 
	GPIOI->MODER |= (2 << 2 * 5);	// PI5 Output Alternate function mode					
	GPIOI->OSPEEDR |= (3 << 2 * 5);	// PI5 Output speed (100MHz High speed)
	GPIOI->OTYPER &= ~(1 << 5);	// PI5 Output type push-pull (reset state)
	GPIOI->AFR[0] |= (3 << 20); 	// AFR[0].: Connect TIM5 pins(PI5) to AF3(TIM8)
					// PI5 ==> TIM8_CH1

	TIM8->BDTR |= (1 << 15);  //������� Ÿ�̸� 1,8�� ���� �׻� ����� �ϴ� ��.

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
				// OC1(TIM8_CH1) Active: �ش����� ���� ��ȣ���
	TIM8->CCER &= ~(1 << 1);	// CC1P=0: CC1 channel Output Polarity (OCPolarity_High : OC1���� �������� ���)  

	// 'Mode' Selection : Output mode, toggle  
	TIM8->CCMR1 &= ~(3 << 0); // CC1S(CC1 channel) = '0b00' : Output 
	TIM8->CCMR1 &= ~(1 << 3); // OC1P=0: Output Compare 3 preload disable
	TIM8->CCMR1 |= (3 << 4);	// OC1M : Output Compare  Mode : toggle
				

	TIM8->CCR1 = 10000;	// TIM8 CCR1 TIM8_Pulse

	TIM8->CR1 |= (1 << 0);	// CEN: Enable the Tim8 Counter  					
}

void TIMER14_Init(void)  //�Ҹ� ������ ����ϱ� ���� ����Ÿ�̸�
{
	// ��:PF9(TIM14 CH1)
	// Clock Enable : GPIOF & TIMER14
	RCC->AHB1ENR |= (1 << 5);	// GPIOF Enable
	RCC->APB1ENR |= (1 << 8);	// TIMER14 Enable 

// PF9�� ��¼����ϰ� Alternate function(TIM14_CH1)���� ��� ���� 
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
					// �ش���(40��)�� ���� ��ȣ���
	TIM14->CCER &= ~(1 << 1);	// CC1P=0: CC1 output Polarity High (OC1���� �������� ���)

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

void _EXTI_Init(void)  //sw7 ����.
{
	RCC->AHB1ENR |= 0x0080;   // RCC_AHB1ENR GPIOH Enable
	RCC->APB2ENR |= 0x4000;   // Enable System Configuration Controller Clock

	GPIOH->MODER &= 0x0000FFFF;   // GPIOH PIN8~PIN15 Input mode (reset state)             

	SYSCFG->EXTICR[3] |= 0x7700;         // EXTI15�� ���� �ҽ� �Է��� GPIOF�� ���� 

	EXTI->FTSR |= 0x00C000;      // Falling Trigger Enable (EXTI15:PH15)
	EXTI->IMR |= 0x00C000;     // EXTI15���ͷ�Ʈ mask (Interrupt Enable)

	NVIC->ISER[1] |= (1 << (40 - 32));      // Enable Interrupt EXTI,15 Vector table Position ����
}

void EXTI15_10_IRQHandler(void)      // EXTI 15~10 ���ͷ�Ʈ �ڵ鷯
{
	if (EXTI->PR & 0x8000)       // EXTI15 nterrupt Pending?   
	{
		EXTI->PR |= 0x8000;    // Pending bit Clear
		TIM14->CR1 ^= (1 << 0);	// CEN: Counter TIM14 enable ��۵���.

	}
}

void _GPIO_Init(void)  //�����κ� ����.
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
	LCD_Clear(RGB_YELLOW);  //���� ���
	LCD_SetFont(&Gulim10);		//��Ʈ 
	LCD_SetBackColor(RGB_YELLOW);	//���ڹ���
	LCD_SetTextColor(RGB_BLACK);	//���ڻ�
	LCD_DisplayText(0, 0, "EXT VOL : 0.00V");   //�ʱ�ȭ�� ����
	LCD_DisplayText(1, 0, "EXT TMP : 00.0C");
	LCD_DisplayText(2, 0, "FREQ : 0000HZ");
	LCD_DisplayText(5, 0, "INT TMP : 00.0C");

	LCD_SetBrushColor(RGB_GREEN);   //�ʱ� ���� �� ���� ���
	LCD_DrawFillRect(10, 60, 140, 10);// MAX �ȼ��� X�� 150��! ���簢�� ���� ����
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