#pragma once

#ifndef __ARC_IDRAWABLE_IMAGE_H__
#define __ARC_IDRAWABLE_IMAGE_H__

#include "Common.h"
#include "IDrawable.h"

#include "Animation.h"

namespace Arc
{
    class IDrawableImage :
        public IDrawable
    {
    protected:

        Animation
            *_pAnimation;

        double
            _animationTimeout;

        bool
            _animationComplete;

    public:

        int
            Frame;

        bool
            Looping;

        IDrawableImage( void )
            : _pAnimation(nullptr),
              _animationTimeout(),
              _animationComplete(),
              Frame(),
              Looping()
        {
        }

        virtual ~IDrawableImage( void ) { }

        virtual void init( Animation* pAnimation = nullptr, bool looping = false, Color blendColor = Color::WHITE, float rot = 0.0f, float alpha = 0.0f )
        {
            IDrawable::init(blendColor, rot, alpha);

            Frame = 0;
            Looping = looping;
            setAnimation(pAnimation);
        }

        virtual void updateImage( const double elapsedMillis )
        {
            if (_pAnimation == nullptr)
                return;

            if (_animationComplete)
                return;

            _animationTimeout -= elapsedMillis;
            if (_animationTimeout <= 0)
            {
                if (!Looping && Frame == _pAnimation->length() - 1)
                {
                    animationComplete();
                    _animationComplete = true;
                    return;
                }
                Frame = (Frame + 1) % _pAnimation->length();
                _animationTimeout = _pAnimation->Speed;
            }
        }

        virtual void renderImage( const RenderTarget* renderTarget, const Point pos, const Vector2 origin )
        {
            if (_pAnimation == nullptr)
                return;

            if (!_pAnimation->hasFrame(Frame))
            {
                ERROR("IDrawableImage", "Frame Index out of range");
                return;
            }

            Sprite* sprite = _pAnimation->getFrameAt(Frame);

            renderTarget->draw(pos, sprite->getTexture(), sprite->SourceRect, BlendColor, Rot, origin);
        }

        virtual void setAnimation( Animation* pAnimation )
        {
            _pAnimation = pAnimation;

            if (_pAnimation == nullptr)
                return;

            Frame = 0;
            _animationComplete = false;

            if (_pAnimation->hasFrame(Frame))
            {
                _animationTimeout = _pAnimation->Speed;
            }
        }

        virtual void animationComplete( void ) { };

    }; // class IDrawableImage

} // namespace Arc

#endif // __ARC_IDRAWABLE_IMAGE_H__
