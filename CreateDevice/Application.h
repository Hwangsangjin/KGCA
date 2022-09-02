#pragma once

#include "Window.h"

class Application : public Window
{
public:
	// 초기화
	HRESULT Init(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// 실시간 계산
	HRESULT Frame();
	// 실시간 렌더링
	HRESULT Render();
	// 소멸 및 삭제
	HRESULT Release();
};