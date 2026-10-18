#include "configData.h"

static uint16_t maxConnections;

void ConfigInit(void)
{
    maxConnections = 0;
}

void configSetMaxConnections(uint16_t value)
{
    maxConnections = value;
}

uint16_t configGetMaxConnections(void)
{
    return maxConnections;
}