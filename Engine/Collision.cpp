#include "pch.h"
#include "Collision.h"

COLLISION_TYPE Collision::RectToRect(MyRect& a, MyRect& b)
{
    float min_x;   float min_y;
    float max_x;   float max_y;

    min_x = a.x1 < b.x1 ? a.x1 : b.x1;
    min_y = a.y1 < b.y1 ? a.y1 : b.y1;
    max_x = a.x2 > b.x2 ? a.x2 : b.x2;
    max_y = a.y2 > b.y2 ? a.y2 : b.y2;

    //  가로 판정
    if ((a.w + b.w) >= (max_x - min_x))
    {
        //  세로 판정
        if ((a.h + b.h) >= (max_y - min_y))
        {
            // 교집합
            float x1, y1, x2, y2;
            x1 = a.x1 > b.x1 ? a.x1 : b.x1;
            y1 = a.y1 > b.y1 ? a.y1 : b.y1;
            x2 = a.x2 < b.x2 ? a.x2 : b.x2;
            y2 = a.y2 < b.y2 ? a.y2 : b.y2;

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

bool Collision::RectToPoint(MyRect& a, POINT& p)
{
    if (a.x1 <= p.x && a.x2 >= p.x)
    {
        if (a.y1 <= p.y && a.y2 >= p.y)
        {
            return true;
        }
    }

    return false;
}

bool Collision::CircleToCircle(MyCircle& a, MyCircle& b)
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

COLLISION_TYPE Collision::BoxToBox(MyBox& a, MyBox& b)
{
    float min_x;    float max_x;
    float min_y;    float max_y;
    float min_z;    float max_z;
    min_x = a.min.x < b.min.x ? a.min.x : b.min.x;
    min_y = a.min.y < b.min.y ? a.min.y : b.min.y;
    max_x = a.max.x > b.max.x ? a.max.x : b.max.x;
    max_y = a.max.y > b.max.y ? a.max.y : b.max.y;

    min_z = a.min.z < b.min.z ? a.min.z : b.min.z;
    max_z = a.max.z > b.max.z ? a.max.z : b.max.z;

    //  가로 판정
    if ((a.size.x + b.size.x) >= (max_x - min_x))
    {
        //  세로 판정
        if ((a.size.y + b.size.y) >= (max_y - min_y))
        {
            if ((a.size.z + b.size.z) >= (max_z - min_z))
            {
                // 교차한다. 교집합
                DxVector3 min, max;
                MyBox intersect;
                min.x = a.min.x > b.min.x ? a.min.x : b.min.x;
                min.y = a.min.y > b.min.y ? a.min.y : b.min.y;
                min.z = a.min.z > b.min.z ? a.min.z : b.min.z;
                                                                
                max.x = a.max.x < b.max.x ? a.max.x : b.max.x;
                max.y = a.max.y < b.max.y ? a.max.y : b.max.y;
                max.z = a.max.z < b.max.z ? a.max.z : b.max.z;

                intersect.Set(min, max - min);
                if (intersect == a || intersect == b)
                {
                    return COLLISION_TYPE::RECT_IN;
                }
                return COLLISION_TYPE::RECT_OVERLAP;
            }
        }
    }
    return COLLISION_TYPE::RECT_OUT;
}

bool Collision::BoxToInBox(MyBox& a, MyBox& b)
{
    if (a.min.x <= b.min.x &&
        a.min.y <= b.min.y &&
        a.min.z <= b.min.z)
    {
        if (a.max.x >= b.max.x &&
            a.max.y >= b.max.y &&
            a.max.z >= b.max.z)
        {
            return true;
        }
    }

    return false;
}

bool Collision::SphereToSphere(MySphere& a, MySphere& b)
{
    float sum = a.radius + b.radius;
    DxVector3 direction = a.center - b.center;
    float distance = direction.Length();
    if (distance <= sum)
    {
        return true;
    }

    return false;
}
