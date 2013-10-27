#include "Vector2.h"
#include "Angle.h"
#include "MathFunc.h"
#include "StreamFunc.h"

Arc::Vector2 Arc::Vector2::ZERO         = Vector2(0);
Arc::Vector2 Arc::Vector2::ONE          = Vector2(1);
Arc::Vector2 Arc::Vector2::NEGATIVE_ONE = Vector2(-1);

int Arc::Vector2::serialize( ostream &stream )
{
    int bytes = 0;

    bytes += streamWriteFloat(X, stream);
    bytes += streamWriteFloat(Y, stream);

    return bytes;
}

int Arc::Vector2::deserialize( istream &stream )
{
    int bytes = 0;

    bytes += streamReadFloat(X, stream);
    bytes += streamReadFloat(Y, stream);

    return bytes;
}

const Arc::Vector2 Arc::Vector2::operator+( const Vector2 &rhs ) const
{
    Vector2 result = *this;
    result += rhs;
    return result;
}

const Arc::Vector2 Arc::Vector2::operator-( const Vector2 &rhs ) const
{
    Vector2 result = *this;
    result -= rhs;
    return result;
}

const Arc::Vector2 Arc::Vector2::operator*( const Vector2& rhs ) const
{
	Vector2 result = *this;
	result *= rhs;
	return result;
}

const Arc::Vector2 Arc::Vector2::operator/( const Vector2& rhs ) const
{
	Vector2 result = *this;
	result /= rhs;
	return result;
}

const Arc::Vector2 Arc::Vector2::operator*( float value ) const
{
    Vector2 result = *this;
    result *= value;
    return result;
}

const Arc::Vector2 Arc::Vector2::operator/( float value ) const
{
    Vector2 result = *this;
    result /= value;
    return result;
}

Arc::Vector2& Arc::Vector2::operator+=( const Vector2 &rhs )
{
    X += rhs.X;
    Y += rhs.Y;
    return *this;
}

Arc::Vector2& Arc::Vector2::operator-=( const Vector2 &rhs )
{
    X -= rhs.X;
    Y -= rhs.Y;
    return *this;
}

Arc::Vector2& Arc::Vector2::operator*=( const Vector2& rhs )
{
	X *= rhs.X;
	Y *= rhs.Y;
	return *this;
}

Arc::Vector2& Arc::Vector2::operator/=( const Vector2& rhs )
{
	X /= rhs.X;
	Y /= rhs.Y;
	return *this;
}

Arc::Vector2& Arc::Vector2::operator*=( float value )
{
    X *= value;
    Y *= value;
    return *this;
}

Arc::Vector2& Arc::Vector2::operator/=( float value )
{
    X /= value;
    Y /= value;
    return *this;
}

Arc::Vector2& Arc::Vector2::operator=( const Vector2 &rhs )
{
    if (rhs == *this)
        return *this;

    X = rhs.X;
    Y = rhs.Y;
    return *this;
}

bool Arc::Vector2::operator==( const Vector2 &rhs ) const
{
    return (X == rhs.X && Y == rhs.Y);
}

bool Arc::Vector2::operator!=( const Vector2 &rhs ) const
{
    return !(*this == rhs);
}

bool Arc::Vector2::operator<( const Vector2& rhs ) const
{
	return (X < rhs.X && Y < rhs.Y);
}

bool Arc::Vector2::operator>( const Vector2& rhs ) const
{
	return (X > rhs.X && Y > rhs.Y);
}

bool Arc::Vector2::operator<=( const Vector2& rhs ) const
{
	return (X <= rhs.X && Y <= rhs.Y);
}

bool Arc::Vector2::operator>=( const Vector2& rhs ) const
{
	return (X >= rhs.X && Y >= rhs.Y);
}

float Arc::Vector2::getDistanceToSquared( const Vector2& other ) const
{
	float 
		dx = other.X - X,
		dy = other.Y - Y;

	return (dx * dx + dy * dy);
}

Arc::Angle Arc::Vector2::getAngleTo( const Vector2& other ) const
{
	return Angle(getAngleToRad(other), ANGLE_TYPE_RAD);
}

void Arc::Vector2::normalize( void )
{
	float length = getLength();
	if (length != 0)
	{
		X /= length;
	    Y /= length;
	}
}
