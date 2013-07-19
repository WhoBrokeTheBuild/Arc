
#pragma once

#ifndef __ARC_FUNCTIONS_H__
#define __ARC_FUNCTIONS_H__

#include "Defines.h"

#include <iostream>
#include <sstream>

#include "TimeFunc.h"
#include "MathFunc.h"
#include "RandFunc.h"
#include "ParseFunc.h"
#include "StringFunc.h"
#include "InputFunc.h"

using std::string;
using std::stringstream;
using std::cin;
using std::cout;
using std::cerr;
#ifndef endl
    #define endl "\n"
#endif

namespace Arc
{
#ifdef DEBUG

#define ERR(SRC, MSG) \
    cerr << "[" << SRC << "] Error: " << MSG << " (In " << basename(__FILE__) << " on line " << __LINE__ << ")" << endl;

#define INF(SRC, MSG) \
    cout << "[" << SRC << "] Info: " << MSG << " (In " << basename(__FILE__) << " on line " << __LINE__ << ")" << endl;

#else

#define ERR(SRC, MSG)
#define INF(SRC, MSG)

#endif

    inline void noop ( void ) { }
    void die  ( int errorLevel = 0 );
    void pause( const std::string msg = "Press enter to continue" );

    template <typename Value>
    bool arrayContains(unsigned int size, const Value list[], const Value& element)
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            if (list[i] == element)
                return true;
        }

        return false;
    }

    template <typename Value>
    int arrayIndexOf(unsigned int size, const Value list[], const Value& element)
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            if (list[i] == element)
                return i;
        }

        return -1;
    }
}

#endif
