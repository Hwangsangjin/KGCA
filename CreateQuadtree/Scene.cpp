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

HRESULT Scene::Init()
{
	// 뷰포트
	_viewport[0].TopLeftX = 650.0f;
	_viewport[0].TopLeftY = 0.0f;
	_viewport[0].Width = 200.0f;
	_viewport[0].Height = 150.0f;
	_viewport[0].MinDepth = 0.0f;
	_viewport[0].MaxDepth = 1.0f;

	_viewport[1].TopLeftX = 650.0f;
	_viewport[1].TopLeftY = 180.0f;
	_viewport[1].Width = 200.0f;
	_viewport[1].Height = 150.0f;
	_viewport[1].MinDepth = 0.0f;
	_viewport[1].MaxDepth = 1.0f;

	_viewport[2].TopLeftX = 650.0f;
	_viewport[2].TopLeftY = 330.0f;
	_viewport[2].Width = 200.0f;
	_viewport[2].Height = 150.0f;
	_viewport[2].MinDepth = 0.0f;
	_viewport[2].MaxDepth = 1.0f;

	_viewport[3].TopLeftX = 650.0f;
	_viewport[3].TopLeftY = 480.0f;
	_viewport[3].Width = 200.0f;
	_viewport[3].Height = 150.0f;
	_viewport[3].MinDepth = 0.0f;
	_viewport[3].MaxDepth = 1.0f;

	// 맵
	_pMap = new Map;
	_pMap->Customize(256 + 1, 256 + 1);
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Map/Map.png");
	
	//// 라이언
	_pRyan = new Actor;
	_pRyan->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Ryan/Ryan.png");
	AddObject(_pRyan);
	
	// 박스
	_pBox = new TextureBox;
	_pBox->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Box/Box.png");
	_pBox->_world.Translation(9.0f, 1.0f, 0.0f);
	AddObject(_pBox);
	
	_pBox2 = new TextureBox;
	_pBox2->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Box/Box.png");
	_pBox2->_world.Translation(10.0f, 1.0f, 2.0f);
	AddObject(_pBox2);
	
	// 큐브
	_pCube = new Cube;
	_pCube->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Shape.hlsl", L"");
	AddObject(_pCube);

	// 메인 카메라
	_pMainCamera = new CameraDebug;
	_pMainCamera->CreateView(MyVector3(0.0f, 5.0f, -30.0f), MyVector3(0.0f, 0.0f, 0.0f), MyVector3(0.0f, 1.0f, 0.0f));
	_pMainCamera->CreateProjection(1.0f, 10000.0f, PI_DIVISION_4, RESOLUTION_RATIO);
	
	// 카메라
	MyVector3 position = MyVector3(0.0f, 10.0f, -0.1f);
	MyVector3 up(0.0f, 1.0f, 0.0f);
	
	// 탑 뷰
	_pCamera[0] = new Camera;
	_pCamera[0]->CreateView(position, _pCube->_position, up);
	// 프론트 뷰
	position = MyVector3(0.0f, 1.0f, -10.0f);
	_pCamera[1] = new Camera;
	_pCamera[1]->CreateView(position, _pCube->_position, up);
	// 사이드 뷰
	position = MyVector3(10.0f, 1.0f, 0.0f);
	_pCamera[2] = new Camera;
	_pCamera[2]->CreateView(position, _pCube->_position, up);
	// 유저 뷰
	position = MyVector3(10.0f, 10.0f, -10.0f);
	_pCamera[3] = new Camera;
	_pCamera[3]->CreateView(position, _pCube->_position, up);
	
	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->CreateProjection(1.0f, 100.0f, PI_DIVISION_4, (float)_viewport[i].Width / (float)_viewport[i].Height);
	}
	
	// 뷰포트에 맞게 카메라 조정
	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->SetObjectView(MyVector3{ -2.0f, -2.0f, -2.0f }, MyVector3{ 2.0f, 2.0f, 2.0f });
	}

	return TRUE;
}

HRESULT Scene::Frame()
{
	if (INPUT->GetKey(VK_RBUTTON) == KEY_STATE::HOLD)
	{
		_pMainCamera->_yaw += INPUT->_offset.x * 0.002f;
		_pMainCamera->_pitch += INPUT->_offset.y * 0.002f;
	}

	_pMainCamera->Frame();

	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->Frame();
	}

	for (auto& pObject : _pObjects)
	{
		pObject->Frame();
	}

	return TRUE;
}

HRESULT Scene::Render()
{
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

	// 뷰포트
	D3D11_VIEWPORT oldViewport[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	UINT viewports = 1;
	_pImmediateContext->RSGetViewports(&viewports, oldViewport);

	for (size_t i = 0; i < 4; i++)
	{
		_pImmediateContext->RSSetViewports(1, &_viewport[i]);
		_pCube->SetMatrix(nullptr, &_pCamera[i]->_view, &_pCamera[i]->_projection);
		_pCube->Render();
	}
	
	_pImmediateContext->RSSetViewports(viewports, oldViewport);

	return TRUE;
}

HRESULT Scene::Release()
{
	for (auto& pObject : _pObjects)
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
