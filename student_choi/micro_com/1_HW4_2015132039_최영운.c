//***************************************************
//작성자 : 2015132039 최영운
//작성일 : 2019 / 11 / 29
//////////////////////////////////////////////////////////////////////////
#include "stm32f4xx.h"
#include "GLCD.h"
#include "ACC.h"
#include "FRAM.h"

#define SW0_PUSH        0xFE00  //PH8

void DisplayTitle(void);
void _GPIO_Init(void);
void SPI1_Init(void);
void TIMER10_Init(void);
void Display_Process(UINT16 *pBuf);

void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);
void USART1_Init(void);

void USART_BRR_Configuration(uint32_t USART_BaudRate);

uint16_t KEY_Scan(void);
void SerialSendChar(uint8_t c);
void SerialSendString(char *s);

int axcon = 0;    // x축 센서를 컨트롤 하기위한 변수선언
int aycon = 0;    // y축 센서를 컨트롤 하기위한 변수선언
int azcon = 0;    // z축 센서를 컨트롤 하기위한 변수선언
int text = 0;     //700ms동작을 위한 변수선언
int sendstop = 0; // sw0를 눌렀을때 작동하기 위한 변수선언

UINT8 bControl;

int main(void)
{
	UINT16 buffer[3];

	LCD_Init();		// LCD 구동 함수
	DelayMS(10);		// LCD구동 딜레이
	DisplayTitle();		// LCD 초기화면구동 함수

	_GPIO_Init();		// LED, SW 초기화
	SPI1_Init();        	// SPI1 초기화
	ACC_Init();		// 가속도센서 초기화
	TIMER10_Init();		// 가속도센서 스캔 주기 생성
	USART1_Init();     //uart통신 초기화
	Fram_Init();        // FRAM 초기화 
	Fram_Status_Config();



	while (1)
	{
		switch (KEY_Scan())
		{
		case SW0_PUSH: 		//SW0

			sendstop = 1;  //전송시작!
			break;
		}
		if (bControl)
		{
			bControl = FALSE;
			SPI1_Process(&buffer[0]);	// SPI통신을 이용하여 가속도센서 측정
			Display_Process(&buffer[0]);	// 측정값을 LCD에 표시
			if ((Fram_Read(350) & 0x01) == 0x01)  //0x01값이 있었다면 x축 설정
			{
				LCD_DisplayChar(1, 0, '*');     
				LCD_DisplayChar(2, 0, ' ');
				LCD_DisplayChar(3, 0, ' ');
				axcon = 1;
				aycon = 0;
				azcon = 0;
			}
			if ((Fram_Read(350) & 0x02) == 0x02)//0x02값이 있었다면 y축 설정
			{
				LCD_DisplayChar(1, 0, ' ');
				LCD_DisplayChar(2, 0, '*');
				LCD_DisplayChar(3, 0, ' ');
				axcon = 0;
				aycon = 1;
				azcon = 0;
			}
			if ((Fram_Read(350) & 0x03) == 0x03)//0x03값이 있었다면 x축, y축 설정
			{
				LCD_DisplayChar(1, 0, '*');
				LCD_DisplayChar(2, 0, '*');
				LCD_DisplayChar(3, 0, ' ');
				axcon = 1;
				aycon = 1;
				azcon = 0;
			}
			if ((Fram_Read(350) & 0x04) == 0x04)//0x04값이 있었다면 z축 설정
			{
				LCD_DisplayChar(1, 0, ' ');
				LCD_DisplayChar(2, 0, ' ');
				LCD_DisplayChar(3, 0, '*');
				axcon = 0;
				aycon = 0;
				azcon = 1;
			}
			if ((Fram_Read(350) & 0x05) == 0x05)//0x05값이 있었다면 x축, z축 설정
			{
				LCD_DisplayChar(1, 0, '*');
				LCD_DisplayChar(2, 0, ' ');
				LCD_DisplayChar(3, 0, '*');
				axcon = 1;
				aycon = 0;
				azcon = 1;
			}
			if ((Fram_Read(350) & 0x06) == 0x06)//0x06값이 있었다면 y축, z축 설정
			{
				LCD_DisplayChar(1, 0, ' ');
				LCD_DisplayChar(2, 0, '*');
				LCD_DisplayChar(3, 0, '*');
				axcon = 0;
				aycon = 1;
				azcon = 1;
			}
			if ((Fram_Read(350) & 0x07) == 0x07)//0x07값이 있었다면 x축, y축, z축 설정
			{
				LCD_DisplayChar(1, 0, '*');
				LCD_DisplayChar(2, 0, '*');
				LCD_DisplayChar(3, 0, '*');
				axcon = 1;
				aycon = 1;
				azcon = 1;
			}
			if (Fram_Read(350) == 0x00) //0x00값 이었다면 모두 비설정
			{
				LCD_DisplayChar(1, 0, ' ');
				LCD_DisplayChar(2, 0, ' ');
				LCD_DisplayChar(3, 0, ' ');
				axcon = 0;
				aycon = 0;
				azcon = 0;
			}
		}
	}
}

void USART1_IRQHandler(void)	//모든 인터럽트시 핸들러.
{

	if ((USART1->SR & USART_SR_RXNE)) 	// USART_SR_RXNE=(1<<5) 
	{
		uint16_t ch;

		ch = (uint16_t)(USART1->DR & (uint16_t)0x01FF);	// 수신된 문자 저장
		Fram_Write(350, ch);  //수신된 값을 350번지에 저장
		if ((ch & 0x01) == 0x01)     //수신된 문자에 0x01이 참이면 작동
		{
			axcon = 1;
			aycon = 0;
			azcon = 0;
			sendstop = 1; 
		}

		if ((ch & 0x02) == 0x02)    //수신된 문자에 0x02가 참이면 작동
		{
			axcon = 0;
			aycon = 1;
			azcon = 0;
			sendstop = 1;
		}
		if ((ch & 0x03) == 0x03)     //수신된 문자에 0x03가 참이면 작동
		{
			axcon = 1;
			aycon = 1;
			azcon = 0;
			sendstop = 1;
		}
		if ((ch & 0x04) == 0x04)     //수신된 문자에 0x04가 참이면 작동
		{
			axcon = 0;
			aycon = 0;
			azcon = 1;
			sendstop = 1;
		}
		if ((ch & 0x05) == 0x05)     //수신된 문자에 0x05가 참이면 작동
		{
			axcon = 1;
			aycon = 0;
			azcon = 1;
			sendstop = 1;
		}
		if ((ch & 0x06) == 0x06)     //수신된 문자에 0x06가 참이면 작동
		{
			axcon = 0;
			aycon = 1;
			azcon = 1;
			sendstop = 1;
		}
		if ((ch & 0x07) == 0x07)     //수신된 문자에 0x07가 참이면 작동
		{
			axcon = 1;
			aycon = 1;
			azcon = 1;
			sendstop = 1;
		}
		if ((ch & 0x00) == 0x00)     //수신된 문자에 0x00가 참이면 작동
		{
			axcon = 0;
			aycon = 0;
			azcon = 0;
			LCD_DisplayChar(1, 0, ' ');
			LCD_DisplayChar(2, 0, ' ');
			LCD_DisplayChar(3, 0, ' ');
		}
	}
	// DR 을 읽으면 SR.RXNE bit(flag bit)는 clear 된다. 즉 clear 할 필요없음 

	if ((USART1->SR & USART_SR_PE)) 	// USART_SR_PE=(1<<0)   페리티 인터럽트만 검출  (0x0001)
	{
		SerialSendString("error!!");
	}
}

void USART1_Init(void)
{
	// USART1 : TX(PA9)
	RCC->AHB1ENR |= (1 << 0);	// RCC_AHB1ENR GPIOA Enable
	GPIOA->MODER |= (2 << 2 * 9);	// GPIOB PIN9 Output Alternate function mode					
	GPIOA->OSPEEDR |= (3 << 2 * 9);	// GPIOB PIN9 Output speed (100MHz Very High speed)
	GPIOA->AFR[1] |= (7 << 4);	// Connect GPIOA pin9 to AF7(USART1)

	// USART1 : RX(PA10)
	GPIOA->MODER |= (2 << 2 * 10);	// GPIOA PIN10 Output Alternate function mode
	GPIOA->OSPEEDR |= (3 << 2 * 10);	// GPIOA PIN10 Output speed (100MHz Very High speed
	GPIOA->AFR[1] |= (7 << 8);	// Connect GPIOA pin10 to AF7(USART1)

	RCC->APB2ENR |= (1 << 4);	// RCC_APB2ENR USART1 Enable

	USART_BRR_Configuration(9600); // USART Baud rate Configuration

	USART1->CR1 &= ~(1 << 12);	// USART_WordLength 8 Data bit  보내는 데이터의 길이 설정

	USART1->CR1 &= (1 << 10);	// USART_Parity_ disable


	USART1->CR1 |= (1 << 2);	// 0x0004, USART_Mode_RX Enable
	USART1->CR1 |= (1 << 3);	// 0x0008, USART_Mode_Tx Enable
	USART1->CR2 &= ~(3 << 12);	// 0b00, USART_StopBits_1
	USART1->CR3 = 0x0000;	// No HardwareFlowControl, No DMA

	USART1->CR1 |= (1 << 5);	// 0x0020, RXNE interrupt Enable
	NVIC->ISER[1] |= (1 << (37 - 32));// Enable Interrupt USART1 (NVIC 37번)
	USART1->CR1 |= (1 << 13);	//  0x2000, USART1 Enable
}

void SerialSendChar(uint8_t Ch) // 1문자 보내기 함수
{
	while ((USART1->SR & USART_SR_TXE) == RESET); // USART_SR_TXE=(1<<7), 송신 가능한 상태까지 대기

	USART1->DR = (Ch & 0x01FF);	// 전송 (최대 9bit 이므로 0x01FF과 masking)


}

void SerialSendString(char *str) // 여러문자 보내기 함수
{
	while (*str != '\0') // 종결문자가 나오기 전까지 구동, 종결문자가 나온후에도 구동시 메모리 오류 발생가능성 있음.
	{
		SerialSendChar(*str);	// 포인터가 가르키는 곳의 데이터를 송신
		str++; 			// 포인터 수치 증가
	}
}

///////////////////////////////////////////////////////
// Master mode, Full-duplex, 8bit frame(MSB first), 
// fPCLK/32 Baud rate, Software slave management EN
void SPI1_Init(void)
{
	/*!< Clock Enable  *********************************************************/
	RCC->APB2ENR |= (1 << 12);	// 0x1000, SPI1 Clock EN
	RCC->AHB1ENR |= (1 << 0);	// 0x0001, GPIOA Clock EN		

	/*!< SPI1 pins configuration ************************************************/

	/*!< SPI1 NSS pin(PA8) configuration : GPIO 핀  */
	GPIOA->MODER |= (1 << (2 * 8));	// 0x00010000, PA8 Output mode
	GPIOA->OTYPER &= ~(1 << 8); 	// 0x0100, push-pull(reset state)
	GPIOA->OSPEEDR |= (3 << (2 * 8));	// 0x00030000, PA8 Output speed (100MHZ) 
	GPIOA->PUPDR &= ~(3 << (2 * 8));	// 0x00030000, NO Pullup Pulldown(reset state)

	/*!< SPI1 SCK pin(PA5) configuration : SPI1_SCK */
	GPIOA->MODER |= (2 << (2 * 5)); 	// 0x00000800, PA5 Alternate function mode
	GPIOA->OTYPER &= ~(1 << 5); 	// 0020, PA5 Output type push-pull (reset state)
	GPIOA->OSPEEDR |= (3 << (2 * 5));	// 0x00000C00, PA5 Output speed (100MHz)
	GPIOA->PUPDR |= (2 << (2 * 5)); 	// 0x00000800, PA5 Pull-down
	GPIOA->AFR[0] |= (5 << (4 * 5));	// 0x00500000, Connect PA5 to AF5(SPI1)

	/*!< SPI1 MOSI pin(PA7) configuration : SPI1_MOSI */
	GPIOA->MODER |= (2 << (2 * 7));	// 0x00008000, PA7 Alternate function mode
	GPIOA->OTYPER &= ~(1 << 7);	// 0x0080, PA7 Output type push-pull (reset state)
	GPIOA->OSPEEDR |= (3 << (2 * 7));	// 0x0000C000, PA7 Output speed (100MHz)
	GPIOA->PUPDR |= (2 << (2 * 7)); 	// 0x00008000, PA7 Pull-down
	GPIOA->AFR[0] |= (5 << (4 * 7));	// 0x50000000, Connect PA7 to AF5(SPI1)

	/*!< SPI1 MISO pin(PA6) configuration : SPI1_MISO */
	GPIOA->MODER |= (2 << (2 * 6));	// 0x00002000, PA6 Alternate function mode
	GPIOA->OTYPER &= ~(1 << 6);	// 0x0040, PA6 Output type push-pull (reset state)
	GPIOA->OSPEEDR |= (3 << (2 * 6));	// 0x00003000, PA6 Output speed (100MHz)
	GPIOA->PUPDR |= (2 << (2 * 6));	// 0x00002000, PA6 Pull-down
	GPIOA->AFR[0] |= (5 << (4 * 6));	// 0x05000000, Connect PA6 to AF5(SPI1)

   // Init SPI1 Registers 
	SPI1->CR1 |= (1 << 2);	// MSTR(Master selection)=1, Master mode
	SPI1->CR1 &= ~(1 << 15);	// SPI_Direction_2 Lines_FullDuplex
	SPI1->CR1 &= ~(1 << 11);	// SPI_DataSize_8bit
	SPI1->CR1 |= (1 << 9);  	// SSM(Software slave management)=1, 
			// NSS 핀 상태가 코딩에 의해 결정
	SPI1->CR1 |= (1 << 8);   	// SSI(Internal_slave_select)=1,
			// 현재 MCU를 Master가 이므로 NSS 상태는 'High' 
	SPI1->CR1 &= ~(1 << 7);	// LSBFirst=0, MSB transmitted first    
	SPI1->CR1 |= (4 << 3);	// BR(BaudRate)=0b100, fPCLK/32 (84MHz/32 = 2.625MHz)
	SPI1->CR1 |= (1 << 1);	// CPOL(Clock polarity)=1, CK is 'High' when idle
	SPI1->CR1 |= (1 << 0);	// CPHA(Clock phase)=1, 두 번째 edge 에서 데이터가 샘플링

	SPI1->CR1 |= (1 << 6);	// SPE=1, SPI1 Enable 
}

void TIMER10_Init(void)	// 가속도센서 측정 주기 생성: 350ms
{
	RCC->APB2ENR |= (1 << 17);	// TIMER10 Clock Enable

	TIM10->PSC = 16800 - 1;	// Prescaler 168MHz/16800 = 10KHz (0.1ms)  
	TIM10->ARR = 3500 - 1;	// Auto reload  0.1ms * 3500 = 350ms

	TIM10->CR1 &= ~(1 << 4);	// Countermode = Upcounter (reset state)
	TIM10->CR1 &= ~(3 << 8);	// Clock division = 1 (reset state)
	TIM10->EGR |= (1 << 0);	// Update Event generation    

	TIM10->DIER |= (1 << 0);	// Enable Tim10 Update interrupt
	NVIC->ISER[0] |= (1 << 25);	// Enable Timer10 global Interrupt
	TIM10->CR1 |= (1 << 0);	// Enable Tim10 Counter    
}

void TIM1_UP_TIM10_IRQHandler(void)	// 350ms int
{
	static UINT16 LED_cnt = 0;

	TIM10->SR &= ~(1 << 0);		//Interrupt flag Clear

	bControl = TRUE;		// 350ms마다 센서 측정
	text = 0;
	LED_cnt++;
	if (LED_cnt >= 2)		// 700ms마다 작동
	{
		LED_cnt = 0;
		text = 1;
	}
}

void Display_Process(UINT16 *pBuf)
{
	char str[10];

	if ((int16)pBuf[0] < 0)          //x축 값이 0보다 작다면
	{
		LCD_DisplayText(1, 4, "-");
		sprintf(str, "%d", (abs((int16)pBuf[0])) / 100);	//X축 정수값
		LCD_DisplayText(1, 6, str);

		if (text == 1)                //700ms 주기마다
		{
			if (axcon == 1)              //x값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar('A');     //x축값 전송
					SerialSendChar('x');
					SerialSendChar(':');
					SerialSendChar('-');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[0])) % 100 / 10);	//X축 소숫값
		LCD_DisplayText(1, 8, str);


		if (text == 1)                //700ms 주기마다
		{
			if (axcon == 1)              //x값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 55, 50, 7);             //좌우 막대바 리셋
		LCD_DrawFillRect(93, 55, 50, 7);
		LCD_SetBrushColor(RGB_RED);
		LCD_DrawFillRect(90 - (2.5*(abs((int16)pBuf[0])) / 10), 55, (2.5*(abs((int16)pBuf[0])) / 10) + 1, 7);  //빨간 막대바 그리기
	}
	else if ((int16)pBuf[0] >= 0)    // x축 값이 0보다 크다면
	{
		LCD_DisplayText(1, 4, " ");
		sprintf(str, "%d", (abs((int16)pBuf[0])) / 100);	//x 축 정수값
		LCD_DisplayText(1, 6, str);

		if (text == 1)//700ms 주기마다
		{
			if (axcon == 1)//x값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar('A');       //x축값 전송
					SerialSendChar('x');
					SerialSendChar(':');
					SerialSendChar(' ');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[0])) % 100 / 10);	//x축 소수값
		LCD_DisplayText(1, 8, str);

		if (text == 1)//700ms 주기마다
		{
			if (axcon == 1)//x값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 55, 50, 7);//좌우 막대바 리셋
		LCD_DrawFillRect(93, 55, 50, 7);
		LCD_SetBrushColor(RGB_RED);
		LCD_DrawFillRect(93, 55, (2.5*(abs((int16)pBuf[0])) / 10), 7);//빨간 막대바 그리기
	}

	if ((int16)pBuf[1] < 0)   //y축값이 0보다 작다면
	{
		LCD_DisplayText(2, 4, "-");
		sprintf(str, "%d", (abs((int16)pBuf[1])) / 100);	//y 축 정수값
		LCD_DisplayText(2, 6, str);

		if (text == 1)//700ms 주기마다
		{
			if (aycon == 1)//y값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar('A');        //y축값 전송
					SerialSendChar('y');
					SerialSendChar(':');
					SerialSendChar('-');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[1])) % 100 / 10);	//y축 소수값
		LCD_DisplayText(2, 8, str);

		if (text == 1)//700ms 주기마다
		{
			if (aycon == 1)//y값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 68, 50, 7);         //좌우 막대바 리셋
		LCD_DrawFillRect(93, 68, 50, 7);
		LCD_SetBrushColor(RGB_GREEN);
		LCD_DrawFillRect(90 - (2.5*(abs((int16)pBuf[1])) / 10), 68, (2.5*(abs((int16)pBuf[1])) / 10) + 1, 7);   //녹색 막대바 그리기
	}
	else if ((int16)pBuf[1] >= 0)   //y축 값이 0보다 크다면
	{
		LCD_DisplayText(2, 4, " ");
		sprintf(str, "%d", (abs((int16)pBuf[1])) / 100);	//y축 정수값
		LCD_DisplayText(2, 6, str);

		if (text == 1)//700ms 주기마다
		{
			if (aycon == 1)//y값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar('A');        //y축값 전송
					SerialSendChar('y');
					SerialSendChar(':');
					SerialSendChar(' ');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[1])) % 100 / 10);	//y축 소수값
		LCD_DisplayText(2, 8, str);

		if (text == 1)//700ms 주기마다
		{
			if (aycon == 1)//y값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 68, 50, 7);            //좌우 막대바 리셋
		LCD_DrawFillRect(93, 68, 50, 7);
		LCD_SetBrushColor(RGB_GREEN);
		LCD_DrawFillRect(93, 68, (2.5*(abs((int16)pBuf[1])) / 10), 7);      //녹색 막대바 그리기
	}

	if ((int16)pBuf[2] < 0)   //z축 값이 0보다 작다면
	{
		LCD_DisplayText(3, 4, "-");
		sprintf(str, "%d", (abs((int16)pBuf[2])) / 100);	//z축 정수값
		LCD_DisplayText(3, 6, str);

		if (text == 1)//700ms 주기마다
		{
			if (azcon == 1)//z값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar('A');       //z축값 전송
					SerialSendChar('z');
					SerialSendChar(':');
					SerialSendChar('-');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[2])) % 100 / 10);	//z축 소수값
		LCD_DisplayText(3, 8, str);

		if (text == 1)//700ms 주기마다
		{
			if (azcon == 1)//z값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 80, 50, 7);     //좌우 막대바 리셋
		LCD_DrawFillRect(93, 80, 50, 7);
		LCD_SetBrushColor(RGB_BLUE);
		LCD_DrawFillRect(90 - (2.5*(abs((int16)pBuf[2])) / 10), 80, (2.5*(abs((int16)pBuf[2])) / 10) + 1, 7);  //파란 막대바 그리기
	}
	else if ((int16)pBuf[2] >= 0)  //z축 값이 0보다 크다면
	{
		LCD_DisplayText(3, 4, " ");
		sprintf(str, "%d", (abs((int16)pBuf[2])) / 100);	//z축 정수값
		LCD_DisplayText(3, 6, str);

		if (text == 1)//700ms 주기마다
		{
			if (azcon == 1)//z값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar('A');//z축값 전송
					SerialSendChar('z');
					SerialSendChar(':');
					SerialSendChar(' ');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[2])) % 100 / 10);	//z축 소수값
		LCD_DisplayText(3, 8, str);

		if (text == 1)//700ms 주기마다
		{
			if (azcon == 1)//z값을 요청한 상태라면
			{
				if (sendstop == 1)          //sw0 혹은 pc로 부터 요청이 온다면
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 80, 50, 7);//좌우 막대바 리셋
		LCD_DrawFillRect(93, 80, 50, 7);
		LCD_SetBrushColor(RGB_BLUE);
		LCD_DrawFillRect(93, 80, (2.5*(abs((int16)pBuf[2])) / 10), 7);  //파란 막대바 그리기
	}

	LCD_SetBrushColor(GET_RGB(255, 144, 190));  //보라색
	LCD_DrawFillRect(90, 50, 3, 45);              //막대바 그리기

}

void USART_BRR_Configuration(uint32_t USART_BaudRate)//소숫점을 살리기 위해 최대한 한것.
{
	uint32_t tmpreg = 0x00;
	uint32_t APB2clock = 84000000;	//PCLK2_Frequency
	uint32_t integerdivider = 0x00;
	uint32_t fractionaldivider = 0x00;

	// Determine the integer part 
	if ((USART1->CR1 & USART_CR1_OVER8) != 0) // USART_CR1_OVER8=(1<<15)
	{                                         // USART1->CR1.OVER8 = 1 (8 oversampling)
	// Computing 'Integer part' when the oversampling mode is 8 Samples 
		integerdivider = ((25 * APB2clock) / (2 * USART_BaudRate));
	}
	else  // USART1->CR1.OVER8 = 0 (16 oversampling)
	{	// Computing 'Integer part' when the oversampling mode is 16 Samples 
		integerdivider = ((25 * APB2clock) / (4 * USART_BaudRate));
	}
	tmpreg = (integerdivider / 100) << 4;

	// Determine the fractional part 
	fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

	// Implement the fractional part in the register 
	if ((USART1->CR1 & USART_CR1_OVER8) != 0)	// 8 oversampling
	{
		tmpreg |= (((fractionaldivider * 8) + 50) / 100) & (0x07);
	}
	else 						// 16 oversampling
	{
		tmpreg |= (((fractionaldivider * 16) + 50) / 100) & (0x0F);
	}

	// Write to USART BRR register
	USART1->BRR = (uint16_t)tmpreg;
}

void _GPIO_Init(void)
{
	// LED (GPIO G) 설정
	RCC->AHB1ENR |= 0x00000040;	// RCC_AHB1ENR : GPIOG(bit#6) Enable							
	GPIOG->MODER |= 0x00005555;	// GPIOG 0~7 : Output mode (0b01)						
	GPIOG->OTYPER &= ~0x00FF;	// GPIOG 0~7 : Push-pull  (GP8~15:reset state)	
	GPIOG->OSPEEDR |= 0x00005555;	// GPIOG 0~7 : Output speed 25MHZ Medium speed 

	// SW (GPIO H) 설정 
	RCC->AHB1ENR |= 0x00000080;	// RCC_AHB1ENR : GPIOH(bit#7) Enable							
	GPIOH->MODER &= ~0xFFFF0000;	// GPIOH 8~15 : Input mode (reset state)				
	GPIOH->PUPDR &= ~0xFFFF0000;	// GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

	// Buzzer (GPIO F) 설정 
	RCC->AHB1ENR |= 0x00000020; // RCC_AHB1ENR : GPIOF(bit#5) Enable							
	GPIOF->MODER |= 0x00040000;	// GPIOF 9 : Output mode (0b01)						
	GPIOF->OTYPER &= ~0x0200;	// GPIOF 9 : Push-pull  	
	GPIOF->OSPEEDR |= 0x00040000;	// GPIOF 9 : Output speed 25MHZ Medium speed 

	GPIOG->ODR &= 0x00;	// LED0~7 Off 
}

void DelayMS(unsigned short wMS)
{
	register unsigned short i;

	for (i = 0; i < wMS; i++)
		DelayUS(1000);		//1000us => 1ms
}

void DelayUS(unsigned short wUS)
{
	volatile int Dly = (int)wUS * 17;
	for (; Dly; Dly--);
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

void DisplayTitle(void)
{
	LCD_Clear(RGB_WHITE);
	LCD_SetFont(&Gulim8);		//폰트 
	LCD_SetBackColor(RGB_YELLOW);
	LCD_SetTextColor(RGB_BLACK);    //글자색
	LCD_DisplayText(0, 0, "ACC senseo(SPI)");  // Title

	LCD_SetBackColor(RGB_WHITE);    //글자배경색

	LCD_DisplayText(1, 0, " AX:");	//X 
	LCD_DisplayText(2, 0, " AY:");	//Y 
	LCD_DisplayText(3, 0, " AZ:");	//Z 
	LCD_DisplayText(4, 0, " Ax:");	//X 
	LCD_DisplayText(5, 0, " Ay:");	//y 
	LCD_DisplayText(6, 0, " AZ:");	//Z 
	LCD_DisplayText(1, 7, ".");
	LCD_DisplayText(2, 7, ".");
	LCD_DisplayText(3, 7, ".");

	LCD_SetBrushColor(GET_RGB(255, 144, 190));
	LCD_DrawFillRect(90, 50, 3, 45);
}
