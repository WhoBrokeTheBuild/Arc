#include "AnimatedUnit.h"

const EventType AnimatedUnit::EVENT_ANIMATION_COMPLETE = "animationComplete";

AnimatedUnit::AnimatedUnit( void )
{
}

AnimatedUnit::~AnimatedUnit( void )
{
    term();
}

std::string AnimatedUnit::toString( void ) const
{
    return "Animated Unit";
}

void AnimatedUnit::init( Animation* pAnimation /*= nullptr*/, Vector2 pos /*= Vector2::ZERO*/, Vector2 origin /*= Vector2::ZERO*/, float rot /*= 0.0f*/, Color blendColor /*= Color::WHITE*/, float depth /*= 1.0f*/ )
{
    Unit::init(pos, origin, rot, blendColor, depth);

    setAnimation(pAnimation, true);

    addEventListener(AnimatedUnit::EVENT_ANIMATION_COMPLETE,   this, &AnimatedUnit::animationComplete);
}

void AnimatedUnit::term( void )
{
    removeEventListener(AnimatedUnit::EVENT_ANIMATION_COMPLETE,   this, &AnimatedUnit::animationComplete);
}

void AnimatedUnit::update( const Event& event )
{
    const FrameData* frameData = event.dataAs<FrameData>();

    if (Animating && !(Looping && _animationComplete))
    {
        updateAnimation(frameData);
    }
}

void AnimatedUnit::render( const Event& event )
{
    const RenderData* renderData = event.dataAs<RenderData>();

    if (_pAnimation == nullptr)
        return;

    Sprite *currentFrame = _pAnimation->frameAt(_frame);

    if (currentFrame == nullptr)
        return;

    renderData->renderTarget()->draw(Pos - Origin, currentFrame->texture(), currentFrame->SourceRect, BlendColor, Rot, Origin);
}

void AnimatedUnit::setAnimation( Animation *pAnimation, bool useDefaults /*= true*/ )
{
    _pAnimation = pAnimation;
    _frame = 0;
    _animationTimeout = 0;
    Size = Size::ZERO;

    if (_pAnimation == nullptr)
    {
        Animating = false;
        Looping = false;
        _animationComplete = false;
        return;
    }

    if (useDefaults)
    {
        _animationTimeout = pAnimation->frameAt(_frame)->FrameTime;
        Size = _pAnimation->frameSize(_frame);

        Animating = pAnimation->Animating;
        Looping = pAnimation->Looping;
        _animationComplete = false;
    }
}

void AnimatedUnit::updateAnimation( const FrameData* pFrameData )
{
    _animationTimeout -= pFrameData->elapsedMilliseconds();
    if (_animationTimeout < 0)
    {
        if (!Looping)
        {
            if (_frame == _pAnimation->length() - 1)
            {
                _frame = clamp(_frame, 0, _pAnimation->length() - 1);
                dispatchEvent(Event(AnimatedUnit::EVENT_ANIMATION_COMPLETE));
                return;
            }
        }
        _frame = (_frame + 1) % _pAnimation->length();
        _animationTimeout = _pAnimation->frameAt(_frame)->FrameTime;
        Size = _pAnimation->frameSize(_frame);
    }
}

void AnimatedUnit::animationComplete( const Event& event )
{
    _animationComplete = true;
}