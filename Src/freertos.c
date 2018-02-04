/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "ssd1306.h"
#include "fontes.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* USER CODE BEGIN Variables */
float temp_lm35 = 0, vref_int = 0, temp_int = 0;
char buffer[10] = {0};
extern uint32_t temperatura[];
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    ssd1306_clear_display();
   // ssd1306_write_text(1, 30, 1, "EU");
    ssd1306_write_text(1, 40, 20, "William");
    //ssd1306_write_text(1, 50, 40, "AMO");
    ssd1306_write_text(1, 40, 48, "Trevine");
    ssd1306_write_display(1);
    
    ssd1306_clear_display();
    //ssd1306_write_text(1, 44, 2, "CAIRES");
    ssd1306_write_image(11, 0, (uint8_t*) &opala);
    ssd1306_write_display(2);
    
    //ssd1306_clear_display();
    //ssd1306_write_text(1, 44, 2, "TREVINE");
    //ssd1306_write_display(3);
    
    osDelay(300);
    ssd1306_clear_display();
    ssd1306_write_display(1);
    ssd1306_write_display(2);
    osDelay(300);
    
    temp_int = temperatura[0];
    vref_int = temperatura[1];
    vref_int = vref_int * 3.3 /4096;
    temp_lm35 = temperatura[2];
    temp_lm35 = temp_lm35 * 330 / 4096;
    
    
    ssd1306_clear_display();
    
    sprintf(buffer, "%.0f", temp_int);
    ssd1306_write_text(2, 10, 0, buffer);
    
    sprintf(buffer, "%.3fV", vref_int);
    ssd1306_write_text(2, 10, 20, buffer);
    
    sprintf(buffer, "%.1f°C", temp_lm35);
    ssd1306_write_text(2, 10, 40, buffer);
    
    ssd1306_write_display(3);
    
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
