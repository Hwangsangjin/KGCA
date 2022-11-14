#include "pch.h"
#include "Scene.h"
#include "Input.h"
#include "DxRT.h"
#include "DxState.h"
#include "Camera.h"
#include "Map.h"
#include "Quadtree.h"
#include "Timer.h"
#include "FbxData.h"
#include "Actor.h"

HRESULT Scene::Init()
{
	// ¸ÞÀÎ Ä«¸Þ¶ó
	_pMainCamera = new CameraDebug;
	_pMainCamera->CreateView(DxVector3(0.0f, 5.0f, -20.0f), DxVector3(0.0f, 0.0f, 0.0f), DxVector3(0.0f, 1.0f, 0.0f));
	_pMainCamera->CreateProjection(1.0f, 10000.0f, PI_DIVISION_4, (float)gClient.right / (float)gClient.bottom);

	// ¸Ê
	_pMap = new Map;
	_pMap->LoadHeightMap(_pd3dDevice, _pImmediateContext, L"../../Resource/Map/HeightMap.bmp");
	_pMap->BuildMap(_pMap->_width, _pMap->_height);
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Tile/Tile.png");

	// ÄõµåÆ®¸®
	_pQuadtree = new Quadtree;
	_pQuadtree->CreateTree(_pMainCamera, _pMap);

	// FBX
	FbxData* pFbxDataA = new FbxData;
	if (SUCCEEDED(pFbxDataA->Init()))
	{
		if (SUCCEEDED(pFbxDataA->Load("../../Resource/FBX/Ryan.fbx")))
		{
			pFbxDataA->CreateConstantBuffer(_pd3dDevice);
		}
	}
	_pFbxDatas.push_back(pFbxDataA);

	W_STR defaultDir = L"../../Resource/FBX/";
	std::wstring shaderfilename = L"../../Resource/Shader/Skinning.hlsl";
	for (auto& fbx : _pFbxDatas)
	{
		for (size_t i = 0; i < fbx->_pDrawObjects.size(); i++)
		{
			FbxObject3D* pObject = fbx->_pDrawObjects[i];
			std::wstring load = defaultDir + pObject->_textureName;
			pObject->CreateObject(_pd3dDevice, _pImmediateContext, shaderfilename, load);
		}
	}

	// ¶óÀÌ¾ð
	_pActor = new Actor;
	_pActor->_fbxListIndex = 0;
	_pActor->_pFbxData = _pFbxDatas[_pActor->_fbxListIndex];
	_pActor->_pFbxActionData = pFbxDataA;
	if (_pActor->_pFbxActionData)
	{
		_pActor->_animScene = _pActor->_pFbxActionData->_animScene;
		_pActor->_pFbxDatas.insert(std::make_pair(L"Walk", pFbxDataA));
		_pActor->_currentAction.startFrame = pFbxDataA->_animScene.startFrame;
		_pActor->_currentAction.endFrame = pFbxDataA->_animScene.endFrame;
	}
	else
	{
		_pActor->_animScene = _pActor->_pFbxData->_animScene;
		ActionTable action;
		action.startFrame = _pActor->_animScene.startFrame;
		action.endFrame = _pActor->_animScene.endFrame;
		action.isLoop = true;
		_pActor->_actions.insert(std::make_pair(L"Idle", action));
	}

	_pActor->CreateConstantBuffer(_pd3dDevice);
	D3DXMatrixTranslation(&_pActor->_world, 0, _pMap->GetHeight(0, 0), 0);

	// ºäÆ÷Æ®
	int width = gClient.right / 5;
	int height = gClient.bottom / 4;
	for (int i = 0; i < 4; i++)
	{
		_viewport[i].Width = width;
		_viewport[i].Height = height;
		_viewport[i].TopLeftX = gClient.right - width;
		_viewport[i].TopLeftY = height * i;
		_viewport[i].MinDepth = 0.0f;
		_viewport[i].MaxDepth = 1.0f;
	}

	// Å¾ ºä
	DxVector3 position = DxVector3(0.0f, 10.0f, -0.1f);
	DxVector3 up(0.0f, 1.0f, 0.0f);
	_pCamera[0] = new Camera;
	_pCamera[0]->CreateView(position, _pMainCamera->_position, up);
	// ÇÁ·ÐÆ® ºä
	position = DxVector3(0.0f, 0.0f, -10.0f);
	_pCamera[1] = new Camera;
	_pCamera[1]->CreateView(position, _pMainCamera->_position, up);
	// »çÀÌµå ºä
	position = DxVector3(10.0f, 0.0f, 0.0f);
	_pCamera[2] = new Camera;
	_pCamera[2]->CreateView(position, _pMainCamera->_position, up);
	// À¯Àú ºä
	position = DxVector3(10.0f, 10.0f, -10.0f);
	_pCamera[3] = new Camera;
	_pCamera[3]->CreateView(position, _pMainCamera->_position, up);

	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->CreateProjection(1.0f, 100.0f, PI_DIVISION_4, (float)_viewport[i].Width / (float)_viewport[i].Height);
	}

	// ºäÆ÷Æ®¿¡ ¸Â°Ô Ä«¸Þ¶ó Á¶Á¤
	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->SetObjectView(DxVector3{ -2.0f, -2.0f, -2.0f }, DxVector3{ 2.0f, 2.0f, 2.0f });
	}
	
	return TRUE;
}

HRESULT Scene::Frame()
{
	ClearDeviceContext(_pImmediateContext);
	
	_pQuadtree->Frame();

	_pMainCamera->Frame();

	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->Frame();
	}

	DxVector3 v = _pMainCamera->_look;
	v.y = 0.0f;
	D3DXVec3Normalize(&v, &v);
	_pActor->_look = v;
	_pActor->_position.y = _pMap->GetHeight(_pActor->_position.x, _pActor->_position.z);
	_pActor->UpdateAnimation(_pImmediateContext);
	_pActor->Frame();

	return TRUE;
}

HRESULT Scene::Render()
{
	// ¸Ê
	_pMap->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	_pQuadtree->Render();

	// ¶óÀÌ¾ð
	_pActor->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	_pActor->Render(_pImmediateContext);

	// ºäÆ÷Æ®
	for (size_t i = 0; i < 4; i++)
	{
		_pImmediateContext->RSSetViewports(1, &_viewport[i]);

		DxMatrix controlWorld;
		_pActor->SetMatrix(&controlWorld, &_pCamera[i]->_view, &_pCamera[i]->_projection);
		_pActor->Render(_pImmediateContext);
	}

	_pImmediateContext->RSSetState(DxState::_pDefaultRSSolid);

	return TRUE;
}

HRESULT Scene::Release()
{
	if (_pQuadtree)
	{
		_pQuadtree->Release();
		delete _pQuadtree;
		_pQuadtree = nullptr;
	}

	if (_pMap)
	{
		_pMap->Release();
		delete _pMap;
		_pMap = nullptr;
	}

	if (_pMainCamera)
	{
		_pMainCamera->Release();
		delete _pMainCamera;
		_pMainCamera = nullptr;
	}

	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->Release();
		delete _pCamera[i];
		_pCamera[i] = nullptr;
	}

	for (auto& fbx : _pFbxDatas)
	{
		fbx->Release();
		delete fbx;
		fbx = nullptr;
	}

	if (_pActor)
	{
		_pActor->Release();
		delete _pActor;
		_pActor = nullptr;
	}

	return TRUE;
}

void Scene::CreateScene(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmedtateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmedtateContext;
}

void Scene::ClearDeviceContext(ID3D11DeviceContext* pd3dDeviceContext)
{
	// Unbind all objects from the immediate context
	if (!pd3dDeviceContext)
	{
		return;
	}

	ID3D11ShaderResourceView* pSRVs[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	ID3D11RenderTargetView* pRTVs[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	ID3D11DepthStencilView* pDSV = nullptr;
	ID3D11Buffer* pBuffers[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	ID3D11SamplerState* pSamplers[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	UINT StrideOffset[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// Shaders
	//pd3dDeviceContext->VSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->HSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->DSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->GSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->PSSetShader(NULL, NULL, 0);

	// IA clear
	//pd3dDeviceContext->IASetVertexBuffers(0, 16, pBuffers, StrideOffset, StrideOffset);
	//pd3dDeviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
	//pd3dDeviceContext->IASetInputLayout(NULL);

	// Constant buffers
	//pd3dDeviceContext->VSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->HSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->DSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->GSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->PSSetConstantBuffers(0, 14, pBuffers);

	// Resources
	pd3dDeviceContext->VSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->HSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->DSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->GSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->PSSetShaderResources(0, 16, pSRVs);

	// Samplers
	//pd3dDeviceContext->VSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->HSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->DSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->GSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->PSSetSamplers(0, 16, pSamplers);

	// Render targets
	//pd3dDeviceContext->OMSetRenderTargets(8, pRTVs, pDSV);

	// States
	//FLOAT blendFactor[4] = { 0,0,0,0 };
	//pd3dDeviceContext->OMSetBlendState(NULL, blendFactor, 0xFFFFFFFF);
	//pd3dDeviceContext->OMSetDepthStencilState(NULL, 0);
	//pd3dDeviceContext->RSSetState(NULL);
}
