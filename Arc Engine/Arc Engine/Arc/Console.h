#pragma once

#ifndef __ARC_CONSOLE_H__
#define __ARC_CONSOLE_H__

#include "Defines.h"

#ifdef WINDOWS

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

    void initConsole( void );

} // namespace Arc

#else // LINUX

namespace Arc
{
    void initConsole( void ) { }

} // namespace Arc

#endif // WINDOWS

#endif // __ARC_CONSOLE_H__
