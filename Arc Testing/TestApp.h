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
#include <Arc/Sound.h>

#include "ResourceManager.h"
#include "SpinMenu.h"

class TestApp :
    public Program,
    public IKeyboardListener
{
protected:

	Font
		*_pFont;

	RenderedText
		*_pFPSText;

	SpinMenu
		*_pRootMenu,
		*_pCurrMenu;

public:

    Scene
        *pScene;

	ResourceManager
		*pResourceManager;

    TestApp( void );
    virtual ~TestApp( void );

    virtual inline string toString( void ) const { return "Test App"; }

    virtual void update( const Event& event );
    virtual void render( const Event& event );
	virtual void renderEnd( const Event& event );

    virtual void keyPressed( const Event& event );

}; // class TestApp

#endif // __TEST_APP_H__
