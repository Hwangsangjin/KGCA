#include "pch.h"
#include "Player.h"
#include "Input.h"
#include "Timer.h"

HRESULT Player::Frame()
{
    Vector2 pos = _pos;

    if (INPUT->GetKey('W'))
    {
        pos.y -= 1.0f * DELTA_TIME * _speed;
    }

    if (INPUT->GetKey('A'))
    {
        pos.x -= 1.0f * DELTA_TIME * _speed;
        if (pos.x <= 0)
        {
            pos.x = 0;
        }
    }

    if (INPUT->GetKey('D'))
    {
        pos.x += 1.0f * DELTA_TIME * _speed;
        if (pos.x + 110 >= RESOLUTION_X / HALF)
        {
            pos.x = RESOLUTION_X / HALF - 110;
        }
    }

    if (INPUT->GetKey(VK_SPACE))
    {

    }

    SetPosition(pos);

    return TRUE;
}
