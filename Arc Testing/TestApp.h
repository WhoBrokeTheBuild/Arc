#pragma once

#ifndef __TEST_APP_H__
#define __TEST_APP_H__

#include "Common.h"
#include <Arc/GraphicalProgram.h>

#include <Arc/ServerSocket.h>
#include <Arc/Font.h>
#include <Arc/RenderedText.h>
#include <Arc/IKeyboardListener.h>

class TestApp :
    public GraphicalProgram,
	public IKeyboardListener
{
protected:

	Font
		*_pFont;

	RenderedText
		*_pFPSText;

	Vector2
		_leftEyePos,
		_rightEyePos,
		_leftPupilPos,
		_rightPupilPos,
		_nosePos,
		_mouthLeftPos,
		_mouthCenterPos,
		_mouthRightPos;

public:

    TestApp( void );
    virtual ~TestApp( void );

    virtual inline string toString( void ) const { return "Test App"; }

    virtual void update( const Event& event );
	virtual void render( const Event& event );

	virtual void keyPressed( const Event& event );

}; // class TestApp

#endif // __TEST_APP_H__
