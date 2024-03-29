#pragma once

#include <Windows.h>
#include <assert.h>

class Window
{
protected:
	HWND _hWnd;		// 윈도우 핸들
	RECT _rtWindow;	// 윈도우 영역
	RECT _rtClient;	// 클라이언트 영역
	UINT _width;	// 클라이언트 영역 가로 크기
	UINT _height;	// 클라이언트 영역 세로 크기

public:
	Window();
	virtual ~Window() = default;

	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT Render();
	// 메모리 해제
	virtual HRESULT Release();
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

