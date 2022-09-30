#include "pch.h"
#include "Wave.h"
#include "Timer.h"

HRESULT Wave::Frame()
{
    _timer += DELTA_TIME;

    if (!_isFull)
    {
        _position.y -= 1.0f * _speed * DELTA_TIME;

        if (_timer >= 1.0f)
        {
            _isFull = true;
            _timer = 0.0f;
        }
    }
    else
    {
        _position.y += 1.0f * _speed * DELTA_TIME;

        if (_position.y - _rect.h >= RESOLUTION_Y)
        {
            _isFull = false;
            _timer = 0.0f;
        }
    }

    SetPosition(_position);

    return TRUE;
}
