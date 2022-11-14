#include "pch.h"
#include "Sample.h"
#include "Scene.h"
#include "Camera.h"

HRESULT Sample::Init()
{
	_pScene = new Scene;
	_pScene->CreateScene(_pd3dDevice, _pImmediateContext);
	_pScene->Init();

	return TRUE;
}

HRESULT Sample::Frame()
{
	_pScene->Frame();

	return TRUE;
}

HRESULT Sample::Render()
{
	if (INPUT->GetKey(VK_SHIFT) == KEY_STATE::HOLD)
	{
		_pImmediateContext->RSSetState(DxState::_pDefaultRSWireFrame);
	}

	_pScene->Render();

	return TRUE;
}

HRESULT Sample::Release()
{
	if (_pScene)
	{
		_pScene->Release();
		delete _pScene;
		_pScene = nullptr;
	}

	return TRUE;
}

HRESULT Sample::CreateDXResource()
{
	Core::CreateDXResource();

	if (_pScene)
	{
		_pScene->_pMainCamera->CreateProjection(1.0f, 1000.0f, PI_DIVISION_4, (float)gClient.right / (float)gClient.bottom);
	}

	return TRUE;
}
