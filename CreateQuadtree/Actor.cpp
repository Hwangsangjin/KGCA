#include "pch.h"
#include "Actor.h"
#include "Shape.h"
#include "Timer.h"

void Actor::CreateVertexData()
{
	_vertices.resize(4);

	_vertices[0].position = MyVector3{ -1.0f, 1.0f, 0.0f };
	_vertices[0].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[0].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[1].position = MyVector3{ 1.0f, 1.0f , 0.0f };
	_vertices[1].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[1].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[2].position = MyVector3{ 1.0f, -1.0f, 0.0f };
	_vertices[2].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[2].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[3].position = MyVector3{ -1.0f, -1.0f, 0.0f };
	_vertices[3].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[3].uv = MyVector2{ 0.0f, 1.0f };

	_init = _vertices;
}

void Actor::CreateIndexData()
{
	_indices.resize(6);

	_indices[0] = 0; _indices[1] = 2; _indices[2] = 3;
	_indices[3] = 0; _indices[4] = 1; _indices[5] = 2;

	_face = _indices.size() / 3;
}

void Actor::SetMatrix(MyMatrix* pWorld, MyMatrix* pView, MyMatrix* pProjection)
{
	Object::SetMatrix(pWorld, pView, pProjection);

	_position._x = _world._41;
	_position._y = _world._42;
	_position._z = _world._43;

	_right._x = _world._11;
	_right._y = _world._12;
	_right._z = _world._13;

	_up._x = _world._21;
	_up._y = _world._22;
	_up._z = _world._23;

	_look._x = _world._31;
	_look._y = _world._32;
	_look._z = _world._33;

	MyVector3 up;
	MyVector3 right;

	MyMatrix lineWorld;
	lineWorld.Scale(2.0f, 2.0f, 2.0f);
	lineWorld = lineWorld * _world;

	MyMatrix scale;
	scale.Scale(2.0f, 2.0f, 2.0f);

	static float timer = 0.0f;
	timer += DELTA_TIME;
	MyMatrix rotation;
	rotation.RotationY(timer * 0.1f);

	MyMatrix translation;
	translation.Translation(-10.0f, 2.0f, 0.0f);
	_world = scale * rotation * translation;

	if (_pDirectionLine)
	{
		_pDirectionLine->SetMatrix(&lineWorld, pView, pProjection);
	}
}

HRESULT Actor::Init()
{
	_pDirectionLine = new ShapeDirectionLine;
	_pDirectionLine->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Shape.hlsl", L"");

	return TRUE;
}

HRESULT Actor::Frame()
{
	return TRUE;
}

HRESULT Actor::Render()
{
	Object::Render();
	_pDirectionLine->Render();

	return TRUE;
}

HRESULT Actor::Release()
{
	if (_pDirectionLine)
	{
		_pDirectionLine->Release();
		delete _pDirectionLine;
		_pDirectionLine = nullptr;
	}

	Object3D::Release();

	return TRUE;
}
