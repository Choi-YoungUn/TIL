#include "stm32f4xx.h"
#include "GLCD.h"

void _GPIO_Init(void);
uint16_t KEY_Scan(void);
void _EXTI_Init(void);
void BEEP(void);

void DisplayInitScreen(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

uint8_t   SW0_Flag;
uint8_t   SW7_Flag = 0;   //각 스위치에 대한 변수 설정.
int blueEV =1;
int redEV =1;        //왼쪽, 오른쪽 엘리베이터에 대한 변수 설정
int nowfloor=1, nextfloor =0;  //현재 층과 가야할 층 강제 초기화.(원활한 작동을 위한 값 대입)
int rightev, leftev;  //왼쪽과 오른쪽중 선택하기 위한 변수선언
int numbers[7] ={ 0, 105, 92, 79,66,53,40};  //각 층을 표시하기 위한 위치 배열  정의
uint8_t pass= 0;     //키 동작을 설정해주기 위한 변수 선언
uint8_t  again;         //키 동작을 설정해주기 위한 변수 선언
uint8_t j;                //중단모드에서 반복문에 쓰기 위한 선언

int main(void)
{
    _GPIO_Init(); // GPIO (LED & SW) 초기화
    LCD_Init();   // LCD 모듈 초기화
    _EXTI_Init();      //인터럽트 초기화.
    DelayMS(100);
    BEEP();

    GPIOG->ODR = 0xFF00;   // LED 초기값: LED0~7 Off
    GPIOG->ODR ^= 0x01;    //램프 0번  켜짐
    DisplayInitScreen();   // LCD 초기화면
 
    while(1)//동작 무한 반복 시작.
    {
      LCD_SetTextColor(RGB_BLUE);// 글자색 : BLUE  //동작을 끝낸 후 처음으로 왔을때를 대비하여 다시 디스플레이해줌
        LCD_DisplayText(0,16,"FL"); //FL 표시
while(SW7_Flag==0)            // SW7이 입력되지 않았을시
      {
         switch(KEY_Scan())
         {
         case 0xFD00 :     //SW1
           if(pass==0)
           {
            nowfloor =1 ;//출발층
            GPIOG->ODR |= 0x0002;  // LED1 ON
            GPIOG->ODR &= ~0x007C;//0과 7을 제외한 나머지 LED OFF(1제외)
            LCD_SetTextColor(RGB_BLACK);//층 수 디스플레이
            LCD_DisplayChar(5,8,'1');
            again =1;             //컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
                break;
           }
           else
           {
             nextfloor = 1;//목표층
             if(nextfloor != nowfloor)
             {
             GPIOG->ODR |= 0x0002; // LED1 ON
             GPIOG->ODR &= ~0x007C; //0과 7을 제외한 나머지 LED OFF (1제외)
             LCD_SetTextColor(RGB_BLACK);//층 수 디스플레이
             LCD_DisplayChar(5,11,'1');
             again=0;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
             }
                break;
           }
          case 0xFB00 :
             if(pass==0)
           {
            nowfloor =2;//출발층
            GPIOG->ODR |= 0x0004;  // LED2 ON 
            GPIOG->ODR &= ~0x007A;//0과 7을 제외한 나머지 LED OFF (2제외)
            LCD_SetTextColor(RGB_BLACK);
            LCD_DisplayChar(5,8,'2');//층 수 디스플레이
            again =1;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
                break;
           }
           else
           {
             nextfloor = 2;   //목표층
             if(nextfloor != nowfloor)
             {
             GPIOG->ODR |= 0x0004;  // LED2 ON 
             GPIOG->ODR &= ~0x007A;//0과 7을 제외한 나머지 LED OFF (2제외)
             LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,11,'2');//층 수 디스플레이
             again=0;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
             }
                                break;
           }
          case 0xF700 :
            if(pass==0)
           {
             nowfloor =3;//출발층
             GPIOG->ODR |= 0x0008; // LED3 ON
             GPIOG->ODR &= ~0x0076;//0과 7을 제외한 나머지 LED OFF(3제외)
             LCD_SetTextColor(RGB_BLACK);
              LCD_DisplayChar(5,8,'3');//층 수 디스플레이
              again =1;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
              break;
           }
           else
             {
              nextfloor =3;//목표층
              if(nextfloor != nowfloor)
             {
             GPIOG->ODR |= 0x0008; // LED3 ON
             GPIOG->ODR &= ~0x0076;//0과 7을 제외한 나머지 LED OFF(3제외)
             LCD_SetTextColor(RGB_BLACK);
              LCD_DisplayChar(5,11,'3');//층 수 디스플레이
              again=0;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
             }
              break;
           }
             case 0xEF00 :
              if(pass==0)
           {
             nowfloor =4;//출발층
             GPIOG->ODR |= 0x0010; // LED4 ON
             GPIOG->ODR &= ~0x006E;//0과 7을 제외한 나머지 LED OFF(4제외)
             LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,8,'4');//층 수 디스플레이
              again =1;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
                        break;
           }
             else
             {
               nextfloor =4;//목표층
               if(nextfloor != nowfloor)
             {
            GPIOG->ODR |= 0x0010; // LED4 ON
             GPIOG->ODR &= ~0x006E;//0과 7을 제외한 나머지 LED OFF(4제외)
             LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,11,'4');//층 수 디스플레이
             again=0;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
             }
            break;
             }
            
            
         case 0xDF00 :
           if(pass==0)
           {
           nowfloor =5;//출발층
            GPIOG->ODR |= 0x0020;  // LED5 ON
            GPIOG->ODR &= ~0x005E;//0과 7을 제외한 나머지 LED OFF(5제외)
            LCD_SetTextColor(RGB_BLACK);
            LCD_DisplayChar(5,8,'5');//층 수 디스플레이
            again =1;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
                        break;
           }
           else
           {
             nextfloor =5;//목표층
             if(nextfloor != nowfloor)
             {
             GPIOG->ODR |= 0x0020;  // LED5 ON
             GPIOG->ODR &= ~0x005E;//0과 7을 제외한 나머지 LED OFF(5제외)
             LCD_SetTextColor(RGB_BLACK);
              LCD_DisplayChar(5,11,'5');//층 수 디스플레이
              again=0;//컨트롤을 위한 변수 초기화
              
            BEEP();
             DelayMS(20);
             }
             break;
           }
         case 0xBF00 :
           if(pass==0)
           {
           nowfloor =6;//출발층
             GPIOG->ODR |= 0x0040; // LED6 ON
             GPIOG->ODR &= ~0x003E;//0과 7을 제외한 나머지 LED OFF(6제외)
             LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,8,'6');//층 수 디스플레이
             again =1;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
                                 break;
           }
           else
           {
             nextfloor =6;//목표층
             if(nextfloor != nowfloor)
             {
            GPIOG->ODR |= 0x0040; // LED6 ON
            GPIOG->ODR &= ~0x003E;//0과 7을 제외한 나머지 LED OFF(6제외)
            LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,11,'6');//층 수 디스플레이
             again=0;//컨트롤을 위한 변수 초기화
            BEEP();
             DelayMS(20);
             }
             break;
           }
                                                   
         }
         if(pass==0&&again==1)  //pass가 0이고  출발층 설정이 되었다면
         {
              pass=1;           //pass 가 1
         }
         else if(pass==1&&again==0)   //pass가 1이며 출발층 설정이 되어야 할 차례일때
         {
            if(nowfloor==nextfloor) //출발층과 목표층이 같다면   다시  목표층을 설정해라
               continue;
            pass=0;
         }
      }
    
    //실행모드
if(SW7_Flag)     //SW7인터럽트가 발생시.
{
     GPIOG->ODR ^= 0x01;      //LED 0번 꺼짐
      GPIOG->ODR ^= 0x80;     //LED 7번 켜짐
    LCD_SetTextColor(RGB_BLUE);// 글자색 : BLUE
    LCD_DisplayText(0,16,"EX"); //EX 표시
    
    
    //출발층까지 이동 동작
    rightev = (nowfloor - redEV);  //왼쪽 오른쪽 엘리베이터를 선택하기 위한 계산을 위해 설정
    leftev = (nowfloor - blueEV);
    
    if(abs(rightev) >= abs(leftev)) //왼쪽 엘리베이터가 더 가까이 있다면.
    {  //블루 엘리베이터 작동 --출발층으로 가기 위한 것
       if(nowfloor < blueEV)  //출발층이 왼쪽 엘리베이터의 층보다 낮다면
       {
        LCD_SetTextColor(RGB_BLUE);//글자색 파랑
    LCD_DisplayText(4,8,"L:D"); //상태 표시 
                          for(blueEV ; blueEV >=  nowfloor; blueEV--)    // 출발층에 왼쪽 엘리베이터 도달까지
                          {
                            LCD_SetBrushColor(RGB_BLUE);//면의 색깔 파랑
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //직사각형 내부 색 만들기
                            DelayMS(500);
                            if(blueEV > nowfloor)   //지나간 층은 지워주자.
                            {
                            LCD_SetBrushColor(RGB_YELLOW);//면의 색깔 노랑
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //직사각형 내부 색 만들기
                            }
                          }
         }
       else if(nowfloor > blueEV)//출발층이 왼쪽 엘리베이터의 층보다 높다면
       {
    LCD_SetTextColor(RGB_BLUE);//글자색 파랑
    LCD_DisplayText(4,8,"L:U"); //상태 표시 
          for(blueEV ; blueEV <=  nowfloor; blueEV++)  // 출발층에 왼쪽 엘리베이터 도달까지
                          {
                             LCD_SetBrushColor(RGB_BLUE);//면의 색깔 파랑
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //직사각형 내부 색 만들기
                            DelayMS(500);
                            if(blueEV < nowfloor)  //지나간 층은 지워주자.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//면의 색깔 노랑
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //직사각형 내부 색 만들기
                            }
                          }
       }
       else if( nowfloor == blueEV) //출발층과 왼쪽 엘리베이터 층이가 같은 경우
       {
    LCD_SetTextColor(RGB_BLUE);//글자색 파랑
    LCD_DisplayText(4,8,"L:U"); //상태 표시 
    DelayMS(500);
       }
       blueEV = nowfloor;
                        LCD_SetTextColor(RGB_BLUE);//글자색 파랑
                        LCD_DisplayText(4,8,"L:S"); //상태 표시 
                        DelayMS(500);
                        
                        //목표층으로 가기위한 이동
                        if(nextfloor < blueEV)
       {
        LCD_SetTextColor(RGB_BLUE);//글자색 파랑
    LCD_DisplayText(4,8,"L:D"); //상태 표시 
                          for(blueEV ; blueEV >=  nextfloor; blueEV--)  // 목표층에 왼쪽 엘리베이터 도달까지
                          {
                            LCD_SetBrushColor(RGB_BLUE);//면의 색깔 파랑
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //직사각형 내부 색 만들기
                            DelayMS(500);
                            if(blueEV > nextfloor)  //지나간 층은 지워주자.
                            {
                            LCD_SetBrushColor(RGB_YELLOW);//면의 색깔 노랑
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //직사각형 내부 색 만들기
                            }
                          }
         }
       else if(nextfloor > blueEV)//목표층보다 왼쪽 엘리베이터 층이 낮을 경우
       {
    LCD_SetTextColor(RGB_BLUE);//글자색 파랑
    LCD_DisplayText(4,8,"L:U"); //상태 표시 
          for(blueEV ; blueEV <=  nextfloor; blueEV++)  //목표층에 왼쪽 엘리베이터 도달까지
                          {
                             LCD_SetBrushColor(RGB_BLUE);//면의 색깔 파랑
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //직사각형 내부 색 만들기
                            DelayMS(500);
                            if(blueEV < nextfloor)  //지나간 층은 지워주자.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//면의 색깔 노랑
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //직사각형 내부 색 만들기
                            }
                          }
       }
       else if( nextfloor == blueEV)  //목표층과 왼쪽 엘리베이터 층이가 같은 경우
       {
    LCD_SetTextColor(RGB_BLUE);//글자색 파랑
    LCD_DisplayText(4,8,"L:U"); //상태 표시 
    DelayMS(500);
       }
       blueEV = nextfloor;
                        LCD_SetTextColor(RGB_BLUE);//글자색 파랑
                        LCD_DisplayText(4,8,"L:S"); //상태 표시 
    }
    
    
    
    else//오른쪽 엘리베이터가 더 가까이 있다면.
    {
       if(nowfloor < redEV)
       {
        LCD_SetTextColor(RGB_RED);//글자색 빨강
    LCD_DisplayText(4,8,"R:D"); //상태 표시 
                          for( redEV ;  redEV >=  nowfloor;  redEV--)  // 출발층에 오른쪽 엘리베이터 도달까지
                          {
                             LCD_SetBrushColor(RGB_RED);//면의 색깔 빨강
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //직사각형 내부 색 만들기
                            DelayMS(500);
                            if(redEV > nowfloor)  //지나간 층은 지워주자.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//면의 색깔 노랑
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //직사각형 내부 색 만들기
                            }
                          }
         }
       else if(nowfloor > redEV)
       {
    LCD_SetTextColor(RGB_RED);//글자색 파랑
    LCD_DisplayText(4,8,"R:U"); //상태 표시 
          for(redEV ; redEV <=  nowfloor; redEV++)  // 출발층에 오른쪽 엘리베이터 도달까지
                          {
                             LCD_SetBrushColor(RGB_RED);//면의 색깔 빨강
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //직사각형 내부 색 만들기
                            DelayMS(500);
                            if(redEV < nowfloor)  //지나간 층은 지워주자.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//면의 색깔 노랑
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //직사각형 내부 색 만들기
                            }
                          }
       }
       else if( nowfloor == redEV)//출발층과 오른쪽 엘리베이터 층이 같다면
       {
    LCD_SetTextColor(RGB_RED);//글자색 파랑
    LCD_DisplayText(4,8,"R:U"); //상태 표시 
    DelayMS(500);
       }
        
        redEV= nowfloor;
      LCD_SetTextColor(RGB_RED);//글자색 빨강
      LCD_DisplayText(4,8,"R:S"); //상태 표시
      DelayMS(500);
      
      //목표층으로 가기위한 이동
      
       if(nextfloor < redEV)
       {
        LCD_SetTextColor(RGB_RED);//글자색 빨강
    LCD_DisplayText(4,8,"R:D"); //상태 표시 
                          for( redEV ;  redEV >=  nextfloor;  redEV--)  // 목표층에 오른쪽 엘리베이터 도달까지
                          {
                             LCD_SetBrushColor(RGB_RED);//면의 색깔 빨강
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //직사각형 내부 색 만들기
                            DelayMS(500);
                            if(redEV > nextfloor)  //지나간 층은 지워주자.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//면의 색깔 노랑
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //직사각형 내부 색 만들기
                            }
                          }
         }
       else if(nextfloor > redEV)
       {
    LCD_SetTextColor(RGB_RED);//글자색 파랑
    LCD_DisplayText(4,8,"R:U"); //상태 표시 
          for(redEV ; redEV <=  nextfloor; redEV++)  // 목표층에 오른쪽 엘리베이터 도달까지
                          {
                             LCD_SetBrushColor(RGB_RED);//면의 색깔 빨강
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //직사각형 내부 색 만들기
                            DelayMS(500);
                            if(redEV < nextfloor)  //지나간 층은 지워주자.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//면의 색깔 노랑
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //직사각형 내부 색 만들기
                            }
                          }
       }
       else if( nextfloor == redEV)  //목표층과 오른쪽 엘리베이터 층이 같다면
       {
    LCD_SetTextColor(RGB_RED);//글자색 파랑
    LCD_DisplayText(4,8,"R:U"); //상태 표시 
    DelayMS(500);
       }
        redEV= nextfloor;
      LCD_SetTextColor(RGB_RED);//글자색 빨강
      LCD_DisplayText(4,8,"R:S"); //상태 표시
    }
    
    
    
    
    
    
    
    SW7_Flag = 0;    //다시 인터럽트에서 설정된 변수를 초기화 시켜서 처음으로 돌아가게 한다
    LCD_SetTextColor(RGB_BLUE);// 글자색 : BLUE
    LCD_DisplayText(0,16,"FL"); //FL 표시
    GPIOG->ODR ^= 0x0081;  //LED 0번과 7번  토글시킴.   0번 ON  7번 OFF
     DelayMS(100); ///소리 세번.
     BEEP();
     DelayMS(100);
     BEEP();
     DelayMS(100);
     BEEP();
    
    
    
    
    
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
}   
   
void DisplayInitScreen(void)        //초기화면 표시기.
{
    LCD_Clear(RGB_YELLOW);   // 화면 클리어
    LCD_SetFont(&Gulim8);   // 폰트 : 굴림 8
    LCD_SetBackColor(RGB_YELLOW);  //글자 배경색 노랑
    LCD_SetTextColor(RGB_BLACK);// 글자색 : Black
    LCD_DisplayText(0,1,"Mecha-OMOK");  // Title
    
    
    
    LCD_SetBrushColor(RGB_BLUE);//면의 색깔 파랑
    LCD_DrawFillRect(20, 105,5,10); //직사각형 내부 색 만들기
    
    LCD_SetBrushColor(RGB_RED);//면의 색깔 빨강
    LCD_DrawFillRect(125, 105,5,10); //직사각형 내부 색 만들기
    
    LCD_DrawHorLine(30, 30, 100);

  
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
void _EXTI_Init(void)
{
       RCC->AHB1ENR    |= 0x00000080;   // RCC_AHB1ENR GPIOH Enable
   RCC->APB2ENR    |= 0x00004000;   // Enable System Configuration Controller Clock
   
   GPIOH->MODER    &= 0x0000FFFF;   // GPIOH PIN8~PIN15 Input mode (reset state)             
   
   SYSCFG->EXTICR[2] |= 0x0007;    // EXTI8에 대한 소스 입력은 GPIOH로 설정 (EXTICR3) (reset value: 0x0000)   
        
        
        
        SYSCFG->EXTICR[3] |= 0x7000;   //EXTI 13,14,15에 대한 입력을 GPIOH로 설정  EXTICR4 이므로 [3]을 설정
   
        
        
         
   EXTI->FTSR |= 0x00000100;      // Falling Trigger Enable  (EXTI8:PH8)
        EXTI->FTSR |= 0x00008000;              //눌릴시 EXTI15 작동
        
       EXTI->IMR  |= 0x00000100;     // EXTI8인터럽트 mask (Interrupt Enable)
        EXTI-> IMR |= 0x00008000;         //EXTI15 인터럽트 마스크 벗김.
        
         
   NVIC->ISER[0] |= (1<<23 );   // Enable Interrupt EXTI8 Vector table Position 참조
        NVIC->ISER[1] |=(1<<(40-32) );  //백터 테이블에 해당하는 번호를 찾아서 설정해준다.
        
}

void EXTI9_5_IRQHandler(void)      // EXTI 5~9 인터럽트 핸들러
{
   if((EXTI->PR & 0x0100))       // EXTI8 Interrupt Pending?
   {
      EXTI->PR |= 0x0100;// Pending bit Clear
      if(SW7_Flag==1)         //실행 모드 중이라면.
      {
        DelayMS(500);
            BEEP();
        LCD_SetTextColor(RGB_BLUE); //글자색 파랑
         LCD_DisplayText(0,16,"HL");
         for(j=1;j<=10;j++)            // 10번 반복 0.5초씩
         {
            DelayMS(500);
            BEEP();
         }
         LCD_DisplayText(0,16,"EX");
      }
   }
   SW0_Flag=0;
}

void EXTI15_10_IRQHandler(void)      //EXTI15_10핸들러를 설정해준다
{
   
  if(EXTI->PR & 0x8000)              //EXTI15 입력시  SW7 =1
    {
      EXTI->PR |= 0x8000;            //눌렸으니 다시 원상복구 해준다   이것을 해놓지 않으면 눌린상태로 있게 된다.
      if(pass ==0)          // 목표층이 설정 되었을 시.
   {
     SW7_Flag = 1;
            BEEP();
            DelayMS(20);
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


