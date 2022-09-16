#include "pch.h"
#include "Collision.h"

COLLISION_TYPE Collision::RectToRect(Rect& a, Rect& b)
{
    float minX;   float minY;
    float maxX;   float maxY;

    minX = a.x < b.x ? a.x : b.x;
    minY = a.y < b.y ? a.y : b.y;
    maxX = a.w > b.w ? a.w : b.w;
    maxY = a.h > b.h ? a.h : b.h;

    //  가로 판정
    if ((a.w + b.w) >= (maxX - minX))
    {
        //  세로 판정
        if ((a.h + b.h) >= (maxY - minY))
        {
            // 교집합
            float x, y, w, h;
            Rect intersect;

            x = a.x > b.x ? a.x : b.y;
            y = a.y > b.y ? a.y : b.y;
            w = a.w < b.w ? a.w : b.w;
            h = a.h < b.h ? a.h : b.h;

            intersect.Set(x, y, w, h);

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
    if (a.x <= b.x)
    {
        if ((a.x + a.w) >= b.x + b.w)
        {
            if (a.y <= b.y)
            {
                if ((a.y + a.h) >= b.y + b.h)
                {
                    return true;
                }
            }
        }
    }

    return false;
}
