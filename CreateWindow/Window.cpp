#include "pch.h"
#include "Window.h"

// ������ ���ν���
Window* gWindow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(gWindow);
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
HRESULT Window::InitWindow(const WindowInfo& info)
{
    // ������ Ŭ������ ����Ѵ�.
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = info.hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = info.title;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        return E_FAIL;
    }

    // ����� �����츦 �����Ѵ�.
    _hInstance = info.hInstance;
    RECT rect = { 0, 0, info.width, info.height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindowEx(WS_EX_TOPMOST, info.title, info.title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, _hInstance, NULL);
    if (FAILED(_hWnd))
    {
        return E_FAIL;
    }

    // ������ ������ Ŭ���̾�Ʈ ������ ��´�.
    GetWindowRect(_hWnd, &_rtWindow);
    GetClientRect(_hWnd, &_rtClient);
    ShowWindow(_hWnd, SW_SHOW);
    ShowCursor(TRUE);
    UpdateWindow(_hWnd);
    CenterWindow();

    return TRUE;
}

// ������ �߾����� �̵�
void Window::CenterWindow()
{
    // ȭ�� ��ũ���� �ػ�(���̿� ����)�� ��´�.
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
    int x = (width - (_rtWindow.right - _rtWindow.left)) / 2;
    int y = (height - (_rtWindow.bottom - _rtWindow.top)) / 2;

    // �����츦 ȭ�� �߾����� �̵��Ѵ�.
    MoveWindow(_hWnd, x, y, _rtWindow.right - _rtWindow.left, _rtWindow.bottom - _rtWindow.top, true);
}

HRESULT Window::Init(const WindowInfo& info)
{
    if (FAILED(InitWindow(info)))
    {
        return E_FAIL;
    }

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
