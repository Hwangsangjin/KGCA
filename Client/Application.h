#pragma once

#include "Window.h"

class Application : public Window
{
public:
	// 초기화
	bool Init();
	// 실시간 계산
	bool Frame();
	// 실시간 렌더링
	bool Render();
	// 소멸 및 삭제
	bool Release();
};

