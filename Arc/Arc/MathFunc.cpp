#include "MathFunc.h"
#include "Vector2.h"
#include "MathHelper.h"

bool Arc::linesIntersect( Vector2 L1P1, Vector2 L1P2, Vector2 L2P1, Vector2 L2P2 )
{
    float
        ua = 0,
        ub = 0,
        ud = (L2P2.Y - L2P1.Y) * (L1P2.X - L1P1.X) - (L2P2.X - L2P1.X) * (L1P2.Y - L1P1.Y);

    if (ud != 0)
    {
        ua = ((L2P2.X - L2P1.X) * (L1P1.Y - L2P1.Y) - (L2P2.Y - L2P1.Y) * (L1P1.X - L2P1.X)) / ud;
        ub = ((L1P2.X - L1P1.X) * (L1P1.Y - L2P1.Y) - (L1P2.Y - L1P1.Y) * (L1P1.X - L2P1.X)) / ud;

        if (ua < 0 || ua > 1 || ub < 0 || ub > 1)
            ua = 0;
    }

    return ua != 0;
}
