#include "Line.h"
#include "Angle.h"

Arc::Line& Arc::Line::operator=( const Line &rhs )
{
    if (rhs == *this)
        return *this;

    A = rhs.A;
    B = rhs.B;
    return *this;
}

int Arc::Line::serialize( ostream &stream )
{
    int bytes = 0;

    bytes += A.serialize(stream);
    bytes += B.serialize(stream);

    return bytes;
}

int Arc::Line::deserialize( istream &stream )
{
    int bytes = 0;

    bytes += A.deserialize(stream);
    bytes += B.deserialize(stream);

    return bytes;
}

bool Arc::Line::operator==( const Line &rhs ) const
{
    return (A == rhs.A && B == rhs.B);
}

bool Arc::Line::operator!=( const Line &rhs ) const
{
    return !(*this == rhs);
}

Arc::Angle Arc::Line::angleAtoB( void )
{
    return A.getAngleTo(B);
}

Arc::Angle Arc::Line::angleBtoA( void )
{
    return B.getAngleTo(A);
}
