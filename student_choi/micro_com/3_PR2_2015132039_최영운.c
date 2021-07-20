#include "stm32f4xx.h"
#include "GLCD.h"
#include "FRAM.h"

#define SW0_PUSH        0xFE00  //PH8
#define SW1_PUSH        0xFD00  //PH9
#define SW2_PUSH        0xFB00  //PH10
#define SW3_PUSH        0xF700  //PH11

// NO Joy-Button : 0x03E0 : 0000 0011 1110 0000 
		        //Bit No      FEDC BA98 7654 3210
#define NAVI_PUSH	0x03C0  //PI5 0000 0011 1100 0000 
#define NAVI_UP	0x03A0  //PI6 0000 0011 1010 0000 
#define NAVI_DOWN   0x0360  //PI7 0000 0011 0110 0000 
#define NAVI_RIGHT	0x02E0  //PI8 0000 0010 1110 0000 
#define NAVI_LEFT	0x01E0  //PI9 0000 0001 1110 0000 

void _GPIO_Init(void);
uint16_t KEY_Scan(void);
uint16_t JOY_Scan(void);
void _EXTI_Init(void);
void BEEP(void);
void DisplayInitScreen(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

void stonedisplay(void);        //���� display �Լ�
void pointdisplay(void);        //��ǥ�� �Լ�
 
uint8_t   SW0_Flag = 0;
uint8_t   SW1_Flag = 0;
uint8_t   SW6_Flag = 0;
uint8_t   SW7_Flag = 0;   //�� ����ġ�� ���� ���� ����.

int j,i, k,p,q;    //���� ������ ��Ű�� ���� ���� ����

uint8_t xpoint, ypoint, bluexpoint, blueypoint, redxpoint, redypoint;
int bluewin, redwin;

int grop[100]; //���� ���Ҵ��� ���ߴ��� �Ǵ��ϱ� ���� �迭

int main(void)
{
    _GPIO_Init(); // GPIO (LED & SW) �ʱ�ȭ
    LCD_Init();   // LCD ��� �ʱ�ȭ
    _EXTI_Init();      //���ͷ�Ʈ �ʱ�ȭ.
     Fram_Init();        // FRAM �ʱ�ȭ 
    Fram_Status_Config(); 
   
    DisplayInitScreen();   // LCD �ʱ�ȭ��
    
 while(1)
    {
    GPIOG->ODR = 0xFF00;   // LED �ʱⰪ: LED0~7 Off
    p = 0;
    if(SW0_Flag ==1)      //SW0 �Է½�
                    {
                        xpoint = redxpoint;  //������ ���� ���Ҵ� �� �ҷ�����.
                        ypoint = redypoint; 
                         p = 1;
      LCD_DrawChar(137,115,' '); 
     LCD_SetTextColor(RGB_RED);  
      LCD_DrawChar(1,115,'*');         // * ǥ�ñ�
       GPIOG->ODR = 0xFF00;          // LED ALL OFF
      GPIOG->ODR |= 0x0001;            // LED 0 
                    }
        else if (SW7_Flag == 1)       //SW7 �Է½�
                    {
                        xpoint = bluexpoint;        //�Ķ��� ���� ���Ҵ� �� �ҷ�����.
                        ypoint = blueypoint ;
                        p = 1;
     LCD_DrawChar(1,115,' ');
        LCD_SetTextColor(RGB_BLUE);
     LCD_DrawChar(137,115,'*');         // * ǥ�ñ�
     GPIOG->ODR = 0xFF00;         // LED ALL OFF
      GPIOG->ODR |= 0x0080;            // LED 0 
                    }
   while(p ==1)      //�� ���� ������
    {

      
        switch(JOY_Scan())     //���̽�ƽ ��Ʈ��
        {
        	case 0x01E0 : 	// NAVI_LEFT
                  if(xpoint >0)
                  {
			xpoint = xpoint -1;  //�������� �̵�
                        BEEP();
             DelayMS(20);
                  }
	        break;
        	case 0x02E0: 	// NAVI_RIGHT
                  if(xpoint <9)
                  {
			xpoint = xpoint + 1;   //���������� �̵�
                        BEEP();
             DelayMS(20);
                  }
          	break;
                case 0x0360: 	// NAVI_DOWN
                  if(ypoint <9)
                  {
			ypoint = ypoint + 1;   //�Ʒ��� �̵�
                        BEEP();
             DelayMS(20);
                  }
          	break;
                case 0x03A0: 	// NAVI_UP
                  if(ypoint >0)
                  {
			ypoint = ypoint - 1;   //���� �̵�
                        BEEP();
             DelayMS(20);
                  }
          	break;
                case 0x03C0: 	// NAVI_PUSH
                 
                 
                    if(grop[xpoint+(ypoint*10)]==0)      //���õ� �ڸ��� ���� ������
                    {
                      if(SW0_Flag ==1)            //������  ����
                    {
                        grop[xpoint+(ypoint*10)] = 1;  //redstone = 1
                        
                    }
                    else if (SW7_Flag == 1)    //�Ķ��� ����
                    {
                        grop[xpoint+(ypoint*10)] = 2;  //bluestone = 2
                    }
                     p = 2;        //�� ������ �Ѿ�� ���� ����
                    }
                  
                  break;
        }  // switch(JOY_Scan())
        if(SW0_Flag ==1)         
                    {
                        redxpoint = xpoint;     //���� ��ǥ�� �Է�
                        redypoint = ypoint;
                    }
        else if (SW7_Flag == 1)
                    {
                         bluexpoint = xpoint;  //�Ķ� ��ǥ�� �Է�
                         blueypoint = ypoint;
                    }
     pointdisplay();    //��ǥ ���÷���
    }  // while()
   
   if(p == 2)    //�� ���� ���÷���
   {
     stonedisplay();
     SW0_Flag = 0;
     SW7_Flag = 0;
     p = 0;       //�ٽ� ó������.
   }
   
   if(p==3)  //���� �¸� ��ư�� �Է� �Ǿ��ٸ�.
   {
     if(SW1_Flag ==1)   //������ �¸���
     {
       if(Fram_Read(300)<9)   //�¸� Ƚ���� 9���Ͽ��ٸ�
       {
         Fram_Write(300,Fram_Read(300)+1);   //FRAM  300������  1�� ���Ͽ� �Է�
       }
       else
       {
         Fram_Write(300,0);  //Ƚ���� 9���ٸ�  0���� �Է�
       }
       SW1_Flag =0;
       }
     else if(SW6_Flag ==1)   //�Ķ��� �¸���
     {
       if(Fram_Read(301)<9)   //�¸� Ƚ���� 9���Ͽ��ٸ�
       {
         Fram_Write(301,Fram_Read(301)+1);   //FRAM  301������  1�� ���Ͽ� �Է�
       }
       else
       {
         Fram_Write(301,0);  //Ƚ���� 9���ٸ�  0���� �Է�
       }
       SW6_Flag =0;
     }
     LCD_SetTextColor(RGB_BLUE);
    LCD_DrawChar(95,115,Fram_Read(301)+0x30);  //�Ķ��� �¸� Ƚ�� ǥ��.
    LCD_SetTextColor(RGB_RED);
    LCD_DrawChar(65,115,Fram_Read(300)+0x30);  //������ �¸� Ƚ�� ǥ��.
     p=0;          //ó������ �ٽ�.
     DelayMS(5000);       //5�ʰ� ����
      DisplayInitScreen();   // LCD �ʱ�ȭ��
   }
   
}
}

    

void _GPIO_Init(void)
{
   // LED (GPIO G) ����
       RCC->AHB1ENR   |=  0x00000040;   // RCC_AHB1ENR : GPIOG(bit#6) Enable                     
   GPIOG->MODER    |=  0x00005555;   // GPIOG 0~7 : Output mode (0b01)                  
   GPIOG->OTYPER   &= ~0x000000FF;   // GPIOG 0~7 : Push-pull  (GP8~15:reset state)   
    GPIOG->OSPEEDR    |=  0x00005555;   // GPIOG 0~7 : Output speed 25MHZ Medium speed 
    
   // SW (GPIO H) ���� 
   RCC->AHB1ENR    |=  0x00000080;   // RCC_AHB1ENR : GPIOH(bit#7) Enable                     
   GPIOH->MODER    &= ~0xFFFF0000;   // GPIOH 8~15 : Input mode (reset state)            
   GPIOH->PUPDR    &= ~0xFFFF0000;   // GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

   // Buzzer (GPIO F) ���� 
       RCC->AHB1ENR   |=  0x00000020; // RCC_AHB1ENR : GPIOF(bit#5) Enable                     
   GPIOF->MODER    |=  0x00040000;   // GPIOF 9 : Output mode (0b01)                  
   GPIOF->OTYPER    &= ~0x00000200;   // GPIOF 9 : Push-pull     
    GPIOF->OSPEEDR    |=  0x00040000;   // GPIOF 9 : Output speed 25MHZ Medium speed 
    
    //Joy Stick SW(PORT I) ����
	RCC->AHB1ENR 	|= 0x00000100;	// RCC_AHB1ENR GPIOI Enable
	GPIOI->MODER 	&= 0x000FFC00;	// GPIOI 5~9 : Input mode (reset state)
	GPIOI->PUPDR    &= ~0x000FFC00;	// GPIOI 5~9 : Floating input (No Pull-up, pull-down) (reset state)
}   
   
void DisplayInitScreen(void)        //�ʱ�ȭ�� ǥ�ñ�.
{
    LCD_Clear(RGB_YELLOW);   // ȭ�� Ŭ����
    LCD_SetFont(&Gulim8);   // ��Ʈ : ���� 8
    LCD_SetBackColor(RGB_YELLOW);  //���� ���� ���
    LCD_SetTextColor(RGB_BLACK);// ���ڻ� : Black
    LCD_DisplayText(0,1,"Mecha-OMOK");  // Title
   
    LCD_SetPenColor(RGB_BLACK);
    j=0;
    for(j; j<10; j++)
    {
    LCD_DrawHorLine(40, 25+(j*9), 81);       //���� �׸���
    LCD_DrawVerLine(40+(j*9),25, 81);        //������ �׸���
    }
    LCD_DisplayText(1,4,"0");
    LCD_DisplayText(1,10,"5");
    LCD_DisplayText(1,15,"9");
    LCD_DisplayText(5,4,"5");
    LCD_DisplayText(8,4,"9");
    
    LCD_SetTextColor(RGB_RED);
    LCD_DrawChar(10,115,'(' );
    LCD_DrawChar(20,115,',' );
    LCD_DrawChar(30,115,')' );
     LCD_SetTextColor(RGB_BLUE);
    LCD_DrawChar(110,115,'(' );
    LCD_DrawChar(120,115,',' );
    LCD_DrawChar(130,115,')' );
    
    xpoint = 5;             //��ǥ���� �߾����� �ʱ�ȭ
    ypoint = 5;             //��ǥ���� �߾����� �ʱ�ȭ
    bluexpoint = 5;              //��ǥ���� �߾����� �ʱ�ȭ
    blueypoint = 5;             //��ǥ���� �߾����� �ʱ�ȭ
    redxpoint = 5;             //��ǥ���� �߾����� �ʱ�ȭ
    redypoint = 5;             //��ǥ���� �߾����� �ʱ�ȭ
    q=0;   //ó������ �ٽ�.
    for(q ; q<100; q++)
    {
      grop[q] = 0;
    }
    
    pointdisplay();
    
    
    LCD_SetTextColor(RGB_BLACK);
    LCD_DrawText(75,115,"VS");
    LCD_SetTextColor(RGB_BLUE);
    LCD_DrawChar(95,115,Fram_Read(301)+0x30);    //FRAM 301������ ����� �� �о� ǥ��
    LCD_SetTextColor(RGB_RED);
    LCD_DrawChar(65,115,Fram_Read(300)+0x30);    //FRAM 300������ ����� �� �о� ǥ��
    
    LCD_SetBrushColor(RGB_BLACK);
    LCD_DrawFillRect(83,68,5,5);
}

void stonedisplay(void)           //���� ������ ǥ���ϱ� ���� �Լ�
{
    k=0;
      for(k;k<100;k++)   
      {
        if(grop[k]==1)     //�迭 �ȿ� �ڸ��� 1�̶�� ������ ����
        {
          LCD_SetBrushColor(RGB_RED);
         if(k<10)  //ù��
          {
             LCD_DrawFillRect(38+(k*9),23,5,5);
          }
          else if(k<20)  //��°��
          {
            LCD_DrawFillRect(38+((k-10)*9),32,5,5);
          }
          else if(k<30)  //��°��
          {
            LCD_DrawFillRect(38+((k-20)*9),41,5,5);
          }
          else if(k<40) //��°��
          {
            LCD_DrawFillRect(38+((k-30)*9),50,5,5);
          }
          else if(k<50) //�ټ�°��
          {
            LCD_DrawFillRect(38+((k-40)*9),59,5,5);
          }
           else if(k<60) //����°��
          {
            LCD_DrawFillRect(38+((k-50)*9),68,5,5);
          }
           else if(k<70) //�ϰ�°��
          {
            LCD_DrawFillRect(38+((k-60)*9),77,5,5);
          }
           else if(k<80) //����°��
          {
            LCD_DrawFillRect(38+((k-70)*9),86,5,5);
          }
           else if(k<90) //��ȩ°��
          {
            LCD_DrawFillRect(38+((k-80)*9),95,5,5);
          }
           else if(k<100) //����°��
          {
            LCD_DrawFillRect(38+((k-90)*9),104,5,5);
          }
        }
      else if(grop[k]==2)     //�迭 �ȿ� �ڸ��� 2�̶�� ������ ����
        {
          LCD_SetBrushColor(RGB_BLUE);
         if(k<10)  //ù��
          {
             LCD_DrawFillRect(38+(k*9),23,5,5);
          }
          else if(k<20)  //��°��
          {
            LCD_DrawFillRect(38+((k-10)*9),32,5,5);
          }
          else if(k<30)  //��°��
          {
            LCD_DrawFillRect(38+((k-20)*9),41,5,5);
          }
          else if(k<40) //��°��
          {
            LCD_DrawFillRect(38+((k-30)*9),50,5,5);
          }
          else if(k<50) //�ټ�°��
          {
            LCD_DrawFillRect(38+((k-40)*9),59,5,5);
          }
           else if(k<60) //����°��
          {
            LCD_DrawFillRect(38+((k-50)*9),68,5,5);
          }
           else if(k<70) //�ϰ�°��
          {
            LCD_DrawFillRect(38+((k-60)*9),77,5,5);
          }
           else if(k<80) //����°��
          {
            LCD_DrawFillRect(38+((k-70)*9),86,5,5);
          }
           else if(k<90) //��ȩ°��
          {
            LCD_DrawFillRect(38+((k-80)*9),95,5,5);
          }
           else if(k<100) //����°��
          {
            LCD_DrawFillRect(38+((k-90)*9),104,5,5);
          }
        }
      }
             BEEP();
             DelayMS(20);
             BEEP();
             DelayMS(20);
             BEEP();
             DelayMS(20);
}

void pointdisplay(void)    //��ǥ�� ǥ���ϱ� ���� �Լ�
{
  
  LCD_SetTextColor(RGB_RED);
    LCD_DrawChar(15,115,0x30+redxpoint);  //������ X��ǥ�� ǥ��
    LCD_DrawChar(25,115,0x30+redypoint);  //������ Y��ǥ�� ǥ��
  
    LCD_SetTextColor(RGB_BLUE);
     LCD_DrawChar(115,115,0x30+bluexpoint);  //�Ķ��� X��ǥ�� ǥ��
    LCD_DrawChar(125,115,0x30+blueypoint);  //�Ķ��� Y��ǥ�� ǥ��
}


uint8_t key_flag = 0;
uint16_t KEY_Scan(void)   // input key SW0 - SW7 
{ 
   uint16_t key;
   key = GPIOH->IDR & 0xFF00;   // any key pressed ?
   if(key == 0xFF00)      // if no key, check key off
   {     if(key_flag == 0)
              return key;
            else
      {   DelayMS(10);
              key_flag = 0;
              return key;
           }
       }
     else            // if key input, check continuous key
   {   if(key_flag != 0)   // if continuous key, treat as no key input
              return 0xFF00;
            else         // if new key,delay for debounce
      {   key_flag = 1;
         DelayMS(10);
          return key;
           }
   }
}
uint8_t joy_flag = 0;
uint16_t JOY_Scan(void)	// input joy stick NAVI_* 
{ 
	uint16_t key;
	key = GPIOI->IDR & 0x03E0;	// any key pressed ?
	if(key == 0x03E0)		// if no key, check key off
	{  	if(joy_flag == 0)
        		return key;
      		else
		{	DelayMS(10);
        		joy_flag = 0;
        		return key;
        	}
    	}
  	else				// if key input, check continuous key
	{	if(joy_flag != 0)	// if continuous key, treat as no key input
        		return 0x03E0;
      		else			// if new key,delay for debounce
		{	joy_flag = 1;
			DelayMS(10);
 			return key;
        	}
	}
}
void _EXTI_Init(void)
{
       RCC->AHB1ENR    |= 0x00000080;   // RCC_AHB1ENR GPIOH Enable
   RCC->APB2ENR    |= 0x00004000;   // Enable System Configuration Controller Clock
   
   GPIOH->MODER    &= 0x0000FFFF;   // GPIOH PIN8~PIN15 Input mode (reset state)             
   
   SYSCFG->EXTICR[2] |= 0x0077;    // EXTI8,9�� ���� �ҽ� �Է��� GPIOH�� ���� (EXTICR3) (reset value: 0x0000)   
        
        
        
        SYSCFG->EXTICR[3] |= 0x7700;   //EXTI 14,15�� ���� �Է��� GPIOH�� ����  EXTICR4 �̹Ƿ� [3]�� ����
   
        
        
         
   EXTI->FTSR |= 0x00000300;      // Falling Trigger Enable  (EXTI8:PH8)
        EXTI->FTSR |= 0x0000C000;              //������ EXTI15 �۵�
        
       EXTI->IMR  |= 0x00000300;     // EXTI8 , 9���ͷ�Ʈ mask (Interrupt Enable)
        EXTI-> IMR |= 0x0000C000;         //EXTI 14,15 ���ͷ�Ʈ ����ũ ����.
        
         
   NVIC->ISER[0] |= (1<<23 );   // Enable Interrupt EXTI8 Vector table Position ����
        NVIC->ISER[1] |=(1<<(40-32) );  //���� ���̺� �ش��ϴ� ��ȣ�� ã�Ƽ� �������ش�.
        
}

void EXTI9_5_IRQHandler(void)      // EXTI 5~9 ���ͷ�Ʈ �ڵ鷯
{
   if((EXTI->PR & 0x0100))       // EXTI8 Interrupt Pending?
   {
     if(SW7_Flag == 0)
      {
      EXTI->PR |= 0x0100;// Pending bit Clear
      SW0_Flag = 1;
      }
   }
   
   if((EXTI->PR & 0x0200))       // EXTI9 Interrupt Pending?
   {
      EXTI->PR |= 0x0200;// Pending bit Clear
      SW1_Flag = 1;
      p=3;
   }
}

void EXTI15_10_IRQHandler(void)      //EXTI15_10�ڵ鷯�� �������ش�
{
  if(EXTI->PR & 0x4000)              //EXTI14 �Է½�  SW7 =1
    {
      EXTI->PR |= 0x4000;            //�������� �ٽ� ���󺹱� ���ش�   �̰��� �س��� ������ �������·� �ְ� �ȴ�.
     SW6_Flag = 1;
     p=3;
     
    }
  
  if(EXTI->PR & 0x8000)              //EXTI15 �Է½�  SW7 =1
    {
      if(SW0_Flag == 0)
      {
      EXTI->PR |= 0x8000;            //�������� �ٽ� ���󺹱� ���ش�   �̰��� �س��� ������ �������·� �ְ� �ȴ�.
     SW7_Flag = 1;
      }
    }
}

void BEEP(void)         /* beep for 30 ms */
{    
   GPIOF->ODR |=  0x0200;   // PF9 'H' Buzzer on
   DelayMS(30);      // Delay 30 ms
   GPIOF->ODR &= ~0x0200;   // PF9 'L' Buzzer off
}

void DelayMS(unsigned short wMS)
{
    register unsigned short i;
    for (i=0; i<wMS; i++)
        DelayUS(1000);               // 1000us => 1ms
}

void DelayUS(unsigned short wUS)
{
    volatile int Dly = (int)wUS*17;
    for(; Dly; Dly--);
}
