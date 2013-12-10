#pragma once

#ifndef __ARC_FRAME_TIME_H__
#define __ARC_FRAME_TIME_H__

#include "Common.h"
#include "ManagedObject.h"

namespace Arc
{
	/** Event data containing timing and frame rate information for each update
	  */
    class FrameTime :
		public ManagedObject
    {
    private:

        double
            _totalMilliseconds,   // Total milliseconds since the program started
            _elapsedMilliseconds, // Elapsed milliseconds since the last frame
            _deltaTime,           // Modifier based on ratio between the current and target FPS
			                      // the value is 1.0 if current FPS = target FPS and higher than
								  // 1.0 if current FPS < target FPS
            _currentFPS,          // Current FPS that the program is running at
            _targetFPS;           // Target FPS that the program is trying to run at

    public:

        FrameTime( void )
			: _totalMilliseconds(),
			  _elapsedMilliseconds(),
			  _deltaTime(),
			  _currentFPS(),
			  _targetFPS()
        {
        }

		FrameTime( double totalMillis, double elapsedMillis, double deltaTime, double currFPS = 0.0, double targetFPS = 0.0 )
			: _totalMilliseconds(totalMillis),
			_elapsedMilliseconds(elapsedMillis),
			_deltaTime(deltaTime),
			_currentFPS(currFPS),
			_targetFPS(targetFPS)
        {
        }

        virtual inline string toString( void ) const { return "Frame Data"; }

        inline void update(double elapsedMillis, double currFPS, double targetFPS)
        {
            _currentFPS = currFPS;
            _targetFPS  = targetFPS;

            _elapsedMilliseconds = elapsedMillis;
            _totalMilliseconds += _elapsedMilliseconds;
            _deltaTime = _targetFPS / _currentFPS;
        }

        double getTotalSeconds  ( void ) const { return _totalMilliseconds   / 1000.0; }
        double getElapsedSeconds( void ) const { return _elapsedMilliseconds / 1000.0; }

        double getTotalMilliseconds  ( void ) const { return _totalMilliseconds; }
        double getElapsedMilliseconds( void ) const { return _elapsedMilliseconds; }

        double getDeltaTime( void ) const { return _deltaTime; }

        double getCurrentFPS( void ) const { return _currentFPS; }
        double getTargetFPS( void ) const { return _targetFPS; }

    }; // class FrameData

} // namespace Arc

#endif // __ARC_FRAME_TIME_H__