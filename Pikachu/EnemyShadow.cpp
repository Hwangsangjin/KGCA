#include "pch.h"
#include "EnemyShadow.h"

HRESULT EnemyShadow::Frame()
{
    SetPosition(_position);

    return TRUE;
}
