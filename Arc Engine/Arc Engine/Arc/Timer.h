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
	/** A timer class to handle calculating lengths of time and sleeping for lengths of time
	  */
    class Timer :
        public ManagedObject
    {
    private:

		// Constant for converting from microseconds to seconds
        static double
            MICRO;

        double
            _startTimeMillis, // Start time in milliseconds
            _endTimeMillis;   // End time in milliseconds

		// Whether the timer is stopped or not
        bool
            _stopped;

#ifdef WINDOWS

		// Start and end times 
        LARGE_INTEGER
            _freq,
            _startCount,
            _endCount;

		inline double calcDiffMillis( LARGE_INTEGER from, LARGE_INTEGER to ) const
		{
			return (double)(to.QuadPart - from.QuadPart) * (MICRO / _freq.QuadPart) * 0.001;
		}

#else

		// Start and end times 
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
		virtual inline ~Timer( void ) { }

        virtual inline string toString( void ) const { return "Timer"; }

		// Start the timer and reset the time
        void start( void );

		// Stop the timer and record the stop time
        void stop ( void );

		// Get the elapsed milliseconds from when the timer was started until now
		// if the timer is running, or until it stopped if it isn't running 
        double getElapsedMilli( void );

		// Get the elapsed time in seconds
        double getElapsedSeconds( void );

		// Sleep until the specificed number of milliseconds have passed
        void sleepUntilElapsed( double millis );

    }; // class Timer

} // namespace Arc

#endif // __ARC_TIMER_H__
