#include "RectCollider.h"
#include "CircleCollider.h"

bool RectCollider::check( Vector2 pos, Collider* pOther )
{
    RectCollider*   rectOther   = dynamic_cast<RectCollider*>(pOther);
    CircleCollider* circleOther = dynamic_cast<CircleCollider*>(pOther);

    if (rectOther != nullptr)
    {
        return rectOther->RectMask.containsRect(RectMask);
    }
    else if (circleOther != nullptr)
    {
        return circleOther->CircleMask.containsRect(RectMask);
    }

    return false;
}

