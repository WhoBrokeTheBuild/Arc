#pragma once

#ifndef __TEST_APP_H__
#define __TEST_APP_H__

#include "Common.h"
#include <Arc/Program.h>
#include <Arc/IKeyboardListener.h>
#include <Arc/IMouseListener.h>

#include <Arc/Scene.h>
#include <Arc/Font.h>
#include <Arc/RenderedText.h>

class TestApp :
    public Program,
    public IKeyboardListener,
    public IMouseListener
{
public:

    Scene
        *pScene;

    Font
        *pFont;

    RenderedText
        *pFPSText;

    TestApp( void ) { }
    virtual ~TestApp( void ) { term(); }

    virtual inline string toString( void ) const { return "Test App"; }

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void keyPressed( const Event& event );

    virtual void mousePressed( const Event& event );

}; // class TestApp

#endif // __TEST_APP_H__
