#pragma once

#include "Window.h"
#include "Graphics.h"
#include "Timer.h"

class GameCore : public Window
{
	float _gameTimer;

protected:
	Graphics* _pGraphics;
	Timer* _pTimer;

public:
	// 초기화
	HRESULT Init(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// 프레임
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 릴리즈
	HRESULT Release();
};

