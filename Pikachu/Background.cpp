#include "pch.h"
#include "Background.h"
#include "Timer.h"

HRESULT Background::Frame()
{
    Vector2 normal = _direction;
    normal.Normalize();

    _position += normal * _speed * DELTA_TIME;
    if (_position.x <= init.x - 208.0f && _position.y <= init.y - 208.0f)
    {
        _position.x = init.x;
        _position.y = init.y;
    }

    SetPosition(_position);

    return TRUE;
}
