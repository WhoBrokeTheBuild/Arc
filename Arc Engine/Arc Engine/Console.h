
#pragma once

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#ifdef WINDOWS

#include "Defines.h"

#include <windows.h>

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

using namespace std;

static const WORD MAX_CONSOLE_LINES = 500;

void init_console( void );

#else

void init_console( void ) { }

#endif

#endif //__CONSOLE_H__
