#pragma once

#include <ArcApp.h>
#include "Test.h"
#include <Scene.h>
#include <Sound.h>

class TestApp :
    public ArcApp,
    public IKeyboardListener
{
public:

    Sound
        *sound;

    Scene
        *scene;

    Test
        *pTest,
        *pTest2,
        *pTest3,
        *pTest4;

    Texture
        *tex;
    Animation
        *anim;

    ArrayList<Sprite*>
        sprites;

    TestApp( void );
    virtual ~TestApp( void );

    virtual string toString( void ) const { return "Test App"; }

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void keyPressed( const Event& event );

};

