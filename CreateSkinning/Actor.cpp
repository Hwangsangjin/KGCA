#include "pch.h"
#include "Actor.h"
#include "Shape.h"
#include "Timer.h"

void Actor::CreateVertexData()
{
	_vertices.resize(4);

	_vertices[0].position = DxVector3{ -1.0f, 1.0f, 0.0f };
	_vertices[0].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[0].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[1].position = DxVector3{ 1.0f, 1.0f , 0.0f };
	_vertices[1].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[1].uv = DxVector2{ 1.0f, 0.0f };
	_vertices[2].position = DxVector3{ 1.0f, -1.0f, 0.0f };
	_vertices[2].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[2].uv = DxVector2{ 1.0f, 1.0f };
	_vertices[3].position = DxVector3{ -1.0f, -1.0f, 0.0f };
	_vertices[3].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[3].uv = DxVector2{ 0.0f, 1.0f };

	_init = _vertices;
}

void Actor::CreateIndexData()
{
	_indices.resize(6);

	_indices[0] = 0; _indices[1] = 2; _indices[2] = 3;
	_indices[3] = 0; _indices[4] = 1; _indices[5] = 2;

	_face = _indices.size() / 3;
}

void Actor::SetMatrix(DxMatrix* pWorld, DxMatrix* pView, DxMatrix* pProjection)
{
	Object::SetMatrix(pWorld, pView, pProjection);

	_position.x = _world._41;
	_position.y = _world._42;
	_position.z = _world._43;

	_right.x = _world._11;
	_right.y = _world._12;
	_right.z = _world._13;

	_up.x = _world._21;
	_up.y = _world._22;
	_up.z = _world._23;

	_look.x = _world._31;
	_look.y = _world._32;
	_look.z = _world._33;

	DxMatrix lineWorld;
	D3DXMatrixScaling(&lineWorld, 2.0f, 2.0f, 2.0f);
	lineWorld = lineWorld * _world;

	DxMatrix scale;
	//D3DXMatrixScaling(&scale, 2.0f, 2.0f, 2.0f);

	static float timer = 0.0f;
	timer += DELTA_TIME;
	DxMatrix rotation;
	D3DXMatrixRotationY(&rotation, timer * 0.1f);

	DxMatrix translation;
	D3DXMatrixTranslation(&translation, 0.0f, 1.0f, 0.0f);
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
	Object3D::Render();
	_pDirectionLine->Render();

	return TRUE;
}

HRESULT Actor::Release()
{
	Object3D::Release();

	if (_pDirectionLine)
	{
		_pDirectionLine->Release();
		delete _pDirectionLine;
		_pDirectionLine = nullptr;
	}

	return TRUE;
}
