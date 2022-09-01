#pragma once

#include "Window.h"

class Application
{
private:
	Window _window;

public:
	// 초기화
	HRESULT Init(const IWND& iWnd);
	// 실시간 계산
	HRESULT Frame();
	// 실시간 렌더링
	HRESULT Render();
	// 소멸 및 삭제
	HRESULT Release();
};