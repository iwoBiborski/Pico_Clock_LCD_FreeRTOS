#ifndef SPIRO_STATES_H
#define SPIRO_STATES_H

typedef enum Clock_State_Tag
{
    WELCOME = 0,
    CLOCK_INIT,
    CLOCK_RUN,
    CLOCK_IMAGE,
    STOP
}State_T;

typedef struct Pair_Tag
{
    float x;
    float y;

}Pair_T;

typedef struct Clock_Tag
{
    int hour;
    int min;
    int sec;
}Clock_T;

#endif