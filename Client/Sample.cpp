#include "pch.h"
#include "Sample.h"

GAME_RUN(Client, 800, 600)

HRESULT Sample::Init()
{
	// 로드
	TEXTURE->Load(L"../../Resource/Pikachu/Image/Sheet.png");

	// 하늘
	for (size_t y = 0; y < 12; y++)
	{
		for (size_t x = 0; x < 25; x++)
		{
			_sky = new Tile;
			_sky->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
			_sky->SetRectangle({ 156, 2, 16, 16 });
			_sky->SetScale(4.0f, 4.0f);
			_sky->SetPosition({ rtClient.left - 0.0f + x * 32, rtClient.bottom - 600.0f + y * 32 });
			AddObject(_sky);
		}
	}

	// 구름
	_cloud = new Cloud;
	_cloud->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
	_cloud->SetRectangle({ 101, 90, 45, 20 });
	_cloud->SetScale(5.0f, 5.0f);
	_cloud->SetPosition({ rtClient.left + 200.0f, rtClient.bottom - 500.0f });
	AddObject(_cloud);

	// 산
	_mountain = new Tile;
	_mountain->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
	_mountain->SetRectangle({ 2, 200, 432, 64 });
	_mountain->SetScale(3.7f, 3.5f);
	_mountain->SetPosition({ rtClient.left - 0.0f, rtClient.bottom - 220.0f });
	AddObject(_mountain);

	// 그라운드
	for (size_t x = 0; x < 25; x++)
	{
		_ground = new Tile;
		_ground->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");

		_ground->SetRectangle({ 120, 2, 16, 16 });
		_ground->SetScale(4.0f, 4.0f);
		_ground->SetPosition({ rtClient.left - 0.0f + x * 32, rtClient.bottom - 110.0f });
		AddObject(_ground);
	}

	for (size_t x = 0; x < 25; x++)
	{
		_ground = new Tile;
		_ground->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");

		if (x == 0)
		{
			_ground->SetRectangle({ 84, 2, 16, 16 });
			_ground->SetScale(4.0f, 4.0f);
			_ground->SetPosition({ rtClient.left - 0.0f, rtClient.bottom - 80.0f });
			AddObject(_ground);
		}
		else if (x < 24)
		{
			_ground->SetRectangle({ 66, 2, 16, 16 });
			_ground->SetScale(4.0f, 4.0f);
			_ground->SetPosition({ rtClient.left - 0.0f + x * 32, rtClient.bottom - 80.0f });
			AddObject(_ground);
		}
		else
		{
			_ground->SetRectangle({ 102, 2, 16, 16 });
			_ground->SetScale(4.0f, 4.0f);
			_ground->SetPosition({ rtClient.left - 0.0f + x * 32, rtClient.bottom - 80.0f });
			AddObject(_ground);
		}
	}

	for (size_t y = 0; y < 15; y++)
	{
		for (size_t x = 0; x < 27; x++)
		{
			_ground = new Tile;
			_ground->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");

			_ground->SetRectangle({ 138, 2, 16, 16 });
			_ground->SetScale(4.0f, 4.0f);
			_ground->SetPosition({ rtClient.left - 0.0f + x * 30, rtClient.bottom - 48.0f + y * 30 });
			AddObject(_ground);
		}
	}

	// 네트
	for (size_t y = 0; y < 12; y++)
	{
		_net = new Tile;
		_net->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");

		if (y == 0)
		{
			_net->SetRectangle({ 23, 2, 6, 8 });
			_net->SetScale(4.0f, 4.0f);
			_net->SetPosition({ rtClient.right / 2.0f, rtClient.bottom - 240.0f });
			AddObject(_net);
		}
		else
		{
			_net->SetRectangle({ 13, 2, 6, 8 });
			_net->SetScale(4.0f, 4.0f);
			_net->SetPosition({ rtClient.right / 2.0f, rtClient.bottom - 240.0f + y * 16 });
			AddObject(_net);
		}
		
	}

	// 파도
	//for (size_t x = 0; x < 27; x++)
	//{
	//	_wave = new Wave;
	//	_wave->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");

	//	_wave->SetRectangle({ 70, 160, 16, 30 });
	//	_wave->SetScale(4.0f, 4.0f);
	//	_wave->SetPosition({ rtClient.left - 0.0f + x * 30, rtClient.bottom - 40.0f });
	//	AddObject(_wave);
	//}

	// 플레이어
	_player = new Player;
	_player->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
	_player->SetRectangle({ 2, 265, 65, 65 });
	_player->SetSpeed(300.0f);
	_player->SetScale(3.5f, 3.5f);
	_player->SetPosition({ rtClient.left - 0.0f, rtClient.bottom - 170.0f });
	AddObject(_player);

	// 적
	_enemy = new Enemy;
	_enemy->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
	_enemy->SetRectangle({ 2, 265, 65, 65 });
	_enemy->SetSpeed(300.0f);
	_enemy->SetScale(3.5f, 3.5f);
	_enemy->SetPosition({ rtClient.right - 130.0f, rtClient.bottom - 170.0f });
	AddObject(_enemy);

	// 공
	_ball = new Ball;
	_ball->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shader.hlsl", L"../../Resource/Pikachu/Image/Sheet.png");
	_ball->SetRectangle({ 88, 158, 40, 40 });
	_ball->SetSpeed(300.0f);
	_ball->SetScale(3.5f, 3.5f);
	_ball->SetPosition({ rtClient.left + 370.0f, rtClient.bottom - 400.0f });
	AddObject(_ball);

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
