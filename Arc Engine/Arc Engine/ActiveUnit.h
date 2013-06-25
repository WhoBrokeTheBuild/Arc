#pragma once

#ifndef __ACTIVE_UNIT_H__
#define __ACTIVE_UNIT_H__

#include "ArcCommon.h"
#include "AnimatedUnit.h"

#include "Animation.h"

class ActiveUnit :
    public AnimatedUnit
{
protected:

    virtual void updateMovement( const FrameData* frameData );

public:

    Vector2
        Vel,
        Acc;

    ActiveUnit( void );
    virtual ~ActiveUnit( void );

    virtual string toString( void ) const;

    virtual void init( Animation* pAnimation = nullptr, Vector2 pos = Vector2::ZERO, Vector2 vel = Vector2::ZERO, Vector2 acc = Vector2::ZERO, Vector2 origin = Vector2::ZERO, float rot = 0.0f, Color blendColor = Color::WHITE, float depth = 1.0f );
    virtual void term( void );

    virtual void update( const Event& event );

    virtual void inputPressed ( const Event& event );
    virtual void inputReleased( const Event& event );
    virtual void inputHeld    ( const Event& event );

};

#endif