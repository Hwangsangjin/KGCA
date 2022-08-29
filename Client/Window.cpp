#include "pch.h"
#include "Window.h"

// ���� ������ ���ν���
Window* gWindow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(gWindow);
    return gWindow->MsgProc(hWnd, message, wParam, lParam);
}

// ������ ���ν���
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

    // �ü���� ����� �����츦 �����Ѵ�.
    _info.hWnd = CreateWindowEx(WS_EX_TOPMOST, info.title, info.title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, info.hInstance, NULL);
    if (FAILED(_info.hWnd))
    {
        return E_FAIL;
    }

    ShowWindow(_info.hWnd, _info.nCmdShow);
    UpdateWindow(_info.hWnd);

    return TRUE;
}

// ������ �߾����� �̵�
void Window::CenterWindow(const WindowInfo& info)
{
    // ȭ�� ��ũ���� �ػ�(���̿� ����)�� ��´�.
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
    int x = (width - (info.bound.right - info.bound.left)) / 2;
    int y = (height - (info.bound.bottom - info.bound.top)) / 2;

    // �����츦 ȭ�� �߾����� �̵��Ѵ�.
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
