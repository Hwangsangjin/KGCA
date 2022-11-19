#include "pch.h"
#include "Core.h"
#include "Timer.h"
#include "Input.h"
#include "Text.h"

// �ʱ�ȭ
HRESULT Core::Init()
{
	return TRUE;
}

// ������
HRESULT Core::Frame()
{
	return TRUE;
}

// ����
HRESULT Core::Render()
{
	return TRUE;
}

// ������
HRESULT Core::Release()
{
	return TRUE;
}

// ����
HRESULT Core::Run()
{
	// �ھ� �ʱ�ȭ
	assert(SUCCEEDED(CoreInit()));

	while (_isRun)
	{
		// ������ ����
		if (Window::Run() == TRUE)
		{
			// �ھ� ������, ����
			CoreFrame();
			CoreRender();
		}
		else
		{
			_isRun = false;
		}
	}

	// �ھ� ������
	assert(SUCCEEDED(CoreRelease()));

	return TRUE;
}

// ���ҽ� ����
HRESULT Core::CreateResource()
{
	TEXT->Init();
	Microsoft::WRL::ComPtr<IDXGISurface1> pBackBuffer;
	assert(SUCCEEDED(_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)pBackBuffer.GetAddressOf())));
	assert(SUCCEEDED(TEXT->SetSurface(pBackBuffer.Get())));

	return TRUE;
}

// ���ҽ� ����
HRESULT Core::DeleteResource()
{
	TEXT->DeleteResource();

	return TRUE;
}

// �ھ� �ʱ�ȭ
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

// �ھ� ������
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
	// �ĸ� ���� ����
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
	// �ø���
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
