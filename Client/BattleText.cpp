#include "pch.h"
#include "BattleText.h"
#include "Timer.h"

HRESULT BattleText::Frame()
{
    SetNormalize();
    SetVertexBuffer();

    return TRUE;
}
