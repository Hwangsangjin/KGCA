#pragma once

#include "Vector2.h"
#include <vector>
#include <queue>

enum CollisionType
{
    RECT_OUT = 0,
    RECT_IN,
    RECT_OVERLAP,
};

struct TRect
{
    float x1;
    float y1;
    float w;
    float h;
};

struct CRect : TRect
{
    float x2; // x+w
    float y2; // y+h
    float cx;
    float cy;
    bool operator == (CRect& dest)
    {
        if (fabs(x1 - dest.x1) < 0.001f)
        {
            if (fabs(y1 - dest.y1) < 0.001f)
            {
                if (fabs(w - dest.w) < 0.001f)
                {
                    if (fabs(h - dest.h) < 0.001f)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    CRect() {}
    CRect(float x, float y, float z, float w)
    {
        Set(x, y, z, w);
    }

    void  Set(float x, float y, float z, float w)
    {
        this->x1 = x;
        this->y1 = y;
        this->w = z;
        this->h = w;
        x2 = x + w;
        y2 = y + h;
        cx = (x + x2) / 2.0f;
        cy = (y + y2) / 2.0f;
    }
};

class Collision
{
public:
    static CollisionType RectToRect(CRect& a, CRect& b);
    static bool RectToInRect(CRect& a, CRect& b);
};