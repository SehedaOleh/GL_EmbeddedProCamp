#include "stm32f30x.h"
#include <string.h>
#include "USART.h"

# define RxLength 32

static volatile uint32_t runtime = 0;
	
/* Private function prototypes -----------------------------------------------*/

//void delay(int);

void RestoreConfiguration(void);
void delay_ms(uint32_t);

int main(void)
{
	//string for debug
	 static uint8_t UART_rxdata[10] = {"adsr"};
	//
	UART1_init();
	UART1_open();
  while(1)
  {
		UART1_write(UART_rxdata, sizeof(UART_rxdata));
		delay_ms (100);
		UART1_read(UART_rxdata, 3);
		delay_ms (1000);
		UART1_write(UART_rxdata, 3);
		delay_ms (1000);
	}
	/* USART Disable */
	UART1_close();
  USART1_DeInit();
	
  return 0;
}

/* Test delay function --------------------------------------------*/
//void delay(int test_delay)
//{
//	int i = test_delay * 10000;
//	while(i--);
//}	

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
