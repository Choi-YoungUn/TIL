#include "stm32f4xx.h"

void _GPIO_Init(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);
void BEEP(void);
uint16_t KEY_Scan(void);

int main(void)
{
	_GPIO_Init();
	GPIOG->ODR &= 0xFFFFFF00;		// �ʱⰪ: LED0~7 Off
       
       int now=0;  //���� ��
       int point;    //������ ��
       int pointer[8];    //������ LED��ȣ
       pointer[0] = (0x00000001);
       pointer[1] = (0x00000002);
       pointer[2] = (0x00000004);
       pointer[3] = (0x00000008);
       pointer[4] = (0x00000010);
       pointer[5] = (0x00000020);
       pointer[6] = (0x00000040);
       pointer[7] = (0x00000080);
       GPIOG->ODR |= pointer[now];  //�ʱⰪ 0���� ���� ����
	while (1)
	{
          
           switch(KEY_Scan())
        {
        	case 0xFE00  : 	//SW0
                        point =0;  //0�� ��ư ����
                       
                        if ( now > point )   //���� ���� 0������  ������
                        {
                           BEEP();  
                        DelayMS(50);
                          for(now ; now >= point; now--)  //0������ �Һ� ������.
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            if(now > point)  
                            {
                            GPIOG->ODR &= ~pointer[now];
                            }
                          }
                           DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                        }
                        now=0; //FOR���� ������ ����� -1 ���̹Ƿ� 0���� �ʱ�ȭ �Ѵ�.
                       
  	        break;
        	case 0xFD00 : 	//SW1
                        point =1;
                         
                        if ( now < point )  //1������ ���ٸ�
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now < point; now++)    //���� �ø���
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)    //1���� ���޽�  �Һ��� ����  �� �Ҹ� ����.
                          {
                            GPIOG->ODR |= pointer[now];   //����������  ������ ��ư�� ������ �Ҹ��� ���� �ʰ� �ϱ�����
                            DelayMS(100);                     //IF���� �ȿ� �Ȱ��� ���ش�,
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        if(now > point)   //1������ ���ٸ�  
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now > point; now--)   //���� ������
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)    //1���� ���޽�  �Һ��� ����  �� �Ҹ� ����.
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        
          	break;
		case 0xFB00 : 
			point =2;
                         
                        if ( now < point )  //���� ���� �ݺ�. �������� ������ ������.
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now < point; now++)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                           if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }	
                        }
                        if(now > point)
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now > point; now--)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                           if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }	
                        }
                       
                break;
                case 0xF700 : 
			point =3;
                         
                        if ( now < point )
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now < point; now++)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        if(now > point)
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now > point; now--)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        
                break;
                case 0xEF00 : 
			point =4;
                         
                        if ( now < point )
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now < point; now++)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        if(now > point)
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now > point; now--)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        
                break;
                 case 0xDF00 : 
			point =5;
                         
                        if ( now < point )
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now < point; now++)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        if(now > point)
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now > point; now--)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                break;
                 case 0xBF00 : 
			point =6;
                        
                        if ( now < point )
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now < point; now++)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        if(now > point)
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now > point; now--)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        
          
                break;
                 case 0x7F00 : 
			point =7;
                         
                        if ( now < point )
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now < point; now++)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(100);
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                break;
        }
          
		
}
}
void _GPIO_Init(void)
{
	// LED GPIO(PORT G) ����
    	RCC->AHB1ENR |= 0x00000040;  	// RCC_AHB1ENR(bit8~0) GPIOG(bit#6) Enable	(*(volatile unsigned*)0x40023830) |= 0x40; 
	GPIOG->MODER |= 0x00005555;	// GPIOG PIN0~PIN7 Output mode (0b01)	(*(volatile unsigned*)0x40021800) |= 0x5555; 
        GPIOG->OTYPER 	= 0x00000000;	// GPIOG PIN0~PIN7 Push-pull
	GPIOG->OSPEEDR |= 0x00005555;	// GPIOG PIN0~PIN7 Output speed (25MHZ Medium speed) (*(volatile unsigned*)0x40021808) |= 0x5555; 
    
	// SW GPIO(PORT H) ���� 
	RCC->AHB1ENR |=	0x00000080;	// RCC_AHB1ENR(bit8~0) GPIOH(bit#7) Enable	(*(volatile unsigned*)0x40023830) |= 0x80; 
	GPIOH->MODER |=	0x00000000;	// GPIOH PIN8~PIN15 Input mode (reset state) (*(volatile unsigned*)0x40021C00) |= 0x00000000;
        
        RCC->AHB1ENR	|=  0x00000020; // RCC_AHB1ENR : GPIOF(bit#5) Enable							
	GPIOF->MODER 	|= 0x00040000;	// GPIOF 9 : Output mode (0b01)						
	GPIOF->OTYPER 	&= ~0x0000200;	// GPIOF 9 : Push-pull  	
 	GPIOF->OSPEEDR 	|= 0x00040000;	// GPIOF 9 : Output speed 25MHZ Medium speed 
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
	
void BEEP(void)			/* beep for 30 ms */
{ 	
	GPIOF->ODR |= 0x00000200;	// PF9 'H' Buzzer on
	DelayMS(1);		// Delay 30 ms
	GPIOF->ODR &= ~0x00000200;	// PF9 'L' Buzzer off
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