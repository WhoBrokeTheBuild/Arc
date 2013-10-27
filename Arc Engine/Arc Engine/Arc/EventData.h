#pragma once

#ifndef __ARC_EVENT_DATA_H__
#define __ARC_EVENT_DATA_H__

#include "Common.h"
#include "ManagedObject.h"

#include "RenderTarget.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Arc
{
	/** Base class for data to be passed along with an event 
	  */
    class EventData
        : public ManagedObject
    {
    public:

        virtual inline ~EventData( void ) { }

        virtual inline string toString( void ) const { return "Event Data"; };

        virtual EventData* clone( void ) const { return New EventData(); };

    }; // class EventData

	/** Event data containing a single X,Y coordinate
	  */
    class PointData
        : public EventData
    {
    public:

        float
            X,
            Y;

        PointData( float x, float y ) { X = x; Y = y; };
        PointData( Vector2 point ) { X = point.X; Y = point.Y; };

        Vector2 getVector2( void ) { return Vector2(X, Y); };

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Point Data [X: " << X << ", Y: " << Y << "]";
            return ss.str();
        };

        virtual EventData* clone( void ) const { return New PointData(X, Y); };

    }; // class PointData

	/** Event data containing a index or count
	  */
    class CountData
        : public EventData
    {
    public:

        int
            Count;

        CountData( int count ) { Count = count; };

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Count Data [Count: " << Count << "]";
            return ss.str();
        };

        virtual EventData* clone( void ) { return New CountData(Count); };

    }; // class CountData

	/** Event data containing timing and frame rate information for each update
	  */
    class FrameData :
        public EventData
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

        FrameData( void )
			: _totalMilliseconds(),
			  _elapsedMilliseconds(),
			  _deltaTime(),
			  _currentFPS(),
			  _targetFPS()
        {
        }

		FrameData( double totalMillis, double elapsedMillis, double deltaTime, double currFPS = 0.0, double targetFPS = 0.0 )
			: _totalMilliseconds(totalMillis),
			_elapsedMilliseconds(elapsedMillis),
			_deltaTime(deltaTime),
			_currentFPS(currFPS),
			_targetFPS(targetFPS)
        {
        }

        virtual inline string toString( void ) const { return "Frame Data"; }

        virtual inline EventData* clone( void ) const { return New FrameData(_totalMilliseconds, _elapsedMilliseconds, _deltaTime, _currentFPS, _targetFPS); }

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

	/** Event data containing the render target for drawing to during render events
	  */
    class RenderData
        : public EventData
    {
    private:

        RenderTarget
            *_pRenderTarget; // The render target for the program

    public:

        RenderData( RenderTarget *pRenderTarget ) { _pRenderTarget = pRenderTarget; }

        virtual inline string toString( void ) const { return "Render Data"; }

        virtual EventData* clone( void ) const { return New RenderData(_pRenderTarget); }

        virtual RenderTarget* getRenderTarget( void ) const { return _pRenderTarget; }

    }; // class RenderData

	/** Event data containing a KeyboardKey used in Keyboard events
	  */
    class KeyData
        : public EventData
    {
    public:

        KeyboardKey
            Key; // Keyboard Key that was either pressed, released, or held

        KeyData( KeyboardKey key ) { Key = key; }

        virtual inline string toString( void ) const { return "Key Data"; }

        virtual EventData* clone( void ) const { return New KeyData(Key); }

    }; // class KeyData

	/** Event data containing a position, delta position, and MouseButton used in Mouse events
	  */
    class MouseData
        : public EventData
    {
    private:

    public:

        Vector2
            Pos,   // Current mouse position
            Delta; // Change in position from the last frame

        MouseButton
            Button; // Mouse Button that was either pressed, released, or held

        MouseData( Vector2 pos, Vector2 delta, MouseButton button = INVALID_MOUSE_BUTTON ) { Pos = pos; Delta = delta; Button = button; }

        virtual inline string toString( void ) const { return "Mouse Data"; }

        virtual EventData* clone( void ) const { return New MouseData(Pos, Delta, Button); }

    }; // class MouseData

} // namespace Arc

#endif // __ARC_EVENT_DATA_H__
