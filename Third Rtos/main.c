

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
	
TaskHandle_t MButton_1_Handler = NULL;
TaskHandle_t MButton_2_Handler = NULL;
TaskHandle_t UART_Transmitter_Handler = NULL;
TaskHandle_t Uart_Receiver_Handler = NULL;
TaskHandle_t Load_1_Handler = NULL;
TaskHandle_t Load_2_Handler = NULL;



int Global_flag1;
int Global_flag2;

const signed char *Button1StringIndication = NULL;
const signed char *Button2StringIndication = NULL;
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/



	void Button_1_Monitor( void * pvParameters )
{
		TickType_t xLastWakeTime = xTaskGetTickCount();
		
    for( ;; )
    {
		
			Global_flag1 = GPIO_read(PORT_0, PIN0);
		
			vTaskDelayUntil(&xLastWakeTime,500);
			
    }
}
void Button_2_Monitor( void * pvParameters )
{

	TickType_t xLastWakeTime = xTaskGetTickCount();
		
    for( ;; )
    {
	
			Global_flag2 = GPIO_read(PORT_0, PIN1);

			vTaskDelayUntil(&xLastWakeTime,50);
		
			
    }
}


	void Periodic_Transmitter( void * pvParameters )
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;){

if(Global_flag1){
strcpy(Button1StringIndication, "button 1 is on "); 
	
}
else{
strcpy(Button1StringIndication, "button 1 is off"); 
}
if(Global_flag2){
strcpy(Button2StringIndication, "button 2 is on "); 
	
}
else{
strcpy(Button2StringIndication, "button 2 is off"); 
}
		vTaskDelayUntil(&xLastWakeTime,100);
}
}



	void Uart_Receiver( void * pvParameters )
{
TickType_t xLastWakeTime = xTaskGetTickCount();
		for(;;){
	
			vSerialPutString(Button1StringIndication, 17 );
			vTaskDelayUntil(&xLastWakeTime,10);
			vSerialPutString(Button2StringIndication, 17 );
			vTaskDelayUntil(&xLastWakeTime,10);
		}
}



	void Load_1_Simulation( void * pvParameters )
{
		TickType_t xLastWakeTime = xTaskGetTickCount();
	int i = 0; 
		for(;;){
			
			for( i = 0 ; i < 35000 ; i ++){
			i = i;
			}
		
			vTaskDelayUntil(&xLastWakeTime,10);

		}
		
}

	void Load_2_Simulation( void * pvParameters )
{
  		TickType_t xLastWakeTime = xTaskGetTickCount();
	int i = 0; 
		for(;;){

			
			for( i = 0 ; i < 82000 ; i ++)
			{
			i = i;
			}
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
void vApplicationIdleHook( void ){
	//your code here
	GPIO_write(PORT_0,PIN7,PIN_IS_HIGH);
	GPIO_write(PORT_0,PIN7,PIN_IS_LOW);
	
	}
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
                  &MButton_1_Handler,50 ); 
										
		     xTaskPeriodicCreate(
                    Button_2_Monitor,       /* Function that implements the task. */
                    "Button 2 Monitor",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &MButton_2_Handler, 50 );      /* Used to pass out the created task's handle. */
		     xTaskPeriodicCreate(
                    Periodic_Transmitter,       /* Function that implements the task. */
                    "UART Transmitter",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &UART_Transmitter_Handler,100 );      /* Used to pass out the created task's handle. */
		     xTaskPeriodicCreate(
                    Uart_Receiver,       /* Function that implements the task. */
                    "Uart Receiver",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Uart_Receiver_Handler,20 );      /* Used to pass out the created task's handle. */
		     xTaskPeriodicCreate(
                    Load_1_Simulation,       /* Function that implements the task. */
                    "Load 1 Simulation",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Load_1_Handler,10 );      /* Used to pass out the created task's handle. */							
		     xTaskPeriodicCreate(
                    Load_2_Simulation,       /* Function that implements the task. */
                    "Load 2 Simulation",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Load_2_Handler,100 );      /* Used to pass out the created task's handle. */				
								
								


	vTaskStartScheduler();

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


