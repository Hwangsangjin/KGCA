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

HRESULT Scene::Init()
{
	// FBX
	FbxLoader* pTest = new FbxLoader;
	if (SUCCEEDED(pTest->Init()))
	{
		pTest->Load("../../Resource/FBX/MultiCameras.fbx");
	}

	_pFbxObjects.push_back(pTest);


	FbxLoader* pRyan = new FbxLoader;
	if (SUCCEEDED(pRyan->Init()))
	{
		pRyan->Load("../../Resource/FBX/Ryan.fbx");
	}

	_pFbxObjects.push_back(pRyan);

	W_STR defaultDir = L"../../Resource/FBX/";
	std::wstring shaderfilename = L"../../Resource/Shader/DefaultObject.hlsl";

	for (auto& object : _pFbxObjects)
	{
		for (size_t i = 0; i < object->_pDrawObjects.size(); i++)
		{
			FbxObject3D* pObject = object->_pDrawObjects[i];
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
	_pMap->Customize(256 + 1, 256 + 1);
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/DefaultObject.hlsl", L"../../../Resource/Map/Map.png");
	
	// 라이언
	_pRyan = new Actor;
	_pRyan->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/DefaultObject.hlsl", L"../../../Resource/Ryan/Ryan.png");
	_pRyan->_world.Translation(0.0f, 0.0f, 0.0f);
	AddObject(_pRyan);
	
	// 박스
	_pBox = new TextureBox;
	_pBox->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/DefaultObject.hlsl", L"../../../Resource/Box/Box.png");
	_pBox->_world.Translation(9.0f, 1.0f, 0.0f);
	AddObject(_pBox);
	
	_pBox2 = new TextureBox;
	_pBox2->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/DefaultObject.hlsl", L"../../../Resource/Box/Box.png");
	_pBox2->_world.Translation(10.0f, 1.0f, 2.0f);
	AddObject(_pBox2);
	
	// 큐브
	_pCube = new Cube;
	_pCube->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Shape.hlsl", L"");
	_pCube->_world.Translation(-10.0f, 1.0f, 0.0f);
	AddObject(_pCube);

	// 메인 카메라
	_pMainCamera = new CameraDebug;
	_pMainCamera->CreateView(MyVector3(0.0f, 5.0f, -30.0f), MyVector3(0.0f, 0.0f, 0.0f), MyVector3(0.0f, 1.0f, 0.0f));
	_pMainCamera->CreateProjection(1.0f, 10000.0f, PI_DIVISION_4, RESOLUTION_RATIO);
	
	// 탑 뷰
	MyVector3 position = MyVector3(0.0f, 10.0f, -0.1f);
	MyVector3 up(0.0f, 0.0f, 0.0f);
	_pCamera[0] = new Camera;
	_pCamera[0]->CreateView(position, _pRyan->_position, up);
	// 프론트 뷰
	position = MyVector3(0.0f, 0.0f, -10.0f);
	_pCamera[1] = new Camera;
	_pCamera[1]->CreateView(position, _pRyan->_position, up);
	// 사이드 뷰
	position = MyVector3(10.0f, 0.0f, 0.0f);
	_pCamera[2] = new Camera;
	_pCamera[2]->CreateView(position, _pRyan->_position, up);
	// 유저 뷰
	position = MyVector3(10.0f, 10.0f, -10.0f);
	_pCamera[3] = new Camera;
	_pCamera[3]->CreateView(position, _pRyan->_position, up);
	
	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->CreateProjection(1.0f, 100.0f, PI_DIVISION_4, (float)_viewport[i].Width / (float)_viewport[i].Height);
	}
	
	// 뷰포트에 맞게 카메라 조정
	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->SetObjectView(MyVector3{ -2.0f, -2.0f, -2.0f }, MyVector3{ 2.0f, 2.0f, 2.0f });
	}

	// 쿼드트리
	_quadtree.CreateTree(_pMainCamera, _pMap);

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

	for (auto& pObject : _pFbxObjects)
	{
		pObject->Frame();
	}

	for (auto& pObject : _pObjects)
	{
		pObject->Frame();
	}

	return TRUE;
}

HRESULT Scene::Render()
{
	_pImmediateContext->OMSetDepthStencilState(DxState::_pDefaultDepthStencil, 0xff);
	//_pMap->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	//_quadtree.Render();

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
	//static float timer = 0.0f;
	//timer += DELTA_TIME;
	//MyVector3 light(0.0f, 0.0f, 1.0f);
	//MyMatrix rotation;
	//rotation.RotationY(timer);
	//light = light * rotation;
	//light.Normalize();

	// FBX
	for (int i = 0; i < _pFbxObjects.size(); i++)
	{
		for (int j = 0; j < _pFbxObjects[i]->_pDrawObjects.size(); j++)
		{
			FbxObject3D* pObject = _pFbxObjects[i]->_pDrawObjects[j];
			MyMatrix world;
			world._41 = 100.0f * i;
			//pObject->_constantBuffer.x = light._x;
			//pObject->_constantBuffer.y = light._y;
			//pObject->_constantBuffer.z = light._z;
			pObject->SetMatrix(&world, &_pMainCamera->_view, &_pMainCamera->_projection);
			pObject->Render();
		}
	}

	// 뷰포트
	D3D11_VIEWPORT oldViewport[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	UINT viewports = 1;
	_pImmediateContext->RSGetViewports(&viewports, oldViewport);

	for (size_t i = 0; i < 4; i++)
	{
		_pImmediateContext->RSSetViewports(1, &_viewport[i]);
		_pRyan->SetMatrix(nullptr, &_pCamera[i]->_view, &_pCamera[i]->_projection);
		_pRyan->Render();
	}
	
	_pImmediateContext->RSSetViewports(viewports, oldViewport);
	_pImmediateContext->RSSetState(DxState::_pDefaultRSSolid);

	return TRUE;
}

HRESULT Scene::Release()
{
	_quadtree.Release();

	for (auto& pObject : _pObjects)
	{
		pObject->Release();
		delete pObject;
	}

	for (auto& pObject : _pFbxObjects)
	{
		pObject->Release();
		delete pObject;
	}

	for (int i = 0; i < 4; i++)
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
