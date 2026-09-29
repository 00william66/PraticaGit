#include "swClockLib.h"


swClock_t swClock;

void resetSwClock(void)
{
    swClock.hundredths = 0;
    swClock.seconds = 0;
    swClock.minutes = 0;
}

void updateSwClock(void)
{
    if (swClock.hundredths == 99)
    {
       if (swClock.seconds == 59)
       {
            swClock.hundredths = 0;
            swClock.seconds = 0;
            swClock.minutes++;
       }
       else
       {
            swClock.hundredths = 0;
            swClock.seconds++;
       }
    } 
    else 
    swClock.hundredths++;
}