#include "stm32f4xx.h"

void _GPIO_Init(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);
void BEEP(void);
uint16_t KEY_Scan(void);

int main(void)
{
	_GPIO_Init();
	GPIOG->ODR &= 0xFFFFFF00;		// 초기값: LED0~7 Off
       
       int now=0;  //현제 층
       int point;    //선택한 층
       int pointer[8];    //층마다 LED번호
       pointer[0] = (0x00000001);
       pointer[1] = (0x00000002);
       pointer[2] = (0x00000004);
       pointer[3] = (0x00000008);
       pointer[4] = (0x00000010);
       pointer[5] = (0x00000020);
       pointer[6] = (0x00000040);
       pointer[7] = (0x00000080);
       GPIOG->ODR |= pointer[now];  //초기값 0층에 불이 들어옴
	while (1)
	{
          
           switch(KEY_Scan())
        {
        	case 0xFE00  : 	//SW0
                        point =0;  //0층 버튼 누름
                       
                        if ( now > point )   //현재 층이 0층보다  높을시
                        {
                           BEEP();  
                        DelayMS(50);
                          for(now ; now >= point; now--)  //0층까지 불빛 내려감.
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
                        now=0; //FOR문의 마지막 시행시 -1 값이므로 0으로 초기화 한다.
                       
  	        break;
        	case 0xFD00 : 	//SW1
                        point =1;
                         
                        if ( now < point )  //1층보다 낮다면
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now < point; now++)    //층을 올린다
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)    //1층에 도달시  불빛을 유지  및 소리 세번.
                          {
                            GPIOG->ODR |= pointer[now];   //현재층에서  현재층 버튼을 누를시 소리가 나지 않게 하기위해
                            DelayMS(100);                     //IF문을 안에 똑같이 써준다,
                            BEEP();
                        DelayMS(100);
                        BEEP();
                        DelayMS(100);
                        BEEP();
                          }
                        }
                        if(now > point)   //1층보다 높다면  
                        {
                          BEEP();
                         DelayMS(50);
                          for(now ; now > point; now--)   //층을 내린다
                          {
                            GPIOG->ODR |= pointer[now];
                            DelayMS(250);
                            GPIOG->ODR &= ~pointer[now];
                          }
                          if(now = point)    //1층에 도달시  불빛을 유지  및 소리 세번.
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
                         
                        if ( now < point )  //위의 설명 반복. 각층마다 동일한 시퀀스.
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
	// LED GPIO(PORT G) 설정
    	RCC->AHB1ENR |= 0x00000040;  	// RCC_AHB1ENR(bit8~0) GPIOG(bit#6) Enable	(*(volatile unsigned*)0x40023830) |= 0x40; 
	GPIOG->MODER |= 0x00005555;	// GPIOG PIN0~PIN7 Output mode (0b01)	(*(volatile unsigned*)0x40021800) |= 0x5555; 
        GPIOG->OTYPER 	= 0x00000000;	// GPIOG PIN0~PIN7 Push-pull
	GPIOG->OSPEEDR |= 0x00005555;	// GPIOG PIN0~PIN7 Output speed (25MHZ Medium speed) (*(volatile unsigned*)0x40021808) |= 0x5555; 
    
	// SW GPIO(PORT H) 설정 
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