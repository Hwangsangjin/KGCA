#include "pch.h"
#include "Core.h"
#include "Input.h"
#include "Timer.h"
#include "Text.h"

// 초기화
HRESULT Core::Init()
{
	return TRUE;
}

// 프레임
HRESULT Core::Frame()
{
	return TRUE;
}

// 렌더
HRESULT Core::Render()
{
	return TRUE;
}

// 릴리즈
HRESULT Core::Release()
{
	return TRUE;
}

// 실행
HRESULT Core::Run()
{
	// 코어 초기화
	if (FAILED(CoreInit()))
	{
		return E_FAIL;
	}

	while (_isRun)
	{
		// 윈도우 실행
		if (Window::Run() == TRUE)
		{
			// 코어 프레임, 렌더
			CoreFrame();
			CoreRender();
		}
		else
		{
			_isRun = false;
		}
	}

	// 코어 릴리즈
	if (FAILED(CoreRelease()))
	{
		return E_FAIL;
	}

	return TRUE;
}

// 리소스 생성
HRESULT Core::CreateResource()
{
	Text::GetInstance()->Init();
	Microsoft::WRL::ComPtr<IDXGISurface1> pBackBuffer;

	if (FAILED(_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)pBackBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	if (FAILED(Text::GetInstance()->SetSurface(pBackBuffer.Get())))
	{
		return E_FAIL;
	}

	return TRUE;
}

// 리소스 삭제
HRESULT Core::DeleteResource()
{
	Text::GetInstance()->DeleteResource();

	return TRUE;
}

// 코어 초기화
HRESULT Core::CoreInit()
{
	if (FAILED(Device::Init()))
	{
		return E_FAIL;
	}

	Input::GetInstance()->Init();
	Timer::GetInstance()->Init();
	Text::GetInstance()->Init();
	Microsoft::WRL::ComPtr<IDXGISurface1> pBackBuffer;

	if (FAILED(_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)pBackBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	if (FAILED(Text::GetInstance()->SetSurface(pBackBuffer.Get())))
	{
		return E_FAIL;
	}

	if (FAILED(Init()))
	{
		return E_FAIL;
	}

	return TRUE;
}

// 코어 프레임
HRESULT Core::CoreFrame()
{
	Input::GetInstance()->Frame();
	Timer::GetInstance()->Frame();
	Text::GetInstance()->SetText(Timer::GetInstance()->GetText());
	Text::GetInstance()->Frame();

	Frame();

	return TRUE;
}

HRESULT Core::CorePreRender()
{
	// 후면 버퍼 삭제
	const float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView.Get(), ClearColor);

	return TRUE;
}

HRESULT Core::CoreRender()
{
	CorePreRender();

	Text::GetInstance()->Render();
	Render();

	CorePostRender();

	return TRUE;
}

HRESULT Core::CorePostRender()
{
	// 플리핑
	if (FAILED(_pSwapChain->Present(0, 0)))
	{
		return E_FAIL;
	}

	return TRUE;
}

HRESULT Core::CoreRelease()
{
	Release();
	Input::GetInstance()->Release();
	Timer::GetInstance()->Release();
	Text::GetInstance()->Release();
	Device::Release();

	return TRUE;
}
