#include "pch.h"
#include "Sample.h"

#define GAME_START  int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
#define GAME_WINDOW(s,x,y)  Sample sample; sample.SetWindow(hInstance,L#s,x,y); return sample.Run();
#define GAME_END    }
#define GAME_RUN(s,x,y) GAME_START GAME_WINDOW(s,x,y) GAME_END

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    Sample app;
    if (FAILED(app.SetWindow(hInstance, L"Client", 800, 600))) return E_FAIL;

    return app.Run();
}

HRESULT Sample::Init()
{
    return TRUE;
}

HRESULT Sample::Frame()
{
    return TRUE;
}

HRESULT Sample::Render()
{
    return TRUE;
}

HRESULT Sample::Release()
{
    return TRUE;
}
