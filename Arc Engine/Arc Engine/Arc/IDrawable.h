#pragma once

#ifndef __ARC_IDRAWABLE_H__
#define __ARC_IDRAWABLE_H__

#include "Common.h"

#include "RenderTarget.h"
#include "OriginLocation.h"

namespace Arc
{
    class IDrawable
    {
    protected:

        OriginLocation
            _originLocation;

        Point
            _origin;

        virtual void calcOriginLocation( void ) { }

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
            _originLocation = INVALID_ORIGIN_LOCATION;
            _origin         = Point::ZERO;

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

        virtual void render( const RenderTarget* renderTarget, const Vector2 pos ) = 0;

        virtual void setOrigin( Vector2 origin )
        {
            _origin = origin;
            _originLocation = ORIGIN_LOCATION_MANUAL;
        }

        virtual void setOrigin( OriginLocation originLocation )
        {
            _originLocation = ORIGIN_LOCATION_MANUAL;
            calcOriginLocation();
        }

    }; // class IDrawable

} // namespace Arc

#endif // __ARC_IDRAWABLE_H__
