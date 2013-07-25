#include "CircleCollider.h"
#include "RectCollider.h"

bool Arc::CircleCollider::check( Point pos, Collider* pOther, Point otherPos )
{
    RectCollider*   rectOther   = dynamic_cast<RectCollider*>(pOther);
    CircleCollider* circleOther = dynamic_cast<CircleCollider*>(pOther);

    Circle newMask = CircleMask;
    newMask.X += pos.X;
    newMask.Y += pos.Y;

    if (rectOther != nullptr)
    {
        Rect newOtherMask = rectOther->RectMask;
        newOtherMask.X += otherPos.X;
        newOtherMask.Y += otherPos.Y;

        return newOtherMask.containsCircle(newMask);
    }
    else if (circleOther != nullptr)
    {
        Circle newOtherMask = circleOther->CircleMask;
        newOtherMask.X += otherPos.X;
        newOtherMask.Y += otherPos.Y;

        return newOtherMask.containsCircle(newMask);
    }

    return false;
}

void Arc::CircleCollider::render( const RenderTarget* renderTarget, Point pos )
{
    renderTarget->drawCircle(Circle(CircleMask.pos() + pos, CircleMask.Radius), Color::GREEN);
}

