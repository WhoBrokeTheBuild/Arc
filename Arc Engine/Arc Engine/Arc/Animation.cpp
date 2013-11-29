#include "Animation.h"

const Arc::EventType Arc::Animation::EVENT_FRAME_ADDED   = "animation.frameAdded";
const Arc::EventType Arc::Animation::EVENT_FRAME_REMOVED = "animation.frameRemoved";
const Arc::EventType Arc::Animation::EVENT_SPEED_CHANGED = "animation.speedChanged";

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

bool Arc::Animation::hasFrame( unsigned int frame )
{
    if (_frames.isEmpty())
        return false;

    return MathHelper::between(frame, unsigned(0), (unsigned int)_frames.getSize());
}
void Arc::Animation::addFrame( Sprite* frame )
{
	_frames.add(frame);
	dispatchEvent(Event(EVENT_FRAME_ADDED));
}

bool Arc::Animation::removeFrame( Sprite* frame )
{
	bool success = _frames.remove(frame);
	dispatchEvent(Event(EVENT_FRAME_REMOVED));
	return success;
}

bool Arc::Animation::removeFrame( int frame )
{
	bool success = _frames.removeAt(frame);
	dispatchEvent(Event(EVENT_FRAME_REMOVED));
	return success;
}