#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include"API001_Network.h"
#include"ApplianceComponentOperationMode.h"

unsigned long TIME = 5;

int DEBUG_TRACE = 1; 

//define task handles
TaskHandle_t TaskBlink_Handler;
TaskHandle_t TaskSerial_Handler;

SemaphoreHandle_t xSerialSemaphore;

// define two Tasks for DigitalRead & AnalogRead
void TaskDigitalRead( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

extern unsigned int RunningMinute;
unsigned long delayStart = 0; // the time the delay started

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  delayStart = millis();   // start delay
   
  //Initialize_ApplianceComponentOperationMode();
  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

   // Now set up two Tasks to run independently.
  xTaskCreate(
    TaskDigitalRead
    ,  "DigitalRead"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle

  xTaskCreate(
    TaskAnalogRead
    ,  "AnalogRead" // A name just for humans
    ,  128  // Stack size
    ,  NULL //Parameters for the task
    ,  2  // Priority
    ,  NULL ); //Task Handle
}

void loop() {
}
/*---------------------- Tasks ---------------------*/
void TaskDigitalRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  for (;;) // A Task shall never return or exit.
  { 
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      if(RunningMinute == TIME){ //Every 5 Seconds
        Serial.println("5 Minute: ");
        if(RunningMinute == 55){
          TIME = 0;
        }else{
          TIME += 5;
        }
        REVEAL_COMMAND_TYPE *command ;
        Reveal__NewCommand2(command,API1,OPCODE2);
        Reveal__AddDataU8(command,0xA);
        Reveal__AddDataU8(command,0xA);
        PublishToSerial(command);
      }

      xSemaphoreGive( xSerialSemaphore ); // Now free  
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskAnalogRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  Serial.println("Initialize Appliance Component");
  Initialize_ApplianceComponentOperationMode();
  for (;;)
  {
    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {

      if(((millis() - delayStart) >= 1000)){
        RunningMinute ++;
        if((RunningMinute/60) == 1){
          UpdateRunningHours(0);
          RunningMinute = 0;
        }
        Serial.print("RunningMinute: ");
        Serial.println(RunningMinute);
        delayStart = millis();
      }
      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}