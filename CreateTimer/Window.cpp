#include "Window.h"
#include <assert.h>

// 윈도우 프로시저
HWND gHandle;
RECT gClient;
Window* gWindow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(gWindow);
    return gWindow->MsgProc(hWnd, message, wParam, lParam);
}

// 메시지 프로시저
LRESULT Window::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZE:
        if (SIZE_MINIMIZED != wParam)
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            ResizeDevice(width, height);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// 생성자
Window::Window()
    : _hWnd(0)
    , _rtWindow{ 0, 0 }
    , _rtClient{ 0, 0 }
{
    gWindow = this;
}

// 초기화
HRESULT Window::Init()
{
    return TRUE;
}

// 프레임
HRESULT Window::Frame()
{
    return TRUE;
}

// 렌더
HRESULT Window::Render()
{
    return TRUE;
}

// 릴리즈
HRESULT Window::Release()
{
    return TRUE;
}

// 실행
HRESULT Window::Run()
{
    // 초기화
    if (FAILED(Init()))
    {
        return E_FAIL;
    }

    // 윈도우 메시지 처리
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 프레임, 렌더
            if (FAILED(Frame()) || FAILED(Render()))
            {
                break;
            }
        }
    }

    // 릴리즈
    if (FAILED(Release()))
    {
        return E_FAIL;
    }

    return TRUE;
}

// 윈도우 설정
HRESULT Window::SetWindow(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height)
{
    // 윈도우 클래스를 등록
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = title;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    if (!RegisterClassEx(&wcex)) return E_FAIL;

    // 등록한 윈도우를 생성
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    HWND hWnd = CreateWindowW(title, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
    if (FAILED(hWnd))
    {
        return E_FAIL;
    }

    // 등록한 윈도우 설정
    SetHandle(hWnd);
    ShowWindow(hWnd, SW_SHOW);
    ShowCursor(TRUE);
    CenterWindow();

    return TRUE;
}

// 윈도우 핸들
void Window::SetHandle(HWND hWnd)
{
    // 윈도우 영역과 클라이언트 영역 설정
    GetWindowRect(hWnd, &_rtWindow);
    GetClientRect(hWnd, &_rtClient);
    gClient = _rtClient;
    gHandle = hWnd;
    _hWnd = hWnd;
}

// 윈도우 중앙으로 이동
void Window::CenterWindow()
{
    // 화면 스크린의 해상도(넓이와 높이)
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // 윈도우 클라이언트 중앙과 화면 스크린 중앙을 설정
    int x = (width - (_rtWindow.right - _rtWindow.left)) / 2;
    int y = (height - (_rtWindow.bottom - _rtWindow.top)) / 2;

    // 윈도우를 화면 중앙으로 이동
    MoveWindow(_hWnd, x, y, _rtWindow.right - _rtWindow.left, _rtWindow.bottom - _rtWindow.top, true);
}
