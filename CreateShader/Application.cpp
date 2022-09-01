#include "pch.h"
#include "Application.h"

IWND iWnd;
HWND hWnd;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    iWnd.hInstance = hInstance;
    iWnd.nCmdShow = nCmdShow;
    iWnd.title = L"Client";
    iWnd.width = 800;
    iWnd.height = 600;

    Application app;
    if (FAILED(app.Init(iWnd)))
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
            if (FAILED(app.Frame()) || FAILED(app.Render()))
            {
                break;
            }
        }
    }

    if (FAILED(app.Release()))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Application::Init(const IWND& iWnd)
{
    if (FAILED(_window.Init(iWnd)))
    {
        return E_FAIL;
    }

    if (FAILED(_graphics.Init(iWnd)))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Application::Frame()
{
    return TRUE;
}

HRESULT Application::Render()
{
    if (FAILED(_graphics.Render()))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Application::Release()
{
    return TRUE;
}
