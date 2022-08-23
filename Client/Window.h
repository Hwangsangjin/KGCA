#pragma once

#include <windows.h>

class Window
{
public:
	HINSTANCE _hInstance;	// 인스턴스 핸들
	HWND _hWnd;				// 윈도우 핸들
	DWORD _dwWindowStyle;	// 윈도우 스타일
	RECT _rcWindowBounds;	// 윈도우 영역
	RECT _rcWindowClient;	// 클라이언트 영역
	UINT _iWindowWidth;		// 클라이언트 영역 가로 크기
	UINT _iWindowHeight;	// 클라이언트 영역 세로 크기

	// 생성자
	Window();
	// 소멸자
	virtual ~Window() {}

	// 윈도우 생성
	bool InitWindow(HINSTANCE hInstance, int nCmdShow, const TCHAR* strWindowTitle);
	// 윈도우 위치를 화면 중앙으로 이동
	void CenterWindow(HWND hwnd);
	// 초기화
	virtual bool Init();
	// 프레임 계산
	virtual bool Frame();
	// 렌더
	virtual bool Render();
	// 메모리 소멸 및 객체 해제
	virtual bool Release();
	// 실행
	virtual bool Run();
	// 윈도우 프로시저
	virtual LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
};

