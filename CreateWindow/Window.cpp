#include "pch.h"
#include "Window.h"

// ������ ���ν���
Window* gWindow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //assert(gWindow);
    return gWindow->MsgProc(hWnd, message, wParam, lParam);
}

// �޽��� ���ν���
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

// ������
Window::Window()
{
    gWindow = this;
}

// ������ �ʱ�ȭ
HRESULT Window::InitWindow(HINSTANCE hInstance, int nCmdShow, const WCHAR* title, UINT width, UINT height)
{
    // ������ Ŭ������ ����Ѵ�.
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

    // ����� �����츦 �����Ѵ�.
    _hInstance = hInstance;
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindowEx(WS_EX_TOPMOST, title, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
    if (FAILED(_hWnd))
    {
        return E_FAIL;
    }

    // ������ ������ Ŭ���̾�Ʈ ������ ��´�.
    GetWindowRect(_hWnd, &_rtWindow);
    GetClientRect(_hWnd, &_rtClient);

    CenterWindow(_hWnd);
    UpdateWindow(_hWnd);

    ShowWindow(_hWnd, nCmdShow);
    CenterWindow(_hWnd);

    return TRUE;
}

// ������ �߾����� �̵�
void Window::CenterWindow(HWND hWnd)
{
    // ȭ�� ��ũ���� �ػ�(���̿� ����)�� ��´�.
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
    int x = (width - (_rtWindow.right - _rtWindow.left)) / 2;
    int y = (height - (_rtWindow.bottom - _rtWindow.top)) / 2;

    // �����츦 ȭ�� �߾����� �̵��Ѵ�.
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
            if (!Frame() || !Render())
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
