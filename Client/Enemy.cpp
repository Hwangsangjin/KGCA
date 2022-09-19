#include "pch.h"
#include "Enemy.h"
#include "Input.h"
#include "Timer.h"

HRESULT Enemy::Frame()
{
    Vector2 normal{ 1.0f, 1.0f };
    normal.Normalize();

    if (INPUT->GetKey(VK_UP))
    {
        _position.y -= normal.y * DELTA_TIME * _speed;
    }

    if (INPUT->GetKey(VK_LEFT))
    {
        _position.x -= normal.x * DELTA_TIME * _speed;
        if (_position.x <= RESOLUTION_X / HALF + 10)
        {
            _position.x = RESOLUTION_X / HALF + 10;
        }
    }

    if (INPUT->GetKey(VK_RIGHT))
    {
        _position.x += normal.x * DELTA_TIME * _speed;
        if (_position.x + 110 >= RESOLUTION_X)
        {
            _position.x = RESOLUTION_X - 110;
        }
    }

    if (INPUT->GetKey(VK_SPACE))
    {

    }

    SetNormalize();
    SetVertexBuffer();

	return TRUE;
}
