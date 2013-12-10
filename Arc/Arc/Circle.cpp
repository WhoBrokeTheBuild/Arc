#include "Circle.h"
#include "Rect.h"
#include "Buffer.h"

Arc::Circle Arc::Circle::ZERO = Circle(0, 0, 0);
Arc::Circle Arc::Circle::ONE  = Circle(1, 1, 1);

int Arc::Circle::serialize( ostream &stream )
{
    int bytes = 0;

    bytes += streamWriteFloat(X, stream);
    bytes += streamWriteFloat(Y, stream);
    bytes += streamWriteFloat(Radius, stream);

    return bytes;
}

int Arc::Circle::serialize( Buffer& buffer )
{
	int bytes = 0;

	buffer.appendFloat(X);
	bytes += sizeof(X);

	buffer.appendFloat(Y);
	bytes += sizeof(Y);

	buffer.appendFloat(Radius);
	bytes += sizeof(Radius);

	return bytes;
}

int Arc::Circle::deserialize( istream &stream )
{
    int bytes = 0;

    bytes += streamReadFloat(X, stream);
    bytes += streamReadFloat(Y, stream);
    bytes += streamReadFloat(Radius, stream);

    return bytes;
}

int Arc::Circle::deserialize( Buffer& buffer )
{
	int bytes = 0;

	X = buffer.readNextFloat();
	bytes += sizeof(X);

	Y = buffer.readNextFloat();
	bytes += sizeof(Y);

	Radius = buffer.readNextFloat();
	bytes += sizeof(Radius);

	return bytes;
}

bool Arc::Circle::intersectsCircle( Circle other ) const
{
    float dist = getPos().getDistanceTo(other.getPos());

    return (dist < Radius + other.Radius);
}

bool Arc::Circle::intersectsRect( Rect rect ) const //TODO: Test this later when primitives are implemented
{
    if ( ! rect.intersectsRect(getBounds()))
        return false;

    Point rectCenter = rect.getCenter();

    float
        halfWidth  = rect.getHalfWidth(),
        halfHeight = rect.getHalfHeight(),
        dx = abs(X - rectCenter.X),
        dy = abs(Y - rectCenter.Y);

    if (dx > (Radius + halfWidth) || dy > (Radius + halfHeight))
    {
        return false;
    }

    Size circleDist = Size(abs(X - rect.X - halfWidth), abs(Y - rect.Y - halfHeight));

    if (circleDist.X <= halfWidth)
    {
        return true;
    }

    if (circleDist.Y <= halfHeight)
    {
        return true;
    }

    float cornerDistSquared = pow(circleDist.X - halfWidth, 2) + pow(circleDist.Y - halfHeight, 2);

    return (cornerDistSquared <= (pow(Radius, 2)));
}

bool Arc::Circle::containsPoint( Point point ) const
{
    return (getPos().getDistanceTo(point) < Radius);
}

Arc::Rect Arc::Circle::getBounds( void ) const
{
	return Rect(getLeft(), getTop(), getDiameter(), getDiameter());
}