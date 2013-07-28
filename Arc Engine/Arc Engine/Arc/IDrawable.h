#pragma once

#ifndef __ARC_IDRAWABLE_H__
#define __ARC_IDRAWABLE_H__

#include "Common.h"

#include "RenderTarget.h"

namespace Arc
{
    class IDrawable
    {
    protected:

    public:

        Color
            BlendColor;

        Vector2
            Scale;

        float
            Rot,
            Alpha;

        IDrawable( void )
        {
            BlendColor = Color::BLACK;
            Scale      = Vector2::ZERO;
            Rot        = 0.0f;
            Alpha      = 0.0f;
        }

        virtual ~IDrawable( void ) { }

        virtual void init( Color blendColor = Color::WHITE, float rot = 0.0f, float alpha = 0.0f, Vector2 scale = Vector2::ONE )
        {
            BlendColor = blendColor;
            Rot        = rot;
            Alpha      = alpha;
        }

    }; // class IDrawable

} // namespace Arc

#endif // __ARC_IDRAWABLE_H__
