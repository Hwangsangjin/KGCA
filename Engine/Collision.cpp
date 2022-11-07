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

bool Collision::RectToPoint(MyRect& a, POINT& p)
{
    if (a._x1 <= p.x && a._x2 >= p.x)
    {
        if (a._y1 <= p.y && a._y2 >= p.y)
        {
            return true;
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

COLLISION_TYPE Collision::BoxToBox(MyBox& a, MyBox& b)
{
    float minX;    float maxX;
    float minY;    float maxY;
    float minZ;    float maxZ;
    minX = a._min.x < b._min.x ? a._min.x : b._min.x;
    minY = a._min.y < b._min.y ? a._min.y : b._min.y;
    maxX = a._max.x > b._max.x ? a._max.x : b._max.x;
    maxY = a._max.y > b._max.y ? a._max.y : b._max.y;

    minZ = a._min.z < b._min.z ? a._min.z : b._min.z;
    maxZ = a._max.z > b._max.z ? a._max.z : b._max.z;

    //  가로 판정
    if ((a._size.x + b._size.x) >= (maxX - minX))
    {
        //  세로 판정
        if ((a._size.y + b._size.y) >= (maxY - minY))
        {
            if ((a._size.z + b._size.z) >= (maxZ - minZ))
            {
                // 교차한다. 교집합
                DxVector3 min, max;
                MyBox intersect;
                min.x = a._min.x > b._min.x ? a._min.x : b._min.x;
                min.y = a._min.y > b._min.y ? a._min.y : b._min.y;
                min.z = a._min.z > b._min.z ? a._min.z : b._min.z;
                                                                
                max.x = a._max.x < b._max.x ? a._max.x : b._max.x;
                max.y = a._max.y < b._max.y ? a._max.y : b._max.y;
                max.z = a._max.z < b._max.z ? a._max.z : b._max.z;

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
    if (a._min.x <= b._min.x &&
        a._min.y <= b._min.y &&
        a._min.z <= b._min.z)
    {
        if (a._max.x >= b._max.x &&
            a._max.y >= b._max.y &&
            a._max.z >= b._max.z)
        {
            return true;
        }
    }

    return false;
}

bool Collision::SphereToSphere(MySphere& a, MySphere& b)
{
    float sum = a._radius + b._radius;
    DxVector3 direction = a._center - b._center;
    float distance = direction.Length();
    if (distance <= sum)
    {
        return true;
    }

    return false;
}
