#include "pch.h"
#include "Application.h"

#define GAME_START  int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
#define GAME_WINDOW(s,x,y)  Application app; app.SetWindow(hInstance,L#s,x,y); app.Run(); return 1;
#define GAME_END    }
#define GAME_RUN(s,x,y) GAME_START GAME_WINDOW(s,x,y) GAME_END

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    Application app;
    if (FAILED(app.SetWindow(hInstance, L"Client", 800, 600)))
    {
        return E_FAIL;
    }

    app.Run();
}

HRESULT Application::Init()
{
    return TRUE;
}

HRESULT Application::Frame()
{
    return TRUE;
}

HRESULT Application::Render()
{
    return TRUE;
}

HRESULT Application::Release()
{
    return TRUE;
}
