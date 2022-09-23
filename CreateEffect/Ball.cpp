#include "pch.h"
#include "Ball.h"

HRESULT Ball::Frame()
{
    SetPosition(_position);

    return TRUE;
}
