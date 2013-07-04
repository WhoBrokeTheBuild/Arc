#include "TimeFunc.h"
#include "Timer.h"

time_t now( void )
{
    return time((time_t*)0);
}

void delay( double millis )
{
    Timer delayTimer = Timer();

    delayTimer.start();
    delayTimer.sleepUntilElapsed(millis);
}