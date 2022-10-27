#include "pch.h"
#include "Sample.h"
#include "Scene.h"

GAME_RUN(Client, 800, 600)

HRESULT Sample::Init()
{
	_pScene = new Scene;
	_pScene->CreateScene(_pd3dDevice, _pImmediateContext);
	_pScene->Init();

	_quadtree.CreateTree(_pScene->_pMap);

	return TRUE;
}

HRESULT Sample::Frame()
{
	_pScene->Frame();

	return TRUE;
}

HRESULT Sample::Render()
{
	if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
	{
		_pImmediateContext->RSSetState(DxState::_pDefaultRSWireFrame);
	}

	_pScene->Render();

	return TRUE;
}

HRESULT Sample::Release()
{
	_pScene->Release();

	SAFE_DELETE(_pScene);

	return TRUE;
}
