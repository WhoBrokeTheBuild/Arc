#include "Line.h"

Arc::Line& Arc::Line::operator=( const Line &rhs )
{
    if (rhs == *this)
        return *this;

    A = rhs.A;
    B = rhs.B;
    return *this;
}

bool Arc::Line::operator==( const Line &rhs ) const
{
    return (A == rhs.A && B == rhs.B);
}

bool Arc::Line::operator!=( const Line &rhs ) const
{
    return !(*this == rhs);
}