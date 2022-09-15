#pragma once

enum COLLISION_TYPE
{
    RECT_OUT,
    RECT_IN,
    RECT_OVERLAP
};

class Collision
{
public:
    static COLLISION_TYPE RectToRect(Rect& a, Rect& b);
    static bool RectToInRect(Rect& a, Rect& b);
};

