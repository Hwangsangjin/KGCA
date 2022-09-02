#pragma once

#include "Graphics.h"

class Window
{
private:
	HWND _hWnd;		// 윈도우 핸들
	RECT _rtWindow;	// 윈도우 영역
	RECT _rtClient;	// 클라이언트 영역

protected:
	Graphics _graphics;

public:
	// 생성자
	Window();
	// 소멸자
	virtual ~Window();

	// 초기화
	virtual HRESULT Init(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT Render();
	// 메모리 소멸 및 삭제
	virtual HRESULT Release();

	// 윈도우 생성
	HRESULT InitWindow(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// 윈도우 위치를 화면 중앙으로 이동
	void CenterWindow();

	// 윈도우 핸들
	const HWND GetHWND() const;

	// 윈도우 프로시저
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

