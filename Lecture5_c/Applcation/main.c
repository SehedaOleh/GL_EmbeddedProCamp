#include "stm32f30x.h"
#include <string.h>
#include "USART.h"

# define RxLength 32

//char rx_uart[RxLength] = {}; //data buffer for USART1
char rxData = 0; // data to recive
	
/* Private function prototypes -----------------------------------------------*/

void delay(int);

void RestoreConfiguration(void);

int main(void)
{
	//string for debug
	 uint8_t *pString = "TESTstring any types\r\n";
	//
	UART1_init();
	UART1_open();
	
	UART1_close();
  USART1_DeInit();
  while(1)
  {
		UART1_write(pString, 12);
		delay (1000);
		UART1_read(pString, 10);
		delay (1000);
		UART1_write(pString, 10);
		delay (1000);
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
