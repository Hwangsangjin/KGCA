#pragma once

#include "Window.h"
#include "Graphics.h"

class Application
{
private:
	Window _window;
	Graphics _graphics;

public:
	// 초기화
	HRESULT Init(const WindowInfo& info);
	// 프레임
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();
};