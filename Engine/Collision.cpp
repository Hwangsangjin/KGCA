#include "pch.h"
#include "Collision.h"

COLLISION_TYPE Collision::RectToRect(MyRect& a, MyRect& b)
{
    float minX;   float minY;
    float maxX;   float maxY;

    minX = a._x1 < b._x1 ? a._x1 : b._x1;
    minY = a._y1 < b._y1 ? a._y1 : b._y1;
    maxX = a._x2 > b._x2 ? a._x2 : b._x2;
    maxY = a._y2 > b._y2 ? a._y2 : b._y2;

    //  가로 판정
    if ((a._w + b._w) >= (maxX - minX))
    {
        //  세로 판정
        if ((a._h + b._h) >= (maxY - minY))
        {
            // 교집합
            float x1, y1, x2, y2;
            x1 = a._x1 > b._x1 ? a._x1 : b._x1;
            y1 = a._y1 > b._y1 ? a._y1 : b._y1;
            x2 = a._x2 < b._x2 ? a._x2 : b._x2;
            y2 = a._y2 < b._y2 ? a._y2 : b._y2;

            MyRect intersect;
            intersect.Set(x1, y1, x2 - x1, y2 - y1);

            if (intersect == a || intersect == b)
            {
                return COLLISION_TYPE::RECT_IN;
            }

            return COLLISION_TYPE::RECT_OVERLAP;
        }
    }

    return COLLISION_TYPE::RECT_OUT;
}

bool Collision::RectToInRect(MyRect& a, MyRect& b)
{
    if (a._x1 <= b._x1)
    {
        if ((a._x1 + a._w) >= b._x1 + b._w)
        {
            if (a._y1 <= b._y1)
            {
                if ((a._y1 + a._h) >= b._y1 + b._h)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Collision::CircleToCircle(MyCircle& a, MyCircle& b)
{
    float sum = a._radius + b._radius;
    float x = a._cx - b._cx;
    float y = a._cy - b._cy;
    float distance = sqrtf(x * x + y * y);

    if (distance <= sum)
    {
        return true;
    }

    return false;
}
