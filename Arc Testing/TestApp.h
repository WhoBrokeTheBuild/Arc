#pragma once

#ifndef __TEST_APP_H__
#define __TEST_APP_H__

#include "Common.h"
#include <Arc/Program.h>

#include <Arc/ServerSocket.h>
#include <Arc/Font.h>
#include <Arc/RenderedText.h>

class TestApp :
    public Program
{
protected:

	Font
		*_pFont;

	RenderedText
		*_pFPSText;

public:

    TestApp( void );
    virtual ~TestApp( void );

    virtual inline string toString( void ) const { return "Test App"; }

    virtual void update( const Event& event );

	virtual void render( const Event& event );

}; // class TestApp

#endif // __TEST_APP_H__
