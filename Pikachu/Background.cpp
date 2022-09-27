#include "pch.h"
#include "Background.h"
#include "Timer.h"

HRESULT Background::Frame()
{
    Vector2 normal{ 1.0f, 1.0f };
    normal.Normalize();

    _position.x -= normal.x * DELTA_TIME * _speed;
    _position.y -= normal.y * DELTA_TIME * _speed;
    if (_position.x <= init.x - 208.0f && _position.y <= init.y - 208.0f)
    {
        _position.x = init.x;
        _position.y = init.y;
    }

    SetPosition(_position);

    return TRUE;
}
