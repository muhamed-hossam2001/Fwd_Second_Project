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


/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )
	
TaskHandle_t Button_1_Monitor_Handler = NULL;
TaskHandle_t Button_2_Monitor_Handler = NULL;
TaskHandle_t Periodic_Transmitter_Handler = NULL;
TaskHandle_t Uart_Receiver_Handler = NULL;
TaskHandle_t Load_1_Simulation_Handler = NULL;
TaskHandle_t Load_2_Simulation_Handler = NULL;


/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
int system_time;
int cpu_load;
int Task1_in_time =0 , Task1_out_time,Task1_total_time;
int Task2_in_time = 0 , Task2_out_time,Task2_total_time;
int Task3_in_time  = 0, Task3_out_time,Task3_total_time;
int Task4_in_time , Task4_out_time,Task4_total_time;
int Task5_in_time , Task5_out_time,Task5_total_time;
int Task6_in_time , Task6_out_time,Task6_total_time;
pinState_t ButtonStat1;
pinState_t ButtonStat2;
//pinState_t ButtonStat3;
//pinState_t ButtonStat4;
//pinState_t ButtonStat5;
//pinState_t ButtonStat6;
int flag1;
int flag2;
//int flag3;
//int flag4;
//int flag5;
//int flag6;
char button1_string [17] = "";
char button2_sting [17] = "";
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/



	void Button_1_Monitor( void * pvParameters )
{
		TickType_t xLastWakeTime = xTaskGetTickCount();
		vTaskSetApplicationTaskTag(NULL,(void*)1);
    for( ;; )
    {
		//	GPIO_write(PORT_0,PIN2,PIN_IS_HIGH);
			ButtonStat1 = GPIO_read(PORT_0, PIN0);

			if(ButtonStat1){
			flag1 = 1;
			}
			else{flag1=0;}
			
	//	GPIO_write(PORT_0,PIN2,PIN_IS_LOW);
			vTaskDelayUntil(&xLastWakeTime,50);
			
			//GPIO_write(PORT_0,PIN3,PIN_IS_LOW);
			
    }
}
void Button_2_Monitor( void * pvParameters )
{
	//Button 2 will be pin 1 port 0
//  int j ;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	vTaskSetApplicationTaskTag(NULL,(void*)2);
		
    for( ;; )
    {
		//	GPIO_write(PORT_0,PIN3,PIN_IS_HIGH);
			ButtonStat2 = GPIO_read(PORT_0, PIN1);

			if(ButtonStat2){
			flag2 = 1;
			}
			else{flag2=0;}
		//	GPIO_write(PORT_0,PIN3,PIN_IS_LOW);
			vTaskDelayUntil(&xLastWakeTime,50);
			
			//GPIO_write(PORT_0,PIN3,PIN_IS_LOW);
			
    }
}


	void Periodic_Transmitter( void * pvParameters )
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	vTaskSetApplicationTaskTag(NULL,(void*)3);
	for(;;){
		//GPIO_write(PORT_0,PIN4,PIN_IS_HIGH);
		//	ButtonStat3 = GPIO_read(PORT_0, PIN2);
			
	//		if(ButtonStat3){
		//		flag3 = 1 ;
	//		}
		//	else{
			//	flag3 = 0;
			//GPIO_write(PORT_0,PIN3,PIN_IS_HIGH);
					
		//	}
if(flag1){
strcpy(button1_string, "button 1 is on "); 
	
}
else{
strcpy(button1_string, "button 1 is off"); 
}
if(flag2){
strcpy(button2_sting, "button 2 is on "); 
	
}
else{
strcpy(button2_sting, "button 2 is off"); 
}
		//vSerialPutString(button1_string, 17 );
		//GPIO_write(PORT_0,PIN4,PIN_IS_LOW);
		vTaskDelayUntil(&xLastWakeTime,100);
}
}



	void Uart_Receiver( void * pvParameters )
{
TickType_t xLastWakeTime = xTaskGetTickCount();
	vTaskSetApplicationTaskTag(NULL,(void*)4);
		for(;;){
			
		//				ButtonStat4 = GPIO_read(PORT_0, PIN3);
			
			//			if(ButtonStat4){
		//		flag4 = 1 ;
	//		}
	//		else{
		//		flag4 = 0;
			//GPIO_write(PORT_0,PIN3,PIN_IS_HIGH);
					
			//}
			vSerialPutString(button1_string, 17 );
			vTaskDelayUntil(&xLastWakeTime,10);
			vSerialPutString(button2_sting, 17 );
			
			vTaskDelayUntil(&xLastWakeTime,10);
		}
}



	void Load_1_Simulation( void * pvParameters )
		
{int i = 0; 
		TickType_t xLastWakeTime = xTaskGetTickCount();
	vTaskSetApplicationTaskTag(NULL,(void*)5);
		for(;;){
//						ButtonStat5 = GPIO_read(PORT_0, PIN4);
			
	//					if(ButtonStat5){
		//		flag5 = 1 ;
//			}
	//		else{
		//		flag5 = 0;
			//GPIO_write(PORT_0,PIN3,PIN_IS_HIGH);
					
			//}
			//GPIO_write(PORT_0,PIN2,PIN_IS_HIGH);
			
			
			for( i = 0 ; i < 34000 ; i ++){
			i = i;
			}
			//GPIO_write(PORT_0,PIN2,PIN_IS_LOW);
				
			vTaskDelayUntil(&xLastWakeTime,10);

		}
		
}


	void Load_2_Simulation( void * pvParameters )
{int i = 0; 
  		TickType_t xLastWakeTime = xTaskGetTickCount();
	vTaskSetApplicationTaskTag(NULL,(void*)6);
	
		for(;;){
//						ButtonStat6 = GPIO_read(PORT_0, PIN5);
			
//						if(ButtonStat6){
	//			flag6 = 1 ;
	//		}
		//	else{
			//	flag6 = 0;
			//GPIO_write(PORT_0,PIN3,PIN_IS_HIGH);
					
			//}
	//		GPIO_write(PORT_0,PIN9,PIN_IS_HIGH);
			
			for( i = 0 ; i < 82000 ; i ++){
			i = i;
			}
	//		GPIO_write(PORT_0,PIN9,PIN_IS_LOW);
		//	GPIO_write(PORT_0,PIN3,PIN_IS_LOW);
			vTaskDelayUntil(&xLastWakeTime,100);

		}
		
}

//tick hock function
void vApplicationTickHook( void ){
//your code here
GPIO_write(PORT_0,PIN6,PIN_IS_HIGH);
GPIO_write(PORT_0,PIN6,PIN_IS_LOW);
}
//idle hook function
//void vApplicationIdleHook( void ){
	//your code here
	//GPIO_write(PORT_0,PIN7,PIN_IS_HIGH);
	//GPIO_write(PORT_0,PIN7,PIN_IS_LOW);
	
	//}
/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();

	

	
	
	
    /* Create Tasks here */
			     xTaskPeriodicCreate(
                    Button_1_Monitor,       /* Function that implements the task. */
                    "Button 1 Monitor ",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                  &Button_1_Monitor_Handler,50 ); 
		     xTaskPeriodicCreate(
                    Button_2_Monitor,       /* Function that implements the task. */
                    "Button 2 Monitor",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Button_2_Monitor_Handler, 50 );      /* Used to pass out the created task's handle. */
		     xTaskPeriodicCreate(
                    Periodic_Transmitter,       /* Function that implements the task. */
                    "Periodic Transmitter",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Periodic_Transmitter_Handler,100 );      /* Used to pass out the created task's handle. */
		     xTaskPeriodicCreate(
                    Uart_Receiver,       /* Function that implements the task. */
                    "Uart Receiver",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Uart_Receiver_Handler,20 );      /* Used to pass out the created task's handle. */
		     xTaskPeriodicCreate(
                    Load_1_Simulation,       /* Function that implements the task. */
                    "Load_1_Simulation",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Load_1_Simulation_Handler,10 );      /* Used to pass out the created task's handle. */							
		     xTaskPeriodicCreate(
                    Load_2_Simulation,       /* Function that implements the task. */
                    "Load_2_Simulation",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Load_2_Simulation_Handler,100 );      /* Used to pass out the created task's handle. */				
								
								
    /* Create Tasks here */
			    // xTaskCreate(
                  //  Button_1_Monitor,       /* Function that implements the task. */
                  //  "Button 1 Monitor ",          /* Text name for the task. */
                //    100,      /* Stack size in words, not bytes. */
              //      ( void * ) 0,    /* Parameter passed into the task. */
            //        1,/* Priority at which the task is created. */
          //          &Button_1_Monitor_Handler ); 
		    // xTaskCreate(
                    //Button_2_Monitor,       /* Function that implements the task. */
                  //  "Button 2 Monitor",          /* Text name for the task. */
                //    100,      /* Stack size in words, not bytes. */
              //      ( void * ) 0,    /* Parameter passed into the task. */
            //        1,/* Priority at which the task is created. */
          //          &Button_2_Monitor_Handler );      /* Used to pass out the created task's handle. */
		    // xTaskCreate(
          //          Periodic_Transmitter,       /* Function that implements the task. */
        //            "Periodic Transmitter",          /* Text name for the task. */
      //              100,      /* Stack size in words, not bytes. */
    //                ( void * ) 0,    /* Parameter passed into the task. */
  //                  1,/* Priority at which the task is created. */
//                    &Periodic_Transmitter_Handler );      /* Used to pass out the created task's handle. */
		 //    xTaskCreate(
                //    Uart_Receiver,       /* Function that implements the task. */
              //      "Uart Receiver",          /* Text name for the task. */
            //        100,      /* Stack size in words, not bytes. */
          //          ( void * ) 0,    /* Parameter passed into the task. */
        //            1,/* Priority at which the task is created. */
      //             &Uart_Receiver_Handler );      /* Used to pass out the created task's handle. */
		//     xTaskCreate(
           //         Load_1_Simulation,       /* Function that implements the task. */
         //           "Load_1_Simulation",          /* Text name for the task. */
       //             100,      /* Stack size in words, not bytes. */
     //               ( void * ) 0,    /* Parameter passed into the task. */
   //                 1,/* Priority at which the task is created. */
 //                   &Load_1_Simulation_Handler );      /* Used to pass out the created task's handle. */							
		   //  xTaskCreate(
                   // Load_2_Simulation,       /* Function that implements the task. */
                   // "Load_2_Simulation",          /* Text name for the task. */
                 //   100,      /* Stack size in words, not bytes. */
               //     ( void * ) 0,    /* Parameter passed into the task. */
             //       1,/* Priority at which the task is created. */
           //         &Load_2_Simulation_Handler );      /* Used to pass out the created task's handle. */			



		



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

static void prvSetupHardware( void )
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
/*-----------------------------------------------------------*/


