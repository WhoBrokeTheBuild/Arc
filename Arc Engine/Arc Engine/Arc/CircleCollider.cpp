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

Arc::Point Arc::CircleCollider::getCollisionPoint( Point pos, Collider* pOther, Point otherPos )
{
    RectCollider*   rectOther   = dynamic_cast<RectCollider*>(pOther);
    CircleCollider* circleOther = dynamic_cast<CircleCollider*>(pOther);

    Rect newMask = CircleMask.bounds();
    newMask.X += pos.X;
    newMask.Y += pos.Y;

    if (rectOther != nullptr)
    {
        Rect newOtherMask = rectOther->RectMask;
        newOtherMask.X += otherPos.X;
        newOtherMask.Y += otherPos.Y;

        return newOtherMask.intersect(newMask).center();
    }
    else if (circleOther != nullptr)
    {
        Rect newOtherMask = circleOther->CircleMask.bounds();
        newOtherMask.X += otherPos.X;
        newOtherMask.Y += otherPos.Y;

        return newOtherMask.intersect(newMask).center();
    }

    return Point::ZERO;
}

void Arc::CircleCollider::render( const RenderTarget* renderTarget, Point pos, Vector2 origin /*= Vector2::ZERO*/ )
{
    renderTarget->drawCircle(Circle(CircleMask.pos() + pos, CircleMask.Radius), Color::GREEN, 0.0f, origin);
}

