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

	return TRUE;
}

HRESULT Sample::Frame()
{
	ClearDeviceContext(device_context_.Get());

	object_->Frame();

	return TRUE;
}

HRESULT Sample::Render()
{
	object_->Render();

	return TRUE;
}

HRESULT Sample::Release()
{
	object_->Release();

	return TRUE;
}