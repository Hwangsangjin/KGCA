#include "pch.h"
#include "Shape.h"
#include "Input.h"
#include "Timer.h"

void ShapeBox::CreateVertexData()
{
    _vertices.resize(24);

	// 앞
    _vertices[0].position = MyVector3{ -1.0f, 1.0f, -1.0f };
    _vertices[0].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
    _vertices[0].uv = MyVector2{ 0.0f, 0.0f };
    _vertices[1].position = MyVector3{ 1.0f, 1.0f , -1.0f };
    _vertices[1].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
    _vertices[1].uv = MyVector2{ 1.0f, 0.0f };
    _vertices[2].position = MyVector3{ 1.0f, -1.0f, -1.0f };
    _vertices[2].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
    _vertices[2].uv = MyVector2{ 1.0f, 1.0f };
    _vertices[3].position = MyVector3{ -1.0f, -1.0f, -1.0f };
    _vertices[3].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
    _vertices[3].uv = MyVector2{ 0.0f, 1.0f };

	// 뒤
    _vertices[4].position = MyVector3{ -1.0f, 1.0f, 1.0f };
    _vertices[4].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
    _vertices[4].uv = MyVector2{ 0.0f, 0.0f };
    _vertices[5].position = MyVector3{ 1.0f, 1.0f , 1.0f };
    _vertices[5].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
    _vertices[5].uv = MyVector2{ 1.0f, 0.0f };
    _vertices[6].position = MyVector3{ 1.0f, -1.0f, 1.0f };
    _vertices[6].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
    _vertices[6].uv = MyVector2{ 1.0f, 1.0f };
    _vertices[7].position = MyVector3{ -1.0f, -1.0f, 1.0f };
    _vertices[7].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
    _vertices[7].uv = MyVector2{ 0.0f, 1.0f };

	// 상
	_vertices[8].position = MyVector3{ -1.0f, 1.0f, 1.0f };
	_vertices[8].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[8].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[9].position = MyVector3{ 1.0f, 1.0f , 1.0f };
	_vertices[9].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[9].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[10].position = MyVector3{ 1.0f, 1.0f, -1.0f };
	_vertices[10].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[10].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[11].position = MyVector3{ -1.0f, 1.0f, -1.0f };
	_vertices[11].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[11].uv = MyVector2{ 0.0f, 1.0f };

	// 하
	_vertices[12].position = MyVector3{ -1.0f, -1.0f, 1.0f };
	_vertices[12].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[12].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[13].position = MyVector3{ 1.0f, -1.0f , 1.0f };
	_vertices[13].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[13].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[14].position = MyVector3{ 1.0f, -1.0f, -1.0f };
	_vertices[14].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[14].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[15].position = MyVector3{ -1.0f, -1.0f, -1.0f };
	_vertices[15].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[15].uv = MyVector2{ 0.0f, 1.0f };

	// 좌
	_vertices[16].position = MyVector3{ -1.0f, 1.0f, 1.0f };
	_vertices[16].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[16].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[17].position = MyVector3{ -1.0f, 1.0f , -1.0f };
	_vertices[17].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[17].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[18].position = MyVector3{ -1.0f, -1.0f, -1.0f };
	_vertices[18].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[18].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[19].position = MyVector3{ -1.0f, -1.0f, 1.0f };
	_vertices[19].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[19].uv = MyVector2{ 0.0f, 1.0f };

	// 우
	_vertices[20].position = MyVector3{ 1.0f, 1.0f, -1.0f };
	_vertices[20].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[20].uv = MyVector2{ 0.0f, 0.0f };
	_vertices[21].position = MyVector3{ 1.0f, 1.0f , 1.0f };
	_vertices[21].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[21].uv = MyVector2{ 1.0f, 0.0f };
	_vertices[22].position = MyVector3{ 1.0f, -1.0f, 1.0f };
	_vertices[22].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[22].uv = MyVector2{ 1.0f, 1.0f };
	_vertices[23].position = MyVector3{ 1.0f, -1.0f, -1.0f };
	_vertices[23].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[23].uv = MyVector2{ 0.0f, 1.0f };

    _init = _vertices;
}

void ShapeBox::CreateIndexData()
{
    // 정점 버퍼의 인덱스
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
	_indices[33] = 22; _indices[34] = 22; _indices[35] = 23;
}

HRESULT ShapeBox::Frame()
{
	MyMatrix s, r, t, c;

	static float timer = 0.0f;
	timer += DELTA_TIME;
	//s = StaticMatrix::Scale(400.0f, 300.0f, 1.0f);
	r = StaticMatrix::RotationY(timer);
	//t = StaticMatrix::Translation(0.0f, 0.0f, 0.0f);

	_World = s * r * t;

	return TRUE;
}

HRESULT ShapeBox::Render()
{
	PreRender();
	PostRender();

	return TRUE;
}
