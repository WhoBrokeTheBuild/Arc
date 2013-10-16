#include "Animation.h"

Arc::Animation::Animation( ArrayList<Sprite*> frames, double speed /*= -1.0*/ )
	: _frames(frames),
	  _speed(speed)
{
}

Arc::Animation::~Animation( void )
{
}

Arc::Size Arc::Animation::getFrameSize( int frame )
{
    if (hasFrame(frame))
    {
		return getFrameAt(frame)->getSourceRect().getSize();
    }

    return Size::ZERO;
}

Arc::Sprite* Arc::Animation::getFrameAt( int frame )
{
    if (hasFrame(frame))
    {
        return _frames[frame];
    }

    return nullptr;
}

bool Arc::Animation::hasFrame( int frame )
{
    if (_frames.isEmpty())
        return false;

    return between(frame, 0, (int)_frames.getSize());
}

void Arc::Animation::addFrame( Sprite* frame )
{
    _frames.add(frame);
}

bool Arc::Animation::removeFrame( Sprite* frame )
{
    return _frames.remove(frame);
}

bool Arc::Animation::removeFrame( int frame )
{
    return _frames.removeAt(frame);
}
