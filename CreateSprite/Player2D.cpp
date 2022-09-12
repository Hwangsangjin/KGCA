#include "pch.h"
#include "Player2D.h"
#include "Input.h"
#include "Timer.h"

HRESULT Player2D::Frame()
{
    Vector2 pos = _pos;

    if (INPUT->GetKey('A'))
    {
        pos.x += -1.0f * DELTA_TIME * _speed;
        if (pos.x <= 0)
        {
            pos.x = 0;
        }
    }

    if (INPUT->GetKey('D'))
    {
        pos.x += 1.0f * DELTA_TIME * _speed;
        if (pos.x + PLAYER_WIDTH >= RESOLUTION_X / HALF)
        {
            pos.x = RESOLUTION_X / HALF - PLAYER_WIDTH;
        }
    }

    if (INPUT->GetKey(VK_SPACE))
    {
        pos.y += -1.0f * DELTA_TIME * _speed;
    }

    SetPosition(pos);

    return TRUE;
}
