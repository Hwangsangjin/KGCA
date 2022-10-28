#include "pch.h"
#include "Sample.h"
#include "Scene.h"
#include "Map.h"
#include "Camera.h"
#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#ifdef _DEBUG
void MemoryLeakCheck()
{
	HMODULE dxgidebugdll = GetModuleHandleW(L"dxgidebug.dll");
	decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast<decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgidebugdll, "DXGIGetDebugInterface"));

	IDXGIDebug* debug;

	GetDebugInterface(IID_PPV_ARGS(&debug));

	OutputDebugStringW(L"Starting Live Direct3D Object Dump:\r\n");
	debug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_DETAIL);
	OutputDebugStringW(L"Completed Live Direct3D Object Dump.\r\n");

	debug->Release();
}
#endif

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Sample sample;
	sample.SetWindow(hInstance, L"FBX Loader", RESOLUTION_X, RESOLUTION_Y);
	sample.Run();

#ifdef DEBUG
	MemoryLeakCheck();
#endif

	return 0;
}

HRESULT Sample::Init()
{
	_pScene = new Scene;
	_pScene->CreateScene(_pd3dDevice, _pImmediateContext);
	_pScene->Init();

	//// FBX
	//if (SUCCEEDED(_fbxLoader.Init()))
	//{
	//	_fbxLoader.Load("../../Resource/Ryan/Ryan.fbx");
	//}

	//for (size_t i = 0; i < _fbxLoader._pDrawObjects.size(); i++)
	//{
	//	Object* pObject = _fbxLoader._pDrawObjects[i];
	//	pObject->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/DefaultObject.hlsl", L"../../Resource/Ryan/Ryan_All.png");
	//}

	//_pMainCamera = new CameraDebug;
	//_pMainCamera->CreateView(MyVector3(50, 6, -50), MyVector3(0, 6, 0), MyVector3(0, 1, 0));
	//_pMainCamera->CreateProjection(1.0f, 1000.0f, PI * 0.25f,
	//	(float)rtClient.right / (float)rtClient.bottom);

	return TRUE;
}

HRESULT Sample::Frame()
{
	//_fbxLoader.Frame();
	_pScene->Frame();

	return TRUE;
}

HRESULT Sample::Render()
{
	//if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
	//{
	//	_pImmediateContext->RSSetState(DxState::_pDefaultRSWireFrame);
	//}

	//for (size_t i = 0; i < _fbxLoader._pDrawObjects.size(); i++)
	//{
	//	_fbxLoader._pDrawObjects[i]->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	//	_fbxLoader._pDrawObjects[i]->Render();
	//}

	//_pImmediateContext->RSSetState(DxState::_pDefaultRSSolid);

	if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
	{
		_pImmediateContext->RSSetState(DxState::_pDefaultRSWireFrame);
	}

	_pImmediateContext->OMSetDepthStencilState(DxState::_pDefaultDepthStencil, 0xff);
	_pScene->_pMap->SetMatrix(nullptr, &_pScene->_pMainCamera->_view, &_pScene->_pMainCamera->_projection);

	_pScene->Render();

	return TRUE;
}

HRESULT Sample::Release()
{
	//_fbxLoader.Release();

	if (_pScene)
	{
		_pScene->Release();
		delete _pScene;
		_pScene = nullptr;
	}

	return TRUE;
}
