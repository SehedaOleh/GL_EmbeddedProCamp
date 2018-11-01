#include "stm32f30x.h"
#include <string.h>
#include "USART.h"

# define RxLength 32
#define TIM_PERIOD (8000)

static volatile uint32_t runtime = 0;
	
/* Private function prototypes -----------------------------------------------*/

void delay(int);

void RestoreConfiguration(void);
void delay_ms(uint32_t);
void timer_init(void);
void clk_init(void);

int main(void)
{
	//string for debug
	 static uint8_t UART_rxdata[10] = {"adsr"};
	//
	 
//	clk_init();
//  timer_init();
	 
	UART1_init();
	UART1_open();
  while(1)
  {

		UART1_read(UART_rxdata, 3);
		
		UART1_write(UART_rxdata, 3);
		
	}
	/* USART Disable */
	UART1_close();
  USART1_DeInit();
	
  return 0;
}

/* Test delay function --------------------------------------------*/
void delay(int test_delay)
{
	int i = test_delay * 10000;
	while(i--);
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
void delay_ms(uint32_t delay)
{
  uint32_t target_runtime = runtime + delay;

  while(target_runtime != runtime)
    {
      /* Wait while runtime variable reach target_runtime value */
    }
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

