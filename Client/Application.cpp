#include "Application.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Application app;
	if (!app.InitWindow(hInstance, nCmdShow, L"Client"))
	{
		return 0;
	}

	ShowCursor(TRUE);
	app.Run();

	return 1;
}

bool Application::Init()
{
	return true;
}

bool Application::Frame()
{
	return true;
}

bool Application::Render()
{
	return true;
}

bool Application::Release()
{
	return true;
}
