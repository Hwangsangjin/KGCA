#include "pch.h"
#include "Scene.h"
#include "Core.h"
#include "Camera.h"
#include "Map.h"
#include "Actor.h"
#include "Shape.h"

HRESULT Scene::Init()
{
	// 카메라
	_pMainCamera = new Camera;
	_pMainCamera->CreateView(MyVector3(0.0f, 30.0f, -50.0f), MyVector3(0.0f, 0.0f, 0.0f), MyVector3(0.0f, 1.0f, 0.0f));
	_pMainCamera->CreateProjection(1.0f, 1000.0f, PI_DIVISION_4, RESOLUTION_RATIO);

	// 맵
	_pMap = new Map;
	_pMap->Customize(128 + 1, 128 + 1);
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Map/Map.png");
	AddObject(_pMap);

	// 라이언
	_pRyan = new Actor;
	_pRyan->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Ryan/Ryan.png");
	_pRyan->_world.Translation(-3.0f, 1.0f, 0.0f);
	AddObject(_pRyan);

	// 박스
	_pBox = new ShapeBox;
	_pBox->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Box/Box.png");
	_pBox->_world.Translation(0.0f, 1.0f, 0.0f);
	AddObject(_pBox);

	_pBox2 = new ShapeBox;
	_pBox2->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Box/Box.png");
	_pBox2->_world.Translation(1.0f, 1.0f, 2.0f);
	AddObject(_pBox2);

	return TRUE;
}

HRESULT Scene::Frame()
{
	_pMainCamera->Frame();

	for (auto& pObject : _pObjects)
	{
		pObject->Frame();
	}

	return TRUE;
}

HRESULT Scene::Render()
{
	_pImmediateContext->OMSetDepthStencilState(DxState::_pDefaultDepthStencil, 0xff);

	_pMap->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	_pRyan->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	_pBox->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	_pBox2->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);

	for (auto& pObject : _pObjects)
	{
		pObject->Render();
	}

	return TRUE;
}

HRESULT Scene::Release()
{
	for (auto& pObject : _pObjects)
	{
		SAFE_DELETE(pObject);
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