#include "pch.h"
#include "Core.h"

HRESULT Core::CoreInit()
{
	return Init();
}

HRESULT Core::CoreFrame()
{
	return Frame();
}

HRESULT Core::CorePreRender()
{
	return TRUE;
}

HRESULT Core::CoreRender()
{
	return Render();
}

HRESULT Core::CorePostRender()
{
	return TRUE;
}

HRESULT Core::CoreRelease()
{
	return Release();
}

HRESULT Core::Init()
{
	return TRUE;
}

HRESULT Core::Frame()
{
	return TRUE;
}

HRESULT Core::Render()
{
	return TRUE;
}

HRESULT Core::Release()
{
	return TRUE;
}

HRESULT Core::Run()
{
	if (FAILED(CoreInit())) return E_FAIL;

	while (_isRunning)
	{
		if (Window::Run() == TRUE)
		{
			CoreFrame();
			CoreRender();
		}
		else
		{
			_isRunning = false;
		}
	}

	if (FAILED(CoreRelease())) return E_FAIL;

	return TRUE;
}
