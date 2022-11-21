#pragma once

enum COLLISION_TYPE
{
    RECT_OUT,
    RECT_IN,
    RECT_OVERLAP
};

struct MyRect
{
    float x1;
    float y1;
    float w;
    float h;
    float x2;
    float y2;
    float cx;
    float cy;

    bool operator==(MyRect& dest)
    {
        if (fabs(x1 - dest.x1) < FLT_EPSILON)
        {
            if (fabs(y1 - dest.y1) < FLT_EPSILON)
            {
                if (fabs(w - dest.w) < FLT_EPSILON)
                {
                    if (fabs(h - dest.h) < FLT_EPSILON)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    MyRect() = default;
    MyRect(float x, float y, float w, float h)
    {
        Set(x, y, w, h);
    }

    void Set(float x, float y, float w, float h)
    {
        x1 = x;
        y1 = y;
        this->w = w;
        this->h = h;
        x2 = x1 + w;
        y2 = y1 + h;
        cx = (x1 + x2) / 2.0f;
        cy = (y1 + y2) / 2.0f;
    }
};

struct MyCircle
{
    float cx;
    float cy;
    float radius;

    MyCircle() = default;
    MyCircle(float x, float y, float radius)
    {
        Set(x, y, radius);
    }

    void Set(float x, float y, float radius)
    {
        cx = x;
        cy = y;
        this->radius = radius;
    }
};

struct MySphere
{
    DxVector3 center;
    float radius;

    MySphere() = default;
    MySphere(DxVector3 center, float radius)
    {
        this->center = center;
        this->radius = radius;
    };
};

struct MyBox
{
    DxVector3 min;
    DxVector3 max;
    DxVector3 center;
    DxVector3 size;

    bool operator==(MyBox& dest)
    {
        if (min == dest.min)
        {
            if (size == dest.size)
            {
                return true;
            }
        }

        return false;
    }

    MyBox() {}
    MyBox(DxVector3 pos, DxVector3 size)
    {
        Set(pos, size);
    }
    void  Set(DxVector3 pos, DxVector3 size)
    {
        min = pos;
        this->size = size;
        max = min + size;
        center = (min + max) * 0.5f;
    }
};

struct CollisionAABB
{
    DxVector3 min;
    DxVector3 max;
};

struct CollisionOBB
{
    DxVector3 center;
    DxVector3 axis[3];
    float distance[3];
};

struct CollisionBOX
{
    DxVector3 center;
    DxVector3 position[8];

    // AABB
    DxVector3 min;
    DxVector3 max;

    // OBB
    DxVector3 axis[3];
    float extent[3];
};

class Collision
{
public:
    static COLLISION_TYPE RectToRect(MyRect& a, MyRect& b);
    static bool RectToInRect(MyRect& a, MyRect& b);
    static bool RectToPoint(MyRect& a, POINT& p);
    static bool CircleToCircle(MyCircle& a, MyCircle& b);
    static COLLISION_TYPE BoxToBox(MyBox& a, MyBox& b);
    static bool BoxToInBox(MyBox& a, MyBox& b);
    static bool SphereToSphere(MySphere& a, MySphere& b);
};

