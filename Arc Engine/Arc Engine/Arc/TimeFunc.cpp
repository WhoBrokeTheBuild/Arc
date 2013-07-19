#include "TimeFunc.h"
#include "Timer.h"

time_t Arc::now( void )
{
    return time((time_t*)0);
}

void Arc::delay( double millis )
{
    Timer delayTimer = Timer();

    delayTimer.start();
    delayTimer.sleepUntilElapsed(millis);
}