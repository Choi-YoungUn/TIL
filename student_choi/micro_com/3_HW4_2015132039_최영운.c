#include "stm32f4xx.h"
#include "GLCD.h"

void _GPIO_Init(void);

void _EXTI_Init(void);
void BEEP(void);

void DisplayInitScreen(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

uint8_t	SW0_Flag,SW5_Flag ,SW6_Flag, SW7_Flag;   //�� ����ġ�� ���� ���� ����.
int count;        //total �� ���� ���� ����

int main(void)
{
    _GPIO_Init(); // GPIO (LED & SW) �ʱ�ȭ
    LCD_Init();	// LCD ��� �ʱ�ȭ
    _EXTI_Init();      //���ͷ�Ʈ �ʱ�ȭ.
    DelayMS(100);
    BEEP();

    GPIOG->ODR = 0xFF00;	// LED �ʱⰪ: LED0~7 Off
    DisplayInitScreen();	// LCD �ʱ�ȭ��
 
    while(1)
    {
	if(SW0_Flag)    //���� ����ġ�� �����ٸ�. 
	{
		GPIOG->ODR ^= 0x01;    //���� 0��  ����
                BEEP();                        //��  �Ҹ�
                DelayMS(100);
                LCD_SetTextColor(RGB_RED);   //���� �۾���
                LCD_DisplayChar(1,7,'C');          //c ǥ��
                count ++;                               //tota1 ����! 
                if(count<10)                     // total�� 10 ���϶�� �״�� ���
                        {
                          LCD_DisplayChar(5,7,0x30+count);
                        }
                        else
                        {
                        
                            LCD_DisplayChar(5,7,(0x30+(count-10))); //10 �̻��̶��  �ٽ� 0���� ����
                              count = 0;
                        }
                 
                SW5_Flag =0;       //���� �Է� ����  Ŀ�ǿ� ���� ����ġ�� ������ ��츦 �ʱ�ȭ ��.
                SW6_Flag =0;       //��  ���� Ű�� ��������  �� Ŀ�� ����ġ�� ������ ��츦  ����ϰ��� ��.
                SW7_Flag = 0;
                while(1)   //���� ����ġ�� �ѹ� ������  Ŀ�� Ű�� ������ ���� �������� Ŀ�� Ű�� ��ٸ�.
                {
	if(SW5_Flag)  //�� Ű ����
	{	  
     GPIOG->ODR ^= 0x20;     //5�� ���� ����!
     BEEP();                         //��
                DelayMS(100);
     LCD_SetTextColor(RGB_BLUE);  //�Ķ� �۾���
     LCD_DisplayText(2,7,"CUP    ");  // �۾� �ڿ�  �����̽��ٸ� �س��� ����  �� �� �۾���  �� ��  ���  �������� �ʴ� ������ �����ϰ��� ��.
     DelayMS(500);
     
     LCD_DisplayText(2,7,"Coffee ");
     DelayMS(500);
     
     LCD_DisplayText(2,7,"Water  ");
     DelayMS(500);
     
     LCD_DisplayText(2,7,"-       ");   //������� 0.5�ʾ� ���� �� - ���� ǥ��.
     
     GPIOG->ODR &= ~0x0020;    //�����ִ� 0��, 5�� ����  ����
     GPIOG->ODR &= ~0x0001;
     
     LCD_SetTextColor(RGB_RED);    //���� �۾���
     LCD_DisplayChar(1,7,'S');         //�ٽ� s ǥ��
     
     BEEP();
     DelayMS(500);            //��  ����
      BEEP();
     DelayMS(500);
      BEEP();
     DelayMS(500);
     SW5_Flag = 0;          //���� ����ġ��  �� ����ġ�� �ʱ�ȭ �� 0�� �����.
     SW0_Flag = 0;
                break;  
	}
        else if(SW6_Flag)       //���� Ű ����
        {
          GPIOG->ODR ^= 0x40;   //6�� ���� ����
     BEEP();
                DelayMS(100);           //��
     LCD_SetTextColor(RGB_BLUE);        //�Ķ� �۾���
     LCD_DisplayText(3,7,"Cup    ");         //��.
     DelayMS(500);
     
     LCD_DisplayText(3,7,"Coffee ");         //Ŀ��
     DelayMS(500);
     
     LCD_DisplayText(3,7,"Suger  ");          //����
     DelayMS(500);
     
     LCD_DisplayText(3,7,"Water  ");     //��    ������� 0.5�ʾ� ����
     DelayMS(500);
     
     LCD_DisplayText(3,7,"-       ");
     
     GPIOG->ODR &= ~0x0040;      //0���� 6�� ���� ����
     GPIOG->ODR &= ~0x0001;
     
     LCD_SetTextColor(RGB_RED);
     LCD_DisplayChar(1,7,'S');    //���� �۾��� �ٽ� s ǥ��
     
     BEEP();
     DelayMS(500);
      BEEP();
     DelayMS(500);
      BEEP();
     DelayMS(500);
     SW6_Flag = 0;         //���� ����ġ�� ���� ����ġ�� �ʱ�ȭ
     SW0_Flag = 0;
                break;  
        }
         else if(SW7_Flag)       //�ͽ� Ű  ������
        {
          GPIOG->ODR ^= 0x80;    //7�� ���� ����
     BEEP();
                DelayMS(100);            //��
     LCD_SetTextColor(RGB_BLUE);    //�Ķ��۾���
     LCD_DisplayText(4,7,"Cup    ");  //��
     DelayMS(500);
     
     LCD_DisplayText(4,7,"Coffee ");   //Ŀ��
     DelayMS(500);
     
     LCD_DisplayText(4,7,"Suger  ");      //����
     DelayMS(500);
     
     LCD_DisplayText(4,7,"Cream  ");      //ũ��
     DelayMS(500);
     
     LCD_DisplayText(4,7,"Water  ");      //����  0.5�ʾ� ǥ��
     DelayMS(500);
     
     LCD_DisplayText(4,7,"-       ");  //�۾����� �����̽��ٰ�  ���� ���� �ִ� ����  ������ ǥ�õ� �۾��� �����ֱ� ������
     
     GPIOG->ODR &= ~0x0080;      //0���� 7�� ���� ����
     GPIOG->ODR &= ~0x0001;
     
     LCD_SetTextColor(RGB_RED);
     LCD_DisplayChar(1,7,'S');   //���� �۾��� sǥ��
     
     BEEP();                   //�� ���� 
     DelayMS(500);
      BEEP();
     DelayMS(500);
      BEEP();
     DelayMS(500);
     SW7_Flag = 0;
     SW0_Flag = 0;
                break;  
        }
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
	
void DisplayInitScreen(void)        //�ʱ�ȭ�� ǥ�ñ�.
{
    LCD_Clear(RGB_WHITE);	// ȭ�� Ŭ����
    LCD_SetFont(&Gulim8);	// ��Ʈ : ���� 8
    
    LCD_SetBackColor(RGB_YELLOW);// ���ڹ��� 
    LCD_SetTextColor(RGB_BLUE);// ���ڻ� 
    LCD_DisplayText(0,1,"Mecha-Coffee");  // Title
    LCD_SetTextColor(RGB_GREEN);
    LCD_DisplayText(1,0,"Status: ");  
    LCD_SetTextColor(RGB_RED);
     LCD_DisplayChar(1,7,'S'); 
    //
    LCD_SetTextColor(RGB_BLACK);
    LCD_DisplayText(2,0,"BLACK: ");  
    LCD_SetTextColor(RGB_BLUE);
     LCD_DisplayChar(2,7,'-'); 
    
        LCD_SetTextColor(RGB_BLACK);
    LCD_DisplayText(3,0,"SUGAR: ");  
    LCD_SetTextColor(RGB_BLUE);
    LCD_DisplayChar(3,7,'-'); 

    
        LCD_SetTextColor(RGB_BLACK);
    LCD_DisplayText(4,0,"MIXED: ");  
    LCD_SetTextColor(RGB_BLUE);
      LCD_DisplayChar(4,7,'-'); 
    
        LCD_SetTextColor(RGB_BLACK);
    LCD_DisplayText(5,0,"Total: ");  
    LCD_SetTextColor(RGB_RED);
    LCD_DisplayChar(5,7,'0');  



  
}
void _EXTI_Init(void)
{
    	RCC->AHB1ENR 	|= 0x00000080;	// RCC_AHB1ENR GPIOH Enable
	RCC->APB2ENR 	|= 0x00004000;	// Enable System Configuration Controller Clock
	
	GPIOH->MODER 	&= 0x0000FFFF;	// GPIOH PIN8~PIN15 Input mode (reset state)				 
	
	SYSCFG->EXTICR[2] |= 0x0007; 	// EXTI8�� ���� �ҽ� �Է��� GPIOH�� ���� (EXTICR3) (reset value: 0x0000)	
        
        
        
        SYSCFG->EXTICR[3] |= 0x7770;   //EXTI 13,14,15�� ���� �Է��� GPIOH�� ����  EXTICR4 �̹Ƿ� [3]�� ����
	
        
        
         
	EXTI->FTSR |= 0x00000100;		// Falling Trigger Enable  (EXTI8:PH8)
        EXTI->FTSR |= 0x00002000;        //������ EXTI13 �۵�
	EXTI->FTSR |= 0x00004000;		 //������ EXTI14 �۵�
        EXTI->FTSR |= 0x00008000;              //������ EXTI15 �۵�
        
    	EXTI->IMR  |= 0x00000100;  	// EXTI8���ͷ�Ʈ mask (Interrupt Enable)
        EXTI-> IMR |= 0x0000E000;         //�ؿ� �ִ� ����ũ �� ���ļ� ���ٷ� �����.
        
       // EXTI-> IMR |= 0x00002000;   //EXTI13 ���ͷ�Ʈ ����ũ ����.
      //  EXTI-> IMR |= 0x00004000; //EXTI14���ͷ�Ʈ ����ũ ����.
       // EXTI-> IMR |= 0x00008000; //EXTI15 ���ͷ�Ʈ ����ũ ����.
		
	NVIC->ISER[0] |= (1<<23 );   // Enable Interrupt EXTI8 Vector table Position ����
        NVIC->ISER[1] |=(1<<(40-32) );  //���� ���̺� �ش��ϴ� ��ȣ�� ã�Ƽ� �������ش�.
        
        //NVIC->ISER[0] |= (0x00080000 );   // Enable Interrupt EXTI8,9 Vector table Position ����
}

void EXTI9_5_IRQHandler(void)		// EXTI 5~9 ���ͷ�Ʈ �ڵ鷯
{
    if(EXTI->PR & 0x0100) 		// EXTI8 Interrupt Pending?
    {
        EXTI->PR |= 0x0100; 		// Pending bit Clear
	SW0_Flag = 1;
    }
    else if(EXTI->PR & 0x0200)       //EXTI9 �Է½�  
    {
      EXTI->PR |= 0x0200;        //�������� �ٽ� ���󺹱� ���ش�   �̰��� �س��� ������ �������·� �ְ� �ȴ�.
    SW1_Flag = 1;
    }
   
}

void EXTI15_10_IRQHandler(void)      //EXTI15_10�ڵ鷯�� �������ش�
{
  if(EXTI->PR & 0x8000)              //EXTI15 �Է½� 
    {
      EXTI->PR |= 0x8000;            //�������� �ٽ� ���󺹱� ���ش�   �̰��� �س��� ������ �������·� �ְ� �ȴ�.
    SW7_Flag = 1;
    }
 else if(EXTI->PR & 0x4000)       //EXTI14 �Է½� 
    {
      EXTI->PR |= 0x4000;        //�������� �ٽ� ���󺹱� ���ش�   �̰��� �س��� ������ �������·� �ְ� �ȴ�.
    SW6_Flag = 1;
    }
  else if(EXTI->PR & 0x2000)       //EXTI13 �Է½� 
    {
      EXTI->PR |= 0x2000;       //�������� �ٽ� ���󺹱� ���ش�   �̰��� �س��� ������ �������·� �ְ� �ȴ�.
    SW5_Flag = 1;
    }
  else if(EXTI->PR & 0x1000)       //EXTI12 �Է½�  
    {
      EXTI->PR |= 0x1000;       //�������� �ٽ� ���󺹱� ���ش�   �̰��� �س��� ������ �������·� �ְ� �ȴ�.
    SW4_Flag = 1;
    }
  else if(EXTI->PR & 0x0800)       //EXTI11 �Է½� 
    {
      EXTI->PR |= 0x0800;       //�������� �ٽ� ���󺹱� ���ش�   �̰��� �س��� ������ �������·� �ְ� �ȴ�.
    SW3_Flag = 1;
    }
    
}

void BEEP(void)			/* beep for 30 ms */
{ 	
	GPIOF->ODR |=  0x0200;	// PF9 'H' Buzzer on
	DelayMS(30);		// Delay 30 ms
	GPIOF->ODR &= ~0x0200;	// PF9 'L' Buzzer off
}

void DelayMS(unsigned short wMS)
{
    register unsigned short i;
    for (i=0; i<wMS; i++)
        DelayUS(1000);         		// 1000us => 1ms
}

void DelayUS(unsigned short wUS)
{
    volatile int Dly = (int)wUS*17;
    for(; Dly; Dly--);
}

