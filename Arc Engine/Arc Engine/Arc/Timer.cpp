#include "Timer.h"

double Arc::Timer::MICRO     = 1000000.0;

Arc::Timer::Timer( void )
{
#ifdef WINDOWS

    QueryPerformanceFrequency(&_freq);
    _startCount.QuadPart = 0;
    _endCount.QuadPart   = 0;

#else // LINUX

    _startCount.tv_sec = 0;
    _startCount.tv_usec = 0;
    _endCount.tv_sec = 0;
    _endCount.tv_usec = 0;

#endif // WINDOWS

    _stopped = false;
    _startTimeMillis = 0;
    _endTimeMillis   = 0;
}

void Arc::Timer::start( void )
{
    _stopped = false;

#ifdef WINDOWS

    QueryPerformanceCounter(&_startCount);

#else // LINUX

    gettimeofday(&_startCount, nullptr);

#endif // WINDOWS
}

void Arc::Timer::stop( void )
{
    _stopped = true;

#ifdef WINDOWS

    QueryPerformanceCounter(&_endCount);

#else // LINUX

    gettimeofday(&_endCount, nullptr);

#endif // WINDOWS
}

double Arc::Timer::getElapsedMilli( void )
{
#ifdef WINDOWS

	// Get the current time if the timer is still going
    if ( ! _stopped)
        QueryPerformanceCounter(&_endCount);

	// Convert the start and end times into milliseconds
    _startTimeMillis = (_startCount.QuadPart * (MICRO / _freq.QuadPart)) * 0.001;
    _endTimeMillis   = (_endCount.QuadPart * (MICRO / _freq.QuadPart)) * 0.001;

#else // LINUX

	// Get the current time if the timer is still going
    if ( ! _stopped)
        gettimeofday(&_endCount, nullptr);

	// Convert the start and end times into milliseconds
    _startTimeMillis = ((_startCount.tv_sec * MICRO) + _startCount.tv_usec) * 0.001;
    _endTimeMillis   = ((_endCount.tv_sec * MICRO) + _endCount.tv_usec) * 0.001;

#endif // WINDOWS

    return _endTimeMillis - _startTimeMillis;
}

double Arc::Timer::getElapsedSeconds( void )
{
    return getElapsedMilli() / 1000.0;
}

void Arc::Timer::sleepUntilElapsed( double millis )
{
    double timeToSleep;

#ifdef WINDOWS

    LARGE_INTEGER
        currentTime,
        lastTime;

	// Calculate time necessary to sleep
    QueryPerformanceCounter(&currentTime);
    timeToSleep = millis - calcDiffMillis(_startCount, currentTime);

#else // LINUX

    timeval
        currentTime,
        lastTime;

	// Calculate time necessary to sleep
    gettimeofday(&currentTime, nullptr);
    timeToSleep = millis - calcDiffMillis(_startCount, currentTime);

#endif // WINDOWS
	
	// Hack for preventing negative time to sleep
    timeToSleep = std::max(0.0, timeToSleep);

	// Loop until the time to sleep has been exhausted
    while (timeToSleep > 0.0)
    {
        double timeElapsed;
        lastTime = currentTime;

#ifdef WINDOWS

        QueryPerformanceCounter(&currentTime);
        timeElapsed = calcDiffMillis(lastTime, currentTime);

#else // LINUX

        gettimeofday(&currentTime, nullptr);
        timeElapsed = calcDiffMillis(lastTime, currentTime);

#endif // WINDOWS

        timeToSleep -= timeElapsed;

        if( timeToSleep > 10.0 )
        {
#ifdef WINDOWS

			// Sleep for 10 milliseconds per loop
            Sleep(10);

#else // LINUX

			// Sleep for 10 milliseconds per loop
            usleep(10 * 1000);

#endif // WINDOWS
        }
    }
}
