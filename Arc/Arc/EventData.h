#pragma once

#ifndef __ARC_EVENT_DATA_H__
#define __ARC_EVENT_DATA_H__

#include "Common.h"
#include "ManagedObject.h"

#include "RenderTarget.h"
#include "FrameTime.h"
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

        inline CountData( int count ) { Count = count; };

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Count Data [Count: " << Count << "]";
            return ss.str();
        };

        virtual EventData* clone( void ) { return New CountData(Count); };

    }; // class CountData

	class FrameData
		: public EventData
	{
	private:

		FrameTime* _pFrameTime;

	public:

		FrameData( FrameTime* pFrameTime ) : _pFrameTime(pFrameTime) { }

		virtual inline string toString( void ) const { return "Frame Data"; }

		virtual inline EventData* clone( void ) const { return New FrameData(_pFrameTime); }

		virtual FrameTime* getFrameTime( void ) const { return _pFrameTime; }

	};

	/** Event data containing the render target for drawing to during render events
	  */
    class RenderData
        : public EventData
    {
    private:

        RenderTarget* _pRenderTarget; // The render target for the program

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
