#pragma once

#include "Window.h"
#include "Timer.h"
#include "Write.h"

class Core : public Window
{
private:
	HWND _hWnd;
	RECT _rtClient;

	Timer _timer;
	Write _write;
	IDXGISurface1* _pBackBuffer;

	// 실행 플래그
	bool _isRunning = true;

	// 코어 함수
	HRESULT CoreInit();
	HRESULT CoreFrame();
	HRESULT CorePreRender();
	HRESULT CoreRender();
	HRESULT CorePostRender();
	HRESULT CoreRelease();

public:
	Core() = default;
	virtual ~Core() = default;

	// 초기화
	virtual HRESULT Init() override;
	// 프레임 계산
	virtual HRESULT Frame() override;
	// 렌더
	virtual HRESULT Render() override;
	// 메모리 해제
	virtual HRESULT Release() override;
	// 실행
	virtual HRESULT Run() final;
};

