#include "CircleCollider.h"
#include "RectCollider.h"

bool CircleCollider::check( Vector2 pos, Collider* pOther )
{
    RectCollider*   rectOther   = dynamic_cast<RectCollider*>(pOther);
    CircleCollider* circleOther = dynamic_cast<CircleCollider*>(pOther);

    if (rectOther != nullptr)
    {
        return rectOther->RectMask.containsCircle(CircleMask);
    }
    else if (circleOther != nullptr)
    {
        return circleOther->CircleMask.containsCircle(CircleMask);
    }


    return false;
}

