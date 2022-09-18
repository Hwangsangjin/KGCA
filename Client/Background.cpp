#include "pch.h"
#include "Background.h"
#include "Timer.h"

HRESULT Background::Frame()
{
    _position.x -= 1.0f * DELTA_TIME * _speed;
    _position.y -= 1.0f * DELTA_TIME * _speed;

    if (_position.x <= -208.0f)
    {
        _position.x = 800.0f;
    }

    if (_position.y <= -208.0f)
    {
        _position.y = 600.0f;
    }

    SetUV();
    SetNormalize();
    SetVertexBuffer();

    return TRUE;
}
