#include "pch.h"
#include "Collision.h"

COLLISION_TYPE Collision::RectToRect(Rect& a, Rect& b)
{
    float minX;   float minY;
    float maxX;   float maxY;

    minX = a.x1 < b.x1 ? a.x1 : b.x1;
    minY = a.y1 < b.y1 ? a.y1 : b.y1;
    maxX = a.x2 > b.x2 ? a.x2 : b.x2;
    maxY = a.y2 > b.y2 ? a.y2 : b.y2;

    //  가로 판정
    if ((a.w + b.w) >= (maxX - minX))
    {
        //  세로 판정
        if ((a.h + b.h) >= (maxY - minY))
        {
            // 교집합
            float x1, y1, x2, y2;
            x1 = a.x1 > b.x1 ? a.x1 : b.x1;
            y1 = a.y1 > b.y1 ? a.y1 : b.y1;
            x2 = a.x2 < b.x2 ? a.x2 : b.x2;
            y2 = a.y2 < b.y2 ? a.y2 : b.y2;

            Rect intersect;
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

bool Collision::RectToInRect(Rect& a, Rect& b)
{
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
    float sum = a.radius + b.radius;
    float x = a.cx - b.cx;
    float y = a.cy - b.cy;
    float distance = sqrtf(x * x + y * y);

    if (distance <= sum)
    {
        return true;
    }

    return false;
}
