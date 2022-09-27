#include "pch.h"
#include "Enemy.h"
#include "Input.h"
#include "Timer.h"

HRESULT Enemy::Frame()
{
    const float offsetX = 15.0f;

    Vector2 normal{ RESOLUTION_X, RESOLUTION_Y };
    normal.Normalize();

    if (INPUT->GetKey(VK_UP))
    {
        _position.y -= normal.y * DELTA_TIME * _speed;
    }

    if (INPUT->GetKey(VK_LEFT))
    {
        _position.x -= normal.x * DELTA_TIME * _speed;
        if (_position.x + _rect.w - offsetX <= RESOLUTION_X / HALF)
        {
            _position.x = RESOLUTION_X / HALF - _rect.w + offsetX;
        }
    }

    if (INPUT->GetKey(VK_RIGHT))
    {
        _position.x += normal.x * DELTA_TIME * _speed;
        if (_position.x - _rect.w >= RESOLUTION_X)
        {
            _position.x = RESOLUTION_X + _rect.w;
        }
    }

    if (INPUT->GetKey(VK_SPACE))
    {

    }

    SetPosition(_position);

	return TRUE;
}
