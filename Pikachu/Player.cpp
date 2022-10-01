#include "pch.h"
#include "Player.h"
#include "Input.h"
#include "Timer.h"

HRESULT Player::Frame()
{
    Vector2 normal{ 1.0f, 1.0f };
    normal.Normalize();

    if (INPUT->GetKey('W'))
    {
        _position.y -= normal.y * _speed * DELTA_TIME;
    }

    if (INPUT->GetKey('A'))
    {
        _position.x -= normal.x * _speed * DELTA_TIME;
        if (_position.x - _rect.w <= 0)
        {
            _position.x = _rect.w;
        }
    }

    if (INPUT->GetKey('D'))
    {
        _position.x += normal.x * _speed * DELTA_TIME;
        if (_position.x + _rect.w >= RESOLUTION_X / HALF)
        {
            _position.x = RESOLUTION_X / HALF - _rect.w;
        }
    }

    if (INPUT->GetKey(VK_SPACE))
    {

    }

    SetRect(_rect);
    SetPosition(_position);

    return TRUE;
}
