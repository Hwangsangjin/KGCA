#include "pch.h"
#include "Sample.h"

GAME_RUN(Client, 800, 600)

HRESULT Sample::Init()
{
	// 로드
	TEXTURE->Load(L"../../Resource/Pikachu/Image/Sheet.png");

	// 배경
	_map = new Object2D;
	_map->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
	_map->SetRectangle({ 0, 200, 435, 65 });
	_map->SetScale(3.7f, 3.5f);
	_map->SetPosition({ rtClient.left - 0.0f, rtClient.bottom - 220.0f });
	AddObject(_map);

	// 그라운드
	for (size_t x = 0; x < 50; x++)
	{
		_ground = new Object2D;
		_ground->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
		_ground->SetRectangle({ 70, 0, 16, 16 });
		_ground->SetScale(4.0f, 4.0f);
		_ground->SetPosition({ rtClient.left - 0.0f + x * 16, rtClient.bottom - 80.0f });
		AddObject(_ground);
	}

	// 네트
	for (size_t y = 0; y < 12; y++)
	{
		_net = new Object2D;
		_net->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
		_net->SetRectangle({ 13, 2, 6, 8 });
		_net->SetScale(4.0f, 4.0f);
		_net->SetPosition({ rtClient.right / 2.0f, rtClient.bottom - 60.0f - y * 16 });
		AddObject(_net);
	}

	// 플레이어
	_player = new Player2D;
	_player->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
	_player->SetRectangle({ 0, 265, 65, 65 });
	_player->SetSpeed(300.0f);
	_player->SetScale(3.5f, 3.5f);
	_player->SetPosition({ rtClient.left - 0.0f, rtClient.bottom - 170.0f });
	AddObject(_player);


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
	for (auto& object : _objects)
	{
		object->Render();
	}

	std::wstring pos = L"(" + std::to_wstring(_pos.x) + L", " + std::to_wstring(_pos.y) + L")";

	if (INPUT->GetKey(VK_LBUTTON) == KEY_STATE::NONE)
	{
		_font.Draw(_pos.x, _pos.y - 20, pos, { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		_font.Draw(50, 140, L"W", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		_font.Draw(30, 160, L"A", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		_font.Draw(50, 160, L"S", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		_font.Draw(70, 160, L"D", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
	{
		_font.Draw(30, 240, L"SPACE", { 1, 1, 1, 1 });
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

void Sample::AddObject(Object* object)
{
	_objects.push_back(object);
}
