//***************************************************
//�ۼ��� : 2015132039 �ֿ���
//�ۼ��� : 2019 / 11 / 29
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

int axcon = 0;    // x�� ������ ��Ʈ�� �ϱ����� ��������
int aycon = 0;    // y�� ������ ��Ʈ�� �ϱ����� ��������
int azcon = 0;    // z�� ������ ��Ʈ�� �ϱ����� ��������
int text = 0;     //700ms������ ���� ��������
int sendstop = 0; // sw0�� �������� �۵��ϱ� ���� ��������

UINT8 bControl;

int main(void)
{
	UINT16 buffer[3];

	LCD_Init();		// LCD ���� �Լ�
	DelayMS(10);		// LCD���� ������
	DisplayTitle();		// LCD �ʱ�ȭ�鱸�� �Լ�

	_GPIO_Init();		// LED, SW �ʱ�ȭ
	SPI1_Init();        	// SPI1 �ʱ�ȭ
	ACC_Init();		// ���ӵ����� �ʱ�ȭ
	TIMER10_Init();		// ���ӵ����� ��ĵ �ֱ� ����
	USART1_Init();     //uart��� �ʱ�ȭ
	Fram_Init();        // FRAM �ʱ�ȭ 
	Fram_Status_Config();



	while (1)
	{
		switch (KEY_Scan())
		{
		case SW0_PUSH: 		//SW0

			sendstop = 1;  //���۽���!
			break;
		}
		if (bControl)
		{
			bControl = FALSE;
			SPI1_Process(&buffer[0]);	// SPI����� �̿��Ͽ� ���ӵ����� ����
			Display_Process(&buffer[0]);	// �������� LCD�� ǥ��
			if ((Fram_Read(350) & 0x01) == 0x01)  //0x01���� �־��ٸ� x�� ����
			{
				LCD_DisplayChar(1, 0, '*');     
				LCD_DisplayChar(2, 0, ' ');
				LCD_DisplayChar(3, 0, ' ');
				axcon = 1;
				aycon = 0;
				azcon = 0;
			}
			if ((Fram_Read(350) & 0x02) == 0x02)//0x02���� �־��ٸ� y�� ����
			{
				LCD_DisplayChar(1, 0, ' ');
				LCD_DisplayChar(2, 0, '*');
				LCD_DisplayChar(3, 0, ' ');
				axcon = 0;
				aycon = 1;
				azcon = 0;
			}
			if ((Fram_Read(350) & 0x03) == 0x03)//0x03���� �־��ٸ� x��, y�� ����
			{
				LCD_DisplayChar(1, 0, '*');
				LCD_DisplayChar(2, 0, '*');
				LCD_DisplayChar(3, 0, ' ');
				axcon = 1;
				aycon = 1;
				azcon = 0;
			}
			if ((Fram_Read(350) & 0x04) == 0x04)//0x04���� �־��ٸ� z�� ����
			{
				LCD_DisplayChar(1, 0, ' ');
				LCD_DisplayChar(2, 0, ' ');
				LCD_DisplayChar(3, 0, '*');
				axcon = 0;
				aycon = 0;
				azcon = 1;
			}
			if ((Fram_Read(350) & 0x05) == 0x05)//0x05���� �־��ٸ� x��, z�� ����
			{
				LCD_DisplayChar(1, 0, '*');
				LCD_DisplayChar(2, 0, ' ');
				LCD_DisplayChar(3, 0, '*');
				axcon = 1;
				aycon = 0;
				azcon = 1;
			}
			if ((Fram_Read(350) & 0x06) == 0x06)//0x06���� �־��ٸ� y��, z�� ����
			{
				LCD_DisplayChar(1, 0, ' ');
				LCD_DisplayChar(2, 0, '*');
				LCD_DisplayChar(3, 0, '*');
				axcon = 0;
				aycon = 1;
				azcon = 1;
			}
			if ((Fram_Read(350) & 0x07) == 0x07)//0x07���� �־��ٸ� x��, y��, z�� ����
			{
				LCD_DisplayChar(1, 0, '*');
				LCD_DisplayChar(2, 0, '*');
				LCD_DisplayChar(3, 0, '*');
				axcon = 1;
				aycon = 1;
				azcon = 1;
			}
			if (Fram_Read(350) == 0x00) //0x00�� �̾��ٸ� ��� ����
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

void USART1_IRQHandler(void)	//��� ���ͷ�Ʈ�� �ڵ鷯.
{

	if ((USART1->SR & USART_SR_RXNE)) 	// USART_SR_RXNE=(1<<5) 
	{
		uint16_t ch;

		ch = (uint16_t)(USART1->DR & (uint16_t)0x01FF);	// ���ŵ� ���� ����
		Fram_Write(350, ch);  //���ŵ� ���� 350������ ����
		if ((ch & 0x01) == 0x01)     //���ŵ� ���ڿ� 0x01�� ���̸� �۵�
		{
			axcon = 1;
			aycon = 0;
			azcon = 0;
			sendstop = 1; 
		}

		if ((ch & 0x02) == 0x02)    //���ŵ� ���ڿ� 0x02�� ���̸� �۵�
		{
			axcon = 0;
			aycon = 1;
			azcon = 0;
			sendstop = 1;
		}
		if ((ch & 0x03) == 0x03)     //���ŵ� ���ڿ� 0x03�� ���̸� �۵�
		{
			axcon = 1;
			aycon = 1;
			azcon = 0;
			sendstop = 1;
		}
		if ((ch & 0x04) == 0x04)     //���ŵ� ���ڿ� 0x04�� ���̸� �۵�
		{
			axcon = 0;
			aycon = 0;
			azcon = 1;
			sendstop = 1;
		}
		if ((ch & 0x05) == 0x05)     //���ŵ� ���ڿ� 0x05�� ���̸� �۵�
		{
			axcon = 1;
			aycon = 0;
			azcon = 1;
			sendstop = 1;
		}
		if ((ch & 0x06) == 0x06)     //���ŵ� ���ڿ� 0x06�� ���̸� �۵�
		{
			axcon = 0;
			aycon = 1;
			azcon = 1;
			sendstop = 1;
		}
		if ((ch & 0x07) == 0x07)     //���ŵ� ���ڿ� 0x07�� ���̸� �۵�
		{
			axcon = 1;
			aycon = 1;
			azcon = 1;
			sendstop = 1;
		}
		if ((ch & 0x00) == 0x00)     //���ŵ� ���ڿ� 0x00�� ���̸� �۵�
		{
			axcon = 0;
			aycon = 0;
			azcon = 0;
			LCD_DisplayChar(1, 0, ' ');
			LCD_DisplayChar(2, 0, ' ');
			LCD_DisplayChar(3, 0, ' ');
		}
	}
	// DR �� ������ SR.RXNE bit(flag bit)�� clear �ȴ�. �� clear �� �ʿ���� 

	if ((USART1->SR & USART_SR_PE)) 	// USART_SR_PE=(1<<0)   �丮Ƽ ���ͷ�Ʈ�� ����  (0x0001)
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

	USART1->CR1 &= ~(1 << 12);	// USART_WordLength 8 Data bit  ������ �������� ���� ����

	USART1->CR1 &= (1 << 10);	// USART_Parity_ disable


	USART1->CR1 |= (1 << 2);	// 0x0004, USART_Mode_RX Enable
	USART1->CR1 |= (1 << 3);	// 0x0008, USART_Mode_Tx Enable
	USART1->CR2 &= ~(3 << 12);	// 0b00, USART_StopBits_1
	USART1->CR3 = 0x0000;	// No HardwareFlowControl, No DMA

	USART1->CR1 |= (1 << 5);	// 0x0020, RXNE interrupt Enable
	NVIC->ISER[1] |= (1 << (37 - 32));// Enable Interrupt USART1 (NVIC 37��)
	USART1->CR1 |= (1 << 13);	//  0x2000, USART1 Enable
}

void SerialSendChar(uint8_t Ch) // 1���� ������ �Լ�
{
	while ((USART1->SR & USART_SR_TXE) == RESET); // USART_SR_TXE=(1<<7), �۽� ������ ���±��� ���

	USART1->DR = (Ch & 0x01FF);	// ���� (�ִ� 9bit �̹Ƿ� 0x01FF�� masking)


}

void SerialSendString(char *str) // �������� ������ �Լ�
{
	while (*str != '\0') // ���Ṯ�ڰ� ������ ������ ����, ���Ṯ�ڰ� �����Ŀ��� ������ �޸� ���� �߻����ɼ� ����.
	{
		SerialSendChar(*str);	// �����Ͱ� ����Ű�� ���� �����͸� �۽�
		str++; 			// ������ ��ġ ����
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

	/*!< SPI1 NSS pin(PA8) configuration : GPIO ��  */
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
			// NSS �� ���°� �ڵ��� ���� ����
	SPI1->CR1 |= (1 << 8);   	// SSI(Internal_slave_select)=1,
			// ���� MCU�� Master�� �̹Ƿ� NSS ���´� 'High' 
	SPI1->CR1 &= ~(1 << 7);	// LSBFirst=0, MSB transmitted first    
	SPI1->CR1 |= (4 << 3);	// BR(BaudRate)=0b100, fPCLK/32 (84MHz/32 = 2.625MHz)
	SPI1->CR1 |= (1 << 1);	// CPOL(Clock polarity)=1, CK is 'High' when idle
	SPI1->CR1 |= (1 << 0);	// CPHA(Clock phase)=1, �� ��° edge ���� �����Ͱ� ���ø�

	SPI1->CR1 |= (1 << 6);	// SPE=1, SPI1 Enable 
}

void TIMER10_Init(void)	// ���ӵ����� ���� �ֱ� ����: 350ms
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

	bControl = TRUE;		// 350ms���� ���� ����
	text = 0;
	LED_cnt++;
	if (LED_cnt >= 2)		// 700ms���� �۵�
	{
		LED_cnt = 0;
		text = 1;
	}
}

void Display_Process(UINT16 *pBuf)
{
	char str[10];

	if ((int16)pBuf[0] < 0)          //x�� ���� 0���� �۴ٸ�
	{
		LCD_DisplayText(1, 4, "-");
		sprintf(str, "%d", (abs((int16)pBuf[0])) / 100);	//X�� ������
		LCD_DisplayText(1, 6, str);

		if (text == 1)                //700ms �ֱ⸶��
		{
			if (axcon == 1)              //x���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar('A');     //x�ప ����
					SerialSendChar('x');
					SerialSendChar(':');
					SerialSendChar('-');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[0])) % 100 / 10);	//X�� �Ҽ���
		LCD_DisplayText(1, 8, str);


		if (text == 1)                //700ms �ֱ⸶��
		{
			if (axcon == 1)              //x���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 55, 50, 7);             //�¿� ����� ����
		LCD_DrawFillRect(93, 55, 50, 7);
		LCD_SetBrushColor(RGB_RED);
		LCD_DrawFillRect(90 - (2.5*(abs((int16)pBuf[0])) / 10), 55, (2.5*(abs((int16)pBuf[0])) / 10) + 1, 7);  //���� ����� �׸���
	}
	else if ((int16)pBuf[0] >= 0)    // x�� ���� 0���� ũ�ٸ�
	{
		LCD_DisplayText(1, 4, " ");
		sprintf(str, "%d", (abs((int16)pBuf[0])) / 100);	//x �� ������
		LCD_DisplayText(1, 6, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (axcon == 1)//x���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar('A');       //x�ప ����
					SerialSendChar('x');
					SerialSendChar(':');
					SerialSendChar(' ');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[0])) % 100 / 10);	//x�� �Ҽ���
		LCD_DisplayText(1, 8, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (axcon == 1)//x���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 55, 50, 7);//�¿� ����� ����
		LCD_DrawFillRect(93, 55, 50, 7);
		LCD_SetBrushColor(RGB_RED);
		LCD_DrawFillRect(93, 55, (2.5*(abs((int16)pBuf[0])) / 10), 7);//���� ����� �׸���
	}

	if ((int16)pBuf[1] < 0)   //y�ప�� 0���� �۴ٸ�
	{
		LCD_DisplayText(2, 4, "-");
		sprintf(str, "%d", (abs((int16)pBuf[1])) / 100);	//y �� ������
		LCD_DisplayText(2, 6, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (aycon == 1)//y���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar('A');        //y�ప ����
					SerialSendChar('y');
					SerialSendChar(':');
					SerialSendChar('-');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[1])) % 100 / 10);	//y�� �Ҽ���
		LCD_DisplayText(2, 8, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (aycon == 1)//y���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 68, 50, 7);         //�¿� ����� ����
		LCD_DrawFillRect(93, 68, 50, 7);
		LCD_SetBrushColor(RGB_GREEN);
		LCD_DrawFillRect(90 - (2.5*(abs((int16)pBuf[1])) / 10), 68, (2.5*(abs((int16)pBuf[1])) / 10) + 1, 7);   //��� ����� �׸���
	}
	else if ((int16)pBuf[1] >= 0)   //y�� ���� 0���� ũ�ٸ�
	{
		LCD_DisplayText(2, 4, " ");
		sprintf(str, "%d", (abs((int16)pBuf[1])) / 100);	//y�� ������
		LCD_DisplayText(2, 6, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (aycon == 1)//y���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar('A');        //y�ప ����
					SerialSendChar('y');
					SerialSendChar(':');
					SerialSendChar(' ');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[1])) % 100 / 10);	//y�� �Ҽ���
		LCD_DisplayText(2, 8, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (aycon == 1)//y���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 68, 50, 7);            //�¿� ����� ����
		LCD_DrawFillRect(93, 68, 50, 7);
		LCD_SetBrushColor(RGB_GREEN);
		LCD_DrawFillRect(93, 68, (2.5*(abs((int16)pBuf[1])) / 10), 7);      //��� ����� �׸���
	}

	if ((int16)pBuf[2] < 0)   //z�� ���� 0���� �۴ٸ�
	{
		LCD_DisplayText(3, 4, "-");
		sprintf(str, "%d", (abs((int16)pBuf[2])) / 100);	//z�� ������
		LCD_DisplayText(3, 6, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (azcon == 1)//z���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar('A');       //z�ప ����
					SerialSendChar('z');
					SerialSendChar(':');
					SerialSendChar('-');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[2])) % 100 / 10);	//z�� �Ҽ���
		LCD_DisplayText(3, 8, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (azcon == 1)//z���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 80, 50, 7);     //�¿� ����� ����
		LCD_DrawFillRect(93, 80, 50, 7);
		LCD_SetBrushColor(RGB_BLUE);
		LCD_DrawFillRect(90 - (2.5*(abs((int16)pBuf[2])) / 10), 80, (2.5*(abs((int16)pBuf[2])) / 10) + 1, 7);  //�Ķ� ����� �׸���
	}
	else if ((int16)pBuf[2] >= 0)  //z�� ���� 0���� ũ�ٸ�
	{
		LCD_DisplayText(3, 4, " ");
		sprintf(str, "%d", (abs((int16)pBuf[2])) / 100);	//z�� ������
		LCD_DisplayText(3, 6, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (azcon == 1)//z���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar('A');//z�ప ����
					SerialSendChar('z');
					SerialSendChar(':');
					SerialSendChar(' ');
					SerialSendChar(*str);
					SerialSendChar('.');
				}
			}
		}

		sprintf(str, "%d", (abs((int16)pBuf[2])) % 100 / 10);	//z�� �Ҽ���
		LCD_DisplayText(3, 8, str);

		if (text == 1)//700ms �ֱ⸶��
		{
			if (azcon == 1)//z���� ��û�� ���¶��
			{
				if (sendstop == 1)          //sw0 Ȥ�� pc�� ���� ��û�� �´ٸ�
				{
					SerialSendChar(*str);
					SerialSendChar('g');
					SerialSendChar(' ');
				}
			}
		}

		LCD_SetBrushColor(RGB_WHITE);
		LCD_DrawFillRect(40, 80, 50, 7);//�¿� ����� ����
		LCD_DrawFillRect(93, 80, 50, 7);
		LCD_SetBrushColor(RGB_BLUE);
		LCD_DrawFillRect(93, 80, (2.5*(abs((int16)pBuf[2])) / 10), 7);  //�Ķ� ����� �׸���
	}

	LCD_SetBrushColor(GET_RGB(255, 144, 190));  //�����
	LCD_DrawFillRect(90, 50, 3, 45);              //����� �׸���

}

void USART_BRR_Configuration(uint32_t USART_BaudRate)//�Ҽ����� �츮�� ���� �ִ��� �Ѱ�.
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
	// LED (GPIO G) ����
	RCC->AHB1ENR |= 0x00000040;	// RCC_AHB1ENR : GPIOG(bit#6) Enable							
	GPIOG->MODER |= 0x00005555;	// GPIOG 0~7 : Output mode (0b01)						
	GPIOG->OTYPER &= ~0x00FF;	// GPIOG 0~7 : Push-pull  (GP8~15:reset state)	
	GPIOG->OSPEEDR |= 0x00005555;	// GPIOG 0~7 : Output speed 25MHZ Medium speed 

	// SW (GPIO H) ���� 
	RCC->AHB1ENR |= 0x00000080;	// RCC_AHB1ENR : GPIOH(bit#7) Enable							
	GPIOH->MODER &= ~0xFFFF0000;	// GPIOH 8~15 : Input mode (reset state)				
	GPIOH->PUPDR &= ~0xFFFF0000;	// GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

	// Buzzer (GPIO F) ���� 
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
	LCD_SetFont(&Gulim8);		//��Ʈ 
	LCD_SetBackColor(RGB_YELLOW);
	LCD_SetTextColor(RGB_BLACK);    //���ڻ�
	LCD_DisplayText(0, 0, "ACC senseo(SPI)");  // Title

	LCD_SetBackColor(RGB_WHITE);    //���ڹ���

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
