#pragma once

class Window
{
public:
	// 윈도우 정보
	WindowInfo _info;

	// 생성자
	Window();
	// 소멸자
	~Window() {}

	// 윈도우 생성
	HRESULT InitWindow(const WindowInfo& info);
	// 윈도우 위치를 화면 중앙으로 이동
	void CenterWindow(const WindowInfo& info);
	// 초기화
	HRESULT Init(const WindowInfo& info);
	// 프레임 계산
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 소멸 및 객체 해제
	HRESULT Release();
	// 윈도우 프로시저
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

