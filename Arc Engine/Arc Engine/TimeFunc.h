#pragma once

#ifndef __ARC_TIME_FUNC_H__
#define __ARC_TIME_FUNC_H__

#include <ctime>

class Timer;

time_t now( void );

void delay( double millis );

#endif