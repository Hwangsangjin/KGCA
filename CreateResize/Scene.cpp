#include "pch.h"
#include "Scene.h"
#include "Core.h"

HRESULT Scene::Init()
{
	// 텍스처
	TEXTURE->Load(L"../../../Resource/Ryan/Ryan.png");

	// 라이언
	_pRyan = new Ryan;
	_pRyan->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Ryan/Ryan.png");
	_pRyan->SetRect({ 0.0f, 0.0f, 78.0f, 117.0f });
	_pRyan->SetSpeed(500.0f);
	_pRyan->SetScale(1.0f, 1.0f);
	_pRyan->SetPosition({ 400.0f, 300.0f });
	AddObject(_pRyan);

	return TRUE;
}

HRESULT Scene::Frame()
{
	for (auto& pObject : _pObjects)
	{
		pObject->Frame();
	}

	return TRUE;
}

HRESULT Scene::Render()
{
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
		SAFE_RELEASE(pObject);
	}

	SAFE_DELETE(_pRyan);

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