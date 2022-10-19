#include "pch.h"
#include "Scene.h"
#include "Core.h"
#include "Camera.h"
#include "Actor.h"
#include "Shape.h"

HRESULT Scene::Init()
{
	// 카메라
	_pMainCamera = new Camera;
	_pMainCamera->CreateView(MyVector3(0.0f, 0.0f, -5.0f), MyVector3(0.0f, 0.0f, 0.0f), MyVector3(0.0f, 1.0f, 0.0f));
	_pMainCamera->CreateProjection(1.0f, 100.0f, PI_DIVISION_2, RESOLUTION_RATIO);

	// 라이언
	_pRyan = new Actor;
	_pRyan->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Ryan/Ryan.png");
	AddObject(_pRyan);

	// 박스
	_pBox = new ShapeBox;
	_pBox->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Box/Box.png");
	AddObject(_pBox);

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
	_pRyan->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	_pBox->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);

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