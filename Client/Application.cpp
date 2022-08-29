#include "pch.h"
#include "Application.h"

WindowInfo gWindowInfo;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	gWindowInfo.hInstance = hInstance;
	gWindowInfo.nCmdShow = nCmdShow;
	gWindowInfo.title = L"Client";
	gWindowInfo.width = 800;
	gWindowInfo.height = 600;

	Application app;
	if (FAILED(app.Init(gWindowInfo)))
	{
		return 0;
	}

	ShowCursor(TRUE);
	app.Run(gWindowInfo);

	return 1;
}

HRESULT Application::Init(const WindowInfo& info)
{
	if (FAILED(_window.Init(info))) return E_FAIL;
	if (FAILED(_graphics.Init(info))) return E_FAIL;

	return TRUE;
}

HRESULT Application::Frame()
{
	return TRUE;
}

HRESULT Application::Render()
{
	//if (FAILED(_graphics.Render())) return E_FAIL;

	return TRUE;
}

HRESULT Application::Release()
{
	return TRUE;
}

HRESULT Application::Run(const WindowInfo& info)
{
	if (FAILED(Init(info)))
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
			Frame();
			Render();
		}
	}

	if (FAILED(Release())) return E_FAIL;

	return TRUE;
}
