#include "pch.h"
#include "Actor.h"
#include "Input.h"
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
}

HRESULT Actor::Frame()
{
	MyMatrix s, r, t, c;

	static float timer = 0.0f;
	timer += DELTA_TIME;
	//s = StaticMatrix::Scale(400.0f, 300.0f, 1.0f);
	r = StaticMatrix::RotationY(timer);
	//t = StaticMatrix::Translation(0.0f, 0.0f, 0.0f);

	_world = s * r * t;

	return TRUE;
}

HRESULT Actor::Render()
{
	PreRender();
	PostRender();

	return TRUE;
}
