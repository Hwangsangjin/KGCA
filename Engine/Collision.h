#pragma once

enum COLLISION_TYPE
{
    RECT_OUT,
    RECT_IN,
    RECT_OVERLAP
};

struct Rect
{
    float x1;
    float y1;
    float w;
    float h;
    float x2;
    float y2;
    float cx;
    float cy;

    bool operator==(Rect& dest)
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

    Rect() {}
    Rect(float x, float y, float w, float h)
    {
        Set(x, y, w, h);
    }

    void Set(float x, float y, float w, float h)
    {
        this->x1 = x;
        this->y1 = y;
        this->w = w;
        this->h = h;
        x2 = this->x1 + this->w;
        y2 = this->y1 + this->h;
        cx = (this->x1 + x2) / 2.0f;
        cy = (this->y1 + y2) / 2.0f;
    }
};

struct Circle
{
    float cx;
    float cy;
    float radius;

    Circle() {};
    Circle(float x, float y, float r)
    {
        Set(x, y, r);
    }

    void Set(float x, float y, float r)
    {
        cx = x;
        cy = y;
        radius = r;
    }
};

class Collision
{
public:
    static COLLISION_TYPE RectToRect(Rect& a, Rect& b);
    static bool RectToInRect(Rect& a, Rect& b);
    static bool CircleToCircle(Circle& a, Circle& b);
};

