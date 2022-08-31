#pragma once

#include "Window.h"
#include "Graphics.h"

class Application
{
private:
	Window _window;
	Graphics _graphics;

public:
	// �ʱ�ȭ
	HRESULT Init(const WindowInfo& info);
	// ������
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();
};