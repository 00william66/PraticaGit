#ifndef SWCLOCKLIB_H
#define SWCLOCKLIB_H

#include <stdint.h>

typedef struct 
{
    uint8_t hundredths;
    uint8_t seconds;
    uint16_t minutes;
} swClock_t;

extern swClock_t swClock;

void resetSwClock(void);
void updateSwClock(void);
void test_swClockLib_H_Rollover_S(void);
void test_swClockLib_H_Increment(void);
void test_swClockLib_H_Rollover_M(void);

#endif 