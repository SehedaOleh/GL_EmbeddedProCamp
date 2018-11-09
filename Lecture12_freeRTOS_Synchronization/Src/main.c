#include "main.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"
#include "Init.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define SIZE_BUF 100
#define RESET_TIMEOUT_SEC 5
#define Philosofer_DELAY 0x0FFF
#define Philosofer_Number 5
/* Private variables ---------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

TaskHandle_t myTaskHandle[Philosofer_Number]; //handler for myTask_Philos_1_to_5

SemaphoreHandle_t xSemaphoreFork[Philosofer_Number] = {NULL};

QueueHandle_t xQueue;

volatile uint32_t TIM1_Count = 0;			//counter for ms	 
volatile uint32_t TIM1_Count_Sec = 0;	// counter for s

volatile static unsigned char buf [SIZE_BUF];

/* Private function prototypes -----------------------------------------------*/
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
	
	for(int i = 0; i < Philosofer_Number; i++)
	{
		xSemaphoreFork[i] = xSemaphoreCreateBinary();  
		if( xSemaphoreFork[i]  == NULL ) 
		{    /* There was insufficient FreeRTOS heap available for the semaphore to         be created successfully. */
				 while (1);    
		}
		else
		{
				if( xSemaphoreGive( xSemaphoreFork[i]  ) != pdTRUE )
				{
					while (1);
				}
		}	
	}
		xTaskCreate(myTask_Philos_1,       /* Function that implements the task. */
								"philosopher1",          /* Text name for the task. */
								64,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								0,/* Priority at which the task is created. */
								&myTaskHandle[0] );
	
		xTaskCreate(myTask_Philos_2,       /* Function that implements the task. */
								"philosopher2",          /* Text name for the task. */
								64,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								0,/* Priority at which the task is created. */
								&myTaskHandle[1] );
								
		xTaskCreate(myTask_Philos_3,       /* Function that implements the task. */
								"philosopher3",          /* Text name for the task. */
								64,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								0,/* Priority at which the task is created. */
								&myTaskHandle[2] );
		xTaskCreate(myTask_Philos_4,       /* Function that implements the task. */
								"philosopher4",          /* Text name for the task. */
								64,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								0,/* Priority at which the task is created. */
								&myTaskHandle[3] );	
		xTaskCreate(myTask_Philos_5,       /* Function that implements the task. */
								"philosopher5",          /* Text name for the task. */
								64,      /* Stack size in words, not bytes. */
								NULL,    /* Parameter passed into the task. */
								0,/* Priority at which the task is created. */
								&myTaskHandle[4] );								
	/* Start scheduler */
  osKernelStart();

  while (1)
  {
  }
}
/* Start myTask_Philos_1*/
void myTask_Philos_1( void* pvParameters)
{
	osThreadDef(myTask, vmyTaskCode, osPriorityLow, 0, 32);
	TaskHandle_t myHandle = osThreadCreate(osThread(myTask), NULL);
	for(;;)
  {
		//xQueueOverwrite( xQueue, (void const *)&sendQueue );
		if( (xSemaphoreTake( xSemaphoreFork[0],  portMAX_DELAY ) == pdTRUE) && TIM1_Count_Sec <= 5)
		{ 
			osDelay(10);
			if(xSemaphoreTake( xSemaphoreFork[4],  Philosofer_DELAY ) == pdTRUE )
			{
				/******** eating *******/
				LED02OFF();
				LED01ON();
				osDelay(100);
				LED01OFF();
				LED02ON();
				osDelay(100);
				/******** eating *******/
				xSemaphoreGive( xSemaphoreFork[4] );
				osDelay(10);
				xSemaphoreGive( xSemaphoreFork[0] );
				TIM1_Count_Sec = 0;
			}
			else
			{
				osDelay(10); //waiting
			}
		}
		else if (TIM1_Count_Sec >= 5)
	  {
			xSemaphoreGive( xSemaphoreFork[0] );
			osDelay(10);
			LED01ON();
		}
		else
		{
			osDelay(10);
		}
	}
}
/* Start myTask_Philos_2*/
void myTask_Philos_2( void* pvParameters)
{
	for(;;)
  {
		if( (xSemaphoreTake( xSemaphoreFork[1],  portMAX_DELAY ) == pdTRUE) && TIM1_Count_Sec <= 5)
		{ 
			osDelay(10);
			if(xSemaphoreTake( xSemaphoreFork[0],  Philosofer_DELAY ) == pdTRUE )
			{
				/******** eating *******/
				LED04OFF();
				LED03ON();
				osDelay(100);
				LED03OFF();
				LED04ON();
				osDelay(100);
				/******** eating *******/
				xSemaphoreGive( xSemaphoreFork[0] );
				osDelay(10);
				xSemaphoreGive( xSemaphoreFork[1] );
				TIM1_Count_Sec = 0;
			}
			else
			{
				osDelay(10); //waiting
			}
		}
		else if (TIM1_Count_Sec >= 5)
	  {
			xSemaphoreGive( xSemaphoreFork[1] );
			osDelay(10);
			LED01ON();
		}
		else
		{
			osDelay(10);
		}
	}
}
/* Start myTask_Philos_3*/
void myTask_Philos_3( void* pvParameters)
{
	for(;;)
  {
		if( (xSemaphoreTake( xSemaphoreFork[2],  portMAX_DELAY ) == pdTRUE) && TIM1_Count_Sec <= 5)
		{ 
			osDelay(10);
			if(xSemaphoreTake( xSemaphoreFork[1],  Philosofer_DELAY ) == pdTRUE )
			{
				/******** eating *******/
				LED06OFF();
				LED05ON();
				osDelay(100);
				LED05OFF();
				LED06ON();
				osDelay(100);
				/******** eating *******/
				xSemaphoreGive( xSemaphoreFork[1]);
				osDelay(10);
				xSemaphoreGive( xSemaphoreFork[2]);
				TIM1_Count_Sec = 0;
			}
			else
			{
				osDelay(10); //waiting
			}
		}
		else if (TIM1_Count_Sec >= 5)
	  {
			xSemaphoreGive( xSemaphoreFork[2] );
			osDelay(10);
			LED01ON();
		}
		else
		{
			osDelay(10);
		}
	}
}
/* Start myTask_Philos_4*/
void myTask_Philos_4( void* pvParameters)
{
	for(;;)
  {
		if( (xSemaphoreTake( xSemaphoreFork[3],  portMAX_DELAY ) == pdTRUE) && TIM1_Count_Sec <= 5)
		{ 
			osDelay(10);
			if(xSemaphoreTake( xSemaphoreFork[2],  Philosofer_DELAY ) == pdTRUE )
			{
				/******** eating *******/
				LED08OFF();
				LED07ON();
				osDelay(100);
				LED07OFF();
				LED08ON();
				osDelay(100);
				/******** eating *******/
				xSemaphoreGive( xSemaphoreFork[2]);
				osDelay(10);
				xSemaphoreGive( xSemaphoreFork[3]);
				TIM1_Count_Sec = 0;
			}
			else
			{
				osDelay(10); //waiting
			}
		}
		else if (TIM1_Count_Sec >= 5)
	  {
			xSemaphoreGive( xSemaphoreFork[3] );
			osDelay(10);
			LED01ON();
		}
		else
		{
			osDelay(10);
		}
	}
}
void myTask_Philos_5( void* pvParameters)
{
	for(;;)
  {
		if( (xSemaphoreTake( xSemaphoreFork[4],  portMAX_DELAY ) == pdTRUE) && TIM1_Count_Sec <= 5)
		{ 
			osDelay(10);
			if(xSemaphoreTake( xSemaphoreFork[3],  Philosofer_DELAY ) == pdTRUE )
			{
				/******** eating *******/
				LED06OFF();
				LED04ON();
				osDelay(100);
				LED04OFF();
				LED06ON();
				osDelay(100);
				/******** eating *******/
				xSemaphoreGive( xSemaphoreFork[3]);
				osDelay(10);
				xSemaphoreGive( xSemaphoreFork[4]);
				TIM1_Count_Sec = 0;
			}
			else
			{
				osDelay(10); //waiting
			}
		}
		else if (TIM1_Count_Sec >= 5)
	  {
			xSemaphoreGive( xSemaphoreFork[4] );
			osDelay(10);
			LED01ON();
		}
		else
		{
			osDelay(10);
		}
		osDelay(10);
	}
}

/* Start vmyTaskCode*/
void vmyTaskCode(void const* pvParameters)
{
	for (;;)
	{
			osDelay (100);
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
//		if( 10 == TIM1_Count_Sec )
//		{
//			TIM1_Count_Sec = 0;	//RESET after 10 seconds
//			for(int i = 0; i < Philosofer_Number; i++)
//			{
//				xSemaphoreGive( xSemaphoreFork[i]);
//			}
//						LED01OFF();		// for debug
//		}
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
