#include "Duck.h"

Duck::Duck( Vector2 pos, int speed /*= 1*/, float depth /*= 0.0f*/ )
	: Unit(pos, depth),
	  _speed(speed)
{
}

Duck::~Duck(void)
{
}
