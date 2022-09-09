#include "pch.h"
#include "Sample.h"

GAME_RUN(Client, 800, 600)

HRESULT Sample::Init()
{
    return TRUE;
}

HRESULT Sample::Frame()
{
	pos = INPUT->GetPos();

    return TRUE;
}

HRESULT Sample::Render()
{
	if (INPUT->GetKey(VK_LBUTTON) == KEY_STATE::HOLD)
	{
		_font.Draw(pos.x - 20, pos.y - 20, L"MOUSE", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
	{
		_font.Draw(rtClient.right / 2 - 20, rtClient.bottom / 2 - 20, L"SPACE", { 1, 1, 1, 1 });
	}
	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		_font.Draw(100, 100, L"W", { 1, 1, 1, 1 });
	}
	if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		_font.Draw(100, 130, L"A", { 1, 1, 1, 1 });
	}
	if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		_font.Draw(100, 160, L"S", { 1, 1, 1, 1 });
	}
	if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		_font.Draw(100, 190, L"D", { 1, 1, 1, 1 });
	}

    return TRUE;
}

HRESULT Sample::Release()
{
    return TRUE;
}
