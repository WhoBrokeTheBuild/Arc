#include "Circle.h"
#include "Rect.h"

Arc::Circle Arc::Circle::ZERO = Circle(0, 0, 0);
Arc::Circle Arc::Circle::ONE  = Circle(1, 1, 1);

Arc::Circle::Circle( float x, float y, float radius )
{
    X = x;
    Y = y;
    Radius = radius;
}

Arc::Circle::Circle( Point pos, float radius )
{
    X = pos.X;
    Y = pos.Y;
    Radius = radius;
}

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

bool Arc::Circle::containsCircle( Circle other )
{
    float dist = pos().distanceTo(other.pos());

    return (dist < Radius + other.Radius);
}

bool Arc::Circle::containsRect( Rect rect ) //TODO: Test this later when primitives are implemented
{
    if ( ! rect.containsRect(bounds()))
        return false;

    Point rectCenter = rect.center();

    float
        halfWidth  = rect.halfWidth(),
        halfHeight = rect.halfHeight(),
        dx = abs(center().X - rectCenter.X),
        dy = abs(center().Y - rectCenter.Y);

    if (dx > (Radius + halfWidth) || dy > (Radius + halfHeight))
    {
        return false;
    }

    Size circleDist = Size(abs(center().X - rect.X - halfWidth), abs(center().Y - rect.Y - halfHeight));

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

bool Arc::Circle::containsPoint( Point point )
{
    return (pos().distanceTo(point) < Radius);
}

Arc::Rect Arc::Circle::bounds( void )
{
    return Rect(left(), top(), diameter(), diameter());
}
