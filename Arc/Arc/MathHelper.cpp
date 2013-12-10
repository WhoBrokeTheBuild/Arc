#include "MathHelper.h"

float Arc::MathHelper::floor( float value, int accuracy )
{
	int mult = 10 * accuracy;
	return floorf(value * mult) / mult;
}

double Arc::MathHelper::floor( double value, int accuracy )
{
	int mult = 10 * accuracy;
	return std::floor(value * mult) / mult;
}

float Arc::MathHelper::nearest( float value, int accuracy )
{
	int mult = 10 * accuracy;
	return floorf(value * mult + 0.5f) / mult;
}

double Arc::MathHelper::nearest( double value, int accuracy )
{
	int mult = 10 * accuracy;
	return std::floor(value * mult + 0.5) / mult;
}

float Arc::MathHelper::ceil( float value, int accuracy )
{
	int mult = 10 * accuracy;
	return ceilf(value * mult) / mult;
}

double Arc::MathHelper::ceil( double value, int accuracy )
{
	int mult = 10 * accuracy;
	return std::ceil(value * mult) / mult;
}

template <class Number>
Number Arc::MathHelper::hermite( Number x0, Number x1, Number x2, Number x3, Number mu, double tension, double bias )
{
	Number m0, m1, mu2, mu3;
	Number a0, a1, a2, a3;

	mu2 = mu * mu;
	mu3 = mu2 * mu;
	m0  = (x1 - x0) * (1 + bias) * (1 - tension) / 2;
	m0 += (x2 - x1) * (1 - bias) * (1 - tension) / 2;
	m1  = (x2 - x1) * (1 + bias) * (1 - tension) / 2;
	m1 += (x3 - x2) * (1 - bias) * (1 - tension) / 2;
	a0 =  2 * mu3 - 3 * mu2 + 1;
	a1 =      mu3 - 2 * mu2 + mu;
	a2 =      mu3 -     mu2;
	a3 = -2 * mu3 + 3 * mu2;

	return (a0 * x1 + a1 * m0 + a2 * m1 + a3 * x2);
}
