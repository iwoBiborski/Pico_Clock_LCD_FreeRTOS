#include "Pico_Clock.h"   //Examples
#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

static Clock_T current = {0};
static Clock_T run = {0};
static Clock_T objective = {0};
static int64_t last_sync = 0;

SemaphoreHandle_t xSemaphore;
static QueueHandle_t queHandle = NULL;

#define HOUR_US (3600000000)
#define MIN_US  (60000000)
#define SEC_US  (1000000)


void vTaskClockDisplay( void * pvParameters )
{
   Pico_Clock(&current, &run);
}

void vTaskObjectivTime( void* parameters)
{
    int64_t last_sync = 0;
    int64_t time = 0;
    while(1)
    {
        time = time_us_64();
        if(time - last_sync > 1000000 )
        {
            objective.hour = (objective.hour + (time - last_sync)/HOUR_US) % 12;
            objective.min = (objective.min + (time - last_sync)/MIN_US) % 60;
            objective.sec = (objective.sec + (time - last_sync)/SEC_US) % 60;
            //last_sync = time;
            printf("Objectie time: %i : %i : %i  \n", objective.hour, objective.min, objective.sec);
        }
    }
}

void usb_task(void* parameters)
{
    while(1)
    {
        char *log = malloc(50);
        xQueueReceive(queHandle, &log,portMAX_DELAY);
        printf("LOG: %s", *log);
        free(log);
    }
}

int main(void)
{
    stdio_init_all();
    sleep_ms(3000);
    //printf("Welcome \n");
    
    BaseType_t xReturned, xReturned1;
    TaskHandle_t xHandle = NULL;
    queHandle = xQueueCreate(1, 50);
    xSemaphore = xSemaphoreCreateBinary();
    
    /* Create the task, storing the handle. */
    xReturned = xTaskCreate(
                    vTaskClockDisplay,       /* Function that implements the task. */
                    "Blinky task",   /* Text name for the task. */
                    512,             /* Stack size in words, not bytes. */
                    NULL,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    NULL);   

    xReturned1 = xTaskCreate(vTaskObjectivTime,
                             "Objective",
                             512,
                             NULL,
                             1,
                             NULL);

    vTaskStartScheduler();
    while(1)
    {}
}
