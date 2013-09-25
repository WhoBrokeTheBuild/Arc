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

#include "ResourceManager.h"

#include "Duck.h"

class TestApp :
    public Program,
    public IKeyboardListener,
    public IMouseListener
{
protected:
	
	ArrayList<Vector2> 
		_dirs,
		_obstacles;

public:

    Scene
        *pScene;

    Font
        *pFont;

    RenderedText
        *pFPSText;

	ResourceManager
		*pResourceManager;

	Duck
		*pPlayer;

    TestApp( void );
    virtual ~TestApp( void );

    virtual inline string toString( void ) const { return "Test App"; }

    virtual void update( const Event& event );
    virtual void render( const Event& event );
	virtual void renderEnd( const Event& event );

    virtual void keyPressed( const Event& event );
    virtual void mousePressed( const Event& event );

	ArrayList<Vector2> getValidMoveSpaces( Duck* duck );

}; // class TestApp

#endif // __TEST_APP_H__
