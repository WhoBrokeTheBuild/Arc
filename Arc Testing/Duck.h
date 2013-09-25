#pragma once

#ifndef __DUCK_H__
#define __DUCK_H__

#include "Common.h"
#include <Arc/Unit.h>

class Duck :
	public Unit
{
protected:

	int 
		_speed;

public:
	
    Duck( Vector2 pos, int speed = 1, float depth = 0.0f );
	virtual ~Duck( void );
	
	virtual inline Point getPos( void ) const { return _pos * GRID_SIZE; }

	virtual inline int getSpeed( void ) const { return _speed; }
	virtual inline void setSpeed( int speed ) { _speed = speed; }

};

#endif // __DUCK_H__