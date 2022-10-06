#include "pch.h"
#include "GameStartText.h"
#include "Timer.h"

float GameStartText::_x = 3.0f;
float GameStartText::_y = 3.0f;
float GameStartText::_timer = 0.0f;

HRESULT GameStartText::Frame()
{
    _timer += DELTA_TIME;

    if (!_isFull)
    {
        _x += _speed * DELTA_TIME;
        _y += _speed * DELTA_TIME;

        if (_timer >= 1.0f)
        {
            _isFull = true;
            _timer = 0.0f;
        }
    }

    SetScale(_x, _y);
    SetPosition(_position);

    return TRUE;
}
