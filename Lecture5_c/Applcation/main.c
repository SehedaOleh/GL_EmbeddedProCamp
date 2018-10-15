#include "stm32f30x.h"

/* Private function prototypes -----------------------------------------------*/
/* UART function prototypes --------------------------------------------------*/
void UART_init( void );

/* USART1 send symbol function prototypes ------------------------------------*/
void USART1_send_symb( char );

/* USART1 send string function prototypes ------------------------------------*/
void USART1_send_string( char* );

void delay(int test_delay)
{
	int i = test_delay * 10000;
	while(i--);
}	


/**
  * @brief  This is Main routine. 
  *         It is init all necessary perephery and then just toggle LED with 1 sec period.
  * 
  * @retval If main routine return you something, then you get in trouble :)
  */
int main(void)
{
	//	GPIOA->MODER = GPIO_MODER_MODER7_0;		//digital output
  //	GPIOA->MODER = GPIO_MODER_MODER8_1;		//alternate func
  //	GPIOA->MODER = GPIO_MODER_MODER9;			//analog
	
//  clk_init();
//  timer_init();
  char *pString = "TESTstring any types\r\n";
	UART_init();

  while(1)
  {
		USART1_send_string (pString);
		delay (500);
  }

  return 0;
}

/**
	* @brief  This is an interrupt handler routine for TIM4.
  *         It just check if source of interrupt is Timer Update event.
  *         If yes, then it updates runtime counter and clear pending bit.
  *
  * @retval None
  */
//void TIM4_IRQHandler(void)
//{
//  if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
//    {
//      runtime++;
//      TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//    }
//}
// UART init() use only CMSIS library
//
void UART_init(void)
{
	//ENABLE GPIO FOR USART 
	//ENABLE CORRECT MODE FOR PINS		OPEN DRAIN + PULL_UP + ALTERNATE_MODE
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // I/O port A clock enable 

	GPIOA->AFR[1] = 0X00000770;						//pin9 and pin10 AF7 for USART1
	
	GPIOA->MODER |= GPIO_MODER_MODER9_1;  //pin9 in Alternate function mode
	GPIOA->MODER |= GPIO_MODER_MODER10_1; //pin10 in Alternate function mode
	
	GPIOA->OTYPER |= GPIO_OTYPER_OT_9;    // pin9 Output open-drain
	GPIOA->OTYPER |= GPIO_OTYPER_OT_10;   // pin10 Output open-drain
	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR9_0;  // pin9 Pull-up
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0; // pin10 Pull-up
	
	// ENBALE USART MODULE CLOCKING   (RCC) +
	// INPUT 	BAUDRATE  (BRR)		+
	// ENABLE USART							+
	// ENABLE RECEIVER					+
	// ENABLE TRANSMITTER				+
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // USART1 clock enable
	
	USART1->CR1 |= USART_CR1_UE; //  USART enable
	USART1->BRR = 0x1D4C; // speed = 9600b/s
	USART1->CR1 |= USART_CR1_TE; //  Transmitter enable
	USART1->CR1 |= USART_CR1_RE; //  Receiver enable 
	
	// ENABLE INTERRUPTS				+
	USART1->CR1 |= USART_CR1_RXNEIE; // RXNE Interrupt Enable
	NVIC_EnableIRQ(USART1_IRQn); // USART1 global Interrupt
}

void USART1_send_symb( char symbol)
{
	while (!(USART1->ISR & USART_ISR_TC)); // waiting while Transmission of the last symbol is complete
	
	USART1->TDR = symbol;
}

void USART1_send_string( char *string)
{
	uint8_t string_point = 0;
	
	while (string[string_point])
	{
		USART1_send_symb( string[string_point++] );
	}
}



