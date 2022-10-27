#include "pch.h"
#include "Cube.h"
#include "Shape.h"
#include "Timer.h"

HRESULT Cube::Init()
{
	_pDirectionLine = new ShapeDirectionLine;
	_pDirectionLine->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Shape.hlsl", L"");

	return TRUE;
}

HRESULT Cube::Frame()
{
	return TRUE;
}

HRESULT Cube::Render()
{
	Object::Render();
	_pDirectionLine->Render();

	return TRUE;
}

HRESULT Cube::Release()
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

void Cube::CreateVertexData()
{
	_vertices.resize(24);

	// 앞
	_vertices[0].position = MyVector3{ -1.0f, 1.0f, -1.0f };
	_vertices[0].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[0].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[1].position = MyVector3{ 1.0f, 1.0f, -1.0f };
	_vertices[1].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[1].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[2].position = MyVector3{ 1.0f, -1.0f, -1.0f };
	_vertices[2].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[2].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[3].position = MyVector3{ -1.0f, -1.0f, -1.0f };
	_vertices[3].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[3].uv = MyVector2{ 0.0f, 1.0f };

	// 뒤
	_vertices[4].position = MyVector3{ 1.0f, 1.0f, 1.0f };
	_vertices[4].color = Vector4{ 0.0f, 1.0f, 1.0f, 1.0f };
	_vertices[4].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[5].position = MyVector3{ -1.0f, 1.0f, 1.0f };
	_vertices[5].color = Vector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	_vertices[5].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[6].position = MyVector3{ -1.0f, -1.0f, 1.0f };
	_vertices[6].color = Vector4{ 0.0f, 0.0f, 0.0f, 1.0f };
	_vertices[6].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[7].position = MyVector3{ 1.0f, -1.0f, 1.0f };
	_vertices[7].color = Vector4{ 1.0f, 1.0f, 1.0f, 1.0f };
	_vertices[7].uv = MyVector2{ 0.0f, 1.0f };

	// 상
	_vertices[8].position = MyVector3{ -1.0f, 1.0f, 1.0f };
	_vertices[8].color = Vector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	_vertices[8].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[9].position = MyVector3{ 1.0f, 1.0f , 1.0f };
	_vertices[9].color = Vector4{ 0.0f, 1.0f, 1.0f, 1.0f };
	_vertices[9].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[10].position = MyVector3{ 1.0f, 1.0f, -1.0f };
	_vertices[10].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[10].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[11].position = MyVector3{ -1.0f, 1.0f, -1.0f };
	_vertices[11].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[11].uv = MyVector2{ 0.0f, 1.0f };

	// 하
	_vertices[12].position = MyVector3{ -1.0f, -1.0f, -1.0f };
	_vertices[12].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[12].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[13].position = MyVector3{ 1.0f, -1.0f , -1.0f };
	_vertices[13].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[13].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[14].position = MyVector3{ 1.0f, -1.0f, 1.0f };
	_vertices[14].color = Vector4{ 1.0f, 1.0f, 1.0f, 1.0f };
	_vertices[14].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[15].position = MyVector3{ -1.0f, -1.0f, 1.0f };
	_vertices[15].color = Vector4{ 0.0f, 0.0f, 0.0f, 1.0f };
	_vertices[15].uv = MyVector2{ 0.0f, 1.0f };

	// 좌
	_vertices[16].position = MyVector3{ -1.0f, 1.0f, 1.0f };
	_vertices[16].color = Vector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	_vertices[16].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[17].position = MyVector3{ -1.0f, 1.0f , -1.0f };
	_vertices[17].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[17].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[18].position = MyVector3{ -1.0f, -1.0f, -1.0f };
	_vertices[18].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[18].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[19].position = MyVector3{ -1.0f, -1.0f, 1.0f };
	_vertices[19].color = Vector4{ 0.0f, 0.0f, 0.0f, 1.0f };
	_vertices[19].uv = MyVector2{ 0.0f, 1.0f };

	// 우
	_vertices[20].position = MyVector3{ 1.0f, 1.0f, -1.0f };
	_vertices[20].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[20].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[21].position = MyVector3{ 1.0f, 1.0f , 1.0f };
	_vertices[21].color = Vector4{ 0.0f, 1.0f, 1.0f, 1.0f };
	_vertices[21].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[22].position = MyVector3{ 1.0f, -1.0f, 1.0f };
	_vertices[22].color = Vector4{ 1.0f, 1.0f, 1.0f, 1.0f };
	_vertices[22].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[23].position = MyVector3{ 1.0f, -1.0f, -1.0f };
	_vertices[23].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[23].uv = MyVector2{ 0.0f, 1.0f };

	_init = _vertices;
}

void Cube::CreateIndexData()
{
	_indices.resize(36);

	// 앞
	_indices[0] = 0; _indices[1] = 1; _indices[2] = 2;
	_indices[3] = 0; _indices[4] = 2; _indices[5] = 3;

	// 뒤
	_indices[6] = 4; _indices[7] = 5; _indices[8] = 6;
	_indices[9] = 4; _indices[10] = 6; _indices[11] = 7;

	// 상
	_indices[12] = 8; _indices[13] = 9; _indices[14] = 10;
	_indices[15] = 8; _indices[16] = 10; _indices[17] = 11;

	// 하
	_indices[18] = 12; _indices[19] = 13; _indices[20] = 14;
	_indices[21] = 12; _indices[22] = 14; _indices[23] = 15;

	// 좌
	_indices[24] = 16; _indices[25] = 17; _indices[26] = 18;
	_indices[27] = 16; _indices[28] = 18; _indices[29] = 19;

	// 우
	_indices[30] = 20; _indices[31] = 21; _indices[32] = 22;
	_indices[33] = 20; _indices[34] = 22; _indices[35] = 23;

	_face = _indices.size() / 3;
}

void Cube::SetMatrix(MyMatrix* pWorld, MyMatrix* pView, MyMatrix* pProjection)
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

	if (_pDirectionLine)
	{
		_pDirectionLine->SetMatrix(&lineWorld, pView, pProjection);
	}

	MyMatrix scale;
	//scale.Scale(2.0f, 2.0f, 2.0f);

	static float timer = 0.0f;
	timer += DELTA_TIME;
	MyMatrix rotation;
	rotation.RotationY(timer * 0.1f);

	MyMatrix translation;
	translation.Translation(0.0f, 1.0f, 0.0f);
	_world = scale * rotation * translation;
}
