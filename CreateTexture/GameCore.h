#pragma once

#include "Window.h"
#include "Graphics.h"

class GameCore : public Window
{
protected:
	Graphics* _pGraphics;

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

