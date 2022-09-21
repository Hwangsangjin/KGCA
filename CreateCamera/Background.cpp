#include "pch.h"
#include "Background.h"
#include "Timer.h"

HRESULT Background::Frame()
{
    Vector2 normal{ RESOLUTION_X, RESOLUTION_Y };
    normal.Normalize();

    _position.x -= normal.x * DELTA_TIME * _speed;
    _position.y -= normal.y * DELTA_TIME * _speed;

    if (_position.x <= -_rect.w)
    {
        _position.x = RESOLUTION_X;
    }

    if (_position.y <= -_rect.h)
    {
        _position.y = RESOLUTION_Y;
    }

    SetPosition(_position, _cameraPosition);

    return TRUE;
}
