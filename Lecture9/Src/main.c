#include "main.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"
#include "Init.h"

#include "FreeRTOS.h"
#include "task.h"

/* Private variables ---------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);

void vApplicationIdleHook(void)
{
		volatile int i = 100;
//		LED01ON();
		while (i)
		{

		i--;
		}
//		LED01OFF();
}
int main(void)
{
  HAL_Init();

//	vTaskPrioritySet(StartTask02, 5);
//	vTaskPrioritySet(StartTask03, 2);
  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();

  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* Start scheduler */
  osKernelStart();

  while (1)
  {
  }
}

/* StartDefaultTask */
void StartDefaultTask(void const * argument)
{
	vTaskPrioritySet(NULL, 2);
  for(;;)
  {
    LED02OFF();
		LED01ON();
    osDelay(100);
		LED01OFF();
		LED02ON();
    osDelay(100);
  }
}
/* StartTask02 */
void StartTask02(void const * argument)
{
  for(;;)
  {
		LED04OFF();
		LED03ON();
    osDelay(100);
		LED03OFF();
		LED04ON();
    osDelay(100);
  }
}/* StartTask03 */
void StartTask03(void const * argument)
{
  for(;;)
  {
    osDelay(1);
  }
}
/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 

}
#endif /* USE_FULL_ASSERT */

