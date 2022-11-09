#include "pch.h"
#include "Scene.h"
#include "Input.h"
#include "DxRT.h"
#include "DxState.h"
#include "Camera.h"
#include "Map.h"
#include "Quadtree.h"
#include "Actor.h"
#include "TextureBox.h"
#include "Cube.h"
#include "Timer.h"
#include "FbxLoader.h"

HRESULT Scene::Init()
{
	// FBX
	FbxLoader* pRyan = new FbxLoader;
	if (SUCCEEDED(pRyan->Init()))
	{
		if (SUCCEEDED(pRyan->Load("../../Resource/FBX/Ryan.fbx")))
		{
			pRyan->CreateConstantBuffer(_pd3dDevice);
		}
	}
	_pFbxObjects.push_back(pRyan);
	
	//FbxLoader* pMultiCameras = new FbxLoader;
	//if (SUCCEEDED(pMultiCameras->Init()))
	//{
	//	if (SUCCEEDED(pMultiCameras->Load("../../Resource/FBX/MultiCameras.fbx")))
	//	{
	//		pMultiCameras->CreateConstantBuffer(_pd3dDevice);
	//	}
	//}
	//_pFbxObjects.push_back(pMultiCameras);

	//FbxLoader* pTurret = new FbxLoader;
	//if (SUCCEEDED(pTurret->Init()))
	//{
	//	if (SUCCEEDED(pTurret->Load("../../Resource/FBX/Turret_Deploy1/Turret_Deploy1.fbx")))
	//	{
	//		pTurret->CreateConstantBuffer(_pd3dDevice);
	//	}
	//}
	//_pFbxObjects.push_back(pTurret);

	//FbxLoader* pMan = new FbxLoader;
	//if (SUCCEEDED(pMan->Init()))
	//{
	//	if (SUCCEEDED(pMan->Load("../../Resource/FBX/Man.fbx")))
	//	{
	//		pMan->CreateConstantBuffer(_pd3dDevice);
	//	}
	//}
	//_pFbxObjects.push_back(pMan);

	W_STR defaultDir = L"../../Resource/FBX/";
	std::wstring shaderfilename = L"../../Resource/Shader/Skinning.hlsl";
	for (auto& fbx : _pFbxObjects)
	{
		for (size_t i = 0; i < fbx->_pDrawObjects.size(); i++)
		{
			FbxObject3D* pObject = fbx->_pDrawObjects[i];
			std::wstring load = defaultDir + pObject->_textureName;
			pObject->CreateObject(_pd3dDevice, _pImmediateContext, shaderfilename, load);
		}
	}

	// 뷰포트
	int width = rtClient.right / 5;
	int height = rtClient.bottom / 4;
	for (int i = 0; i < 4; i++)
	{
		_viewport[i].Width = width;
		_viewport[i].Height = height;
		_viewport[i].TopLeftX = rtClient.right - width;
		_viewport[i].TopLeftY = height * i;
		_viewport[i].MinDepth = 0.0f;
		_viewport[i].MaxDepth = 1.0f;
	}

	// 맵
	_pMap = new Map;
	_pMap->Customize(4 + 1, 4 + 1);
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/DefaultObject.hlsl", L"../../Resource/Map/Map.png");
	
	// 라이언
	//_pRyan = new Actor;
	//_pRyan->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/DefaultObject.hlsl", L"../../Resource/Ryan/Ryan.png");
	//AddObject(_pRyan);
	
	// 박스
	_pBox = new TextureBox;
	_pBox->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/DefaultObject.hlsl", L"../../Resource/Box/Box.png");
	DxMatrix m1;
	D3DXMatrixTranslation(&m1, 9.0f, 1.0f, 0.0f);
	_pBox->_world = _pBox->_world * m1;
	AddObject(_pBox);
	
	_pBox2 = new TextureBox;
	_pBox2->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/DefaultObject.hlsl", L"../../Resource/Box/Box.png");
	DxMatrix m2;
	D3DXMatrixTranslation(&m2, 10.0f, 1.0f, 1.0f);
	_pBox2->_world = _pBox2->_world * m2;
	AddObject(_pBox2);
	
	// 큐브
	_pCube = new Cube;
	_pCube->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shape.hlsl", L"");
	AddObject(_pCube);

	// 메인 카메라
	_pMainCamera = new CameraDebug;
	_pMainCamera->CreateView(DxVector3(0.0f, 5.0f, -20.0f), DxVector3(0.0f, 0.0f, 0.0f), DxVector3(0.0f, 1.0f, 0.0f));
	_pMainCamera->CreateProjection(1.0f, 10000.0f, PI_DIVISION_4, RESOLUTION_RATIO);

	// 쿼드트리
	_quadtree.CreateTree(_pMainCamera, _pMap);
	
	// 탑 뷰
	DxVector3 position = DxVector3(0.0f, 10.0f, -0.1f);
	DxVector3 up(0.0f, 1.0f, 0.0f);
	_pCamera[0] = new Camera;
	_pCamera[0]->CreateView(position, DxVector3(0.0f, 0.0f, 0.0f), up);
	// 프론트 뷰
	position = DxVector3(0.0f, 0.0f, -10.0f);
	_pCamera[1] = new Camera;
	_pCamera[1]->CreateView(position, DxVector3(0.0f, 0.0f, 0.0f), up);
	// 사이드 뷰
	position = DxVector3(10.0f, 0.0f, 0.0f);
	_pCamera[2] = new Camera;
	_pCamera[2]->CreateView(position, DxVector3(0.0f, 0.0f, 0.0f), up);
	// 유저 뷰
	position = DxVector3(10.0f, 10.0f, -10.0f);
	_pCamera[3] = new Camera;
	_pCamera[3]->CreateView(position, DxVector3(0.0f, 0.0f, 0.0f), up);
	
	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->CreateProjection(1.0f, 100.0f, PI_DIVISION_4, (float)_viewport[i].Width / (float)_viewport[i].Height);
	}
	
	// 뷰포트에 맞게 카메라 조정
	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->SetObjectView(DxVector3{ -2.0f, -2.0f, -2.0f }, DxVector3{ 2.0f, 2.0f, 2.0f });
	}

	return TRUE;
}

HRESULT Scene::Frame()
{
	ClearDeviceContext(_pImmediateContext);
	
	_quadtree.Frame();

	_pMainCamera->Frame();

	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->Frame();
	}

	for (auto& fbx : _pFbxObjects)
	{
		fbx->UpdateAnimation(_pImmediateContext);
	}

	for (auto& pObject : _pObjects)
	{
		pObject->Frame();
	}

	return TRUE;
}

HRESULT Scene::Render()
{
	// 맵
	_pMap->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	_quadtree.Render();

	// 오브젝트
	for (auto& pObject : _pObjects)
	{
		// 프러스텀 컬링
		HRESULT isRender = _pMainCamera->_frustum.ClassifyPoint(pObject->_position);
		if (SUCCEEDED(isRender))
		{
			pObject->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
			pObject->Render();
		}
	}

	// 조명
	static float timer = 0.0f;
	timer += DELTA_TIME;
	DxVector3 light(0.0f, 0.0f, 1.0f);
	DxMatrix rotation;
	D3DXMatrixRotationY(&rotation, timer);
	D3DXVec3TransformCoord(&light, &light, &rotation);
	D3DXVec3Normalize(&light, &light);

	// FBX
	for (size_t i = 0; i < _pFbxObjects.size(); i++)
	{
		_pImmediateContext->VSSetConstantBuffers(1, 1, &_pFbxObjects[i]->_pConstantBufferBone);

		for (size_t j = 0; j < _pFbxObjects[i]->_pDrawObjects.size(); j++)
		{
			DxMatrix controlWorld;
			//D3DXMatrixRotationY(&controlWorld, timer);
			FbxSkinningObject3D* pObject = _pFbxObjects[i]->_pDrawObjects[j];
			pObject->_constantBuffer.x = light.x;
			pObject->_constantBuffer.y = light.y;
			pObject->_constantBuffer.z = light.z;
			pObject->SetMatrix(&controlWorld, &_pMainCamera->_view, &_pMainCamera->_projection);
			pObject->Render();
		}
	}

	// 뷰포트
	for (size_t i = 0; i < _pFbxObjects.size(); i++)
	{
		_pImmediateContext->VSSetConstantBuffers(1, 1, &_pFbxObjects[i]->_pConstantBufferBone);

		for (size_t j = 0; j < _pFbxObjects[i]->_pDrawObjects.size(); j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				_pImmediateContext->RSSetViewports(1, &_viewport[k]);

				DxMatrix controlWorld;
				FbxSkinningObject3D* pObject = _pFbxObjects[i]->_pDrawObjects[j];
				pObject->SetMatrix(&controlWorld, &_pCamera[k]->_view, &_pCamera[k]->_projection);
				pObject->Render();
			}
		}
	}
	
	_pImmediateContext->RSSetState(DxState::_pDefaultRSSolid);

	return TRUE;
}

HRESULT Scene::Release()
{
	_quadtree.Release();

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

	for (auto& pObject : _pObjects)
	{
		pObject->Release();
		delete pObject;
		pObject = nullptr;
	}

	for (auto& fbx : _pFbxObjects)
	{
		fbx->Release();
		delete fbx;
		fbx = nullptr;
	}

	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->Release();
		delete _pCamera[i];
		_pCamera[i] = nullptr;
	}

	return TRUE;
}

void Scene::CreateScene(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmedtateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmedtateContext;
}

void Scene::AddObject(Object* pObject)
{
	_pObjects.push_back(pObject);
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
