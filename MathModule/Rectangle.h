#pragma once

struct Rectangle
{
	Vector2 _vMin;
	Vector2 _vMax;

	Rectangle() = default;
	Rectangle(const Rectangle& rect);
};

struct RectBase
{
    float  x1;
    float  y1;
    float  w;
    float  h;
};

struct Rect : RectBase
{
    float  x2;//x+w
    float  y2;//y+h
    float  cx;
    float  cy;
    bool   operator == (Rect& dest)
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

    Rect() = default;
    Rect(float x, float y, float z, float w)
    {
        Set(x, y, z, w);
    }

    void Set(float x, float y, float z, float w)
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