#include "Animation.h"

std::string Animation::toString( void ) const
{
    return "Animation";
}

void Animation::init( ArrayList<Sprite*> frames, double speed /*= -1.0*/ )
{
    _frames = frames;
    Speed = speed;
}

void Animation::term( void )
{
}

Size Animation::frameSize( int frame )
{
    if (hasFrame(frame))
    {
        return frameAt(frame)->SourceRect.size();
    }

    return Size::ZERO;
}

Sprite* Animation::frameAt( int frame )
{
    if (hasFrame(frame))
    {
        return _frames[frame];
    }

    return nullptr;
}

bool Animation::hasFrame( int frame )
{
    if (_frames.empty())
        return false;

    return between(frame, 0, (int)_frames.size());
}

void Animation::addFrame( Sprite* frame )
{
    _frames.add(frame);
}

bool Animation::removeFrame( Sprite* frame )
{
    return _frames.remove(frame);
}

bool Animation::removeFrame( int frame )
{
    return _frames.removeAt(frame);;
}
