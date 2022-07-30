#include "Pico_Clock.h"   //Examples
#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

static Clock_T current = {0};
static Clock_T run = {0};
static Clock_T starting = {0};
static Clock_T objective = {0};
static int64_t last_sync = 0;

#define HOUR_US (3600000000)
#define MIN_US  (60000000)
#define SEC_US  (1000000)

/* Task which iterates clock and do the display to LCD */
void vTaskClockDisplay( void * pvParameters )
{
        Pico_Clock(&current, &run, &objective, &last_sync);

}

/* Task which stores objective time and do the sync if necessary */
void vTaskObjectivTime( void* parameters)
{
    int64_t time = 0;
    while(1)
    {
        time = time_us_64();
        if(time - last_sync > 1000000*60)
        {
            printf("Current time: %i : %i : %i\n", current.hour, current.min, current.sec);
            objective.min = (objective.min + (time - last_sync)/MIN_US) % 60;
            objective.sec = (objective.sec + (time - last_sync)/SEC_US) % 60;
            last_sync = time;
            printf("Objectie time: %i : %i : %i  \n", objective.min, objective.min, objective.sec);
            printf("--------------------------------------\n");
            if(current.sec != objective.sec || current.min != objective.min )
            {
                run.sec = objective.sec;
                run.min = objective.min;
                //run.hour = objective.min;
            }
        }
    }
}

int main(void)
{
    stdio_init_all();
    sleep_ms(3000);
    
    BaseType_t xReturned, xReturned1;
    
    /* Create the task, storing the handle. */
    xReturned = xTaskCreate(
                    vTaskClockDisplay,
                    "Blinky task",
                    512,
                    NULL,
                    1,
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
