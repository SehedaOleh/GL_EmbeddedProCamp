#include "stm32f30x.h"
#include <string.h>

/* USART1 init function ---------------------------------------------*/
void UART1_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // I/O port A clock enable 

	GPIOA->AFR[1] = 0X00000770;						//pin9 and pin10 AF7 for USART1
	
	GPIOA->MODER |= GPIO_MODER_MODER9_1;  //pin9 in Alternate function mode
	GPIOA->MODER |= GPIO_MODER_MODER10_1; //pin10 in Alternate function mode
	
	GPIOA->OTYPER |= GPIO_OTYPER_OT_9;    // pin9 Output open-drain
	GPIOA->OTYPER |= GPIO_OTYPER_OT_10;   // pin10 Output open-drain
	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR9_0;  // pin9 Pull-up
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0; // pin10 Pull-up
}

/* USART1 open function ---------------------------------------------*/
void UART1_open(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // USART1 clock enable
	
	USART1->CR1 |= USART_CR1_UE; //  USART enable
	USART1->BRR = 0x1D4C; // speed = 9600b/s
	USART1->CR1 |= USART_CR1_TE; //  Transmitter enable
	USART1->CR1 |= USART_CR1_RE; //  Receiver enable 
	
	// ENABLE INTERRUPTS				+
	USART1->CR1 |= USART_CR1_RXNEIE; // RXNE Interrupt Enable
}

/* USART1 send symbol function --------------------------------------*/
void USART1_send_symb( char symbol)
{
	while (!(USART1->ISR & USART_ISR_TC)); // waiting while Transmission of the last symbol is complete
	
	USART1->TDR = symbol;
}
/* USART1 send string function ------------------------------------*/
void UART1_write(uint8_t *string, size_t len)
{
	uint8_t string_point = 0;
	
	while (string_point < len)
	{
		USART1_send_symb( string[string_point++] );
	}
}

void UART1_read(uint8_t *string, size_t len)
{
	uint8_t string_point = 0;
	while (string_point < len)
	{
		if ((USART1->ISR & USART_ISR_RXNE) != 0)
		{
				string[string_point++] = USART1->RDR; 	// read data from RDR
		}
	}
}


/* USART1 close function --------------------------------------------*/
void UART1_close(void)
{		
	RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN; // USART1 clock disable
	
	USART1->CR1 &= ~USART_CR1_UE; //  USART disable
	
	USART1->CR1 &= ~USART_CR1_TE; //  Transmitter disable
	USART1->CR1 &= ~USART_CR1_RE; //  Receiver disable 
	
	// ENABLE INTERRUPTS				+
	USART1->CR1 |= USART_CR1_RXNEIE; // RXNE Interrupt Enable
}
/* USART1 deinit function -------------------------------------------*/
void USART1_DeInit (void)
{
	RCC->AHBENR &= ~RCC_AHBENR_GPIOAEN; 		// I/O port A clock disable 
	GPIOA->AFR[1] &= ~0X00000770;						//pin9 and pin10 ~AF7 
	
	GPIOA->MODER &= ~GPIO_MODER_MODER9_1;  //pin9 disable Alternate function mode
	GPIOA->MODER &= ~GPIO_MODER_MODER10_1; //pin10 disable Alternate function mode
	
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;    // pin9 disable Output open-drain
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_10;   // pin10 disable Output open-drain
	
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9_0;  // pin9 disable Pull-up 
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10_0; // pin10 disable Pull-up
		
	RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST; //USART1 reset
	RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
}
