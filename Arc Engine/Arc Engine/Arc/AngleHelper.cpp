#include "AngleHelper.h"
#include "MathHelper.h"

Arc::Direction Arc::AngleHelper::angleDegToDirFour( float angle )
{
	angle = abs(angle);

	if (MathHelper::between(angle, 45.0f, 135.0f))
	{
		return DIR_NORTH;
	}
	else if (MathHelper::between(angle, 135.0f, 225.0f))
	{
		return DIR_WEST;
	}
	else if (MathHelper::between(angle, 225.0f, 315.0f))
	{
		return DIR_SOUTH;
	}
	else if (MathHelper::between(angle, 315.0f, 0.0f) || MathHelper::between(angle, 0.0f, 45.0f))
	{
		return DIR_EAST;
	}

	return INVALID_DIRECTION;
}

Arc::Direction Arc::AngleHelper::angleDegToDirEight( float angle )
{
	angle = abs(angle);

	float check = 67.5f; // What is this?
	Direction dir = DIR_NORTH;
	for (unsigned int i = 0; i < 8; ++i)
	{
		float checkEnd = check + 45.0f;
		if (checkEnd >= 360.0f)
			checkEnd -= 360.0f;

		if (MathHelper::between(angle, check, checkEnd))
		{
			return dir;
		}

		dir = (Direction)(dir + 1);
		check += 45.0f;
		if (check >= 360.0f)
			check -= 360.0f;
	}

	return INVALID_DIRECTION;
}
