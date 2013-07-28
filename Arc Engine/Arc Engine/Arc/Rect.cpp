#include "Rect.h"
#include "Circle.h"

Arc::Rect Arc::Rect::ZERO = Rect(0, 0, 0, 0);
Arc::Rect Arc::Rect::ONE  = Rect(0, 0, 1, 1);

Arc::Rect::Rect( float x, float y, float width, float height )
{
    X = x;
    Y = y;
    Width = width;
    Height = height;
}

Arc::Rect::Rect( void )
{
    X = 0;
    Y = 0;
    Width = 0;
    Height = 0;
}

Arc::Rect::Rect( Vector2 pos, Vector2 size )
{
    X = pos.X;
    Y = pos.Y;
    Width = size.X;
    Height = size.Y;
}

string Arc::Rect::toString( void ) const
{
    stringstream ss;
    ss << "Rect [X: " << X << ", Y: " << Y << ", W: " << Width << ", H: " << Height << "]";
    return ss.str();
}

void Arc::Rect::setPos( Vector2 pos )
{ 
    X = pos.X;
    Y = pos.Y;
}

void Arc::Rect::setSize( Vector2 size )
{
    Width = size.X;
    Height = size.Y;
}

bool Arc::Rect::containsRect( Rect other ) const
{
    if ( left() > other.right()  ||
         top()  > other.bottom() ||
         other.left() > right()  ||
         other.top()  > bottom() )
    {
        return false;
    }

    return true;
}

bool Arc::Rect::containsCircle( Circle other ) const
{
    return other.containsRect(*this);
}

bool Arc::Rect::containsPoint( Vector2 point ) const
{
    if( point.X < left()   ||
        point.X > right()  ||
        point.Y < top()    ||
        point.Y > bottom() )
    {
        return false;
    }

    return true;
}

const Arc::Rect Arc::Rect::operator+( const Rect &rhs ) const
{
    Rect result = *this;
    result += rhs;
    return result;
}

const Arc::Rect Arc::Rect::operator-( const Rect &rhs ) const
{
    Rect result = *this;
    result -= rhs;
    return result;
}

Arc::Rect& Arc::Rect::operator+=( const Rect &rhs )
{
    X      += rhs.X;
    Y      += rhs.Y;
    Width  += rhs.Width;
    Height += rhs.Height;
    return *this;
}

Arc::Rect& Arc::Rect::operator-=( const Rect &rhs )
{
    X      -= rhs.X;
    Y      -= rhs.Y;
    Width  -= rhs.Width;
    Height -= rhs.Height;
    return *this;
}

bool Arc::Rect::operator==( const Rect &rhs ) const
{
    return (X == rhs.X && Y == rhs.Y && Width == rhs.Width && Height == rhs.Height);
}

bool Arc::Rect::operator!=( const Rect &rhs ) const
{
    return !(*this == rhs);
}

Arc::Rect Arc::Rect::intersect( Rect other ) const
{
    float newLeft   = std::max(left(),   other.left());
    float newRight  = std::min(right(),  other.right());
    float newTop    = std::max(top(),    other.top());
    float newBottom = std::min(bottom(), other.bottom());

    return Rect(newLeft, newTop, newRight - newLeft, newBottom - newTop);
}


