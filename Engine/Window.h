#pragma once

#include "Device.h"

class Window : public Device
{
protected:
	HWND _hWnd = nullptr;				// 윈도우 핸들
	RECT _rtWindow = { 0, 0, 0, 0 };	// 윈도우 영역
	RECT _rtClient = { 0, 0, 0, 0 };	// 클라이언트 영역

public:
	// 생성자, 소멸자
	Window();
	virtual ~Window() = default;

	// 초기화
	virtual HRESULT Init() override;
	// 프레임 계산
	virtual HRESULT Frame() override;
	// 렌더
	virtual HRESULT Render() override;
	// 메모리 해제
	virtual HRESULT Release() override;
	// 실행
	virtual HRESULT Run();

	// 윈도우 설정
	HRESULT SetWindow(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);

	// 윈도우 핸들
	void SetHandle(HWND hWnd);

	// 윈도우 위치를 화면 중앙으로 이동
	void CenterWindow();

	// 메시지 프로시저
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

