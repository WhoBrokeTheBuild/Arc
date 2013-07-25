#include "Vector2.h"
#include "MathFunc.h"

Arc::Vector2 Arc::Vector2::ZERO         = Vector2(0);
Arc::Vector2 Arc::Vector2::ONE          = Vector2(1);
Arc::Vector2 Arc::Vector2::NEGATIVE_ONE = Vector2(-1);

std::string Arc::Vector2::toString( void ) const
{
    stringstream ss;
    ss << "Vector2 [X: " << X << ", Y: " << Y << "]";
    return ss.str();
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

float Arc::Vector2::distanceTo( Vector2 other )
{
    float dx = other.X - X,
          dy = other.Y - Y;

    return sqrt(dx * dx + dy * dy);
}

float Arc::Vector2::angleToDeg( Vector2 other )
{
    return toDeg(angleToRad(other));
}

float Arc::Vector2::angleToRad( Vector2 other )
{
    float dx = other.X - X,
          dy = other.Y - Y;

    return atan2(dy, dx);
}

Arc::Vector2 Arc::Vector2::lerp( const Vector2& other, float fraction )
{
    using Arc::lerp;
    return Vector2(lerp(X, other.X, fraction), lerp(Y, other.Y, fraction));
}

Arc::Vector2 Arc::Vector2::normLeft( const Vector2& other)
{
	float dx = other.X - X;
	float dy = other.Y - Y;

	return Vector2(-dy, dx);
}

Arc::Vector2 Arc::Vector2::normRright( const Vector2& other)
{
	float dx = other.X - X;
	float dy = other.Y - Y;

	return Vector2(dy, -dx);
}

float Arc::Vector2::dot( const Vector2& rhs )
{
	return (X * rhs.X) + (Y * rhs.Y);
}
