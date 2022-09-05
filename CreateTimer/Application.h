#pragma once

#include "GameCore.h"

class Application : public GameCore
{
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