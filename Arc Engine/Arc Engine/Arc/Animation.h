#pragma once

#ifndef __ARC_ANIMATION_H__
#define __ARC_ANIMATION_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "ArrayList.h"
#include "Sprite.h"

namespace Arc
{
    /* A collection of Sprites to act as frames in an animation.
     */
    class Animation :
        public EventDispatcher
    {
    private:
	
		// The list of frames to animate through
			ArrayList<Sprite*> _frames;
	
		// The animating speed in MS, a negative value won't animate
		double _speed;

	public:

#pragma region Event Types

		static const EventType EVENT_FRAME_ADDED;

		static const EventType EVENT_FRAME_REMOVED;

		static const EventType EVENT_SPEED_CHANGED;

#pragma endregion
			
		/* Creates a new animation with the specified list of frames and speed
		 * 
		 * @param frames: The list of frames to animate through
		 * @param speed: The animating speed in MS
		 *		default: -1.0
		 */
		inline Animation( ArrayList<Sprite*> frames, double speed = -1 )
			: _frames(frames),
			  _speed(speed)
		{ }
	
		/* Creates a new animation with the specified speed and an empty list of frames
		 * 
		 * @param speed: The animating speed in MS
		 *		default: -1.0
		 */
		Animation( double speed = -1 )
			: _frames(),
			  _speed(speed)
		{ }

		virtual inline ~Animation( void ) { }

		virtual inline string toString( void ) const { return "Animation"; }

		/* Whether the animation has a frame at the index specified
		 * 
		 * @param frame: The frame index to check
		 * @returns: Whether the frame index exists
		 */
		virtual bool hasFrame( unsigned int frame );

		/* Whether the animation has the specified sprite as a frame
		 * 
		 * @param pFrame: A pointer to the sprite to check
		 * @returns: Whether the sprite is in the animation
		 */
		virtual bool hasFrame( Sprite* pFrame );

		/* Add a frame to the end of the animation
		 * 
		 * @param pFrame: A pointer to the sprite to add as a frame
		 */
		virtual void addFrame( Sprite* pFrame );

		/* Removes a frame at the specified index, if it exists
		 * 
		 * @param frame: The frame index to remove
		 * @returns: True if the frame was successfully removed, false otherwise
		 */
		virtual bool removeFrame( int frame );
	
		/* Removes a sprite from the animation if it's used
		 * 
		 * @param pFrame: A pointer to the sprite to check
		 * @returns: True if the frame was successfully removed, false otherwise
		 */
		virtual bool removeFrame( Sprite* pFrame );

		/* Get the size of the sprite the specified frame index
		 * 
		 * @param frame: The frame index to check
		 * @returns: The size of the frame if it exists, or a size with a width and height of 0
		 */
		virtual Size getFrameSize( int frame );

		/* Get the sprite at the specified frame index
		 * 
		 * @param frame: The frame index to get
		 * @returns: A pointer to the sprite if it exists, or null if it doesn't
		 */
		virtual Sprite* getFrameAt( int frame );
	
		/* 
		 * @returns: The animation speed
		 */
		virtual inline double getSpeed( void ) { return _speed; }

		/* 
		 * @param speed: The speed in MS that the animation should run at
		 */
		virtual inline void setSpeed( double speed ) { _speed = speed; dispatchEvent(Event(EVENT_SPEED_CHANGED)); }

		/* Get the number of frames
		 * 
		 * @returns: The number of frames in the animation
		 */
		virtual int getLength( void ) { return (int)_frames.getSize(); }

    }; // class Animation

} // namespace Arc

#endif // __ARC_ANIMATION_H__
