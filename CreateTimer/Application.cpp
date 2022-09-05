#include "pch.h"
#include "Application.h"

#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    Application app;
    if (FAILED(app.Init(hInstance, L"Client", 800, 600)))
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

HRESULT Application::Init(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height)
{
    if (FAILED(GameCore::Init(hInstance, title, width, height))) return E_FAIL;

    return TRUE;
}

HRESULT Application::Frame()
{
    if (FAILED(GameCore::Frame())) return E_FAIL;

    return TRUE;
}

HRESULT Application::Render()
{
    if (FAILED(GameCore::Render())) return E_FAIL;
    if (FAILED(Window::Render())) return E_FAIL;

    return TRUE;
}

HRESULT Application::Release()
{
    if (FAILED(GameCore::Release())) return E_FAIL;

    return TRUE;
}
