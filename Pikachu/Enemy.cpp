#include "pch.h"
#include "Enemy.h"
#include "Input.h"
#include "Timer.h"

HRESULT Enemy::Frame()
{
    const float offsetX = 15.0f;
    Vector2 normal{ 1.0f, 1.0f };
    normal.Normalize();

    if (INPUT->GetKey(VK_UP))
    {
        _position.y -= normal.y * _speed * DELTA_TIME;
    }

    if (INPUT->GetKey(VK_LEFT))
    {
        _position.x -= normal.x * _speed * DELTA_TIME;
        if (_position.x + _rect.w - offsetX <= RESOLUTION_X / HALF)
        {
            _position.x = RESOLUTION_X / HALF - _rect.w + offsetX;
        }
    }

    if (INPUT->GetKey(VK_RIGHT))
    {
        _position.x += normal.x * _speed * DELTA_TIME;
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
