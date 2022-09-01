#pragma once

class Window
{
private:
	RECT _rtWindow;			// 윈도우 영역
	RECT _rtClient;			// 클라이언트 영역

public:
	// 초기화
	HRESULT Init(const IWND& iWnd);
	// 프레임
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();

	// 윈도우 생성
	HRESULT InitWindow(const IWND& iWnd);
	// 윈도우 위치를 화면 중앙으로 이동
	void CenterWindow();

	// 윈도우 핸들
	 HWND GetHWND();

	// 윈도우 프로시저
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

