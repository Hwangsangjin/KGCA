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
	// 실시간 계산
	HRESULT Frame();
	// 실시간 렌더링
	HRESULT Render();
	// 소멸 및 삭제
	HRESULT Release();
	// 실행
	HRESULT Run(const WindowInfo& info);
};

