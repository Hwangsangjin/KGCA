#include "pch.h"
#include "Sample.h"
#include "Timer.h"
#include "Object.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Sample sample;
	sample.SetWindow(hInstance, L"Client", 800, 600);
	sample.Run();

	return 0;
}

HRESULT Sample::Init()
{
	object_ = std::make_unique<Object>();
	object_->CreateObject(device_.Get(), device_context_.Get(), L"Sample.hlsl", L"KGCA.bmp");

	int width = g_client_rect.right / 2;
	int height = g_client_rect.bottom / 2;
	viewport_[0].TopLeftX = 0.0f;
	viewport_[0].TopLeftY = 0.0f;
	viewport_[0].Width = (FLOAT)width;
	viewport_[0].Height = (FLOAT)height;
	viewport_[0].MinDepth = 0.0f;
	viewport_[0].MaxDepth = 1.0f;
	viewport_[1].TopLeftX = (FLOAT)width;
	viewport_[1].TopLeftY = 0.0f;
	viewport_[1].Width = (FLOAT)width;
	viewport_[1].Height = (FLOAT)height;
	viewport_[1].MinDepth = 0.0f;
	viewport_[1].MaxDepth = 1.0f;
	viewport_[2].TopLeftX = 0.0f;
	viewport_[2].TopLeftY = (FLOAT)height;
	viewport_[2].Width = (FLOAT)width;
	viewport_[2].Height = (FLOAT)height;
	viewport_[2].MinDepth = 0.0f;
	viewport_[2].MaxDepth = 1.0f;
	viewport_[3].TopLeftX = (FLOAT)width;
	viewport_[3].TopLeftY = (FLOAT)height;
	viewport_[3].Width = (FLOAT)width;
	viewport_[3].Height = (FLOAT)height;
	viewport_[3].MinDepth = 0.0f;
	viewport_[3].MaxDepth = 1.0f;

	return TRUE;
}

HRESULT Sample::Frame()
{
	return TRUE;
}

HRESULT Sample::Render()
{
	for (size_t i = 0; i < 4; i++)
	{
		device_context_->RSSetViewports(1, &viewport_[i]);

		object_->Render();
	}

	return TRUE;
}

HRESULT Sample::Release()
{
	return TRUE;
}