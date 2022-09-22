#include "pch.h"
#include "Scene.h"

HRESULT Scene::Init()
{
    return TRUE;
}

HRESULT Scene::Frame()
{
    return TRUE;
}

HRESULT Scene::Render()
{
    return TRUE;
}

HRESULT Scene::Release()
{
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
