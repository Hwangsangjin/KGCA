#include "Collision.h"

CollisionType Collision::RectToRect(CRect& a, CRect& b)
{
    // 0 : ��������(0)
    // 1 : ��������(1) -> ������ �ִ� ����(2)
    // a.x(10)----30------a.x2(40)
    // ������
    float fMinX;   float fMinY;
    float fMaxX;   float fMaxY;
    fMinX = a.x1 < b.x1 ? a.x1 : b.x1;
    fMinY = a.y1 < b.y1 ? a.y1 : b.y1;
    fMaxX = a.x2 > b.x2 ? a.x2 : b.x2;
    fMaxY = a.y2 > b.y2 ? a.y2 : b.y2;
    //  ���� ����
    if ((a.w + b.w) >= (fMaxX - fMinX))
    {
        //  ���� ����
        if ((a.h + b.h) >= (fMaxY - fMinY))
        {
            // ������
            float x, y, x2, y2;
            CRect Intersect;
            x = a.x1 > b.x1 ? a.x1 : b.y1;
            y = a.y1 > b.y1 ? a.y1 : b.y1;
            x2 = a.x2 < b.x2 ? a.x2 : b.x2;
            y2 = a.y2 < b.y2 ? a.y2 : b.y2;
            Intersect.Set(x, y, x2 - x, y2 - y);

            if (Intersect == a || Intersect == b)
            {
                return CollisionType::RECT_IN;
            }

            return CollisionType::RECT_OVERLAP;
        }
    }

    return CollisionType::RECT_OUT;
}

bool Collision::RectToInRect(CRect& a, CRect& b)
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