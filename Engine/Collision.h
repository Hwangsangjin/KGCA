#pragma once

enum COLLISION_TYPE
{
    RECT_OUT,
    RECT_IN,
    RECT_OVERLAP
};

struct MyRect
{
    float _x1;
    float _y1;
    float _w;
    float _h;
    float _x2;
    float _y2;
    float _cx;
    float _cy;

    bool operator==(MyRect& dest)
    {
        if (fabs(_x1 - dest._x1) < FLT_EPSILON)
        {
            if (fabs(_y1 - dest._y1) < FLT_EPSILON)
            {
                if (fabs(_w - dest._w) < FLT_EPSILON)
                {
                    if (fabs(_h - dest._h) < FLT_EPSILON)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    MyRect() {}
    MyRect(float x, float y, float w, float h)
    {
        Set(x, y, w, h);
    }

    void Set(float x, float y, float w, float h)
    {
        _x1 = x;
        _y1 = y;
        _w = w;
        _h = h;
        _x2 = _x1 + _w;
        _y2 = _y1 + _h;
        _cx = (_x1 + _x2) / 2.0f;
        _cy = (_y1 + _y2) / 2.0f;
    }
};

struct MyCircle
{
    float _cx;
    float _cy;
    float _radius;

    MyCircle() {};
    MyCircle(float x, float y, float r)
    {
        Set(x, y, r);
    }

    void Set(float x, float y, float r)
    {
        _cx = x;
        _cy = y;
        _radius = r;
    }
};

struct MySphere
{
    MyVector3 _center;
    float _radius;

    MySphere() {};
    MySphere(MyVector3 center, float radius)
    {
        _center = center;
        _radius = radius;
    };
};

struct MyBox
{
    MyVector3 min;
    MyVector3 max;
    MyVector3 center;
    MyVector3 size;


    bool   operator == (MyBox& dest)
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
    MyBox(MyVector3 pos, MyVector3 size)
    {
        Set(pos, size);
    }
    void  Set(MyVector3 pos, MyVector3 size)
    {
        min = pos;
        this->size = size;
        max = min + size;
        center = (min + max) * 0.5f;
    }
};

struct CollisionAABB
{
    MyVector3 min;
    MyVector3 max;
};

struct CollisionOBB
{
    MyVector3 center;
    MyVector3 axis[3];
    float distance[3];
};

struct CollisionBOX
{
    MyVector3 _center;
    MyVector3 _position[8];

    // AABB
    MyVector3 _min;
    MyVector3 _max;

    // OBB
    MyVector3 _axis[3];
    float _extent[3];
};

class Collision
{
public:
    static COLLISION_TYPE RectToRect(MyRect& a, MyRect& b);
    static bool RectToInRect(MyRect& a, MyRect& b);
    static bool CircleToCircle(MyCircle& a, MyCircle& b);
};

