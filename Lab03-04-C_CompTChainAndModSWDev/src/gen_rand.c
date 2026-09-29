#include <stdlib.h>
#include "gen_rand.h"

void RandFunc (int *value, int *ncalls)
{
    static int count = 0;
    *value = rand() % (100 - 0 + 1) + 0; //rd_num= (rd_num % (max- min + 1)) + min
    count++;
    *ncalls = count;
}