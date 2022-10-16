#include "pch.h"
#include "Scene.h"
#include "Core.h"

HRESULT Scene::Init()
{
	// 텍스처
	TEXTURE->Load(L"../../../Resource/Ryan/Ryan.png");

	// 라이언
	_pRyan = new Object;
	_pRyan->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Ryan/Ryan.png");

	return TRUE;
}

HRESULT Scene::Frame()
{
	// 카메라
	MyMatrix matView;
	static MyVector3 position = { 0.0f, 0.0f, -5.0f };
	static MyVector3 target = { 0.0f, 0.0f, 10.0f };

	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		position._z += 10.0f * DELTA_TIME;
		target._z += 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		position._z -= 10.0f * DELTA_TIME;
		target._z -= 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		position._x -= 10.0f * DELTA_TIME;
		target._x -= 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		position._x += 10.0f * DELTA_TIME;
		target._x += 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('Q') == KEY_STATE::HOLD)
	{
		position._y += 10.0f * DELTA_TIME;
		target._y += 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('E') == KEY_STATE::HOLD)
	{
		position._y -= 10.0f * DELTA_TIME;
		target._y -= 10.0f * DELTA_TIME;
	}

	MyVector3 up = { 0.0f, 1.0f, 0.0f };
	matView.ViewLookAt(position, target, up);

	MyMatrix matProj;
	matProj.PerspectiveFovLH(1.0f, 100.0f, 3.141592f * 0.5f, 800.0f / 600.0f);

 	MyMatrix s, r, t, c;
	s = s.Scale(1.0f, 1.0f, 1.0f);

	static float timer = 0.0f;
	timer += DELTA_TIME;
	r = r.RotationY(timer);

	t = t.Translation(0.0f, 0.0f, 0.0f);
	c = s * r * t;

	for (size_t i = 0; i < _pRyan->_init.size(); i++)
	{
		MyVector3 v = _pRyan->_init[i].position;
		MyVector3 world = v * c;
		MyVector3 view = world * matView;
		MyVector3 proj = view * matProj;
		float w = proj._x * matProj._14 + proj._y * matProj._24 + proj._z * matProj._34 + 1.0f * matProj._44;
		proj._x /= w;
		proj._y /= w;
		proj._z /= w;
		_pRyan->_vertices[i].position = proj;
	}

	_pRyan->SetVertexBuffer();

	//for (auto& pObject : _pObjects)
	//{
	//	pObject->Frame();
	//}

	return TRUE;
}

HRESULT Scene::Render()
{
	_pRyan->Render();

	/*for (auto& pObject : _pObjects)
	{
		pObject->Render();
	}*/

	return TRUE;
}

HRESULT Scene::Release()
{
	SAFE_DELETE(_pRyan);

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