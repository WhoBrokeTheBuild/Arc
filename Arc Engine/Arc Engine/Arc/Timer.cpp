#include "Timer.h"

double Arc::Timer::MICRO = 1000000.0;

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
    _startTimeMicro = 0;
    _endTimeMicro   = 0;
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

double Arc::Timer::getElapsedMicro( void )
{
#ifdef WINDOWS

    if (!_stopped)
        QueryPerformanceCounter(&_endCount);

    _startTimeMicro = _startCount.QuadPart * (MICRO / _freq.QuadPart);
    _endTimeMicro   = _endCount.QuadPart * (MICRO / _freq.QuadPart);

#else // LINUX

    if (!_stopped)
        gettimeofday(&_endCount, nullptr);

    _startTimeMicro = (_startCount.tv_sec * MICRO) + _startCount.tv_usec;
    _endTimeMicro   = (_endCount.tv_sec * MICRO) + _endCount.tv_usec;

#endif // WINDOWS

    return _endTimeMicro - _startTimeMicro;
}

double Arc::Timer::getElapsedMilli( void )
{
    return getElapsedMicro() / 1000.0;
}

double Arc::Timer::getElapsed( void )
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

    QueryPerformanceCounter(&currentTime);
    timeToSleep = millis - calcDiffMillis(_startCount, currentTime);

#else // LINUX

    timeval
        currentTime,
        lastTime;

    gettimeofday(&currentTime, nullptr);
    timeToSleep = millis - calcDiffMillis(_startCount, currentTime);

#endif // WINDOWS

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

        timeToSleep -= abs(timeElapsed);

        if( timeToSleep > 10.0 )
        {
#ifdef WINDOWS

            Sleep(10);

#else // LINUX

            usleep(10 * 1000);

#endif // WINDOWS
        }
    }
}

#ifdef WINDOWS

double Arc::Timer::calcDiffMillis( LARGE_INTEGER from, LARGE_INTEGER to ) const
{
    double difference = (double)(to.QuadPart - from.QuadPart) * (MICRO / _freq.QuadPart);

    return difference / 1000.0;
}

#else // LINUX

double Arc::Timer::calcDiffMillis( timeval from, timeval to ) const
{
    double
        start = (from.tv_sec / MICRO) + from.tv_usec,
        end   = (to.tv_sec   / MICRO) + to.tv_usec;

    return (end - start) / 1000.0;
}

#endif // WINDOWS
