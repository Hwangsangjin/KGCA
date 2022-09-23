#include "pch.h"
#include "Cloud.h"
#include "Timer.h"

float Cloud::_x = 2.0f;
float Cloud::_y = 2.0f;
float Cloud::_timer = 0.0f;

HRESULT Cloud::Frame()
{
    _timer += DELTA_TIME * _speed / HALF;

    if (!_isFull)
    {
        _x += DELTA_TIME * 1.0f;
        _y += DELTA_TIME * 1.0f;

        if (_timer >= 2.0f)
        {
            _isFull = true;
            _timer = 0.0f;
        }
    }
    else if (_isFull)
    {
        _x -= DELTA_TIME * 0.1f;
        _y -= DELTA_TIME * 0.1f;

        if (_x <= 2.0f && _y <= 2.0f)
        {
            _isFull = false;
            _timer = 0.0f;
        }
    }

    _position.x += 1.0f * DELTA_TIME * _speed;
    if (_position.x - _rect.w >= RESOLUTION_X)
    {
        _position.x = 0.0f;
    }

    SetScale(_x, _y);
    SetPosition(_position);

    return TRUE;
}
