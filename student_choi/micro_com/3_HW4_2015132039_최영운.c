#include "stm32f4xx.h"
#include "GLCD.h"

void _GPIO_Init(void);

void _EXTI_Init(void);
void BEEP(void);

void DisplayInitScreen(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

uint8_t	SW0_Flag,SW5_Flag ,SW6_Flag, SW7_Flag;   //각 스위치에 대한 변수 설정.
int count;        //total 에 대한 변수 설정

int main(void)
{
    _GPIO_Init(); // GPIO (LED & SW) 초기화
    LCD_Init();	// LCD 모듈 초기화
    _EXTI_Init();      //인터럽트 초기화.
    DelayMS(100);
    BEEP();

    GPIOG->ODR = 0xFF00;	// LED 초기값: LED0~7 Off
    DisplayInitScreen();	// LCD 초기화면
 
    while(1)
    {
	if(SW0_Flag)    //코인 스위치가 눌린다면. 
	{
		GPIOG->ODR ^= 0x01;    //램프 0번  켜짐
                BEEP();                        //삡  소리
                DelayMS(100);
                LCD_SetTextColor(RGB_RED);   //빨간 글씨로
                LCD_DisplayChar(1,7,'C');          //c 표시
                count ++;                               //tota1 증가! 
                if(count<10)                     // total이 10 이하라면 그대로 출력
                        {
                          LCD_DisplayChar(5,7,0x30+count);
                        }
                        else
                        {
                        
                            LCD_DisplayChar(5,7,(0x30+(count-10))); //10 이상이라면  다시 0부터 시작
                              count = 0;
                        }
                 
                SW5_Flag =0;       //코인 입력 전에  커피에 대한 스위치가 눌렸을 경우를 초기화 함.
                SW6_Flag =0;       //즉  코인 키를 누르기전  각 커피 스위치가 눌렸을 경우를  대비하고자 함.
                SW7_Flag = 0;
                while(1)   //코인 스위치가 한번 눌리면  커피 키가 눌릴때 까지 무한으로 커피 키를 기다림.
                {
	if(SW5_Flag)  //블랙 키 눌림
	{	  
     GPIOG->ODR ^= 0x20;     //5번 램프 점등!
     BEEP();                         //삡
                DelayMS(100);
     LCD_SetTextColor(RGB_BLUE);  //파란 글씨로
     LCD_DisplayText(2,7,"CUP    ");  // 글씨 뒤에  스페이스바를 해놓은 것은  그 전 글씨가  더 길  경우  지워지지 않는 현상을 방지하고자 함.
     DelayMS(500);
     
     LCD_DisplayText(2,7,"Coffee ");
     DelayMS(500);
     
     LCD_DisplayText(2,7,"Water  ");
     DelayMS(500);
     
     LCD_DisplayText(2,7,"-       ");   //순서대로 0.5초씩 점등 후 - 으로 표시.
     
     GPIOG->ODR &= ~0x0020;    //켜져있던 0번, 5번 램프  꺼짐
     GPIOG->ODR &= ~0x0001;
     
     LCD_SetTextColor(RGB_RED);    //빨간 글씨로
     LCD_DisplayChar(1,7,'S');         //다시 s 표시
     
     BEEP();
     DelayMS(500);            //삡  세번
      BEEP();
     DelayMS(500);
      BEEP();
     DelayMS(500);
     SW5_Flag = 0;          //코인 스위치와  블랙 스위치를 초기화 즉 0을 만든다.
     SW0_Flag = 0;
                break;  
	}
        else if(SW6_Flag)       //설탕 키 눌림
        {
          GPIOG->ODR ^= 0x40;   //6번 램프 점등
     BEEP();
                DelayMS(100);           //삡
     LCD_SetTextColor(RGB_BLUE);        //파란 글씨로
     LCD_DisplayText(3,7,"Cup    ");         //컵.
     DelayMS(500);
     
     LCD_DisplayText(3,7,"Coffee ");         //커피
     DelayMS(500);
     
     LCD_DisplayText(3,7,"Suger  ");          //설탕
     DelayMS(500);
     
     LCD_DisplayText(3,7,"Water  ");     //물    순서대로 0.5초씩 점등
     DelayMS(500);
     
     LCD_DisplayText(3,7,"-       ");
     
     GPIOG->ODR &= ~0x0040;      //0번과 6번 램프 꺼짐
     GPIOG->ODR &= ~0x0001;
     
     LCD_SetTextColor(RGB_RED);
     LCD_DisplayChar(1,7,'S');    //빨간 글씨로 다시 s 표시
     
     BEEP();
     DelayMS(500);
      BEEP();
     DelayMS(500);
      BEEP();
     DelayMS(500);
     SW6_Flag = 0;         //코인 스위치와 설탕 스위치를 초기화
     SW0_Flag = 0;
                break;  
        }
         else if(SW7_Flag)       //믹스 키  눌릴시
        {
          GPIOG->ODR ^= 0x80;    //7번 램프 점등
     BEEP();
                DelayMS(100);            //삡
     LCD_SetTextColor(RGB_BLUE);    //파란글씨로
     LCD_DisplayText(4,7,"Cup    ");  //컵
     DelayMS(500);
     
     LCD_DisplayText(4,7,"Coffee ");   //커피
     DelayMS(500);
     
     LCD_DisplayText(4,7,"Suger  ");      //설탕
     DelayMS(500);
     
     LCD_DisplayText(4,7,"Cream  ");      //크림
     DelayMS(500);
     
     LCD_DisplayText(4,7,"Water  ");      //물을  0.5초씩 표시
     DelayMS(500);
     
     LCD_DisplayText(4,7,"-       ");  //글씨마다 스페이스바가  많이 쳐져 있는 것은  그전에 표시된 글씨를 지워주기 위함임
     
     GPIOG->ODR &= ~0x0080;      //0번과 7번 램프 꺼짐
     GPIOG->ODR &= ~0x0001;
     
     LCD_SetTextColor(RGB_RED);
     LCD_DisplayChar(1,7,'S');   //빨간 글씨로 s표시
     
     BEEP();                   //삡 세번 
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
	// LED (GPIO G) 설정
    	RCC->AHB1ENR	|=  0x00000040;	// RCC_AHB1ENR : GPIOG(bit#6) Enable							
	GPIOG->MODER 	|=  0x00005555;	// GPIOG 0~7 : Output mode (0b01)						
	GPIOG->OTYPER	&= ~0x000000FF;	// GPIOG 0~7 : Push-pull  (GP8~15:reset state)	
 	GPIOG->OSPEEDR 	|=  0x00005555;	// GPIOG 0~7 : Output speed 25MHZ Medium speed 
    
	// SW (GPIO H) 설정 
	RCC->AHB1ENR    |=  0x00000080;	// RCC_AHB1ENR : GPIOH(bit#7) Enable							
	GPIOH->MODER 	&= ~0xFFFF0000;	// GPIOH 8~15 : Input mode (reset state)				
	GPIOH->PUPDR 	&= ~0xFFFF0000;	// GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

	// Buzzer (GPIO F) 설정 
    	RCC->AHB1ENR	|=  0x00000020; // RCC_AHB1ENR : GPIOF(bit#5) Enable							
	GPIOF->MODER 	|=  0x00040000;	// GPIOF 9 : Output mode (0b01)						
	GPIOF->OTYPER 	&= ~0x00000200;	// GPIOF 9 : Push-pull  	
 	GPIOF->OSPEEDR 	|=  0x00040000;	// GPIOF 9 : Output speed 25MHZ Medium speed 
}	
	
void DisplayInitScreen(void)        //초기화면 표시기.
{
    LCD_Clear(RGB_WHITE);	// 화면 클리어
    LCD_SetFont(&Gulim8);	// 폰트 : 굴림 8
    
    LCD_SetBackColor(RGB_YELLOW);// 글자배경색 
    LCD_SetTextColor(RGB_BLUE);// 글자색 
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
	
	SYSCFG->EXTICR[2] |= 0x0007; 	// EXTI8에 대한 소스 입력은 GPIOH로 설정 (EXTICR3) (reset value: 0x0000)	
        
        
        
        SYSCFG->EXTICR[3] |= 0x7770;   //EXTI 13,14,15에 대한 입력을 GPIOH로 설정  EXTICR4 이므로 [3]을 설정
	
        
        
         
	EXTI->FTSR |= 0x00000100;		// Falling Trigger Enable  (EXTI8:PH8)
        EXTI->FTSR |= 0x00002000;        //눌릴시 EXTI13 작동
	EXTI->FTSR |= 0x00004000;		 //눌릴시 EXTI14 작동
        EXTI->FTSR |= 0x00008000;              //눌릴시 EXTI15 작동
        
    	EXTI->IMR  |= 0x00000100;  	// EXTI8인터럽트 mask (Interrupt Enable)
        EXTI-> IMR |= 0x0000E000;         //밑에 있는 마스크 를 합쳐서 한줄로 벗긴다.
        
       // EXTI-> IMR |= 0x00002000;   //EXTI13 인터럽트 마스크 벗김.
      //  EXTI-> IMR |= 0x00004000; //EXTI14인터럽트 마스크 벗김.
       // EXTI-> IMR |= 0x00008000; //EXTI15 인터럽트 마스크 벗김.
		
	NVIC->ISER[0] |= (1<<23 );   // Enable Interrupt EXTI8 Vector table Position 참조
        NVIC->ISER[1] |=(1<<(40-32) );  //백터 테이블에 해당하는 번호를 찾아서 설정해준다.
        
        //NVIC->ISER[0] |= (0x00080000 );   // Enable Interrupt EXTI8,9 Vector table Position 참조
}

void EXTI9_5_IRQHandler(void)		// EXTI 5~9 인터럽트 핸들러
{
    if(EXTI->PR & 0x0100) 		// EXTI8 Interrupt Pending?
    {
        EXTI->PR |= 0x0100; 		// Pending bit Clear
	SW0_Flag = 1;
    }
    else if(EXTI->PR & 0x0200)       //EXTI9 입력시  
    {
      EXTI->PR |= 0x0200;        //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
    SW1_Flag = 1;
    }
   
}

void EXTI15_10_IRQHandler(void)      //EXTI15_10핸들러를 설정해준다
{
  if(EXTI->PR & 0x8000)              //EXTI15 입력시 
    {
      EXTI->PR |= 0x8000;            //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
    SW7_Flag = 1;
    }
 else if(EXTI->PR & 0x4000)       //EXTI14 입력시 
    {
      EXTI->PR |= 0x4000;        //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
    SW6_Flag = 1;
    }
  else if(EXTI->PR & 0x2000)       //EXTI13 입력시 
    {
      EXTI->PR |= 0x2000;       //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
    SW5_Flag = 1;
    }
  else if(EXTI->PR & 0x1000)       //EXTI12 입력시  
    {
      EXTI->PR |= 0x1000;       //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
    SW4_Flag = 1;
    }
  else if(EXTI->PR & 0x0800)       //EXTI11 입력시 
    {
      EXTI->PR |= 0x0800;       //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
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

