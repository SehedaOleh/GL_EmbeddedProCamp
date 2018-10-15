#include "stm32f30x.h"

# define RxLength 32

char rx_uart[RxLength] = {}; //data buffer for USART1
	
/* Private function prototypes -----------------------------------------------*/
/* UART function prototypes --------------------------------------------------*/
void UART_init( void );

/* USART1 send symbol function prototypes ------------------------------------*/
void USART1_send_symb( char );

/* USART1 send string function prototypes ------------------------------------*/
void USART1_send_string( char* );

/* Test delay function prototypes --------------------------------------------*/
void delay(int);

	/* */
void USART1_DeInit (void);
	
	
/* Restore config function prototypes ----------------------------------------*/
void RestoreConfiguration(void);

/**
  * @brief  This is Main routine. 
  *         It is init all necessary perephery and then echo UART info.
  * 
  * @retval If main routine return you something, then you get in trouble :)
  */
int main(void)
{
	//	GPIOA->MODER = GPIO_MODER_MODER7_0;		//digital output
  //	GPIOA->MODER = GPIO_MODER_MODER8_1;		//alternate func
  //	GPIOA->MODER = GPIO_MODER_MODER9;			//analog
	
  char *pString = "TESTstring any types\r\n";
	
	UART_init();
		
  while(1)
  {
//		USART1_send_string (pString);
//		delay (2000);
//		USART1_send_string (rx_uart);
//		delay (2000);
//		rx_uart[0] = '\0'; // clear first symbol in array after resending
  }

	/* USART Disable */
  USART1_DeInit();
	
  return 0;
}

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


// ************************************ from exampels **************************
 
// USART_InitTypeDef USART_InitStructure;

	/* USARTx configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 8 Bits
  - Stop Bit = 1 Stop Bit
  - Parity = No Parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
 
 /* USART_DeInit(USART1);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);*/
	
}

/* USART1 send symbol function ------------------------------------*/
void USART1_send_symb( char symbol)
{
	while (!(USART1->ISR & USART_ISR_TC)); // waiting while Transmission of the last symbol is complete
	
	USART1->TDR = symbol;
}

/* USART1 send string function ------------------------------------*/
void USART1_send_string( char *string)
{
	uint8_t string_point = 0;
	
	while (string[string_point])
	{
		USART1_send_symb( string[string_point++] );
	}
}

/* Test delay function --------------------------------------------*/
void delay(int test_delay)
{
	int i = test_delay * 10000;
	while(i--);
}	

/* USART1 read function --------------------------------------------*/
void USART1_IRQHandler()
{
//	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;		//PORT_E Clock enable
//	GPIOE->MODER |= GPIO_MODER_MODER8_0;	//PE8 digital output enable
//	GPIOE->MODER |= GPIO_MODER_MODER9_0;	//PE9 digital output enable
//	GPIOE->MODER |= GPIO_MODER_MODER10_0;	//PE10 digital output enable
//	GPIOE->MODER |= GPIO_MODER_MODER11_0;	//PE11 digital output enable
//	GPIOE->MODER |= GPIO_MODER_MODER12_0;	//PE12 digital output enable
//	GPIOE->MODER |= GPIO_MODER_MODER13_0;	//PE13 digital output enable
//	GPIOE->MODER |= GPIO_MODER_MODER14_0;	//PE14 digital output enable
//	GPIOE->MODER |= GPIO_MODER_MODER15_0;	//PE15 digital output enable
//	
//	GPIOE->ODR = 0xFF00;
//*********************************************************************************	
	//echo method one
	
  char rxData = 0; // data to recive
	int i = 0;
	if ((USART1->ISR & USART_ISR_RXNE) != 0)
	{
	USART1->TDR = USART1->RDR;
	}
	
//*********************************************************************************	
	
//	while('\0' == rxData)
//	{
//			while ((USART1->ISR & USART_ISR_RXNE) != 0);		// check flag if data is in RDR

//			rxData = USART1->RDR; 					// read data from RDR
//			rx_uart[i] = rxData;

//			i ++;
//	}
}
void USART1_DeInit (void)
{
	RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST; //USART1 reset
	RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
}
void RestoreConfiguration(void) // functions from examples
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/    
  /* Enable HSE */    
  RCC_HSEConfig(RCC_HSE_ON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
  HSEStatus = RCC_WaitForHSEStartUp();

  if (HSEStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    
    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
    
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);
    
    /*  PLL configuration:  = HSE *  9 = 72 MHz */
    RCC_PREDIV1Config(RCC_PREDIV1_Div1);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
    
    /* Enable PLL */
    RCC_PLLCmd(ENABLE);
    
    /* PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  } 
}
