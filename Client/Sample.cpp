#include "pch.h"
#include "Sample.h"

GAME_RUN(Client, 800, 600)

HRESULT Sample::Init()
{
	TEXTURE->Load(L"../../Resource/Ryan/Ryan.png");

	_player = new Player;
	_player->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Ryan/Ryan.png");
	_player->SetRectangle({ 0, 0, 200, 200 });
	_player->SetPosition({ 0, 0 });

	_objects.push_back(_player);


	return TRUE;
}

HRESULT Sample::Frame()
{
	_pos = INPUT->GetPos();

	for (auto& object : _objects)
	{
		object->Frame();
	}

	return TRUE;
}

HRESULT Sample::Render()
{
	std::wstring pos = L"(" + std::to_wstring(_pos.x) + L", " + std::to_wstring(_pos.y) + L")";

	if (INPUT->GetKey(VK_LBUTTON) == KEY_STATE::NONE)
	{
		_font.Draw(_pos.x, _pos.y - 20, pos, { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		_font.Draw(50, 240, L"W", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		_font.Draw(30, 260, L"A", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		_font.Draw(50, 260, L"S", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		_font.Draw(70, 260, L"D", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
	{
		_font.Draw(30, 340, L"SPACE", { 1, 1, 1, 1 });
	}

	for (auto& object : _objects)
	{
		object->Render();
	}

	return TRUE;
}

HRESULT Sample::Release()
{
	for (auto& object : _objects)
	{
		object->Release();
	}

	return TRUE;
}
