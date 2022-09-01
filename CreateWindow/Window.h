#pragma once

class Window
{
private:
	HINSTANCE _hInstance;	// 인스턴스 핸들
	HWND _hWnd;				// 윈도우 핸들
	RECT _rtWindow;			// 윈도우 영역
	RECT _rtClient;			// 클라이언트 영역

public:
	// 생성자
	Window();

	// 윈도우 생성
	HRESULT InitWindow(const IWND& iWnd);
	// 윈도우 위치를 화면 중앙으로 이동
	void CenterWindow();

	// 초기화
	HRESULT Init(const IWND& iWnd);
	// 프레임 계산
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 소멸 및 삭제
	HRESULT Release();

	// 메시지 프로시저
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

