#pragma once

class Window
{
public:
	HINSTANCE _hInstance;	// 인스턴스 핸들
	HWND _hWnd;				// 윈도우 핸들
	RECT _rtWindow;			// 윈도우 영역
	RECT _rtClient;			// 클라이언트 영역

	// 생성자
	Window();
	// 소멸자
	virtual ~Window() {}

	// 윈도우 생성
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, const WCHAR* title, UINT width, UINT height);
	// 윈도우 위치를 화면 중앙으로 이동
	void CenterWindow(HWND hWnd);
	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT Render();
	// 메모리 소멸 및 삭제
	virtual HRESULT Release();
	// 메시지 프로시저
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	// 실행
	HRESULT Run();
};

