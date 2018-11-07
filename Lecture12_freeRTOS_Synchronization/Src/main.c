#include "main.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"
#include "Init.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define SIZE_BUF 100
#define RESET_TIMEOUT_SEC 5
/* Private variables ---------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

TaskHandle_t myTaskHandle_1; //handler for myTask_Philos_1
TaskHandle_t myTaskHandle_2; //handler for myTask_Philos_2
TaskHandle_t myTaskHandle_3; //handler for myTask_Philos_3
TaskHandle_t myTaskHandle_4; //handler for myTask_Philos_4
TaskHandle_t myTaskHandle_5; //handler for myTask_Philos_5

SemaphoreHandle_t xSemaphoreFork1 = NULL;
SemaphoreHandle_t xSemaphoreFork2 = NULL;
SemaphoreHandle_t xSemaphoreFork3 = NULL;
SemaphoreHandle_t xSemaphoreFork4 = NULL;
SemaphoreHandle_t xSemaphoreFork5 = NULL;

QueueHandle_t xQueue;

volatile uint32_t TIM1_Count = 0;			//counter for ms	 
volatile uint32_t TIM1_Count_Sec = 0;	// counter for s

volatile static unsigned char buf [SIZE_BUF];

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void vmyTaskCode(void const * pvParameters);
void myTask_Philos_1(void* pvParameters);
void myTask_Philos_2(void* pvParameters);
void myTask_Philos_3(void* pvParameters);
void myTask_Philos_4(void* pvParameters);
void myTask_Philos_5(void* pvParameters);
int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
	
	xSemaphoreFork1 = xSemaphoreCreateBinary();  
  if( xSemaphoreFork1 == NULL ) 
  {    /* There was insufficient FreeRTOS heap available for the semaphore to         be created successfully. */
       while (1);    
  }
	else
	{
		  if( xSemaphoreGive( xSemaphoreFork1 ) != pdTRUE )
      {
        while (1);
      }
	}	
	
	xSemaphoreFork2 = xSemaphoreCreateBinary();  
  if( xSemaphoreFork2 == NULL ) 
  {    /* There was insufficient FreeRTOS heap available for the semaphore to         be created successfully. */
       while (1);    
  }  
	else
	{
		  if( xSemaphoreGive( xSemaphoreFork2 ) != pdTRUE )
      {
        while (1);
      }
	}	
	
	xSemaphoreFork3 = xSemaphoreCreateBinary();  
  if( xSemaphoreFork3 == NULL ) 
  {    /* There was insufficient FreeRTOS heap available for the semaphore to         be created successfully. */
       while (1);    
  }
	else
	{
		  if( xSemaphoreGive( xSemaphoreFork3 ) != pdTRUE )
      {
        while (1);
      }
	}	
	
	xSemaphoreFork4 = xSemaphoreCreateBinary();  
  if( xSemaphoreFork4 == NULL ) 
  {    /* There was insufficient FreeRTOS heap available for the semaphore to         be created successfully. */
       while (1);    
  }
	else
	{
		  if( xSemaphoreGive( xSemaphoreFork4 ) != pdTRUE )
      {
        while (1);
      }
	}	  
	
	xSemaphoreFork5 = xSemaphoreCreateBinary();  
  if( xSemaphoreFork5 == NULL ) 
  {    /* There was insufficient FreeRTOS heap available for the semaphore to         be created successfully. */
       while (1);    
  }  	
	else
	{
		  if( xSemaphoreGive( xSemaphoreFork5 ) != pdTRUE )
      {
        while (1);
      }
	}	
//	/* Create a queue to hold one unsigned long value. It is strongly
//    recommended *not* to use xQueueOverwrite() on queues that can
//    contain more than one value, and doing so will trigger an assertion
//    if configASSERT() is defined. */
//  xQueue = xQueueCreate( 1, sizeof( unsigned long ) );
//  if( xQueue == NULL )
//  {
//   /* The queue could not be created. */
//   while (1);  
//  }

  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

//  /* definition and creation of myTask02 */
//  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
//  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

//  /* definition and creation of myTask03 */
//  osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
//  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

		xTaskCreate(myTask_Philos_1,       /* Function that implements the task. */
								"philosopher1",          /* Text name for the task. */
								256,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								2,/* Priority at which the task is created. */
								&myTaskHandle_1 );
	
		xTaskCreate(myTask_Philos_2,       /* Function that implements the task. */
								"philosopher2",          /* Text name for the task. */
								256,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								2,/* Priority at which the task is created. */
								&myTaskHandle_2 );
								
		xTaskCreate(myTask_Philos_3,       /* Function that implements the task. */
								"philosopher3",          /* Text name for the task. */
								256,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								2,/* Priority at which the task is created. */
								&myTaskHandle_3 );
		xTaskCreate(myTask_Philos_4,       /* Function that implements the task. */
								"philosopher4",          /* Text name for the task. */
								256,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								2,/* Priority at which the task is created. */
								&myTaskHandle_4 );	
		xTaskCreate(myTask_Philos_5,       /* Function that implements the task. */
								"philosopher5",          /* Text name for the task. */
								256,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								2,/* Priority at which the task is created. */
								&myTaskHandle_5 );								
	/* Start scheduler */
  osKernelStart();

  while (1)
  {
  }
}
/* Start myTask_Philos_1*/
void myTask_Philos_1( void* pvParameters)
{
	//volatile uint64_t sendQueue = 0;
	osThreadDef(myTask, vmyTaskCode, osPriorityLow, 0, 32);
	TaskHandle_t myHandle = osThreadCreate(osThread(myTask), NULL);
	for(;;)
  {
		//xQueueOverwrite( xQueue, (void const *)&sendQueue );
		if( (xSemaphoreTake( xSemaphoreFork1,  portMAX_DELAY ) == pdTRUE) && TIM1_Count_Sec <= 5 )
		{ 
			osDelay(100);
			if(xSemaphoreTake( xSemaphoreFork5,  portMAX_DELAY ) == pdTRUE )
			{
				LED02OFF();
				LED01ON();
				osDelay(100);
				LED01OFF();
				LED02ON();
				osDelay(100);
				xSemaphoreGive( xSemaphoreFork5 );
			}
			//sendQueue += 10;
			osDelay(10);
			xSemaphoreGive( xSemaphoreFork1 );
		}
		else
		{
			xSemaphoreGive( xSemaphoreFork1 );
			osDelay(1000);
			
		}
	}
}
/* Start myTask_Philos_2*/
void myTask_Philos_2( void* pvParameters)
{
	for(;;)
  {
		if( xSemaphoreTake( xSemaphoreFork2,  portMAX_DELAY ) == pdTRUE )
		{ 
			osDelay(100);
			if(xSemaphoreTake( xSemaphoreFork1,  portMAX_DELAY ) == pdTRUE )
			{
				LED04OFF();
				LED03ON();
				osDelay(100);
				LED03OFF();
				LED04ON();
				osDelay(100);
				xSemaphoreGive( xSemaphoreFork1);
			}
			xSemaphoreGive( xSemaphoreFork2);
		}
		else
		{
			osDelay(1000);
			xSemaphoreGive( xSemaphoreFork2);
		}
	}
}
/* Start myTask_Philos_3*/
void myTask_Philos_3( void* pvParameters)
{
	for(;;)
  {
		if( xSemaphoreTake( xSemaphoreFork3,  portMAX_DELAY ) == pdTRUE )
		{ 
			osDelay(100);
			if(xSemaphoreTake( xSemaphoreFork2,  portMAX_DELAY ) == pdTRUE )
			{
				LED06OFF();
				LED05ON();
				osDelay(100);
				LED05OFF();
				LED06ON();
				osDelay(100);
				xSemaphoreGive( xSemaphoreFork2);
			}
			xSemaphoreGive( xSemaphoreFork3);
		}
		else
		{
			osDelay(1000);
			xSemaphoreGive( xSemaphoreFork3);
		}
	}
}
/* Start myTask_Philos_4*/
void myTask_Philos_4( void* pvParameters)
{
	for(;;)
  {
		if( xSemaphoreTake( xSemaphoreFork4,  portMAX_DELAY ) == pdTRUE )
		{ 
			osDelay(100);
			if(xSemaphoreTake( xSemaphoreFork3,  portMAX_DELAY ) == pdTRUE )
			{
				LED08OFF();
				LED07ON();
				osDelay(100);
				LED07OFF();
				LED08ON();
				osDelay(100);
				xSemaphoreGive( xSemaphoreFork3);
			}
			xSemaphoreGive( xSemaphoreFork4);
		}
		else
		{
			osDelay(1000);
			xSemaphoreGive( xSemaphoreFork4);
		}
	}
}
void myTask_Philos_5( void* pvParameters)
{
	for(;;)
  {
		if( xSemaphoreTake( xSemaphoreFork5,  portMAX_DELAY ) == pdTRUE )
		{ 
			osDelay(100);
			if(xSemaphoreTake( xSemaphoreFork4,  portMAX_DELAY ) == pdTRUE )
			{
				LED02OFF();
				LED04ON();
				osDelay(100);
				LED04OFF();
				LED02ON();
				osDelay(100);
				xSemaphoreGive( xSemaphoreFork4);
			}
			xSemaphoreGive( xSemaphoreFork5);
		}
		else
		{
			osDelay(1000);
			xSemaphoreGive( xSemaphoreFork5);
		}
	}
}

/* Start vmyTaskCode*/
void vmyTaskCode(void const* pvParameters)
{
	
//	volatile uint64_t recQueue = 0;
	
	for (;;)
	{
//			xQueueReceive(xQueue,(void* const)&recQueue, portMAX_DELAY);
			LED08OFF();
			LED07ON(); 
			osDelay (100);
			LED07OFF();
			LED08ON();
			osDelay (100);
		//vTaskDelete(NULL);
	}
		
}
	/* StartDefaultTask */
void StartDefaultTask(void const * argument)
{
	//vTaskPrioritySet(NULL, 2);
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
	TIM1_Count++; // one ms
  if(TIM1_Count%1000==0)
  {
    TIM1_Count_Sec++; // one second
  }
  if(TIM1_Count>=10000000) 
	{
		TIM1_Count=0; // reset
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

