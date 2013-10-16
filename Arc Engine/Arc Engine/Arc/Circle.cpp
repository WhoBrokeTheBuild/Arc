#include "Circle.h"
#include "Rect.h"

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

int Arc::Circle::deserialize( istream &stream )
{
    int bytes = 0;

    bytes += streamReadFloat(X, stream);
    bytes += streamReadFloat(Y, stream);
    bytes += streamReadFloat(Radius, stream);

    return bytes;
}

bool Arc::Circle::intersectsCircle( Circle other )
{
    float dist = getPos().getDistanceTo(other.getPos());

    return (dist < Radius + other.Radius);
}

bool Arc::Circle::intersectsRect( Rect rect ) //TODO: Test this later when primitives are implemented
{
    if ( ! rect.intersectsRect(getBounds()))
        return false;

    Point rectCenter = rect.getCenter();

    float
        halfWidth  = rect.getHalfWidth(),
        halfHeight = rect.getHalfHeight(),
        dx = abs(getCenter().X - rectCenter.X),
        dy = abs(getCenter().Y - rectCenter.Y);

    if (dx > (Radius + halfWidth) || dy > (Radius + halfHeight))
    {
        return false;
    }

    Size circleDist = Size(abs(getCenter().X - rect.X - halfWidth), abs(getCenter().Y - rect.Y - halfHeight));

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
