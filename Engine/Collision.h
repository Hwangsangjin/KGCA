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
    DxVector3 _center;
    float _radius;

    MySphere() {};
    MySphere(DxVector3 center, float radius)
    {
        _center = center;
        _radius = radius;
    };
};

struct MyBox
{
    DxVector3 _min;
    DxVector3 _max;
    DxVector3 _center;
    DxVector3 _size;


    bool   operator == (MyBox& dest)
    {
        if (_min == dest._min)
        {
            if (_size == dest._size)
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
        _min = pos;
        _size = size;
        _max = _min + size;
        _center = (_min + _max) * 0.5f;
    }
};

struct CollisionAABB
{
    DxVector3 _min;
    DxVector3 _max;
};

struct CollisionOBB
{
    DxVector3 _center;
    DxVector3 _axis[3];
    float _distance[3];
};

struct CollisionBOX
{
    DxVector3 _center;
    DxVector3 _position[8];

    // AABB
    DxVector3 _min;
    DxVector3 _max;

    // OBB
    DxVector3 _axis[3];
    float _extent[3];
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

