#include "pch.h"
#include "Core.h"
#include "Input.h"
#include "Timer.h"
#include "Text.h"
#include "DxState.h"
#include "ShaderManager.h"
#include "TextureManager.h"

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

	while (is_Running_)
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
			is_Running_ = false;
		}
	}

	// 코어 릴리즈
	assert(SUCCEEDED(CoreRelease()));

	return TRUE;
}

// 리소스 생성
HRESULT Core::CreateResource()
{
	Text::GetInstance()->Init();
	Microsoft::WRL::ComPtr<IDXGISurface1> back_buffer;
	assert(SUCCEEDED(swap_chain_->GetBuffer(0, __uuidof(IDXGISurface1), (void**)back_buffer.GetAddressOf())));
	assert(SUCCEEDED(Text::GetInstance()->SetSurface(back_buffer.Get())));

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
	assert(SUCCEEDED(Device::Init()));
	assert(SUCCEEDED(DxState::SetState(device_.Get())));
	assert(SUCCEEDED(Input::GetInstance()->Init()));
	assert(SUCCEEDED(Timer::GetInstance()->Init()));
	assert(SUCCEEDED(Text::GetInstance()->Init()));
	Microsoft::WRL::ComPtr<IDXGISurface1> back_buffer;
	assert(SUCCEEDED(swap_chain_->GetBuffer(0, __uuidof(IDXGISurface1), (void**)back_buffer.GetAddressOf())));
	assert(SUCCEEDED(Text::GetInstance()->SetSurface(back_buffer.Get())));
	assert(SUCCEEDED(ShaderManager::GetInstance()->SetDevice(device_.Get(), device_context_.Get())));
	assert(SUCCEEDED(TextureManager::GetInstance()->SetDevice(device_.Get(), device_context_.Get())));
	assert(SUCCEEDED(Init()));

	return TRUE;
}

// 코어 프레임
HRESULT Core::CoreFrame()
{
	assert(SUCCEEDED(Input::GetInstance()->Frame()));
	assert(SUCCEEDED(Timer::GetInstance()->Frame()));
	Text::GetInstance()->SetText();
	assert(SUCCEEDED(Text::GetInstance()->Frame()));

	assert(SUCCEEDED(Frame()));

	return TRUE;
}

HRESULT Core::CorePreRender()
{
	// 그래픽스 파이프라인 바인딩
	device_context_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	device_context_->RSSetViewports(1, &viewport_);
	device_context_->RSSetState(DxState::default_solid_.Get());
	device_context_->PSSetSamplers(0, 1, DxState::default_mirror_.GetAddressOf());
	device_context_->OMSetBlendState(DxState::alpha_blend_.Get(), 0, -1);
	device_context_->OMSetRenderTargets(1, render_target_view_.GetAddressOf(), nullptr);
	device_context_->OMSetDepthStencilState(DxState::default_depth_stencil_.Get(), 0xff);

	// 후면 버퍼 삭제
	const float clear_color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
	device_context_->ClearRenderTargetView(render_target_view_.Get(), clear_color);

	return TRUE;
}

HRESULT Core::CoreRender()
{
	assert(SUCCEEDED(CorePreRender()));

	assert(SUCCEEDED(Render()));
	assert(SUCCEEDED(Text::GetInstance()->Render()));

	assert(SUCCEEDED(CorePostRender()));

	return TRUE;
}

HRESULT Core::CorePostRender()
{
	// 플리핑
	assert(SUCCEEDED(swap_chain_->Present(0, 0)));

	return TRUE;
}

HRESULT Core::CoreRelease()
{
	assert(SUCCEEDED(Release()));
	assert(SUCCEEDED(TextureManager::GetInstance()->Release()));
	assert(SUCCEEDED(ShaderManager::GetInstance()->Release()));
	assert(SUCCEEDED(Input::GetInstance()->Release()));
	assert(SUCCEEDED(Timer::GetInstance()->Release()));
	assert(SUCCEEDED(Text::GetInstance()->Release()));
	assert(SUCCEEDED(DxState::Release()));
	assert(SUCCEEDED(Device::Release()));

	return TRUE;
}
