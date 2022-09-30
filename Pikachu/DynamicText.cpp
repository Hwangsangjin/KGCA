#include "pch.h"
#include "DynamicText.h"
#include "Timer.h"

HRESULT DynamicText::Frame()
{
    _position.x -= 1.0f * _speed * DELTA_TIME;
    if (_position.x <= 530.f)
    {
        _position.x = 530.0f;
    }

    SetPosition(_position);

    return TRUE;
}
