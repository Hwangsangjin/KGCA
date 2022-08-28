#include "pch.h"
#include "Collision.h"

CollisionType Collision::RectToRect(Rect& a, Rect& b)
{
    // 0 : 완전제외(0)
    // 1 : 완전포함(1) -> 걸쳐져 있는 상태(2)
    // a.x(10)----30------a.x2(40)
    // 합집합
    float fMinX;   float fMinY;
    float fMaxX;   float fMaxY;
    fMinX = a.x1 < b.x1 ? a.x1 : b.x1;
    fMinY = a.y1 < b.y1 ? a.y1 : b.y1;
    fMaxX = a.x2 > b.x2 ? a.x2 : b.x2;
    fMaxY = a.y2 > b.y2 ? a.y2 : b.y2;
    //  가로 판정
    if ((a.w + b.w) >= (fMaxX - fMinX))
    {
        //  세로 판정
        if ((a.h + b.h) >= (fMaxY - fMinY))
        {
            // 교차한다. 교집합
            float x, y, x2, y2;
            Rect Intersect;
            x = a.x1 > b.x1 ? a.x1 : b.y1;
            y = a.y1 > b.y1 ? a.y1 : b.y1;
            x2 = a.x2 < b.x2 ? a.x2 : b.x2;
            y2 = a.y2 < b.y2 ? a.y2 : b.y2;
            Intersect.Set(x, y, x2 - x, y2 - y);
            if (Intersect == a || Intersect == b)
            {
                return CollisionType::In;
            }
            return CollisionType::Overlap;
        }
    }
    return CollisionType::Out;
}

bool Collision::RectToInRect(Rect& a, Rect& b)
{
    //  |             |
    if (a.x1 <= b.x1)
    {
        if ((a.x1 + a.w) >= b.x1 + b.w)
        {
            if (a.y1 <= b.y1)
            {
                if ((a.y1 + a.h) >= b.y1 + b.h)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Collision::CircleToCircle(Circle& a, Circle& b)
{
    float fSumRadius = a._radius + b._radius;
    float x = a._x - b._x;
    float y = a._y - b._y;
    float fDistance = sqrtf(x * x + y * y);
    if (fDistance <= fSumRadius)
    {
        return true;
    }

    return false;
}

CollisionType Collision::BoxToBox(Box& a, Box& b)
{
    // 0 : 완전제외(0)
    // 1 : 완전포함(1) -> 걸쳐져 있는 상태(2)
    // a.x(10)----30------a.x2(40)
    // 합집합
    float fMinX;    float fMaxX;
    float fMinY;    float fMaxY;
    float fMinZ;    float fMaxZ;
    fMinX = a._vMin._x < b._vMin._x ? a._vMin._x : b._vMin._x;
    fMinY = a._vMin._y < b._vMin._y ? a._vMin._y : b._vMin._y;
    fMaxX = a._vMax._x > b._vMax._x ? a._vMax._x : b._vMax._x;
    fMaxY = a._vMax._y > b._vMax._y ? a._vMax._y : b._vMax._y;

    fMinZ = a._vMin._z < b._vMin._z ? a._vMin._z : b._vMin._z;
    fMaxZ = a._vMax._z > b._vMax._z ? a._vMax._z : b._vMax._z;

    //  가로 판정
    if ((a._vSize._x + b._vSize._x) >= (fMaxX - fMinX))
    {
        //  세로 판정
        if ((a._vSize._y + b._vSize._y) >= (fMaxY - fMinY))
        {
            if ((a._vSize._z + b._vSize._z) >= (fMaxZ - fMinZ))
            {
                // 교차한다. 교집합
                Vector3 vMin, vMax;
                Box Intersect;
                vMin._x = a._vMin._x > b._vMin._x ? a._vMin._x : b._vMin._x;
                vMin._y = a._vMin._y > b._vMin._y ? a._vMin._y : b._vMin._y;
                vMin._z = a._vMin._z > b._vMin._z ? a._vMin._z : b._vMin._z;

                vMax._x = a._vMax._x < b._vMax._x ? a._vMax._x : b._vMax._x;
                vMax._y = a._vMax._y < b._vMax._y ? a._vMax._y : b._vMax._y;
                vMax._z = a._vMax._z < b._vMax._z ? a._vMax._z : b._vMax._z;

                Intersect.Set(vMin, vMax - vMin);
                if (Intersect == a || Intersect == b)
                {
                    return CollisionType::In;
                }
                return CollisionType::Overlap;
            }
        }
    }
    return CollisionType::Out;
}

bool Collision::BoxToInBox(Box& a, Box& b)
{
    //  |             |
    if (a._vMin <= b._vMin)
    {
        if (a._vMax >= b._vMax)
        {
            return true;
        }
    }

    return false;
}

bool Collision::SphereToSphere(Sphere& a, Sphere& b)
{
    float fSumRadius = a._radius + b._radius;
    Vector3 vDir = a._vCenter - b._vCenter;
    float fDistance = vDir.Size();
    if (fDistance <= fSumRadius)
    {
        return true;
    }

    return false;
}
