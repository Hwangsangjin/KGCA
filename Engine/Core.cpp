#include "pch.h"
#include "Core.h"
#include "Timer.h"
#include "Input.h"
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
	assert(SUCCEEDED(CoreInit()));

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
	assert(SUCCEEDED(CoreRelease()));

	return TRUE;
}

// 리소스 생성
HRESULT Core::CreateResource()
{
	TEXT->Init();
	Microsoft::WRL::ComPtr<IDXGISurface1> pBackBuffer;
	assert(SUCCEEDED(_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)pBackBuffer.GetAddressOf())));
	assert(SUCCEEDED(TEXT->SetSurface(pBackBuffer.Get())));

	return TRUE;
}

// 리소스 삭제
HRESULT Core::DeleteResource()
{
	TEXT->DeleteResource();

	return TRUE;
}

// 코어 초기화
HRESULT Core::CoreInit()
{
	assert(SUCCEEDED(Device::Init()));

	assert(SUCCEEDED(TIMER->Init()));
	assert(SUCCEEDED(INPUT->Init()));
	assert(SUCCEEDED(TEXT->Init()));
	Microsoft::WRL::ComPtr<IDXGISurface1> pBackBuffer;
	assert(SUCCEEDED(_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)pBackBuffer.GetAddressOf())));
	assert(SUCCEEDED(Text::GetInstance()->SetSurface(pBackBuffer.Get())));

	assert(SUCCEEDED(Init()));

	return TRUE;
}

// 코어 프레임
HRESULT Core::CoreFrame()
{
	assert(SUCCEEDED(TIMER->Frame()));
	assert(SUCCEEDED(INPUT->Frame()));
	TEXT->SetText(TIMER->GetText());
	assert(SUCCEEDED(TEXT->Frame()));

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
	assert(SUCCEEDED(CorePreRender()));

	assert(SUCCEEDED(TEXT->Render()));
	assert(SUCCEEDED(Render()));

	assert(SUCCEEDED(CorePostRender()));

	return TRUE;
}

HRESULT Core::CorePostRender()
{
	// 플리핑
	assert(SUCCEEDED(_pSwapChain->Present(0, 0)));

	return TRUE;
}

HRESULT Core::CoreRelease()
{
	assert(SUCCEEDED(Release()));
	assert(SUCCEEDED(TIMER->Release()));
	assert(SUCCEEDED(INPUT->Release()));
	assert(SUCCEEDED(TEXT->Release()));
	assert(SUCCEEDED(Device::Release()));

	return TRUE;
}
