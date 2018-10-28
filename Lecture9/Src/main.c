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
TaskHandle_t myTaskHandle; //handler for myTask

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void vmyTaskCode( void* pvParameters);
void vOtherFunction( void );

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
	
	/* definition and creation of vmyTaskCode */
	vOtherFunction();
		
	/* Start scheduler */
  osKernelStart();

  while (1)
  {
  }
}

/* Task to be created. */
	void vmyTaskCode( void* pvParameters)
	{
			/* The parameter value is expected to be 1 as 1 is passed in the
			pvParameters value in the call to xTaskCreate() below. 
			configASSERT( ( ( uint32_t ) pvParameters ) == 1 );*/

			for( ;; )
			{
//				LED08OFF();
//				LED07ON();
//				osDelay(100);
//				LED07OFF();
//				LED08ON();
//				osDelay(100);
//				vTaskDelete(NULL); 
				osDelay(100);
				vTaskDelete(NULL); 
			}
			
	}
	/* Function that creates a task. */
	
	void vOtherFunction(void)
	{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

			/* Create the task, storing the handle. */
			xReturned = xTaskCreate(
											vmyTaskCode,       /* Function that implements the task. */
											"NAME",          /* Text name for the task. */
											16,      /* Stack size in words, not bytes. */
											( void * ) 1,    /* Parameter passed into the task. */
											tskIDLE_PRIORITY,/* Priority at which the task is created. */
											&myTaskHandle );      /* Used to pass out the created task's handle. */

			if( xReturned == pdPASS )
			{
//					vTaskDelete (xHandle);
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
	vTaskPrioritySet(NULL, 3);

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
	vTaskPrioritySet(NULL, 4);
  for(;;)
  {
    LED06OFF();
		LED05ON();
    osDelay(100);
		LED05OFF();
		LED06ON();
    osDelay(100);
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

