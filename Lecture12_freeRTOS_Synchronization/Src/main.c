#include "main.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"
#include "Init.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define  PHIL1 0
#define  PHIL2 1
#define  PHIL3 2
#define  PHIL4 3
#define  PHIL5 4


#define RESET_TIMEOUT_SEC   5
#define Philosofer_DELAY    0x0FFF
#define Philosofer_NUMBER   5
#define Phiholofer_THINKING 0	  //status for time when philosopher is thinking
#define Phiholofer_WAITING 	1 	//status for time when philosopher is waiting for forks
#define Phiholofer_EATING 	2  	//status for time when philosopher is eating

#define LEFT_Fork_NUMBER(i) 	(i + Philosofer_NUMBER - 1) % Philosofer_NUMBER 
#define RIGHT_Fork_NUMBER(i)  (i + 1) % Philosofer_NUMBER

/* Private variables ---------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

TaskHandle_t myTaskHandle[Philosofer_NUMBER]; //handler for myTask_Philos_1_to_5

SemaphoreHandle_t xSemaphorePhilosofer[Philosofer_NUMBER] = {NULL}; //semaphores for each of philosofer
SemaphoreHandle_t xSemaphoreTakingFork = NULL; // semafor for fork taking

volatile uint32_t TIM1_Count = 0;			//counter for ms	 
volatile uint32_t TIM1_Count_Sec = 0;	// counter for s
volatile uint8_t philosopherStatus[Philosofer_NUMBER] = {0}; //for start of the program all philosophers are thinking

	
/* Private function prototypes -----------------------------------------------*/
void vmyTaskCode(void const * pvParameters);
void myTask_Philos_1(void* pvParameters);
void myTask_Philos_2(void* pvParameters);
void myTask_Philos_3(void* pvParameters);
void myTask_Philos_4(void* pvParameters);
void myTask_Philos_5(void* pvParameters);
void takeFork (uint8_t);
void putFork (uint8_t);
/* ---------------------------------------------------------------------------*/
int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
	// creating semaphors for each forks
	for(int i = 0; i < Philosofer_NUMBER; i++)
	{
		xSemaphorePhilosofer[i] = xSemaphoreCreateBinary();  
		if( xSemaphorePhilosofer[i]  == NULL ) 
		{    /* There was insufficient FreeRTOS heap available for the semaphore to be created successfully. */
				 while (1);    
		}
		else
		{
				if( xSemaphoreGive( xSemaphorePhilosofer[i]  ) != pdTRUE )
				{
					while (1);
				}
		}	
	}
	// creating semaphor for taking fork
	xSemaphoreTakingFork = xSemaphoreCreateBinary();
	if( xSemaphoreTakingFork  == NULL ) 
		{    /* There was insufficient FreeRTOS heap available for the semaphore to be created successfully. */
				 while (1);    
		}
		else
		{
				if( xSemaphoreGive(xSemaphoreTakingFork) != pdTRUE )
				{
					while (1);
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
/**
  * @brief  This function is executed when one of the philosophers try to take a fork.
  * @param  philosopher: Number of philosopher who want to take a fork.
  * @retval None
  */
void takeFork (uint8_t philosopher)
{
	if (xSemaphoreTakingFork != NULL)
  {
    if(osSemaphoreWait(xSemaphoreTakingFork , 100) == osOK)
    {
			philosopherStatus[philosopher] = Phiholofer_WAITING;
			//taking forks
			if (philosopherStatus[philosopher] == Phiholofer_WAITING 
				  && philosopherStatus[LEFT_Fork_NUMBER(philosopher)] != Phiholofer_EATING 
					&& philosopherStatus[RIGHT_Fork_NUMBER(philosopher)] != Phiholofer_EATING) 
			{
				philosopherStatus[philosopher] = Phiholofer_EATING;
				// release semaphor for philosopher how whants to eat
				xSemaphoreGive( xSemaphorePhilosofer[philosopher] );
			}
			//taking semaphor for philosofer how waithing for forks
			osSemaphoreRelease(xSemaphoreTakingFork);
		}
		else
		{
			// taking semaphor for philosopher how whants to eat
			xSemaphoreTake( xSemaphorePhilosofer[philosopher],  portMAX_DELAY );
		}
	}
}
void putFork (uint8_t philosopher)
{
	if(osSemaphoreWait(xSemaphoreTakingFork , 100) == osOK)
	{
		philosopherStatus[philosopher] = Phiholofer_THINKING;
		osSemaphoreRelease(xSemaphoreTakingFork);
	}
}

/* Start myTask_Philos_1*/
void myTask_Philos_1( void* pvParameters)
{
//	osThreadDef(myTask, vmyTaskCode, osPriorityLow, 0, 32);
//	TaskHandle_t myHandle = osThreadCreate(osThread(myTask), NULL);
	for(;;)
  {
		// Philosopher is thinking
		osDelay(100);
		//trying to take forks
		takeFork (PHIL1);
		
		if(xSemaphoreTake( xSemaphorePhilosofer[PHIL1],  portMAX_DELAY ) == pdTRUE && philosopherStatus[PHIL1] == Phiholofer_EATING) 
		{ 
				/******** eating *******/
				LED02OFF();
				LED01ON();
				osDelay(100);
				LED01OFF();
				LED02ON();
				osDelay(100);
				/******** eating *******/
				xSemaphoreGive( xSemaphorePhilosofer[PHIL1]);
				putFork(PHIL1);
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
		// Philosopher is thinking
		osDelay(70);
		//trying to take forks
		takeFork (PHIL2);
		
		if(xSemaphoreTake( xSemaphorePhilosofer[PHIL2],  portMAX_DELAY ) == pdTRUE && philosopherStatus[PHIL2] == Phiholofer_EATING) 
		{ 
		
				/******** eating *******/
				LED04OFF();
				LED03ON();
				osDelay(100);
				LED03OFF();
				LED04ON();
				osDelay(100);
				/******** eating *******/
				xSemaphoreGive(xSemaphorePhilosofer[PHIL2]);
				putFork(PHIL2);
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
		
				/******** eating *******/
//				LED06OFF();
//				LED05ON();
//				osDelay(100);
//				LED05OFF();
//				LED06ON();
				osDelay(100);
				/******** eating *******/
			
	}
}
/* Start myTask_Philos_4*/
void myTask_Philos_4( void* pvParameters)
{
	for(;;)
  {
				/******** eating *******/
//				LED08OFF();
//				LED07ON();
//				osDelay(100);
//				LED07OFF();
//				LED08ON();
				osDelay(100);
				/******** eating *******/

	}
}
void myTask_Philos_5( void* pvParameters)
{
	for(;;)
  {
		
				/******** eating *******/
//				LED06OFF();
//				LED04ON();
//				osDelay(100);
//				LED04OFF();
//				LED06ON();
				osDelay(100);
				/******** eating *******/
	
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
//				xSemaphoreGive( xSemaphorePhilosofer[i]);
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
