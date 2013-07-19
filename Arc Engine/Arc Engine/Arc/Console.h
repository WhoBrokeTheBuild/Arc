
#pragma once

#ifndef __ARC_CONSOLE_H__
#define __ARC_CONSOLE_H__

#include "Defines.h"

#ifdef WINDOWS

#include "Defines.h"

#include <windows.h>

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

using std::string;
using std::ios;

namespace Arc
{
    static const WORD MAX_CONSOLE_LINES = 500;

    void init_console( void );
}

#else

namespace Arc
{
    void init_console( void ) { }
}

#endif

#endif //__CONSOLE_H__
