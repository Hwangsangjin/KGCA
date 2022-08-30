#include "pch.h"
#include "Collision.h"

CollisionType Collision::RectToRect(Rect& a, Rect& b)
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
                return CollisionType::In;
            }

            return CollisionType::Overlap;
        }
    }

    return CollisionType::Out;
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

CollisionType Collision::BoxToBox(Box& a, Box& b)
{
    float minX;    float maxX;
    float minY;    float maxY;
    float minZ;    float maxZ;

    minX = a.vMin.x < b.vMin.x ? a.vMin.x : b.vMin.x;
    minY = a.vMin.y < b.vMin.y ? a.vMin.y : b.vMin.y;
    maxX = a.vMax.x > b.vMax.x ? a.vMax.x : b.vMax.x;
    maxY = a.vMax.y > b.vMax.y ? a.vMax.y : b.vMax.y;
    minZ = a.vMin.z < b.vMin.z ? a.vMin.z : b.vMin.z;
    maxZ = a.vMax.z > b.vMax.z ? a.vMax.z : b.vMax.z;

    //  가로 판정
    if ((a.vSize.x + b.vSize.x) >= (maxX - minX))
    {
        //  세로 판정
        if ((a.vSize.y + b.vSize.y) >= (maxY - minY))
        {
            if ((a.vSize.z + b.vSize.z) >= (maxZ - minZ))
            {
                // 교집합
                Vector3 vMin, vMax;
                Box intersect;

                vMin.x = a.vMin.x > b.vMin.x ? a.vMin.x : b.vMin.x;
                vMin.y = a.vMin.y > b.vMin.y ? a.vMin.y : b.vMin.y;
                vMin.z = a.vMin.z > b.vMin.z ? a.vMin.z : b.vMin.z;

                vMax.x = a.vMax.x < b.vMax.x ? a.vMax.x : b.vMax.x;
                vMax.y = a.vMax.y < b.vMax.y ? a.vMax.y : b.vMax.y;
                vMax.z = a.vMax.z < b.vMax.z ? a.vMax.z : b.vMax.z;

                intersect.Set(vMin, vMax - vMin);
                if (intersect == a || intersect == b)
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
    if (a.vMin <= b.vMin)
    {
        if (a.vMax >= b.vMax)
        {
            return true;
        }
    }

    return false;
}

bool Collision::SphereToSphere(Sphere& a, Sphere& b)
{
    float sum = a.radius + b.radius;
    Vector3 direction = a.vCenter - b.vCenter;
    float distance = direction.Length();
    if (distance <= sum)
    {
        return true;
    }

    return false;
}
