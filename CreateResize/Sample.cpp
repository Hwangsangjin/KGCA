#include "Sample.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Sample sample;
	sample.SetWindow(hInstance, L"Client", 800, 600);
	sample.Run();

	return 0;
}

HRESULT Sample::Init()
{
    if (FAILED(CreateDevice()))
    {
        return E_FAIL;
    }

    if (FAILED(CreateFactory()))
    {
        return E_FAIL;
    }

    if (FAILED(CreateSwapChain()))
    {
        return E_FAIL;
    }

    if (FAILED(SetRenderTargetView()))
    {
        return E_FAIL;
    }

    if (FAILED(SetViewport()))
    {
        return E_FAIL;
    }

	return TRUE;
}

HRESULT Sample::Frame()
{
	return TRUE;
}

HRESULT Sample::Render()
{
	if (FAILED(PreRender()))
	{
		return E_FAIL;
	}

	if (FAILED(PostRender()))
	{
		return E_FAIL;

	}
	return TRUE;
}

HRESULT Sample::Release()
{
    if (FAILED(CleanupDevice()))
    {
        return E_FAIL;
    }

	return TRUE;
}
