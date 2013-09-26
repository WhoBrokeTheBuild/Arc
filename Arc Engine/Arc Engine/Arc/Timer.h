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
            MICRO,
			INV_MICRO;

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

		inline double calcDiffMillis( LARGE_INTEGER from, LARGE_INTEGER to ) const
		{
			double difference = (double)(to.QuadPart - from.QuadPart) * (MICRO / _freq.QuadPart);

			return difference * 0.001;
		}

#else

        timeval
            _startCount,
			_endCount;

		inline double calcDiffMillis( timeval from, timeval to ) const
		{
			return (double)( ((to.tv_sec - from.tv_sec) * 1000.0) + ((to.tv_usec - from.tv_usec) / 1000.0) );
		}

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
