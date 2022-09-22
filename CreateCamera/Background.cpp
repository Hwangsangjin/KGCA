#include "pch.h"
#include "Background.h"
#include "Timer.h"

HRESULT Background::Frame()
{
    Vector2 normal{ RESOLUTION_X, RESOLUTION_Y };
    normal.Normalize();

    //_position -= normal * DELTA_TIME * _speed;
    //if (_position.x <= -400 && _position.y <= -300)
    //{
    //    _position.x = init.x;
    //    _position.y = init.y;
    //}

    SetPosition(_position, _cameraPosition);

    return TRUE;
}
