#include "Rect.h"
#include "Circle.h"

Arc::Rect Arc::Rect::ZERO = Rect(0.0f, 0.0f, 0.0f, 0.0f);
Arc::Rect Arc::Rect::ONE  = Rect(0.0f, 0.0f, 1.0f, 1.0f);

int Arc::Rect::serialize( ostream &stream )
{
    int bytes = 0;

    bytes += streamWriteFloat(X, stream);
    bytes += streamWriteFloat(Y, stream);
    bytes += streamWriteFloat(Width,  stream);
    bytes += streamWriteFloat(Height, stream);

    return bytes;
}

int Arc::Rect::deserialize( istream &stream )
{
    int bytes = 0;

    bytes += streamReadFloat(X, stream);
    bytes += streamReadFloat(Y, stream);
    bytes += streamReadFloat(Width,  stream);
    bytes += streamReadFloat(Height, stream);

    return bytes;
}

void Arc::Rect::setPos( Point pos )
{
    X = pos.X;
    Y = pos.Y;
}

void Arc::Rect::setSize( Size size )
{
    Width  = size.X;
    Height = size.Y;
}

bool Arc::Rect::intersectsRect( Rect other ) const
{
	Rect normal = getPositiveRect();

    if ( normal.getLeft() > other.getRight()  ||
         normal.getTop()  > other.getBottom() ||
         other.getLeft() > normal.getRight()  ||
         other.getTop()  > normal.getBottom() )
    {
        return false;
    }

    return true;
}

bool Arc::Rect::containsPoint( Point point ) const
{
	Rect normal = getPositiveRect();

	if( point.X < normal.getLeft()   ||
		point.X > normal.getRight()  ||
		point.Y < normal.getTop()    ||
		point.Y > normal.getBottom() )
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

Arc::Rect Arc::Rect::getIntersect( Rect other ) const
{
    float newLeft   = std::max(getLeft(),   other.getLeft());
    float newRight  = std::min(getRight(),  other.getRight());
    float newTop    = std::max(getTop(),    other.getTop());
    float newBottom = std::min(getBottom(), other.getBottom());

    return Rect(newLeft, newTop, newRight - newLeft, newBottom - newTop);
}

Arc::Rect Arc::Rect::getPositiveRect( void ) const
{
	// Create copy of rectangle without negatives
	Rect normal = Rect(X, Y, Width, Height);

	// Fix the X and Width
	if (normal.Width < 0)
	{
		normal.Width = abs(normal.Width);
		normal.X -= normal.Width;
	}

	// Fix the Y and Height
	if (normal.Height < 0)
	{
		normal.Height = abs(normal.Height);
		normal.Y -= normal.Height;
	}

	return normal;
}


