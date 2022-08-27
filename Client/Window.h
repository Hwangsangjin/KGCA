#pragma once

#include <windows.h>

class Window
{
public:
	HINSTANCE _hInstance;	// 인스턴스 핸들
	HWND _hWnd;				// 윈도우 핸들
	RECT bound;	// 윈도우 영역
	RECT _client;	// 클라이언트 영역
	UINT _width;		// 클라이언트 영역 가로 크기
	UINT _height;	// 클라이언트 영역 세로 크기

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
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

