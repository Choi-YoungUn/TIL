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

void stonedisplay(void);        //오목돌 display 함수
void pointdisplay(void);        //좌표값 함수
 
uint8_t   SW0_Flag = 0;
uint8_t   SW1_Flag = 0;
uint8_t   SW6_Flag = 0;
uint8_t   SW7_Flag = 0;   //각 스위치에 대한 변수 설정.

int j,i, k,p,q;    //내부 동작을 시키기 위한 변수 설절

uint8_t xpoint, ypoint, bluexpoint, blueypoint, redxpoint, redypoint;
int bluewin, redwin;

int grop[100]; //돌을 놓았는지 않했는지 판단하기 위한 배열

int main(void)
{
    _GPIO_Init(); // GPIO (LED & SW) 초기화
    LCD_Init();   // LCD 모듈 초기화
    _EXTI_Init();      //인터럽트 초기화.
     Fram_Init();        // FRAM 초기화 
    Fram_Status_Config(); 
   
    DisplayInitScreen();   // LCD 초기화면
    
 while(1)
    {
    GPIOG->ODR = 0xFF00;   // LED 초기값: LED0~7 Off
    p = 0;
    if(SW0_Flag ==1)      //SW0 입력시
                    {
                        xpoint = redxpoint;  //빨간돌 전에 놓았던 곳 불러오기.
                        ypoint = redypoint; 
                         p = 1;
      LCD_DrawChar(137,115,' '); 
     LCD_SetTextColor(RGB_RED);  
      LCD_DrawChar(1,115,'*');         // * 표시기
       GPIOG->ODR = 0xFF00;          // LED ALL OFF
      GPIOG->ODR |= 0x0001;            // LED 0 
                    }
        else if (SW7_Flag == 1)       //SW7 입력시
                    {
                        xpoint = bluexpoint;        //파란돌 전에 놓았던 곳 불러오기.
                        ypoint = blueypoint ;
                        p = 1;
     LCD_DrawChar(1,115,' ');
        LCD_SetTextColor(RGB_BLUE);
     LCD_DrawChar(137,115,'*');         // * 표시기
     GPIOG->ODR = 0xFF00;         // LED ALL OFF
      GPIOG->ODR |= 0x0080;            // LED 0 
                    }
   while(p ==1)      //돌 착수 시퀀스
    {

      
        switch(JOY_Scan())     //조이스틱 컨트롤
        {
        	case 0x01E0 : 	// NAVI_LEFT
                  if(xpoint >0)
                  {
			xpoint = xpoint -1;  //왼쪽으로 이동
                        BEEP();
             DelayMS(20);
                  }
	        break;
        	case 0x02E0: 	// NAVI_RIGHT
                  if(xpoint <9)
                  {
			xpoint = xpoint + 1;   //오른쪽으로 이동
                        BEEP();
             DelayMS(20);
                  }
          	break;
                case 0x0360: 	// NAVI_DOWN
                  if(ypoint <9)
                  {
			ypoint = ypoint + 1;   //아레로 이동
                        BEEP();
             DelayMS(20);
                  }
          	break;
                case 0x03A0: 	// NAVI_UP
                  if(ypoint >0)
                  {
			ypoint = ypoint - 1;   //위로 이동
                        BEEP();
             DelayMS(20);
                  }
          	break;
                case 0x03C0: 	// NAVI_PUSH
                 
                 
                    if(grop[xpoint+(ypoint*10)]==0)      //선택된 자리에 돌이 없으면
                    {
                      if(SW0_Flag ==1)            //빨간돌  선택
                    {
                        grop[xpoint+(ypoint*10)] = 1;  //redstone = 1
                        
                    }
                    else if (SW7_Flag == 1)    //파란돌 선택
                    {
                        grop[xpoint+(ypoint*10)] = 2;  //bluestone = 2
                    }
                     p = 2;        //돌 착수로 넘어가기 위한 변수
                    }
                  
                  break;
        }  // switch(JOY_Scan())
        if(SW0_Flag ==1)         
                    {
                        redxpoint = xpoint;     //빨간 좌표에 입력
                        redypoint = ypoint;
                    }
        else if (SW7_Flag == 1)
                    {
                         bluexpoint = xpoint;  //파란 좌표에 입력
                         blueypoint = ypoint;
                    }
     pointdisplay();    //좌표 디스플레이
    }  // while()
   
   if(p == 2)    //돌 착수 디스플레이
   {
     stonedisplay();
     SW0_Flag = 0;
     SW7_Flag = 0;
     p = 0;       //다시 처음으로.
   }
   
   if(p==3)  //만약 승리 버튼이 입력 되었다면.
   {
     if(SW1_Flag ==1)   //빨간돌 승리시
     {
       if(Fram_Read(300)<9)   //승리 횟수가 9이하였다면
       {
         Fram_Write(300,Fram_Read(300)+1);   //FRAM  300번지에  1을 더하여 입력
       }
       else
       {
         Fram_Write(300,0);  //횟수가 9였다면  0으로 입력
       }
       SW1_Flag =0;
       }
     else if(SW6_Flag ==1)   //파란돌 승리시
     {
       if(Fram_Read(301)<9)   //승리 횟수가 9이하였다면
       {
         Fram_Write(301,Fram_Read(301)+1);   //FRAM  301번지에  1을 더하여 입력
       }
       else
       {
         Fram_Write(301,0);  //횟수가 9였다면  0으로 입력
       }
       SW6_Flag =0;
     }
     LCD_SetTextColor(RGB_BLUE);
    LCD_DrawChar(95,115,Fram_Read(301)+0x30);  //파란돌 승리 횟수 표시.
    LCD_SetTextColor(RGB_RED);
    LCD_DrawChar(65,115,Fram_Read(300)+0x30);  //빨간돌 승리 횟수 표시.
     p=0;          //처음부터 다시.
     DelayMS(5000);       //5초간 멈춤
      DisplayInitScreen();   // LCD 초기화면
   }
   
}
}

    

void _GPIO_Init(void)
{
   // LED (GPIO G) 설정
       RCC->AHB1ENR   |=  0x00000040;   // RCC_AHB1ENR : GPIOG(bit#6) Enable                     
   GPIOG->MODER    |=  0x00005555;   // GPIOG 0~7 : Output mode (0b01)                  
   GPIOG->OTYPER   &= ~0x000000FF;   // GPIOG 0~7 : Push-pull  (GP8~15:reset state)   
    GPIOG->OSPEEDR    |=  0x00005555;   // GPIOG 0~7 : Output speed 25MHZ Medium speed 
    
   // SW (GPIO H) 설정 
   RCC->AHB1ENR    |=  0x00000080;   // RCC_AHB1ENR : GPIOH(bit#7) Enable                     
   GPIOH->MODER    &= ~0xFFFF0000;   // GPIOH 8~15 : Input mode (reset state)            
   GPIOH->PUPDR    &= ~0xFFFF0000;   // GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

   // Buzzer (GPIO F) 설정 
       RCC->AHB1ENR   |=  0x00000020; // RCC_AHB1ENR : GPIOF(bit#5) Enable                     
   GPIOF->MODER    |=  0x00040000;   // GPIOF 9 : Output mode (0b01)                  
   GPIOF->OTYPER    &= ~0x00000200;   // GPIOF 9 : Push-pull     
    GPIOF->OSPEEDR    |=  0x00040000;   // GPIOF 9 : Output speed 25MHZ Medium speed 
    
    //Joy Stick SW(PORT I) 설정
	RCC->AHB1ENR 	|= 0x00000100;	// RCC_AHB1ENR GPIOI Enable
	GPIOI->MODER 	&= 0x000FFC00;	// GPIOI 5~9 : Input mode (reset state)
	GPIOI->PUPDR    &= ~0x000FFC00;	// GPIOI 5~9 : Floating input (No Pull-up, pull-down) (reset state)
}   
   
void DisplayInitScreen(void)        //초기화면 표시기.
{
    LCD_Clear(RGB_YELLOW);   // 화면 클리어
    LCD_SetFont(&Gulim8);   // 폰트 : 굴림 8
    LCD_SetBackColor(RGB_YELLOW);  //글자 배경색 노랑
    LCD_SetTextColor(RGB_BLACK);// 글자색 : Black
    LCD_DisplayText(0,1,"Mecha-OMOK");  // Title
   
    LCD_SetPenColor(RGB_BLACK);
    j=0;
    for(j; j<10; j++)
    {
    LCD_DrawHorLine(40, 25+(j*9), 81);       //수평선 그리기
    LCD_DrawVerLine(40+(j*9),25, 81);        //수직선 그리기
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
    
    xpoint = 5;             //좌표값을 중앙으로 초기화
    ypoint = 5;             //좌표값을 중앙으로 초기화
    bluexpoint = 5;              //좌표값을 중앙으로 초기화
    blueypoint = 5;             //좌표값을 중앙으로 초기화
    redxpoint = 5;             //좌표값을 중앙으로 초기화
    redypoint = 5;             //좌표값을 중앙으로 초기화
    q=0;   //처음부터 다시.
    for(q ; q<100; q++)
    {
      grop[q] = 0;
    }
    
    pointdisplay();
    
    
    LCD_SetTextColor(RGB_BLACK);
    LCD_DrawText(75,115,"VS");
    LCD_SetTextColor(RGB_BLUE);
    LCD_DrawChar(95,115,Fram_Read(301)+0x30);    //FRAM 301번지에 저장된 값 읽어 표시
    LCD_SetTextColor(RGB_RED);
    LCD_DrawChar(65,115,Fram_Read(300)+0x30);    //FRAM 300번지에 저장된 값 읽어 표시
    
    LCD_SetBrushColor(RGB_BLACK);
    LCD_DrawFillRect(83,68,5,5);
}

void stonedisplay(void)           //놓인 오목돌을 표시하기 위한 함수
{
    k=0;
      for(k;k<100;k++)   
      {
        if(grop[k]==1)     //배열 안에 자리가 1이라면 빨간돌 착수
        {
          LCD_SetBrushColor(RGB_RED);
         if(k<10)  //첫줄
          {
             LCD_DrawFillRect(38+(k*9),23,5,5);
          }
          else if(k<20)  //둘째줄
          {
            LCD_DrawFillRect(38+((k-10)*9),32,5,5);
          }
          else if(k<30)  //셋째줄
          {
            LCD_DrawFillRect(38+((k-20)*9),41,5,5);
          }
          else if(k<40) //넷째줄
          {
            LCD_DrawFillRect(38+((k-30)*9),50,5,5);
          }
          else if(k<50) //다섯째줄
          {
            LCD_DrawFillRect(38+((k-40)*9),59,5,5);
          }
           else if(k<60) //여섯째줄
          {
            LCD_DrawFillRect(38+((k-50)*9),68,5,5);
          }
           else if(k<70) //일곱째줄
          {
            LCD_DrawFillRect(38+((k-60)*9),77,5,5);
          }
           else if(k<80) //여덟째줄
          {
            LCD_DrawFillRect(38+((k-70)*9),86,5,5);
          }
           else if(k<90) //아홉째줄
          {
            LCD_DrawFillRect(38+((k-80)*9),95,5,5);
          }
           else if(k<100) //열번째줄
          {
            LCD_DrawFillRect(38+((k-90)*9),104,5,5);
          }
        }
      else if(grop[k]==2)     //배열 안에 자리가 2이라면 빨간돌 착수
        {
          LCD_SetBrushColor(RGB_BLUE);
         if(k<10)  //첫줄
          {
             LCD_DrawFillRect(38+(k*9),23,5,5);
          }
          else if(k<20)  //둘째줄
          {
            LCD_DrawFillRect(38+((k-10)*9),32,5,5);
          }
          else if(k<30)  //셋째줄
          {
            LCD_DrawFillRect(38+((k-20)*9),41,5,5);
          }
          else if(k<40) //넷째줄
          {
            LCD_DrawFillRect(38+((k-30)*9),50,5,5);
          }
          else if(k<50) //다섯째줄
          {
            LCD_DrawFillRect(38+((k-40)*9),59,5,5);
          }
           else if(k<60) //여섯째줄
          {
            LCD_DrawFillRect(38+((k-50)*9),68,5,5);
          }
           else if(k<70) //일곱째줄
          {
            LCD_DrawFillRect(38+((k-60)*9),77,5,5);
          }
           else if(k<80) //여덟째줄
          {
            LCD_DrawFillRect(38+((k-70)*9),86,5,5);
          }
           else if(k<90) //아홉째줄
          {
            LCD_DrawFillRect(38+((k-80)*9),95,5,5);
          }
           else if(k<100) //열번째줄
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

void pointdisplay(void)    //좌표를 표시하기 위한 함수
{
  
  LCD_SetTextColor(RGB_RED);
    LCD_DrawChar(15,115,0x30+redxpoint);  //빨간돌 X좌표값 표시
    LCD_DrawChar(25,115,0x30+redypoint);  //빨간돌 Y좌표값 표시
  
    LCD_SetTextColor(RGB_BLUE);
     LCD_DrawChar(115,115,0x30+bluexpoint);  //파란돌 X좌표값 표시
    LCD_DrawChar(125,115,0x30+blueypoint);  //파란돌 Y좌표값 표시
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
   
   SYSCFG->EXTICR[2] |= 0x0077;    // EXTI8,9에 대한 소스 입력은 GPIOH로 설정 (EXTICR3) (reset value: 0x0000)   
        
        
        
        SYSCFG->EXTICR[3] |= 0x7700;   //EXTI 14,15에 대한 입력을 GPIOH로 설정  EXTICR4 이므로 [3]을 설정
   
        
        
         
   EXTI->FTSR |= 0x00000300;      // Falling Trigger Enable  (EXTI8:PH8)
        EXTI->FTSR |= 0x0000C000;              //눌릴시 EXTI15 작동
        
       EXTI->IMR  |= 0x00000300;     // EXTI8 , 9인터럽트 mask (Interrupt Enable)
        EXTI-> IMR |= 0x0000C000;         //EXTI 14,15 인터럽트 마스크 벗김.
        
         
   NVIC->ISER[0] |= (1<<23 );   // Enable Interrupt EXTI8 Vector table Position 참조
        NVIC->ISER[1] |=(1<<(40-32) );  //백터 테이블에 해당하는 번호를 찾아서 설정해준다.
        
}

void EXTI9_5_IRQHandler(void)      // EXTI 5~9 인터럽트 핸들러
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

void EXTI15_10_IRQHandler(void)      //EXTI15_10핸들러를 설정해준다
{
  if(EXTI->PR & 0x4000)              //EXTI14 입력시  SW7 =1
    {
      EXTI->PR |= 0x4000;            //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
     SW6_Flag = 1;
     p=3;
     
    }
  
  if(EXTI->PR & 0x8000)              //EXTI15 입력시  SW7 =1
    {
      if(SW0_Flag == 0)
      {
      EXTI->PR |= 0x8000;            //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
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
