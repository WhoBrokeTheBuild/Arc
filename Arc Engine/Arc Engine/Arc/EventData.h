#pragma once

#ifndef __ARC_EVENT_DATA_H__
#define __ARC_EVENT_DATA_H__

#include "Common.h"
#include "GameObject.h"

#include "RenderTarget.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Arc
{
    class EventData
        : public GameObject
    {
    public:

        virtual string toString( void ) const { return "Event Data"; };

        virtual EventData* clone( void ) const { return New EventData(); };

    }; // class EventData

    class PointData
        : public EventData
    {
    public:

        float
            X,
            Y;

        PointData( float x, float y ) { X = x; Y = y; };
        PointData( Vector2 point ) { X = point.X; Y = point.Y; };

        Vector2 vector2( void ) { return Vector2(X, Y); };

        virtual string toString( void ) const
        {
            stringstream ss;
            ss << "Point Data [X: " << X << ", Y: " << Y << "]";
            return ss.str();
        };

        virtual EventData* clone( void ) const { return New PointData(X, Y); };

    }; // class PointData

    class CountData
        : public EventData
    {
    public:

        int
            Count;

        CountData( int count ) { Count = count; };

        virtual string toString( void ) const
        {
            stringstream ss;
            ss << "Count Data [Count: " << Count << "]";
            return ss.str();
        };

        virtual EventData* clone( void ) { return New CountData(Count); };

    }; // class CountData

    class FrameData :
        public EventData
    {
    private:

        double
            _totalMilliseconds,
            _elapsedMilliseconds,
            _deltaTime,
            _currentFPS,
            _targetFPS;

    public:

        FrameData( void )
        {
            _totalMilliseconds   = 0;
            _elapsedMilliseconds = 0;
            _deltaTime = 0;
        }

        FrameData( double totalMillis, double elapsedMillis, double deltaTime )
        {
            _totalMilliseconds   = totalMillis;
            _elapsedMilliseconds = elapsedMillis;
            _deltaTime           = deltaTime;
        }

        virtual string toString( void ) const { return "Frame Data"; }

        virtual EventData* clone( void ) const { return New FrameData(_totalMilliseconds, _elapsedMilliseconds, _deltaTime); }

        inline void update(double elapsedMillis, double currFPS, double targetFPS)
        {
            _currentFPS = currFPS;
            _targetFPS  = targetFPS;

            _elapsedMilliseconds = elapsedMillis;
            _totalMilliseconds += elapsedMillis;
            _deltaTime = _targetFPS / _currentFPS;
        }

        double totalSeconds  ( void ) const { return _totalMilliseconds   / 1000.0; }
        double elapsedSeconds( void ) const { return _elapsedMilliseconds / 1000.0; }

        double totalMilliseconds  ( void ) const { return _totalMilliseconds; }
        double elapsedMilliseconds( void ) const { return _elapsedMilliseconds; }

        double deltaTime( void ) const { return _deltaTime; }

        double currentFPS( void ) const { return _currentFPS; }
        double targetFPS( void ) const { return _currentFPS; }

    }; // class FrameData

    class RenderData
        : public EventData
    {
    private:

        RenderTarget
            *_pRenderTarget;

    public:

        RenderData( RenderTarget *pRenderTarget ) { _pRenderTarget = pRenderTarget; }

        virtual string toString( void ) const { return "Render Data"; }

        virtual EventData* clone( void ) const { return New RenderData(_pRenderTarget); }

        virtual RenderTarget* renderTarget( void ) const { return _pRenderTarget; }

    }; // class RenderData

    class KeyData
        : public EventData
    {
    public:

        KeyboardKey
            Key;

        KeyData( KeyboardKey key ) { Key = key; }

        virtual string toString( void ) const { return "Key Data"; }

        virtual EventData* clone( void ) const { return New KeyData(Key); }

    }; // class KeyData

    class MouseData
        : public EventData
    {
    private:

    public:

        Vector2
            Pos,
            Delta;

        MouseButton
            Button;

        MouseData( Vector2 pos, Vector2 delta, MouseButton button = INVALID_MOUSE_BUTTON ) { Pos = pos; Delta = delta; Button = button; }

        virtual string toString( void ) const { return "Mouse Data"; }

        virtual EventData* clone( void ) const { return New MouseData(Pos, Delta, Button); }

    }; // class MouseData

} // namespace Arc

#endif // __ARC_EVENT_DATA_H__
