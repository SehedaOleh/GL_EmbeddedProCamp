#include "stm32f30x.h"

#define TIM_PERIOD (8000)


USART_InitTypeDef USART_InitStructure;
extern uint32_t NbrOfDataToTransfer;
extern uint32_t NbrOfDataToRead;
extern __IO uint32_t TxCounter; 
extern __IO uint32_t RxCounter; 
/** @brief This is runtime counter  */
static volatile uint32_t runtime = 0;

/* Private function prototypes -----------------------------------------------*/
static void NVIC_Config(void);
/* UART function prototypes --------------------------------------------------*/
void UART_init( void );
/* USART1 send symbol function prototypes ------------------------------------*/
void USART1_send_symb( char );
/* USART1 send string function prototypes ------------------------------------*/
void USART1_send_string( char* );

/**
  * @brief  This function init timer to updates each 1 millisecond
  *         and set up interrupt to handle it
  * 
  * @retbal None
  */
void timer_init(void)
{
  TIM_TimeBaseInitTypeDef tim = {0};
  NVIC_InitTypeDef nvic = {0};
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  
  /* Period 1ms */
  tim.TIM_Prescaler = 0;
  tim.TIM_CounterMode = TIM_CounterMode_Up;
  tim.TIM_Period = TIM_PERIOD;
  tim.TIM_ClockDivision = TIM_CKD_DIV1;
  tim.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM4, &tim);

  /* Enable the TIM4 global Interrupt */
  nvic.NVIC_IRQChannel = TIM4_IRQn;
  nvic.NVIC_IRQChannelPreemptionPriority = 0;
  nvic.NVIC_IRQChannelSubPriority = 1;
  nvic.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&nvic);
  
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

  TIM_Cmd(TIM4, ENABLE);
}

/**
  * @brief This function set up system clock source as High Speed Internal (HSI) source
  * 
  * @retval
  */
void clk_init(void)
{
  RCC_HSICmd(ENABLE);

  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET)    
    {
      /* Wait while HSI source is not ready */
    }
    
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
}

/**
  * @brief This function perform a delay in miliseconds
  * 
  * @retval None
  */
void delay_ms(uint32_t delay)
{
  uint32_t target_runtime = runtime + delay;

  while(target_runtime != runtime)
    {
      /* Wait while runtime variable reach target_runtime value */
    }
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

	/* NVIC configuration */
  // NVIC_Config();
  
  /* USARTx configuration ------------------------------------------------------*/
  /* USARTx configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - Two Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
//  USART_InitStructure.USART_BaudRate = 9600;
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits = USART_StopBits_2;
//  USART_InitStructure.USART_Parity = USART_Parity_Odd;
//  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//STM_EVAL_COMInit(COM1, &USART_InitStructure);
	
	
	UART_init();
  clk_init();
  timer_init();

  while(1)
  {
   USART1_send_string ("Test");
		delay_ms(500);
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
void TIM4_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
    {
      runtime++;
      TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}
// UART init() use only CMSIS library
//
void UART_init(void)
{
	//ENABLE GPIO FOR USART 
	//ENABLE CORRECT MODE FOR PINS		OPEN DRAIN + PULL_UP + ALTERNATE_MODE
		
	// DEVICE->REGISTER = VALUE;
	
	// ENBALE USART MODULE CLOCKING   (RCC) +
	// INPUT 	BAUDRATE  (BRR)		+
	// ENABLE USART		+
	// ENABLE RECEIVER		+
	// ENABLE TRANSMITTER		+
	// ENABLE INTERRUPTS
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // I/O port A clock enable 

	GPIOA->AFR[1] = 0X00000770;						//pin9 and pin10 AF7 for USART1
	
	GPIOA->MODER |= GPIO_MODER_MODER9_1;  //pin9 in Alternate function mode
	GPIOA->MODER |= GPIO_MODER_MODER10_1; //pin10 in Alternate function mode
	
	GPIOA->OTYPER |= GPIO_OTYPER_OT_9;    // pin9 Output open-drain
	GPIOA->OTYPER |= GPIO_OTYPER_OT_10;   // pin10 Output open-drain
	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR9_0;  // pin9 Pull-up
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0; // pin10 Pull-up

	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // USART1 clock enable
	
	USART1->CR1 |= USART_CR1_UE; //  USART enable
	USART1->BRR = 0x1D4C; // speed = 9600b/s
	USART1->CR1 |= USART_CR1_TE; //  Transmitter enable
	USART1->CR1 |= USART_CR1_RE; //  Receiver enable 
	
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
	
	while ( string[string_point])
	{
		USART1_send_symb(string[string_point++]);
	}
}


/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
//static void NVIC_Config(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;

//  /* Enable the USART1 Interrupt */
//  //NVIC_InitStructure.NVIC_IRQChannel = EVAL_COM1_;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//}
