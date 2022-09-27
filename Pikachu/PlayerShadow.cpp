#include "pch.h"
#include "PlayerShadow.h"
#include "Input.h"
#include "Timer.h"

HRESULT PlayerShadow::Frame()
{
    SetPosition(_position);

    return TRUE;
}
