#include "xtimer.h"

int clock(void)
{
    return xtimer_now().ticks32;
}
