#include "Angle.h"

const Arc::Angle Arc::Angle::ZERO        = Arc::Angle(0.0f);
const Arc::Angle Arc::Angle::HALF_CIRCLE = Arc::Angle(180.0f);
const Arc::Angle Arc::Angle::UP          = Arc::Angle(90.0f);
const Arc::Angle Arc::Angle::DOWN        = Arc::Angle(270.0f);
const Arc::Angle Arc::Angle::LEFT        = Arc::Angle(180.0f);
const Arc::Angle Arc::Angle::RIGHT       = Arc::Angle(0.0f);

const Arc::Angle Arc::Angle::operator+( const Angle& rhs ) const
{
    Angle result = *this;
    result += rhs;
    return result;
}

const Arc::Angle Arc::Angle::operator-( const Angle& rhs ) const
{
    Angle result = *this;
    result -= rhs;
    return result;
}

const Arc::Angle Arc::Angle::operator*( float value ) const
{
    Angle result = *this;
    result *= value;
    return result;
}

const Arc::Angle Arc::Angle::operator/( float value ) const
{
    Angle result = *this;
    result /= value;
    return result;
}

Arc::Angle& Arc::Angle::operator+=( const Angle& rhs )
{
    setDeg(_degrees + rhs._degrees);
    return *this;
}

Arc::Angle& Arc::Angle::operator-=( const Angle& rhs )
{
    setDeg(_degrees -= rhs._degrees);
    return *this;
}

Arc::Angle& Arc::Angle::operator*=( float value )
{
    setDeg(_degrees * value);
    return *this;
}

Arc::Angle& Arc::Angle::operator/=( float value )
{
    setDeg(_degrees / value);
    return *this;
}

Arc::Angle& Arc::Angle::operator=( const Angle& rhs )
{
    if (rhs == *this)
        return *this;

    _degrees = rhs._degrees;
    return *this;
}

bool Arc::Angle::operator==( const Angle& rhs ) const
{
    return (_degrees == rhs._degrees);
}

bool Arc::Angle::operator!=( const Angle& rhs ) const
{
    return (_degrees != rhs._degrees);
}

bool Arc::Angle::operator<( const Angle& rhs ) const
{
    return (_degrees < rhs._degrees);
}

bool Arc::Angle::operator>( const Angle& rhs ) const
{
    return (_degrees > rhs._degrees);
}

bool Arc::Angle::operator<=( const Angle& rhs ) const
{
    return (_degrees <= rhs._degrees);
}

bool Arc::Angle::operator>=( const Angle& rhs ) const
{
    return (_degrees >= rhs._degrees);
}
