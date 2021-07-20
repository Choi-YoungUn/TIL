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
uint8_t   SW7_Flag = 0;   //�� ����ġ�� ���� ���� ����.
int blueEV =1;
int redEV =1;        //����, ������ ���������Ϳ� ���� ���� ����
int nowfloor=1, nextfloor =0;  //���� ���� ������ �� ���� �ʱ�ȭ.(��Ȱ�� �۵��� ���� �� ����)
int rightev, leftev;  //���ʰ� �������� �����ϱ� ���� ��������
int numbers[7] ={ 0, 105, 92, 79,66,53,40};  //�� ���� ǥ���ϱ� ���� ��ġ �迭  ����
uint8_t pass= 0;     //Ű ������ �������ֱ� ���� ���� ����
uint8_t  again;         //Ű ������ �������ֱ� ���� ���� ����
uint8_t j;                //�ߴܸ�忡�� �ݺ����� ���� ���� ����

int main(void)
{
    _GPIO_Init(); // GPIO (LED & SW) �ʱ�ȭ
    LCD_Init();   // LCD ��� �ʱ�ȭ
    _EXTI_Init();      //���ͷ�Ʈ �ʱ�ȭ.
    DelayMS(100);
    BEEP();

    GPIOG->ODR = 0xFF00;   // LED �ʱⰪ: LED0~7 Off
    GPIOG->ODR ^= 0x01;    //���� 0��  ����
    DisplayInitScreen();   // LCD �ʱ�ȭ��
 
    while(1)//���� ���� �ݺ� ����.
    {
      LCD_SetTextColor(RGB_BLUE);// ���ڻ� : BLUE  //������ ���� �� ó������ �������� ����Ͽ� �ٽ� ���÷�������
        LCD_DisplayText(0,16,"FL"); //FL ǥ��
while(SW7_Flag==0)            // SW7�� �Էµ��� �ʾ�����
      {
         switch(KEY_Scan())
         {
         case 0xFD00 :     //SW1
           if(pass==0)
           {
            nowfloor =1 ;//�����
            GPIOG->ODR |= 0x0002;  // LED1 ON
            GPIOG->ODR &= ~0x007C;//0�� 7�� ������ ������ LED OFF(1����)
            LCD_SetTextColor(RGB_BLACK);//�� �� ���÷���
            LCD_DisplayChar(5,8,'1');
            again =1;             //��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
                break;
           }
           else
           {
             nextfloor = 1;//��ǥ��
             if(nextfloor != nowfloor)
             {
             GPIOG->ODR |= 0x0002; // LED1 ON
             GPIOG->ODR &= ~0x007C; //0�� 7�� ������ ������ LED OFF (1����)
             LCD_SetTextColor(RGB_BLACK);//�� �� ���÷���
             LCD_DisplayChar(5,11,'1');
             again=0;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
             }
                break;
           }
          case 0xFB00 :
             if(pass==0)
           {
            nowfloor =2;//�����
            GPIOG->ODR |= 0x0004;  // LED2 ON 
            GPIOG->ODR &= ~0x007A;//0�� 7�� ������ ������ LED OFF (2����)
            LCD_SetTextColor(RGB_BLACK);
            LCD_DisplayChar(5,8,'2');//�� �� ���÷���
            again =1;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
                break;
           }
           else
           {
             nextfloor = 2;   //��ǥ��
             if(nextfloor != nowfloor)
             {
             GPIOG->ODR |= 0x0004;  // LED2 ON 
             GPIOG->ODR &= ~0x007A;//0�� 7�� ������ ������ LED OFF (2����)
             LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,11,'2');//�� �� ���÷���
             again=0;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
             }
                                break;
           }
          case 0xF700 :
            if(pass==0)
           {
             nowfloor =3;//�����
             GPIOG->ODR |= 0x0008; // LED3 ON
             GPIOG->ODR &= ~0x0076;//0�� 7�� ������ ������ LED OFF(3����)
             LCD_SetTextColor(RGB_BLACK);
              LCD_DisplayChar(5,8,'3');//�� �� ���÷���
              again =1;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
              break;
           }
           else
             {
              nextfloor =3;//��ǥ��
              if(nextfloor != nowfloor)
             {
             GPIOG->ODR |= 0x0008; // LED3 ON
             GPIOG->ODR &= ~0x0076;//0�� 7�� ������ ������ LED OFF(3����)
             LCD_SetTextColor(RGB_BLACK);
              LCD_DisplayChar(5,11,'3');//�� �� ���÷���
              again=0;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
             }
              break;
           }
             case 0xEF00 :
              if(pass==0)
           {
             nowfloor =4;//�����
             GPIOG->ODR |= 0x0010; // LED4 ON
             GPIOG->ODR &= ~0x006E;//0�� 7�� ������ ������ LED OFF(4����)
             LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,8,'4');//�� �� ���÷���
              again =1;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
                        break;
           }
             else
             {
               nextfloor =4;//��ǥ��
               if(nextfloor != nowfloor)
             {
            GPIOG->ODR |= 0x0010; // LED4 ON
             GPIOG->ODR &= ~0x006E;//0�� 7�� ������ ������ LED OFF(4����)
             LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,11,'4');//�� �� ���÷���
             again=0;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
             }
            break;
             }
            
            
         case 0xDF00 :
           if(pass==0)
           {
           nowfloor =5;//�����
            GPIOG->ODR |= 0x0020;  // LED5 ON
            GPIOG->ODR &= ~0x005E;//0�� 7�� ������ ������ LED OFF(5����)
            LCD_SetTextColor(RGB_BLACK);
            LCD_DisplayChar(5,8,'5');//�� �� ���÷���
            again =1;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
                        break;
           }
           else
           {
             nextfloor =5;//��ǥ��
             if(nextfloor != nowfloor)
             {
             GPIOG->ODR |= 0x0020;  // LED5 ON
             GPIOG->ODR &= ~0x005E;//0�� 7�� ������ ������ LED OFF(5����)
             LCD_SetTextColor(RGB_BLACK);
              LCD_DisplayChar(5,11,'5');//�� �� ���÷���
              again=0;//��Ʈ���� ���� ���� �ʱ�ȭ
              
            BEEP();
             DelayMS(20);
             }
             break;
           }
         case 0xBF00 :
           if(pass==0)
           {
           nowfloor =6;//�����
             GPIOG->ODR |= 0x0040; // LED6 ON
             GPIOG->ODR &= ~0x003E;//0�� 7�� ������ ������ LED OFF(6����)
             LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,8,'6');//�� �� ���÷���
             again =1;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
                                 break;
           }
           else
           {
             nextfloor =6;//��ǥ��
             if(nextfloor != nowfloor)
             {
            GPIOG->ODR |= 0x0040; // LED6 ON
            GPIOG->ODR &= ~0x003E;//0�� 7�� ������ ������ LED OFF(6����)
            LCD_SetTextColor(RGB_BLACK);
             LCD_DisplayChar(5,11,'6');//�� �� ���÷���
             again=0;//��Ʈ���� ���� ���� �ʱ�ȭ
            BEEP();
             DelayMS(20);
             }
             break;
           }
                                                   
         }
         if(pass==0&&again==1)  //pass�� 0�̰�  ����� ������ �Ǿ��ٸ�
         {
              pass=1;           //pass �� 1
         }
         else if(pass==1&&again==0)   //pass�� 1�̸� ����� ������ �Ǿ�� �� �����϶�
         {
            if(nowfloor==nextfloor) //������� ��ǥ���� ���ٸ�   �ٽ�  ��ǥ���� �����ض�
               continue;
            pass=0;
         }
      }
    
    //������
if(SW7_Flag)     //SW7���ͷ�Ʈ�� �߻���.
{
     GPIOG->ODR ^= 0x01;      //LED 0�� ����
      GPIOG->ODR ^= 0x80;     //LED 7�� ����
    LCD_SetTextColor(RGB_BLUE);// ���ڻ� : BLUE
    LCD_DisplayText(0,16,"EX"); //EX ǥ��
    
    
    //��������� �̵� ����
    rightev = (nowfloor - redEV);  //���� ������ ���������͸� �����ϱ� ���� ����� ���� ����
    leftev = (nowfloor - blueEV);
    
    if(abs(rightev) >= abs(leftev)) //���� ���������Ͱ� �� ������ �ִٸ�.
    {  //��� ���������� �۵� --��������� ���� ���� ��
       if(nowfloor < blueEV)  //������� ���� ������������ ������ ���ٸ�
       {
        LCD_SetTextColor(RGB_BLUE);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"L:D"); //���� ǥ�� 
                          for(blueEV ; blueEV >=  nowfloor; blueEV--)    // ������� ���� ���������� ���ޱ���
                          {
                            LCD_SetBrushColor(RGB_BLUE);//���� ���� �Ķ�
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //���簢�� ���� �� �����
                            DelayMS(500);
                            if(blueEV > nowfloor)   //������ ���� ��������.
                            {
                            LCD_SetBrushColor(RGB_YELLOW);//���� ���� ���
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //���簢�� ���� �� �����
                            }
                          }
         }
       else if(nowfloor > blueEV)//������� ���� ������������ ������ ���ٸ�
       {
    LCD_SetTextColor(RGB_BLUE);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"L:U"); //���� ǥ�� 
          for(blueEV ; blueEV <=  nowfloor; blueEV++)  // ������� ���� ���������� ���ޱ���
                          {
                             LCD_SetBrushColor(RGB_BLUE);//���� ���� �Ķ�
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //���簢�� ���� �� �����
                            DelayMS(500);
                            if(blueEV < nowfloor)  //������ ���� ��������.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//���� ���� ���
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //���簢�� ���� �� �����
                            }
                          }
       }
       else if( nowfloor == blueEV) //������� ���� ���������� ���̰� ���� ���
       {
    LCD_SetTextColor(RGB_BLUE);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"L:U"); //���� ǥ�� 
    DelayMS(500);
       }
       blueEV = nowfloor;
                        LCD_SetTextColor(RGB_BLUE);//���ڻ� �Ķ�
                        LCD_DisplayText(4,8,"L:S"); //���� ǥ�� 
                        DelayMS(500);
                        
                        //��ǥ������ �������� �̵�
                        if(nextfloor < blueEV)
       {
        LCD_SetTextColor(RGB_BLUE);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"L:D"); //���� ǥ�� 
                          for(blueEV ; blueEV >=  nextfloor; blueEV--)  // ��ǥ���� ���� ���������� ���ޱ���
                          {
                            LCD_SetBrushColor(RGB_BLUE);//���� ���� �Ķ�
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //���簢�� ���� �� �����
                            DelayMS(500);
                            if(blueEV > nextfloor)  //������ ���� ��������.
                            {
                            LCD_SetBrushColor(RGB_YELLOW);//���� ���� ���
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //���簢�� ���� �� �����
                            }
                          }
         }
       else if(nextfloor > blueEV)//��ǥ������ ���� ���������� ���� ���� ���
       {
    LCD_SetTextColor(RGB_BLUE);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"L:U"); //���� ǥ�� 
          for(blueEV ; blueEV <=  nextfloor; blueEV++)  //��ǥ���� ���� ���������� ���ޱ���
                          {
                             LCD_SetBrushColor(RGB_BLUE);//���� ���� �Ķ�
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //���簢�� ���� �� �����
                            DelayMS(500);
                            if(blueEV < nextfloor)  //������ ���� ��������.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//���� ���� ���
                            LCD_DrawFillRect(20, numbers[blueEV],5,10); //���簢�� ���� �� �����
                            }
                          }
       }
       else if( nextfloor == blueEV)  //��ǥ���� ���� ���������� ���̰� ���� ���
       {
    LCD_SetTextColor(RGB_BLUE);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"L:U"); //���� ǥ�� 
    DelayMS(500);
       }
       blueEV = nextfloor;
                        LCD_SetTextColor(RGB_BLUE);//���ڻ� �Ķ�
                        LCD_DisplayText(4,8,"L:S"); //���� ǥ�� 
    }
    
    
    
    else//������ ���������Ͱ� �� ������ �ִٸ�.
    {
       if(nowfloor < redEV)
       {
        LCD_SetTextColor(RGB_RED);//���ڻ� ����
    LCD_DisplayText(4,8,"R:D"); //���� ǥ�� 
                          for( redEV ;  redEV >=  nowfloor;  redEV--)  // ������� ������ ���������� ���ޱ���
                          {
                             LCD_SetBrushColor(RGB_RED);//���� ���� ����
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //���簢�� ���� �� �����
                            DelayMS(500);
                            if(redEV > nowfloor)  //������ ���� ��������.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//���� ���� ���
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //���簢�� ���� �� �����
                            }
                          }
         }
       else if(nowfloor > redEV)
       {
    LCD_SetTextColor(RGB_RED);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"R:U"); //���� ǥ�� 
          for(redEV ; redEV <=  nowfloor; redEV++)  // ������� ������ ���������� ���ޱ���
                          {
                             LCD_SetBrushColor(RGB_RED);//���� ���� ����
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //���簢�� ���� �� �����
                            DelayMS(500);
                            if(redEV < nowfloor)  //������ ���� ��������.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//���� ���� ���
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //���簢�� ���� �� �����
                            }
                          }
       }
       else if( nowfloor == redEV)//������� ������ ���������� ���� ���ٸ�
       {
    LCD_SetTextColor(RGB_RED);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"R:U"); //���� ǥ�� 
    DelayMS(500);
       }
        
        redEV= nowfloor;
      LCD_SetTextColor(RGB_RED);//���ڻ� ����
      LCD_DisplayText(4,8,"R:S"); //���� ǥ��
      DelayMS(500);
      
      //��ǥ������ �������� �̵�
      
       if(nextfloor < redEV)
       {
        LCD_SetTextColor(RGB_RED);//���ڻ� ����
    LCD_DisplayText(4,8,"R:D"); //���� ǥ�� 
                          for( redEV ;  redEV >=  nextfloor;  redEV--)  // ��ǥ���� ������ ���������� ���ޱ���
                          {
                             LCD_SetBrushColor(RGB_RED);//���� ���� ����
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //���簢�� ���� �� �����
                            DelayMS(500);
                            if(redEV > nextfloor)  //������ ���� ��������.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//���� ���� ���
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //���簢�� ���� �� �����
                            }
                          }
         }
       else if(nextfloor > redEV)
       {
    LCD_SetTextColor(RGB_RED);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"R:U"); //���� ǥ�� 
          for(redEV ; redEV <=  nextfloor; redEV++)  // ��ǥ���� ������ ���������� ���ޱ���
                          {
                             LCD_SetBrushColor(RGB_RED);//���� ���� ����
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //���簢�� ���� �� �����
                            DelayMS(500);
                            if(redEV < nextfloor)  //������ ���� ��������.
                            {
                             LCD_SetBrushColor(RGB_YELLOW);//���� ���� ���
                            LCD_DrawFillRect(125, numbers[redEV],5,10); //���簢�� ���� �� �����
                            }
                          }
       }
       else if( nextfloor == redEV)  //��ǥ���� ������ ���������� ���� ���ٸ�
       {
    LCD_SetTextColor(RGB_RED);//���ڻ� �Ķ�
    LCD_DisplayText(4,8,"R:U"); //���� ǥ�� 
    DelayMS(500);
       }
        redEV= nextfloor;
      LCD_SetTextColor(RGB_RED);//���ڻ� ����
      LCD_DisplayText(4,8,"R:S"); //���� ǥ��
    }
    
    
    
    
    
    
    
    SW7_Flag = 0;    //�ٽ� ���ͷ�Ʈ���� ������ ������ �ʱ�ȭ ���Ѽ� ó������ ���ư��� �Ѵ�
    LCD_SetTextColor(RGB_BLUE);// ���ڻ� : BLUE
    LCD_DisplayText(0,16,"FL"); //FL ǥ��
    GPIOG->ODR ^= 0x0081;  //LED 0���� 7��  ��۽�Ŵ.   0�� ON  7�� OFF
     DelayMS(100); ///�Ҹ� ����.
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
}   
   
void DisplayInitScreen(void)        //�ʱ�ȭ�� ǥ�ñ�.
{
    LCD_Clear(RGB_YELLOW);   // ȭ�� Ŭ����
    LCD_SetFont(&Gulim8);   // ��Ʈ : ���� 8
    LCD_SetBackColor(RGB_YELLOW);  //���� ���� ���
    LCD_SetTextColor(RGB_BLACK);// ���ڻ� : Black
    LCD_DisplayText(0,1,"Mecha-OMOK");  // Title
    
    
    
    LCD_SetBrushColor(RGB_BLUE);//���� ���� �Ķ�
    LCD_DrawFillRect(20, 105,5,10); //���簢�� ���� �� �����
    
    LCD_SetBrushColor(RGB_RED);//���� ���� ����
    LCD_DrawFillRect(125, 105,5,10); //���簢�� ���� �� �����
    
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
   
   SYSCFG->EXTICR[2] |= 0x0007;    // EXTI8�� ���� �ҽ� �Է��� GPIOH�� ���� (EXTICR3) (reset value: 0x0000)   
        
        
        
        SYSCFG->EXTICR[3] |= 0x7000;   //EXTI 13,14,15�� ���� �Է��� GPIOH�� ����  EXTICR4 �̹Ƿ� [3]�� ����
   
        
        
         
   EXTI->FTSR |= 0x00000100;      // Falling Trigger Enable  (EXTI8:PH8)
        EXTI->FTSR |= 0x00008000;              //������ EXTI15 �۵�
        
       EXTI->IMR  |= 0x00000100;     // EXTI8���ͷ�Ʈ mask (Interrupt Enable)
        EXTI-> IMR |= 0x00008000;         //EXTI15 ���ͷ�Ʈ ����ũ ����.
        
         
   NVIC->ISER[0] |= (1<<23 );   // Enable Interrupt EXTI8 Vector table Position ����
        NVIC->ISER[1] |=(1<<(40-32) );  //���� ���̺� �ش��ϴ� ��ȣ�� ã�Ƽ� �������ش�.
        
}

void EXTI9_5_IRQHandler(void)      // EXTI 5~9 ���ͷ�Ʈ �ڵ鷯
{
   if((EXTI->PR & 0x0100))       // EXTI8 Interrupt Pending?
   {
      EXTI->PR |= 0x0100;// Pending bit Clear
      if(SW7_Flag==1)         //���� ��� ���̶��.
      {
        DelayMS(500);
            BEEP();
        LCD_SetTextColor(RGB_BLUE); //���ڻ� �Ķ�
         LCD_DisplayText(0,16,"HL");
         for(j=1;j<=10;j++)            // 10�� �ݺ� 0.5�ʾ�
         {
            DelayMS(500);
            BEEP();
         }
         LCD_DisplayText(0,16,"EX");
      }
   }
   SW0_Flag=0;
}

void EXTI15_10_IRQHandler(void)      //EXTI15_10�ڵ鷯�� �������ش�
{
   
  if(EXTI->PR & 0x8000)              //EXTI15 �Է½�  SW7 =1
    {
      EXTI->PR |= 0x8000;            //�������� �ٽ� ���󺹱� ���ش�   �̰��� �س��� ������ �������·� �ְ� �ȴ�.
      if(pass ==0)          // ��ǥ���� ���� �Ǿ��� ��.
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


