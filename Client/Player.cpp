#include "pch.h"
#include "Player.h"
#include "Input.h"
#include "Timer.h"

HRESULT Player::Frame()
{
    Vector2 position = _position;

    if (INPUT->GetKey('W'))
    {
        position.y -= 1.0f * DELTA_TIME * _speed;
    }

    if (INPUT->GetKey('A'))
    {
        position.x -= 1.0f * DELTA_TIME * _speed;
        if (position.x <= 0)
        {
            position.x = 0;
        }
    }

    if (INPUT->GetKey('D'))
    {
        position.x += 1.0f * DELTA_TIME * _speed;
        if (position.x + 110 >= RESOLUTION_X / HALF)
        {
            position.x = RESOLUTION_X / HALF - 110;
        }
    }

    if (INPUT->GetKey(VK_SPACE))
    {

    }

    SetPosition(position);

    return TRUE;
}
