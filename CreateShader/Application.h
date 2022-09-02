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
	// 초기화
	HRESULT Init(const IWND& iWnd);
	// 프레임
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();
};