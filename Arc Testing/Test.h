#pragma once

#include <Animation.h>
#include <Unit.h>
#include <IDrawableImage.h>
#include <IPhysicsObject.h>
#include <ICollidable.h>

#include <IFrameListener.h>
#include <IKeyboardListener.h>

class Test :
    public Unit,
    public IDrawableImage,
    public IPhysicsObject,
    public ICollidable,
    public IKeyboardListener
{
public:

    float speed;

    Test( void ) { };
    virtual ~Test( void ) { term(); }

    virtual void init( Animation* pAnimation );
    virtual void term( void );

    virtual string toString( void ) const { return "Test"; }

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void keyReleased( const Event& event );
    virtual void keyHeld( const Event& event );

};

