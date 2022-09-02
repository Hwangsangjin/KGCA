#pragma once

#include "Window.h"
#include "Graphics.h"

class Application
{
private:
	Application* _pApplication = nullptr;
	Window* _pWindow = nullptr;
	Graphics* _pGraphics = nullptr;

public:
	// �ʱ�ȭ
	HRESULT Init(const IWND& iWnd);
	// ������
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();
};