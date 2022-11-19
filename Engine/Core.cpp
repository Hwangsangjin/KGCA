#include "pch.h"
#include "Core.h"
#include "Input.h"
#include "Timer.h"
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
	if (FAILED(CoreInit()))
	{
		return E_FAIL;
	}

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
	if (FAILED(CoreRelease()))
	{
		return E_FAIL;
	}

	return TRUE;
}

// ���ҽ� ����
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

// ���ҽ� ����
HRESULT Core::DeleteResource()
{
	Text::GetInstance()->DeleteResource();

	return TRUE;
}

// �ھ� �ʱ�ȭ
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

// �ھ� ������
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
	// �ĸ� ���� ����
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
	// �ø���
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
