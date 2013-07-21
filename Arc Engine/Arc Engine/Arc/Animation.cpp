#include "Animation.h"

Arc::Animation::Animation( void )
{
    _frames = ArrayList<Sprite*>();
}

void Arc::Animation::init( ArrayList<Sprite*> frames, double speed /*= -1.0*/ )
{
    _frames = frames;
    Speed   = speed;
}

Arc::Size Arc::Animation::frameSize( int frame )
{
    if (hasFrame(frame))
    {
        return frameAt(frame)->SourceRect.size();
    }

    return Size::ZERO;
}

Arc::Sprite* Arc::Animation::frameAt( int frame )
{
    if (hasFrame(frame))
    {
        return _frames[frame];
    }

    return nullptr;
}

bool Arc::Animation::hasFrame( int frame )
{
    if (_frames.empty())
        return false;

    return between(frame, 0, (int)_frames.size());
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
    return _frames.removeAt(frame);;
}
