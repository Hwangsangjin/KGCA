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
	assert(SUCCEEDED(CoreInit()));

	while (is_Running_)
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
			is_Running_ = false;
		}
	}

	// �ھ� ������
	assert(SUCCEEDED(CoreRelease()));

	return TRUE;
}

// ���ҽ� ����
HRESULT Core::CreateResource()
{
	Text::GetInstance()->Init();
	Microsoft::WRL::ComPtr<IDXGISurface1> back_buffer;
	assert(SUCCEEDED(swap_chain_->GetBuffer(0, __uuidof(IDXGISurface1), (void**)back_buffer.GetAddressOf())));
	assert(SUCCEEDED(Text::GetInstance()->SetSurface(back_buffer.Get())));

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
	assert(SUCCEEDED(Device::Init()));

	assert(SUCCEEDED(Input::GetInstance()->Init()));
	assert(SUCCEEDED(Timer::GetInstance()->Init()));
	assert(SUCCEEDED(Text::GetInstance()->Init()));
	Microsoft::WRL::ComPtr<IDXGISurface1> back_buffer;
	assert(SUCCEEDED(swap_chain_->GetBuffer(0, __uuidof(IDXGISurface1), (void**)back_buffer.GetAddressOf())));
	assert(SUCCEEDED(Text::GetInstance()->SetSurface(back_buffer.Get())));

	assert(SUCCEEDED(Init()));

	return TRUE;
}

// �ھ� ������
HRESULT Core::CoreFrame()
{
	assert(SUCCEEDED(Input::GetInstance()->Frame()));
	assert(SUCCEEDED(Timer::GetInstance()->Frame()));
	Text::GetInstance()->SetText();
	assert(SUCCEEDED(Text::GetInstance()->Frame()));

	Frame();

	return TRUE;
}

HRESULT Core::CorePreRender()
{
	// �ĸ� ���� ����
	const float clear_color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
	device_context_->ClearRenderTargetView(render_target_view_.Get(), clear_color);

	return TRUE;
}

HRESULT Core::CoreRender()
{
	assert(SUCCEEDED(CorePreRender()));

	assert(SUCCEEDED(Text::GetInstance()->Render()));
	assert(SUCCEEDED(Render()));

	assert(SUCCEEDED(CorePostRender()));

	return TRUE;
}

HRESULT Core::CorePostRender()
{
	// �ø���
	assert(SUCCEEDED(swap_chain_->Present(0, 0)));

	return TRUE;
}

HRESULT Core::CoreRelease()
{
	assert(SUCCEEDED(Release()));
	assert(SUCCEEDED(Input::GetInstance()->Release()));
	assert(SUCCEEDED(Timer::GetInstance()->Release()));
	assert(SUCCEEDED(Text::GetInstance()->Release()));
	assert(SUCCEEDED(Device::Release()));

	return TRUE;
}
