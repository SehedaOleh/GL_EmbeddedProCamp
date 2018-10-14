#include "stm32f30x.h"

#define TIM_PERIOD (8000)
/**
  * @brief This is runtime counter
  */
static volatile uint32_t runtime = 0;

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
	

  clk_init();
  timer_init();

//  while(1)
//  {
//   
//  }

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

