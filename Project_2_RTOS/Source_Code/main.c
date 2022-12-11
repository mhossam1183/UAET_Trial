/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"

#if ( configUSE_EDF_SCHEDULER == 1 ) /* Main Application when EDF scheduler is used */

/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )


/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );

/* tasks code prototypes */
static void vTaskCode_Button_1_Monitor( void * pvParameters );
static void vTaskCode_Button_2_Monitor( void * pvParameters );
static void vTaskCode_Periodic_Transmitter( void * pvParameters );
static void vTaskCode_Uart_Receiver( void * pvParameters );
static void vTaskCode_Load_1_Simulation( void * pvParameters );
static void vTaskCode_Load_2_Simulation( void * pvParameters );
/*-----------------------------------------------------------*/

/* variables for use with GPIO pins */
pinState_t button1_port0_pin0 = PIN_IS_LOW;
pinState_t button2_port0_pin1 = PIN_IS_LOW;

unsigned int load1_count = 0;
unsigned int load2_count = 0;

static BaseType_t xReturned = pdFAIL;

/* tasks handlers */
extern TaskHandle_t xHandle_Button_1_Monitor;
extern TaskHandle_t xHandle_Button_2_Monitor;
extern TaskHandle_t xHandle_Periodic_Transmitter;
extern TaskHandle_t xHandle_Uart_Receiver;
extern TaskHandle_t xHandle_Load_1_Simulation;
extern TaskHandle_t xHandle_Load_2_Simulation;

TaskHandle_t xHandle_Button_1_Monitor = NULL;
TaskHandle_t xHandle_Button_2_Monitor = NULL;
TaskHandle_t xHandle_Periodic_Transmitter = NULL;
TaskHandle_t xHandle_Uart_Receiver = NULL;
TaskHandle_t xHandle_Load_1_Simulation = NULL;
TaskHandle_t xHandle_Load_2_Simulation = NULL;

/*-----------------------------------------------------------*/

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();

	/* Create the task, storing the handle. */
	
	xReturned = xTaskPeriodicCreate(
		vTaskCode_Button_1_Monitor,       /* Function that implements the task. */
		"Button_1_Monitor",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		4,/* Priority at which the task is created. */
		&xHandle_Button_1_Monitor,      /* Used to pass out the created task's handle. */
		50 ); /* Periodicity */

	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Button_1_Monitor );
	}

	xReturned = xTaskPeriodicCreate(
		vTaskCode_Button_2_Monitor,       /* Function that implements the task. */
		"Button_2_Monitor",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		4,/* Priority at which the task is created. */
		&xHandle_Button_2_Monitor,      /* Used to pass out the created task's handle. */
		50 ); /* Periodicity */

	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Button_2_Monitor );
	}
	
	xReturned = xTaskPeriodicCreate(
		vTaskCode_Periodic_Transmitter,       /* Function that implements the task. */
		"Periodic_Transmitter",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		1,/* Priority at which the task is created. */
		&xHandle_Periodic_Transmitter,      /* Used to pass out the created task's handle. */
		100 ); /* Periodicity */

	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Periodic_Transmitter );
	}

	xReturned = xTaskPeriodicCreate(
		vTaskCode_Uart_Receiver,       /* Function that implements the task. */
		"Uart_Receiver",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		1,/* Priority at which the task is created. */
		&xHandle_Uart_Receiver,      /* Used to pass out the created task's handle. */
		20 ); /* Periodicity */
		
	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Uart_Receiver );
	}
	
	xReturned = xTaskPeriodicCreate(
		vTaskCode_Load_1_Simulation,       /* Function that implements the task. */
		"Load_1_Simulation",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		1,/* Priority at which the task is created. */
		&xHandle_Load_1_Simulation,      /* Used to pass out the created task's handle. */
		10 ); /* Periodicity */
		
	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Load_1_Simulation );
	}

	xReturned = xTaskPeriodicCreate(
		vTaskCode_Load_2_Simulation,       /* Function that implements the task. */
		"Load_2_Simulation",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		1,/* Priority at which the task is created. */
		&xHandle_Load_2_Simulation,      /* Used to pass out the created task's handle. */
		100 ); /* Periodicity */
		
	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Load_2_Simulation );
	}
    
	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}

/*-----------------------------------------------------------*/

void vTaskCode_Button_1_Monitor( void * pvParameters )
{
	for( ;; )
	{
		if( button1_port0_pin0 != GPIO_read(PORT_0, PIN0) )
		{
			button1_port0_pin0 = GPIO_read(PORT_0, PIN0);
		}
		
		taskYIELD();
	}
}

void vTaskCode_Button_2_Monitor( void * pvParameters )
{
	for( ;; )
	{
		if( button2_port0_pin1 != GPIO_read(PORT_0, PIN1) )
		{
			button2_port0_pin1 = GPIO_read(PORT_0, PIN1);
		}
		
		taskYIELD();
	}
}

void vTaskCode_Periodic_Transmitter( void * pvParameters )
{
	for( ;; )
	{
		if(button1_port0_pin0 == PIN_IS_HIGH)
		{
			GPIO_write(PORT_0, PIN2, PIN_IS_HIGH);
		}
		else
		{
			GPIO_write(PORT_0, PIN2, PIN_IS_LOW);
		}
		
		taskYIELD();
	}
}
void vTaskCode_Uart_Receiver( void * pvParameters )
{
	for( ;; )
	{
		if(button2_port0_pin1 == PIN_IS_HIGH)
		{
			GPIO_write(PORT_0, PIN3, PIN_IS_HIGH);
		}
		else
		{
			GPIO_write(PORT_0, PIN3, PIN_IS_LOW);
		}
		
		taskYIELD();
	}
}
void vTaskCode_Load_1_Simulation( void * pvParameters ){for( ;; ){for(load1_count = 0;load1_count < 9000; load1_count++){}taskYIELD();}}
void vTaskCode_Load_2_Simulation( void * pvParameters ){for( ;; ){for(load2_count = 0;load2_count < 20000; load2_count++){}taskYIELD();}}

#endif


#if ( configUSE_EDF_SCHEDULER == 0 ) /* Main Application when EDF scheduler is used */

/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )


/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );

/* tasks code prototypes */
static void vTaskCode_Button_1_Monitor( void * pvParameters );
static void vTaskCode_Button_2_Monitor( void * pvParameters );
static void vTaskCode_Periodic_Transmitter( void * pvParameters );
static void vTaskCode_Uart_Receiver( void * pvParameters );
static void vTaskCode_Load_1_Simulation( void * pvParameters );
static void vTaskCode_Load_2_Simulation( void * pvParameters );
/*-----------------------------------------------------------*/

/* variables for use with GPIO pins */
pinState_t button1_port0_pin0 = PIN_IS_LOW;
pinState_t button2_port0_pin1 = PIN_IS_LOW;

unsigned int load1_count = 0;
unsigned int load2_count = 0;

static BaseType_t xReturned = pdFAIL;

/* tasks handlers */
extern TaskHandle_t xHandle_Button_1_Monitor;
extern TaskHandle_t xHandle_Button_2_Monitor;
extern TaskHandle_t xHandle_Periodic_Transmitter;
extern TaskHandle_t xHandle_Uart_Receiver;
extern TaskHandle_t xHandle_Load_1_Simulation;
extern TaskHandle_t xHandle_Load_2_Simulation;

TaskHandle_t xHandle_Button_1_Monitor = NULL;
TaskHandle_t xHandle_Button_2_Monitor = NULL;
TaskHandle_t xHandle_Periodic_Transmitter = NULL;
TaskHandle_t xHandle_Uart_Receiver = NULL;
TaskHandle_t xHandle_Load_1_Simulation = NULL;
TaskHandle_t xHandle_Load_2_Simulation = NULL;

/* tasks first call time */
static TickType_t xLastWakeTime_Button_1_Monitor;
static TickType_t xLastWakeTime_Button_2_Monitor;
static TickType_t xLastWakeTime_Periodic_Transmitter;
static TickType_t xLastWakeTime_Uart_Receiver;
static TickType_t xLastWakeTime_Load_1_Simulation;
static TickType_t xLastWakeTime_Load_2_Simulation;

/* tasks periodicity */
const TickType_t xFrequency_Button_1_Monitor = 50;
const TickType_t xFrequency_Button_2_Monitor = 50;
const TickType_t xFrequency_Periodic_Transmitter = 100;
const TickType_t xFrequency_Uart_Receiver = 20;
const TickType_t xFrequency_Load_1_Simulation = 10;
const TickType_t xFrequency_Load_2_Simulation = 100;

/*-----------------------------------------------------------*/

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();

	/* Create the task, storing the handle. */
	
	xReturned = xTaskCreate(
		vTaskCode_Button_1_Monitor,       /* Function that implements the task. */
		"Button_1_Monitor",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		3,/* Priority at which the task is created. */
		&xHandle_Button_1_Monitor );      /* Used to pass out the created task's handle. */

	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Button_1_Monitor );
	}

	xReturned = xTaskCreate(
		vTaskCode_Button_2_Monitor,       /* Function that implements the task. */
		"Button_2_Monitor",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		3,/* Priority at which the task is created. */
		&xHandle_Button_2_Monitor );      /* Used to pass out the created task's handle. */

	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Button_2_Monitor );
	}
	
	xReturned = xTaskCreate(
		vTaskCode_Periodic_Transmitter,       /* Function that implements the task. */
		"Periodic_Transmitter",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		2,/* Priority at which the task is created. */
		&xHandle_Periodic_Transmitter );      /* Used to pass out the created task's handle. */

	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Periodic_Transmitter );
	}

	xReturned = xTaskCreate(
		vTaskCode_Uart_Receiver,       /* Function that implements the task. */
		"Uart_Receiver",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		4,/* Priority at which the task is created. */
		&xHandle_Uart_Receiver );      /* Used to pass out the created task's handle. */

	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Uart_Receiver );
	}
	
	xReturned = xTaskCreate(
		vTaskCode_Load_1_Simulation,       /* Function that implements the task. */
		"Load_1_Simulation",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		4,/* Priority at which the task is created. */
		&xHandle_Load_1_Simulation );      /* Used to pass out the created task's handle. */

	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Load_1_Simulation );
	}

	xReturned = xTaskCreate(
		vTaskCode_Load_2_Simulation,       /* Function that implements the task. */
		"Load_2_Simulation",          /* Text name for the task. */
		100,      /* Stack size in words, not bytes. */
		( void * ) NULL,    /* Parameter passed into the task. */
		2,/* Priority at which the task is created. */
		&xHandle_Load_2_Simulation );      /* Used to pass out the created task's handle. */

	if( xReturned != pdPASS )
	{
		/* The task was created.  Use the task's handle to delete the task. */
		vTaskDelete( xHandle_Load_2_Simulation );
	}
	
    /* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}

/*-----------------------------------------------------------*/

/* Task to be created. */
void vTaskCode_Button_1_Monitor( void * pvParameters )
{
	xLastWakeTime_Button_1_Monitor = xTaskGetTickCount();
	
	for( ;; )
	{
		

		if( button1_port0_pin0 != GPIO_read(PORT_0, PIN0) )
		{
			button1_port0_pin0 = GPIO_read(PORT_0, PIN0);
		}
		
		
		
		vTaskDelayUntil( &xLastWakeTime_Button_1_Monitor, xFrequency_Button_1_Monitor );
	}
}

void vTaskCode_Button_2_Monitor( void * pvParameters )
{
	xLastWakeTime_Button_2_Monitor = xTaskGetTickCount();
	
	for( ;; )
	{
		if( button2_port0_pin1 != GPIO_read(PORT_0, PIN1) )
		{
			button2_port0_pin1 = GPIO_read(PORT_0, PIN1);
		}
		
		vTaskDelayUntil( &xLastWakeTime_Button_2_Monitor, xFrequency_Button_2_Monitor );
	}
}

void vTaskCode_Periodic_Transmitter( void * pvParameters )
{
	xLastWakeTime_Periodic_Transmitter = xTaskGetTickCount();
	
	for( ;; )
	{
		if(button1_port0_pin0 == PIN_IS_HIGH)
		{
			GPIO_write(PORT_0, PIN2, PIN_IS_HIGH);
		}
		else
		{
			GPIO_write(PORT_0, PIN2, PIN_IS_LOW);
		}
		
		vTaskDelayUntil( &xLastWakeTime_Periodic_Transmitter, xFrequency_Periodic_Transmitter );
	}
}

void vTaskCode_Uart_Receiver( void * pvParameters )
{
	xLastWakeTime_Uart_Receiver = xTaskGetTickCount();
	
	for( ;; )
	{
		
		
		if(button2_port0_pin1 == PIN_IS_HIGH)
		{
			GPIO_write(PORT_0, PIN3, PIN_IS_HIGH);
		}
		else
		{
			GPIO_write(PORT_0, PIN3, PIN_IS_LOW);
		}
		
		
		
		vTaskDelayUntil( &xLastWakeTime_Uart_Receiver, xFrequency_Uart_Receiver );
	}
}

void vTaskCode_Load_1_Simulation( void * pvParameters )
{
	xLastWakeTime_Load_1_Simulation = xTaskGetTickCount();
	
	for( ;; )
	{
		
		
		for(load1_count = 0;load1_count < 9000; load1_count++){}
			
		
		
		vTaskDelayUntil( &xLastWakeTime_Load_1_Simulation, xFrequency_Load_1_Simulation );
	}
}

void vTaskCode_Load_2_Simulation( void * pvParameters )
{
	xLastWakeTime_Load_2_Simulation = xTaskGetTickCount();
	
	for( ;; )
	{
		GPIO_write(PORT_0, PIN4, PIN_IS_HIGH);
		
		for(load2_count = 0;load2_count < 20000; load2_count++){}
			
		GPIO_write(PORT_0, PIN4, PIN_IS_LOW);
		
		vTaskDelayUntil( &xLastWakeTime_Load_2_Simulation, xFrequency_Load_2_Simulation );
	}
}

/*-----------------------------------------------------------*/

#endif

/*-----------------------------------------------------------*/

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}

void vApplicationIdleHook( void )
{
	;
}

void vApplicationTickHook( void )
{
	;
}

/*-----------------------------------------------------------*/
