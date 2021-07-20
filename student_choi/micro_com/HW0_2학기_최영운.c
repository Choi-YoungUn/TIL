#include "stm32f4xx.h"    //�ʼ� �ش�
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
void TIMER3_Init(void);

void DisplayInitScreen(void);

void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);
void BEEP(void);

uint8_t	SW0_Flag, SW1_Flag;
uint8_t	SW6_Flag, SW7_Flag;
uint8_t sec_100ms;
uint8_t sec_1000ms;
uint8_t sec_1s;
uint8_t vsec100;
uint8_t vsec1000;
uint8_t vsec1;

int main(void)
{
	_GPIO_Init();  			// GPIO �ʱ�ȭ
	_EXTI_Init();			// �ܺ����ͷ�Ʈ �ʱ�ȭ
	TIMER3_Init();			// ����Ÿ�̸�(TIM3) �ʱ�ȭ : up counting mode
	LCD_Init();			// GLCD �ʱ�ȭ
	BEEP();				// Beep �ѹ� 
	DelayMS(100);			
        SW1_Flag = 0;
	GPIOG->ODR &= 0xFF00;		// �ʱⰪ: LED0~7 Off
        GPIOG->ODR |= 0x0001;
   	DisplayInitScreen();		// LCD �ʱ�ȭ��
        while(1)
        {
          if(SW1_Flag == 0)
          {
          LCD_DisplayChar(1,3,sec_100ms+0x30);
    LCD_DisplayChar(1,1,sec_1000ms+0x30);
    LCD_DisplayChar(1,0,sec_1s+0x30);
          }
          else if(SW1_Flag == 1)
          {
            LCD_DisplayChar(1,3,vsec100+0x30);
    LCD_DisplayChar(1,1,vsec1000+0x30);
    LCD_DisplayChar(1,0,vsec1+0x30);
          }
        }
 
	
}

void TIMER3_Init(void)   //���� Ÿ�̸�  16bit ī����.  
{
	RCC->APB1ENR |= 0x02;	//RCC_APB1ENR TIMER3 Enable   Ÿ�̸� 3��  EN      RCC ���� ����.
    
	NVIC->ISER[0] |= ( 1 << 29 ); // Enable Timer3 global Interrupt     
        //  ���ͷ�Ʈ ���� ���̺� ����.      29�� ���ͷ�Ʈ �̹Ƿ�    32���� �۱⶧����  ISER[0] �̴�.
    
	TIM3->PSC = 420-1;	// Prescaler 84,000,000Hz/8400 = 10,000 Hz (0.1ms)  (1~65536)
	TIM3->ARR = 20000-1;	        // Auto reload  0.1ms * 10 = 1ms  ��  1ms���� ���ͷ�Ʈ �߻��ϰ� �����.
        // 
        
        //CR�������� �� 0���� �����.  ���ص�  ����������  �����ǹ̿��� �س��� ���̴�.
        //Ÿ�̸� �������� ���� ����.

	TIM3->CR1 &= ~(1<<4);	// Upcounter(reset state)   0��  UPī����,  1�� DOWN ī����
	TIM3->CR1 &= ~(3<<8); 	// CKD(Clock division)=1(reset state)     8���� 9�� bit  �� 0����   ����Ŭ�����.
	TIM3->CR1 &= ~(3<<5); 	// CMS(Center-aligned mode Sel): No(reset state)    5���� 6�� ��  �Ⱦ���.  ���� ���

	TIM3->EGR |=(1<<0);	// Update generation    over or under flow��  �̹�Ʈ�� ��� �ϰڴٰ� ���� .. 0�� ��Ʈ�� 1�� �ߴ�.  �ʼ�

	TIM3->DIER |= (1<<0);	// Enable the Tim3 Update interrupt  ���ͷ�Ʈ�� ���ڴ�.  0�� ��Ʈ�� 1�� ����
	TIM3->CR1 |= (1<<0);	// Enable the Tim3 Counter    Ŭ�� EN ���ִ� ��  �� ����!!!!
}

void TIM3_IRQHandler(void)  	// 1ms Interrupt    
{
	
	TIM3->SR &= ~(1<<0);	// Interrupt flag Clear   FLOW�߻��� 1�� �Ǵ� �������� �̹Ƿ�  �ٽ� 0���� ��� �ش�.
    if(sec_100ms <9)
    {
        sec_100ms++;
    }
    else
    {
      sec_100ms = 0;
      if(sec_1000ms < 9)
      {
      sec_1000ms++;
      }
      else
      {
        sec_1000ms = 0;
        if(sec_1s < 5)
      {
      sec_1s++;
      }
      else
      {
        sec_1s = 0;
      }
      }
    }
    
}

void _GPIO_Init(void)
{
	// LED (GPIO G) ����
    	RCC->AHB1ENR	|=  0x00000040;	// RCC_AHB1ENR : GPIOG(bit#6) Enable							
	GPIOG->MODER 	|=  0x00005555;	// GPIOG 0~7 : Output mode (0b01)						
	GPIOG->OTYPER	&= ~0x000000FF;	// GPIOG 0~7 : Push-pull  (GP8~15:reset state)	
 	GPIOG->OSPEEDR 	|=  0x00005555;	// GPIOG 0~7 : Output speed 25MHZ Medium speed 
    
	// SW (GPIO H) ���� 
	RCC->AHB1ENR    |=  0x00000080;	// RCC_AHB1ENR : GPIOH(bit#7) Enable							
	GPIOH->MODER 	&= ~0xFFFF0000;	// GPIOH 8~15 : Input mode (reset state)				
	GPIOH->PUPDR 	&= ~0xFFFF0000;	// GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

	// Buzzer (GPIO F) ���� 
    	RCC->AHB1ENR	|=  0x00000020; // RCC_AHB1ENR : GPIOF(bit#5) Enable							
	GPIOF->MODER 	|=  0x00040000;	// GPIOF 9 : Output mode (0b01)						
	GPIOF->OTYPER 	&= ~0x00000200;	// GPIOF 9 : Push-pull  	
 	GPIOF->OSPEEDR 	|=  0x00040000;	// GPIOF 9 : Output speed 25MHZ Medium speed 
}	

void _EXTI_Init(void)
{
    	RCC->AHB1ENR 	|= 0x0080;	// RCC_AHB1ENR GPIOH Enable
	RCC->APB2ENR 	|= 0x4000;	// Enable System Configuration Controller Clock
	
	GPIOH->MODER 	&= 0x0000FFFF;	// GPIOH PIN8~PIN15 Input mode (reset state)				 
	
	SYSCFG->EXTICR[2] |= 0x0077; 	// EXTI8,9�� ���� �ҽ� �Է��� GPIOH�� ���� (EXTICR3) (reset value: 0x0000)	
	
	EXTI->FTSR |= 0x000100;		// Falling Trigger Enable  (EXTI8:PH8)
	EXTI->RTSR |= 0x000200;		// Rising Trigger  Enable  (EXTI9:PH9) 
    	EXTI->IMR  |= 0x000300;  	// EXTI8,9 ���ͷ�Ʈ mask (Interrupt Enable)
		
	NVIC->ISER[0] |= ( 1 << 23 );   // Enable Interrupt EXTI8,9 Vector table Position ����
}

void EXTI9_5_IRQHandler(void)		// EXTI 5~9 ���ͷ�Ʈ �ڵ鷯
{
	if(EXTI->PR & 0x0100) 		// EXTI8 nterrupt Pending?
	{
		EXTI->PR |= 0x0100; 	// Pending bit Clear
                GPIOG->ODR &= 0xFF00;
                GPIOG->ODR |= 0x0001;		// �ʱⰪ: LED0~7 Off
                sec_1000ms = 0;
                sec_100ms = 0;
                sec_1s = 0;
                vsec1000 = 0;
                vsec100 = 0;
                vsec1 = 0;
                BEEP();				// Beep �ѹ� 
	        DelayMS(100);	
	}
	else if(EXTI->PR & 0x0200) 	// EXTI9 Interrupt Pending?
	{
		EXTI->PR |= 0x0200; 	// Pending bit Clear
                GPIOG->ODR &= 0xFF00;
                 GPIOG->ODR |= 0x0002;
                 BEEP();				// Beep �ѹ� 
	         DelayMS(100);	
                if(SW1_Flag == 0)
                {
                  vsec1000 = sec_1000ms;
                  vsec100 = sec_100ms;
                  vsec1 = sec_1s;
                  SW1_Flag = 1;
                }
                else if(SW1_Flag == 1)
                {
                  sec_1000ms = vsec1000 ;
                  sec_100ms = vsec100;
                  sec_1s =  vsec1;
                  SW1_Flag = 0;
                }
			
	}
}

void BEEP(void)			/* beep for 30 ms */
{ 	GPIOF->ODR |= 0x0200;	// PF9 'H' Buzzer on
	DelayMS(30);		// Delay 30 ms
	GPIOF->ODR &= ~0x0200;	// PF9 'L' Buzzer off
}

void DelayMS(unsigned short wMS)
{
	register unsigned short i;
	for (i=0; i<wMS; i++)
		DelayUS(1000);   // 1000us => 1ms
}

void DelayUS(unsigned short wUS)
{
	volatile int Dly = (int)wUS*17;
		for(; Dly; Dly--);
}

void DisplayInitScreen(void)
{
    LCD_Clear(RGB_WHITE);	// ȭ�� Ŭ����
    LCD_SetFont(&Gulim8);	// ��Ʈ : ���� 8
    LCD_SetBackColor(RGB_GREEN);// ���ڹ��� : Green
    LCD_SetTextColor(RGB_BLACK);// ���ڻ� : Black
    LCD_DisplayText(0,0,"Digital Clock");  // Title

    LCD_SetBackColor(RGB_YELLOW);	//���ڹ��� : Yellow
          
    LCD_DisplayChar(1,0,'0');
    LCD_DisplayChar(1,1,'0');
    LCD_DisplayChar(1,2,':');
    LCD_DisplayChar(1,3,'0');
}

uint8_t key_flag = 0;
uint16_t KEY_Scan(void)	// input key SW0 - SW7 
{ 
	uint16_t key;
	key = GPIOH->IDR & 0xFF00;	// any key pressed ?
	if(key == 0xFF00)		// if no key, check key off
	{  	if(key_flag == 0)
        		return key;
      		else
		{	DelayMS(10);
        		key_flag = 0;
        		return key;
        	}
    	}
  	else				// if key input, check continuous key
	{	if(key_flag != 0)	// if continuous key, treat as no key input
        		return 0xFF00;
      		else			// if new key,delay for debounce
		{	key_flag = 1;
			DelayMS(10);
 			return key;
        	}
	}
}