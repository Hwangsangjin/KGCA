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
	// �ʱ�ȭ
	HRESULT Init(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// ������
	HRESULT Frame();
	// ����
	HRESULT Render();
	// ������
	HRESULT Release();
};

