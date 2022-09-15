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
            float x, y, x2, y2;
            Rect intersect;

            x = a.x1 > b.x1 ? a.x1 : b.y1;
            y = a.y1 > b.y1 ? a.y1 : b.y1;
            x2 = a.x2 < b.x2 ? a.x2 : b.x2;
            y2 = a.y2 < b.y2 ? a.y2 : b.y2;
            intersect.Set(x, y, x2 - x, y2 - y);

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
