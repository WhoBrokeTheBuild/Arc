#pragma once

#ifndef __TEST_APP_H__
#define __TEST_APP_H__

#include "Common.h"
#include <Arc/Program.h>

class TestApp :
    public Program
{
protected:

public:

    TestApp( void );
    virtual ~TestApp( void );

    virtual inline string toString( void ) const { return "Test App"; }

    virtual void update( const Event& event );

}; // class TestApp

#endif // __TEST_APP_H__
