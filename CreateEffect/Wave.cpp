#include "pch.h"
#include "Wave.h"
#include "Timer.h"

HRESULT Wave::Frame()
{
    Vector2 normal{ RESOLUTION_X, RESOLUTION_Y };
    normal.Normalize();

    _timer += DELTA_TIME * _speed;

    if (!_isFull)
    {
        _position.y -= normal.x * DELTA_TIME * _speed;

        if (_timer >= 50.0f)
        {
            _isFull = true;
            _timer = 0.0f;
        }
    }
    else
    {
        _position.y += normal.x * DELTA_TIME * _speed;

        if (_position.y - _rect.h >= RESOLUTION_Y)
        {
            _isFull = false;
            _timer = 0.0f;
        }
    }

    SetPosition(_position);

    return TRUE;
}
