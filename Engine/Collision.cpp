#include "pch.h"
#include "Collision.h"

COLLISION_TYPE Collision::RectToRect(MyRect& a, MyRect& b)
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
    float minX;    float maxX;
    float minY;    float maxY;
    float minZ;    float maxZ;
    minX = a.min.x < b.min.x ? a.min.x : b.min.x;
    minY = a.min.y < b.min.y ? a.min.y : b.min.y;
    maxX = a.max.x > b.max.x ? a.max.x : b.max.x;
    maxY = a.max.y > b.max.y ? a.max.y : b.max.y;

    minZ = a.min.z < b.min.z ? a.min.z : b.min.z;
    maxZ = a.max.z > b.max.z ? a.max.z : b.max.z;

    //  가로 판정
    if ((a.size.x + b.size.x) >= (maxX - minX))
    {
        //  세로 판정
        if ((a.size.y + b.size.y) >= (maxY - minY))
        {
            if ((a.size.z + b.size.z) >= (maxZ - minZ))
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
