#include "pch.h"
#include "Window.h"

// 윈도우 프로시저
Window* gWindow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //assert(gWindow);
    return gWindow->MsgProc(hWnd, message, wParam, lParam);
}

// 메시지 프로시저
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
HRESULT Window::InitWindow(HINSTANCE hInstance, int nCmdShow, const WCHAR* title, UINT width, UINT height)
{
    // 윈도우 클래스를 등록한다.
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = _hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(176, 196, 222));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"Sample";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        return E_FAIL;
    }

    // 등록한 윈도우를 생성한다.
    _hInstance = hInstance;
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindowEx(WS_EX_TOPMOST, title, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
    if (FAILED(_hWnd))
    {
        return E_FAIL;
    }

    // 윈도우 영역과 클라이언트 영역을 얻는다.
    GetWindowRect(_hWnd, &_rtWindow);
    GetClientRect(_hWnd, &_rtClient);

    CenterWindow(_hWnd);
    UpdateWindow(_hWnd);

    ShowWindow(_hWnd, nCmdShow);
    CenterWindow(_hWnd);

    return TRUE;
}

// 윈도우 중앙으로 이동
void Window::CenterWindow(HWND hWnd)
{
    // 화면 스크린의 해상도(넓이와 높이)을 얻는다.
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // 윈도우 클라이언트 중앙과 화면 스크린 중앙을 맞춘다.
    int x = (width - (_rtWindow.right - _rtWindow.left)) / 2;
    int y = (height - (_rtWindow.bottom - _rtWindow.top)) / 2;

    // 윈도우를 화면 중앙으로 이동한다.
    MoveWindow(hWnd, x, y, _rtWindow.right - _rtWindow.left, _rtWindow.bottom - _rtWindow.top, true);
}

HRESULT Window::Init()
{
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

HRESULT Window::Run()
{
    if (FAILED(Init()))
    {
        return E_FAIL;
    }

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
            if (FAILED(Frame()) || FAILED(Render()))
            {
                break;
            }
        }
    }

    if (FAILED(Release()))
    {
        return E_FAIL;
    }

    return TRUE;
}
