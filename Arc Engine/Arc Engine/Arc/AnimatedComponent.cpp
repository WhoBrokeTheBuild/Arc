#include "AnimatedComponent.h"
#include "Unit.h"

const Arc::UnitComponentType Arc::AnimatedComponent::UNIT_CMP_TYPE_ANIMATED = "animated";

const Arc::EventType Arc::AnimatedComponent::EVENT_ANIMATION_COMPLETE = "animatedComponent.animationComplete";
const Arc::EventType Arc::AnimatedComponent::EVENT_FRAME_CHANGED      = "animatedComponent.frameChanged";


void Arc::AnimatedComponent::update( const FrameData* data )
{
	if (_pAnimation == nullptr)
		return;

	_timeout -= data->getElapsedMilliseconds();
	if (_timeout <= 0)
	{
		_timeout = _pAnimation->getSpeed();
		_frame = (_frame + 1) % _pAnimation->getLength();
		dispatchEvent(Event(EVENT_FRAME_CHANGED));
	}
}

void Arc::AnimatedComponent::render( const RenderData* data )
{
	if (_pAnimation == nullptr)
		return;

	if ( ! _pAnimation->hasFrame(_frame))
		return;

	data->getRenderTarget()->draw(getUnit()->getPos(), _pAnimation->getFrameAt(_frame)->getTexture(), _pAnimation->getFrameAt(_frame)->getSourceRect(), getBlendColor(), getRotation(), getScale(), getOrigin());
}
