#include "pch.h"
#include "Player.h"
#include "Input.h"
#include "Timer.h"

HRESULT Player::Frame()
{
    if (INPUT->GetKey('W'))
    {
        _position.y -= 1.0f * DELTA_TIME * _speed;
    }

    if (INPUT->GetKey('A'))
    {
        _position.x -= 1.0f * DELTA_TIME * _speed;
        if (_position.x <= 0)
        {
            _position.x = 0;
        }
    }

    if (INPUT->GetKey('D'))
    {
        _position.x += 1.0f * DELTA_TIME * _speed;
        if (_position.x + 110 >= RESOLUTION_X / HALF)
        {
            _position.x = RESOLUTION_X / HALF - 110;
        }
    }

    if (INPUT->GetKey(VK_SPACE))
    {

    }

    SetUV();
    SetNormalize();
    SetVertexBuffer();

    return TRUE;
}
