#include "pch.h"
#include "Ryan.h"
#include "Input.h"
#include "Timer.h"

HRESULT Ryan::Frame()
{
    Vector2 normal{ 1.0f, 1.0f };
    normal.Normalize();

    //// ╩С
    //if (INPUT->GetKey('W') == KEY_STATE::HOLD)
    //{
    //    _position.y -= normal.y * _speed * DELTA_TIME;
    //    if (_position.y - _rect.cy <= rtClient.top)
    //    {
    //        _position.y = _rect.cy;
    //    }
    //}

    //// го
    //if (INPUT->GetKey('S') == KEY_STATE::HOLD)
    //{
    //    _position.y += normal.y * _speed * DELTA_TIME;
    //    if (_position.y + _rect.cy >= rtClient.bottom)
    //    {
    //        _position.y = rtClient.bottom - _rect.cy;
    //    }
    //}

    //// аб
    //if (INPUT->GetKey('A') == KEY_STATE::HOLD)
    //{
    //    _position.x -= normal.x * _speed * DELTA_TIME;
    //    if (_position.x - _rect.cx <= 0)
    //    {
    //        _position.x = _rect.cx;
    //    }
    //}

    //// ©Л
    //if (INPUT->GetKey('D') == KEY_STATE::HOLD)
    //{
    //    _position.x += normal.x * _speed * DELTA_TIME;
    //    if (_position.x + _rect.cx >= rtClient.right)
    //    {
    //        _position.x = rtClient.right - _rect.cx;
    //    }
    //}

    SetPosition(_position);

    return TRUE;
}
