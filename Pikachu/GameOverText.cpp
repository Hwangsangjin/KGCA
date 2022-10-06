#include "pch.h"
#include "GameOverText.h"
#include "Timer.h"

float GameOverText::_x = 10.0f;
float GameOverText::_y = 10.0f;
float GameOverText::_timer = 0.0f;

HRESULT GameOverText::Frame()
{
    _timer += DELTA_TIME;

    if (!_isFull)
    {
        _x -= _speed * DELTA_TIME;
        _y -= _speed * DELTA_TIME;

        if (_x <= 3.0f && _y <= 3.0f)
        {
            _isFull = true;
            _timer = 0.0f;
        }
    }

    SetScale(_x, _y);
    SetPosition(_position);

    return TRUE;
}
