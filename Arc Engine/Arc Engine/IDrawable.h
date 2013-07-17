#pragma once

#ifndef __IDRAWABLE_H__
#define __IDRAWABLE_H__

#include "ArcCommon.h"
#include "RenderTarget.h"
#include "OriginLocation.h"

class IDrawable
{
protected:

    OriginLocation
        _originLocation;

    Vector2
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

};

#endif