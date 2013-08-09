#pragma once

#ifndef __TEST_UNIT_H__
#define __TEST_UNIT_H__

#include "Common.h"
#include <Arc/Unit.h>
#include <Arc/IDrawable.h>
#include <Arc/IPhysicsObject.h>
#include <Arc/ICollidable.h>
#include <Arc/IKeyboardListener.h>

class TestUnit :
    public Unit,
    public IDrawable,
    public IPhysicsObject,
    public ICollidable,
    public IKeyboardListener
{
public:

    bool
        Active;

    Size
        UnitSize;

    TestUnit( void );
    virtual ~TestUnit( void ) { term(); }

    virtual inline string toString( void ) const { return "Test Unit"; }

    virtual void init( Vector2 pos, Collider* collider, float depth = 0.0f, bool active = true );
    virtual void term( void );

    virtual void update( const FrameData* event  );
    virtual void render( const RenderData* event );

    virtual void keyHeld    ( const Event& event );
    virtual void keyReleased( const Event& event );

};

#endif // __TEST_UNIT_H__