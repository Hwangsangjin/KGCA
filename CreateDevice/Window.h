#pragma once

class Window
{
private:
	HINSTANCE _hInstance;	// 인스턴스 핸들
	HWND _hWnd;				// 윈도우 핸들
	RECT _rtWindow;			// 윈도우 영역
	RECT _rtClient;			// 클라이언트 영역

public:
	// 초기화
	HRESULT Init(const WindowInfo& info);
	// 프레임
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();

	// 생성자
	Window();

	// 윈도우 생성
	HRESULT InitWindow(const WindowInfo& info);
	// 윈도우 위치를 화면 중앙으로 이동
	void CenterWindow();

	// 메시지 프로시저
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

