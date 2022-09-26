#include "pch.h"
#include "BallShadow.h"

HRESULT BallShadow::Frame()
{
    SetPosition(_position);

    return TRUE;
}
