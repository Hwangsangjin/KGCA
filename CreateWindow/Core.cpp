#include "pch.h"
#include "Core.h"

HRESULT Core::CInit()
{
	return Init();
}

HRESULT Core::CFrame()
{
	return Frame();
}

HRESULT Core::CPreRender()
{
	return TRUE;
}

HRESULT Core::CRender()
{
	return Render();
}

HRESULT Core::CPostRender()
{
	return TRUE;
}

HRESULT Core::CRelease()
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
	if (FAILED(CInit())) return E_FAIL;

	while (_isRunning)
	{
		if (Window::Run() == TRUE)
		{
			CFrame();
			CRender();
		}
		else
		{
			_isRunning = false;
		}
	}

	if (FAILED(CRelease())) return E_FAIL;

	return TRUE;
}
