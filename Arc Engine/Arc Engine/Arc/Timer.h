#pragma once

#ifndef __ARC_TIMER_H__
#define __ARC_TIMER_H__

#include "Common.h"
#include "ManagedObject.h"

#include <ctime>
#include <cmath>

#ifdef WINDOWS

#include <Windows.h>

#else // LINUX

#include <sys/time.h>
#include <unistd.h>

#endif // WINDOWS

namespace Arc
{
    class Timer :
        public ManagedObject
    {
    private:

        static double
            MICRO;

        double
            _startTimeMillis,
            _endTimeMillis;

        bool
            _stopped;

#ifdef WINDOWS

        LARGE_INTEGER
            _freq,
            _startCount,
            _endCount;

        double calcDiffMillis( LARGE_INTEGER from, LARGE_INTEGER to ) const;

#else

        timeval
            _startCount,
            _endCount;

        double calcDiffMillis( timeval from, timeval to ) const;

#endif

    public:

        Timer( void );

        virtual inline string toString( void ) const { return "Timer"; }

        void start( void );
        void stop ( void );

        double getElapsedMilli( void );
        double getElapsed( void );

        void sleepUntilElapsed( double millis );

    }; // class Timer

} // namespace Arc

#endif // __ARC_TIMER_H__
