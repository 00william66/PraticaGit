#include <unity.h>
#include "swClockLib.h"

void setUp(void)
{
    return;
}

void tearDown(void)
{
    return;
}


void test_swClockLib_reset(void)
{
    swClock.hundredths = 38;
    swClock.seconds = 16;
    swClock.minutes = 2;

    resetSwClock();

    TEST_ASSERT_EQUAL_UINT8(0, swClock.hundredths);
    TEST_ASSERT_EQUAL_UINT8(0, swClock.seconds);
    TEST_ASSERT_EQUAL_UINT16(0, swClock.minutes);
}


void test_swClockLib_H_Rollover_M(void)
{
/*Test hundredths rollover to minutes, through seconds of course*/
    swClock.hundredths = 99;
    swClock.seconds = 59;
    swClock.minutes = 2;
    updateSwClock();
    TEST_ASSERT_EQUAL_UINT8(0, swClock.hundredths);
    TEST_ASSERT_EQUAL_UINT8(0, swClock.seconds);
    TEST_ASSERT_EQUAL_UINT16(3, swClock.minutes); 
}

void test_swClockLib_H_Increment(void)
{
/*Test the increment of hundredths*/
    swClock.hundredths = 38;
    swClock.seconds = 16;
    swClock.minutes = 2;
    updateSwClock();
    TEST_ASSERT_EQUAL_UINT8(39, swClock.hundredths);
    TEST_ASSERT_EQUAL_UINT8(16, swClock.seconds);
    TEST_ASSERT_EQUAL_UINT16(2, swClock.minutes);
}

void test_swClockLib_H_Rollover_S(void)
{
    swClock.hundredths = 99;
    swClock.seconds = 16;
    swClock.minutes = 2;
    updateSwClock();
    TEST_ASSERT_EQUAL_UINT8(0, swClock.hundredths);
    TEST_ASSERT_EQUAL_UINT8(17, swClock.seconds);
    TEST_ASSERT_EQUAL_UINT16(2, swClock.minutes);
}


int main (void)
{
    UNITY_BEGIN();

    RUN_TEST(test_swClockLib_reset);
    RUN_TEST(test_swClockLib_H_Increment);
    RUN_TEST(test_swClockLib_H_Rollover_S);
    RUN_TEST(test_swClockLib_H_Rollover_M);

    return UNITY_END();
}