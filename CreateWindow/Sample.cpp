#include "pch.h"
#include "Sample.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Sample sample;
	if (FAILED(sample.InitWindow(hInstance, nCmdShow, L"Sample", 1024, 768)))
	{
		return 0;
	}

	ShowCursor(TRUE);
	sample.Run();

	return 1;
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
