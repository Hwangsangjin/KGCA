#include "pch.h"
#include "Scene.h"
#include "Core.h"

HRESULT Scene::Init()
{
	// 텍스처
	TEXTURE->Load(L"../../../Resource/Ryan/Ryan.png");

	// 테스트
	_pTest = new Object;
	_pTest->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Ryan/Ryan.png");

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
	// 카메라
	MyMatrix matView;
	static MyVector3 position = { 0.0f, 0.0f, -10.0f };
	static MyVector3 target = { 0.0f, 0.0f, 10.0f };

	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		position._z += 10.0f * DELTA_TIME;
		target._z += 10.0f * DELTA_TIME;
	}
	else if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		position._z -= 10.0f * DELTA_TIME;
		target._z -= 10.0f * DELTA_TIME;
	}
	else if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		position._x -= 10.0f * DELTA_TIME;
		target._x -= 10.0f * DELTA_TIME;
	}
	else if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		position._x += 10.0f * DELTA_TIME;
		target._x += 10.0f * DELTA_TIME;
	}
	else if (INPUT->GetKey('Q') == KEY_STATE::HOLD)
	{
		position._y += 10.0f * DELTA_TIME;
		target._y += 10.0f * DELTA_TIME;
	}
	else if (INPUT->GetKey('E') == KEY_STATE::HOLD)
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

	if (INPUT->GetKey(VK_RBUTTON) == KEY_STATE::HOLD)
	{
		r = r.RotationY(90);
	}

	t = t.Translation(0.0f, 0.0f, 0.0f);
	c = s * r * t;

	for (size_t i = 0; i < _pTest->_init.size(); i++)
	{
		MyVector3 v = _pTest->_init[i].position;
		MyVector3 world = v * c;
		MyVector3 view = world * matView;
		MyVector3 proj = view * matProj;
		float w = proj._x * matProj._14 + proj._y * matProj._24 + proj._z * matProj._34 + 1.0f * matProj._44;
		proj._x /= w;
		proj._y /= w;
		proj._z /= w;
		_pTest->_vertices[i].position = proj;
	}

	_pTest->SetVertexBuffer();

	//for (auto& pObject : _pObjects)
	//{
	//	pObject->Frame();
	//}

	return TRUE;
}

HRESULT Scene::Render()
{
	_pTest->Render();

	/*for (auto& pObject : _pObjects)
	{
		pObject->Render();
	}*/

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