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

TaskHandle_t myTaskHandle_1; //handler for myTask_1
TaskHandle_t myTaskHandle; //handler for myTask
BaseType_t xReturned;

SemaphoreHandle_t xMutex;

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void vmyTaskCode(void const * pvParameters);
void myTask_1(void* pvParameters);

//void vATask( void * pvParameters )
//{
//   /* Create a mutex type semaphore. */
//   xMutex = xSemaphoreCreateMutex();

//   if( xMutex != NULL )
//   {
//		 LED06ON();
//       /* The semaphore was created successfully and
//       can be used. */
//   }
//}
int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();

//  /* definition and creation of defaultTask */
//  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
//  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

//  /* definition and creation of myTask03 */
//  osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
//  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);
		xTaskCreate(myTask_1,       /* Function that implements the task. */
								"myTask_1",          /* Text name for the task. */
								256,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								2,/* Priority at which the task is created. */
								&myTaskHandle_1 );
	/* Start scheduler */
	
	
  osKernelStart();

  while (1)
  {
  }
}
void myTask_1( void* pvParameters)
{
	uint8_t my_task_count = 0;
	xMutex = xSemaphoreCreateMutex();

	if( xMutex != NULL )
	{
	 LED06ON();
		 /* The semaphore was created successfully and
		 can be used. */
	}
	for(;;)
	{
		if( xMutex != NULL )
    {
			xSemaphoreTake( xMutex, portMAX_DELAY );

			osDelay(200);
			LED02OFF();
			LED01ON();
			osDelay(100);
			LED01OFF();
			LED02ON();
			xSemaphoreGive( xMutex );

			osDelay(100);
		}
		else
		{
			osDelay(100);
		}
		
		my_task_count ++;
	}
		
}
	/* StartDefaultTask */
void StartDefaultTask(void const * argument)
{
	vTaskPrioritySet(NULL, 2);
	for(;;)
	{
		if( xMutex != NULL )
    {
			xSemaphoreTake( xMutex, portMAX_DELAY );
			LED02OFF();
			LED01ON();
			osDelay(100);
			LED01OFF();
			LED02ON();
			//osDelay(100);
			osDelay(100);
			xSemaphoreGive( xMutex );

			osDelay(100);
		}
		else
		{
			osDelay(100);
		}
	}
}
/* StartTask02 */
void StartTask02(void const * argument)
{
	vTaskPrioritySet(NULL, 3);

  for(;;)
  {
		//taskENTER_CRITICAL();
		//vTaskSuspendAll();
		LED04OFF();
		LED03ON();
		//osDelay(100);
		HAL_Delay(100);
		LED03OFF();
		LED04ON();
		HAL_Delay(100);
		//osDelay(100);
		//xTaskResumeAll();
		//taskEXIT_CRITICAL();
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

