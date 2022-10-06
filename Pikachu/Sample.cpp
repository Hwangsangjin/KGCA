#include "pch.h"
#include "Sample.h"

GAME_RUN(Client, 800, 600)

HRESULT Sample::Init()
{
	_pTitle = new Title;
	_pInGame = new InGame;
	_pTitle->CreateScene(_pd3dDevice, _pImmediateContext);
	_pInGame->CreateScene(_pd3dDevice, _pImmediateContext);
	_pTitle->Init();
	_pInGame->Init();

	_pScene = _pTitle;

	return TRUE;
}

HRESULT Sample::Frame()
{
	if (_pScene->_isSelect)
	{
		_pScene = _pInGame;
	}

	_pScene->Frame();

	return TRUE;
}

HRESULT Sample::Render()
{
	_pScene->Render();

	std::wstring fpsText = L"Game FPS: ";
	fpsText += std::to_wstring((int)TIMER->GetFPS());
	SetWindowText(hWnd, fpsText.c_str());

	return TRUE;
}

HRESULT Sample::Release()
{
	_pTitle->Release();
	_pInGame->Release();

	SAFE_DELETE(_pTitle);
	SAFE_DELETE(_pInGame);

	_pScene = nullptr;

	return TRUE;
}
