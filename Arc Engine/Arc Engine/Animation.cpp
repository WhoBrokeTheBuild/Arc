#include "Animation.h"

Animation::Animation( void )
{
}

Animation::~Animation( void )
{
    term();
}

std::string Animation::toString( void ) const
{
    return "Animation";
}

void Animation::init( vector<Sprite*> frames, bool animating /*= false */, bool looping /*= false */ )
{
    _frames = frames;
    Animating = animating;
    Looping = looping;
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
    return inBounds(frame, 0, (int)_frames.size());
}

void Animation::addFrame( Sprite* frame )
{
    _frames.push_back(frame);
}

bool Animation::removeFrame( Sprite* frame )
{
    return vectorRemove(_frames, frame);
}

bool Animation::removeFrame( int frame )
{
    return vectorRemoveAt(_frames, frame);
}