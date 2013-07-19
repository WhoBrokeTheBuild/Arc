#pragma once

#include "Common.h"

#include <Arc/Program.h>
#include <Arc/Scene.h>
#include <Arc/Sound.h>

#include "Test.h"

class TestApp :
    public Arc::Program,
    public Arc::IKeyboardListener
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

    TestApp( void ) { }
    virtual ~TestApp( void ) { term(); }

    virtual string toString( void ) const { return "Test App"; }

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void keyPressed( const Event& event );

};

