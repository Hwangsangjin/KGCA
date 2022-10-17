#include "pch.h"
#include "Scene.h"
#include "Core.h"

HRESULT Scene::Init()
{
	// 텍스처
	TEXTURE->Load(L"../../../Resource/Ryan/Ryan.png");
	TEXTURE->Load(L"../../../Resource/Box/Box.png");

	// 라이언
	_pRyan = new Object2D;
	_pRyan->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Ryan/Ryan.png");
	_pRyan->SetRect({ 0.0f, 0.0f, 230.0f, 381.0f });
	_pRyan->SetScale(1.0f, 1.0f);
	_pRyan->SetPosition({ 400.0f, 300.0f });

	// 박스
	_pBox = new ShapeBox;
	_pBox->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Box/Box.png");

	// 카메라
	_pMainCamera = new Camera;
	_pMainCamera->CreateView(MyVector3(0, 0, -10), MyVector3(0, 0, 0), MyVector3(0, 1, 0));
	_pMainCamera->CreateProjection(1.0f, 100.0f, 3.141592 * 0.5f, RESOLUTION_X / RESOLUTION_Y);

	return TRUE;
}

HRESULT Scene::Frame()
{
	//_pRyan->Frame();
	_pBox->Frame();
	_pMainCamera->Frame();

	//for (auto& pObject : _pObjects)
	//{
	//	pObject->Frame();
	//}

	return TRUE;
}

HRESULT Scene::Render()
{
	//_pRyan->SetMatrix(nullptr, &_pMainCamera->_View, &_pMainCamera->_Projection);
	//_pRyan->Render();
	_pBox->SetMatrix(nullptr, &_pMainCamera->_View, &_pMainCamera->_Projection);
	_pBox->Render();

	//_pBox->SetMatrix(nullptr, &_pMainCamera->_View, &_pMainCamera->_Projection);
	//_pBox->Render();

	/*for (auto& pObject : _pObjects)
	{
		pObject->Render();
	}*/

	return TRUE;
}

HRESULT Scene::Release()
{
	SAFE_DELETE(_pBox);

	//for (auto& pObject : _pObjects)
	//{
	//	SAFE_RELEASE(pObject);
	//}

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