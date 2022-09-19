#include "pch.h"
#include "Background.h"
#include "Timer.h"

HRESULT Background::Frame()
{
    Vector2 normal{ 1.0f, 1.0f };
    normal.Normalize();

    _position.x -= normal.x * DELTA_TIME * _speed;
    _position.y -= normal.y * DELTA_TIME * _speed;

    if (_position.x <= -200.0f)
    {
        _position.x = 800.0f;
    }

    if (_position.y <= -200.0f)
    {
        _position.y = 600.0f;
    }

    SetNormalize();
    SetVertexBuffer();

    return TRUE;
}
