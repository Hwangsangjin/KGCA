#include "pch.h"
#include "Window.h"

// ������ ���ν���
HWND g_handle;
RECT g_client_rect;
Window* g_window = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(g_window);

    return g_window->MsgProc(hWnd, message, wParam, lParam);
}

// �޽��� ���ν���
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

// ������
Window::Window()
{
    g_window = this;
}

// �ʱ�ȭ
HRESULT Window::Init()
{
    return TRUE;
}

// ������
HRESULT Window::Frame()
{
    return TRUE;
}

// ����
HRESULT Window::Render()
{
    return TRUE;
}

// ������
HRESULT Window::Release()
{
    return TRUE;
}

// ����
HRESULT Window::Run()
{
    // ������ �޽��� ó��
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
#ifdef CORE
        else
        {
            return TRUE;
        }
#endif
    }

    return E_FAIL;
}

// ������ ����
HRESULT Window::SetWindow(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height)
{
    // ������ Ŭ������ ���
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
    assert(RegisterClassEx(&wcex));

    // ����� �����츦 ����
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    HWND hWnd = CreateWindowW(title, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
    assert(SUCCEEDED(hWnd));

    // ����� ������ ����
    SetHandle(hWnd);
    ShowWindow(hWnd, SW_SHOW);
    ShowCursor(TRUE);
    CenterWindow();

    return TRUE;
}

// ������ �ڵ�
void Window::SetHandle(HWND hWnd)
{
    // ������ ������ Ŭ���̾�Ʈ ���� ����
    GetWindowRect(hWnd, &window_rect_);
    GetClientRect(hWnd, &client_rect_);
    hWnd_ = hWnd;
    g_handle = hWnd;
    g_client_rect = client_rect_;
}

// ������ �߾����� �̵�
void Window::CenterWindow()
{
    // ȭ�� ��ũ���� �ػ�(���̿� ����)
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� ����
    int x = (width - (window_rect_.right - window_rect_.left)) / 2;
    int y = (height - (window_rect_.bottom - window_rect_.top)) / 2;

    // �����츦 ȭ�� �߾����� �̵�
    MoveWindow(hWnd_, x, y, window_rect_.right - window_rect_.left, window_rect_.bottom - window_rect_.top, true);
}
