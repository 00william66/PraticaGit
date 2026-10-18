#include "configData.h"
#include "unity.h"

void setUp(void)
{
    return;
}

void tearDown(void)
{
    return;
}

void test_configInit(void)
{
    ConfigInit();
    TEST_ASSERT_EQUAL_UINT16(0, configGetMaxConnections());
}

void test_configSetMaxConnections(void)
{
    configSetMaxConnections(3);
    TEST_ASSERT_EQUAL_UINT16(3, configGetMaxConnections());
}

int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(test_configInit);
    RUN_TEST(test_configSetMaxConnections);

    UNITY_END();
    return 0;
}