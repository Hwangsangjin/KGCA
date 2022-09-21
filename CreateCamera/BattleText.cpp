#include "pch.h"
#include "BattleText.h"
#include "Timer.h"

float BattleText::_x = 0.0f;
float BattleText::_y = 0.0f;
float BattleText::_timer = 0.0f;

HRESULT BattleText::Frame()
{
    _timer += DELTA_TIME;

    if (!_isFull)
    {
        _x += DELTA_TIME * _speed;
        _y += DELTA_TIME * _speed;

        if (_timer >= 0.2f)
        {
            _isFull = true;
            _timer = 0.0f;
        }
    }
    else if (_isFull)
    {
        _x -= DELTA_TIME * _speed;
        _y -= DELTA_TIME * _speed;

        if (_x <= 1.0f && _y <= 1.0f)
        {
            _isFull = false;
            _timer = 0.0f;
        }
    }

    SetScale(_x, _y);
    SetPosition(_position, _cameraPosition);

    return TRUE;
}
