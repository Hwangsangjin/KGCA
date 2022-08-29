#include "pch.h"
#include "Window.h"

// 메인 윈도우 프로시저
Window* gWindow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(gWindow);
    return gWindow->MsgProc(hWnd, message, wParam, lParam);
}

// 윈도우 프로시저
LRESULT Window::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// 생성자
Window::Window()
{
    gWindow = this;
}

// 윈도우 초기화
HRESULT Window::InitWindow(const WindowInfo& info)
{
    // 윈도우 클래스를 등록한다.
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = info.hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(176, 196, 222));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = info.title;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        return E_FAIL;
    }

    _info.hInstance = info.hInstance;
    _info.nCmdShow = info.nCmdShow;
    RECT rect = { 0, 0, 640, 480 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    // 운영체제에 등록한 윈도우를 생성한다.
    _info.hWnd = CreateWindowEx(WS_EX_TOPMOST, info.title, info.title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, info.hInstance, NULL);
    if (FAILED(_info.hWnd))
    {
        return E_FAIL;
    }

    ShowWindow(_info.hWnd, _info.nCmdShow);
    UpdateWindow(_info.hWnd);

    return TRUE;
}

// 윈도우 중앙으로 이동
void Window::CenterWindow(const WindowInfo& info)
{
    // 화면 스크린의 해상도(넓이와 높이)을 얻는다.
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // 윈도우 클라이언트 중앙과 화면 스크린 중앙을 맞춘다.
    int x = (width - (info.bound.right - info.bound.left)) / 2;
    int y = (height - (info.bound.bottom - info.bound.top)) / 2;

    // 윈도우를 화면 중앙으로 이동한다.
    MoveWindow(info.hWnd, x, y, info.bound.right - info.bound.left, info.bound.bottom - info.bound.top, true);
}

HRESULT Window::Init(const WindowInfo& info)
{
    if (FAILED(InitWindow(info))) return E_FAIL;

    return TRUE;
}

HRESULT Window::Frame()
{
    return TRUE;
}

HRESULT Window::Render()
{
    return TRUE;
}

HRESULT Window::Release()
{
    return TRUE;
}
