#ifndef CONFIGDATA_H
#define CONFIGDATA_H

# include <stdio.h>
#include <stdint.h>

void ConfigInit(void);
void configSetMaxConnections(uint16_t value); /*Set the value of maxConections */
uint16_t configGetMaxConnections(void); /*Get the value of maxConnections*/


#endif