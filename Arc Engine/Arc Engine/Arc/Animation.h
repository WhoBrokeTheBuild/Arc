#pragma once

#ifndef __ARC_ANIMATION_H__
#define __ARC_ANIMATION_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "ArrayList.h"
#include "Sprite.h"

namespace Arc
{
	/** A collection of Sprites to act as frames in an animation.
	  *
	  */
    class Animation :
        public EventDispatcher
    {
    private:
		
		// The list of frames
        ArrayList<Sprite*>
            _frames;

		// The animating speed
		double
			_speed;

    public:

        Animation( ArrayList<Sprite*> frames = ArrayList<Sprite*>(), double speed = -1.0 );
        virtual ~Animation( void );

        virtual inline string toString( void ) const { return "Animation"; }

        virtual bool hasFrame   ( int frame );
        virtual void addFrame   ( Sprite* pFrame );
        virtual bool removeFrame( int pFrame );
        virtual bool removeFrame( Sprite* pFrame );

        virtual Size    getFrameSize( int frame );
        virtual Sprite* getFrameAt  ( int frame );

		virtual inline double getSpeed( void ) { return _speed; }
		virtual inline void setSpeed( double speed ) { _speed = speed; }

        virtual int getLength( void ) { return (int)_frames.size(); }

    }; // class Animation

} // namespace Arc

#endif // __ARC_ANIMATION_H__
