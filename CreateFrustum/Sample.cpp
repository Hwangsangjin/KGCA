#include "pch.h"
#include "Sample.h"
#include "Scene.h"

GAME_RUN(Client, 800, 600)

HRESULT Sample::Init()
{
	_pScene = new Scene;
	_pScene->CreateScene(_pd3dDevice, _pImmediateContext);
	_pScene->Init();

	return TRUE;
}

HRESULT Sample::Frame()
{
	_point = INPUT->GetPosition();

	_pScene->Frame();

	return TRUE;
}

HRESULT Sample::Render()
{
	if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
	{
		_pImmediateContext->RSSetState(DxState::_pDefaultRSWireFrame);
	}

	_pScene->Render();

	std::wstring point = L"(" + std::to_wstring(_point.x) + L", " + std::to_wstring(_point.y) + L")";

	if (INPUT->GetKey(VK_LBUTTON) == KEY_STATE::NONE)
	{
		_font.Draw(_point.x, _point.y - 20, L"MOUSE" + point, { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey('Q') == KEY_STATE::HOLD)
	{
		_font.Draw(30, 140, L"Q", { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		_font.Draw(50, 140, L"W", { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	if (INPUT->GetKey('E') == KEY_STATE::HOLD)
	{
		_font.Draw(70, 140, L"E", { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		_font.Draw(30, 160, L"A", { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		_font.Draw(50, 160, L"S", { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		_font.Draw(70, 160, L"D", { 1, 1, 1, 1 });
	}

	if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
	{
		_font.Draw(30, 280, L"SPACE", { 1, 1, 1, 1 });
	}

	_font.Draw(650.0f, 0.0f, L"Top View", { 1.0f, 1.0f, 1.0f, 1.0f });
	_font.Draw(650.0f, 150.0f, L"Front View", { 1.0f, 1.0f, 1.0f, 1.0f });
	_font.Draw(650.0f, 300.0f, L"Side View", { 1.0f, 1.0f, 1.0f, 1.0f });
	_font.Draw(650.0f, 450.0f, L"User View", { 1.0f, 1.0f, 1.0f, 1.0f });

	_font.Render();

	return TRUE;
}

HRESULT Sample::Release()
{
	_pScene->Release();

	SAFE_DELETE(_pScene);

	return TRUE;
}
