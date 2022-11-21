#include "pch.h"
#include "Shape.h"

void ShapeLine::CreateVertexData()
{
	_vertices.resize(2);

	_vertices[0].position = DxVector3{ 0.0f, 0.0f, 0.0f };
	_vertices[0].color = DxVector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	_vertices[0].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[1].position = DxVector3{ 0.0f, 0.0f, 1000.0f };
	_vertices[1].color = DxVector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	_vertices[1].uv = DxVector2{ 1.0f, 0.0f };

	_init = _vertices;
}

void ShapeLine::CreateIndexData()
{
	_indices.resize(2);

	_indices[0] = 0;	_indices[1] = 1;
}

HRESULT ShapeLine::Frame()
{
	return TRUE;
}

HRESULT ShapeLine::Render()
{
	device_context_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	PreRender();
	PostRender();

	device_context_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return TRUE;
}

void ShapeDirectionLine::CreateVertexData()
{
	_vertices.resize(6);

	_vertices[0].position = DxVector3{ 0.0f, 0.0f, 0.0f };
	_vertices[0].color = DxVector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	_vertices[0].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[1].position = DxVector3{ 1.0f, 0.0f, 0.0f };
	_vertices[1].color = DxVector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	_vertices[1].uv = DxVector2{ 1.0f, 0.0f };
	_vertices[2].position = DxVector3{ 0.0f, 0.0f, 0.0f };
	_vertices[2].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[2].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[3].position = DxVector3{ 0.0f, 1.0f , 0.0f };
	_vertices[3].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[3].uv = DxVector2{ 1.0f, 0.0f };
	_vertices[4].position = DxVector3{ 0.0f, 0.0f, 0.0f };
	_vertices[4].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[4].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[5].position = DxVector3{ 0.0f, 0.0f , 1.0f };
	_vertices[5].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[5].uv = DxVector2{ 1.0f, 0.0f };

	_init = _vertices;
}

void ShapeDirectionLine::CreateIndexData()
{
	_indices.resize(6);

	_indices[0] = 0;	_indices[1] = 1;
	_indices[2] = 2;	_indices[3] = 3;
	_indices[4] = 4;	_indices[5] = 5;
}

void ShapePlane::CreateVertexData()
{
}

void ShapePlane::CreateIndexData()
{
}

void ShapeBox::CreateVertexData()
{
	_vertices.resize(24);

	// 앞
	_vertices[0].position = DxVector3{ -1.0f, 1.0f, -1.0f };
	_vertices[0].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[0].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[1].position = DxVector3{ 1.0f, 1.0f, -1.0f };
	_vertices[1].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[1].uv = DxVector2{ 1.0f, 0.0f };
	_vertices[2].position = DxVector3{ 1.0f, -1.0f, -1.0f };
	_vertices[2].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[2].uv = DxVector2{ 1.0f, 1.0f };
	_vertices[3].position = DxVector3{ -1.0f, -1.0f, -1.0f };
	_vertices[3].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[3].uv = DxVector2{ 0.0f, 1.0f };

	// 뒤
	_vertices[4].position = DxVector3{ 1.0f, 1.0f, 1.0f };
	_vertices[4].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[4].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[5].position = DxVector3{ -1.0f, 1.0f, 1.0f };
	_vertices[5].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[5].uv = DxVector2{ 1.0f, 0.0f };
	_vertices[6].position = DxVector3{ -1.0f, -1.0f, 1.0f };
	_vertices[6].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[6].uv = DxVector2{ 1.0f, 1.0f };
	_vertices[7].position = DxVector3{ 1.0f, -1.0f, 1.0f };
	_vertices[7].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[7].uv = DxVector2{ 0.0f, 1.0f };

	// 상
	_vertices[8].position = DxVector3{ -1.0f, 1.0f, 1.0f };
	_vertices[8].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[8].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[9].position = DxVector3{ 1.0f, 1.0f , 1.0f };
	_vertices[9].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[9].uv = DxVector2{ 1.0f, 0.0f };
	_vertices[10].position = DxVector3{ 1.0f, 1.0f, -1.0f };
	_vertices[10].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[10].uv = DxVector2{ 1.0f, 1.0f };
	_vertices[11].position = DxVector3{ -1.0f, 1.0f, -1.0f };
	_vertices[11].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[11].uv = DxVector2{ 0.0f, 1.0f };

	// 하
	_vertices[12].position = DxVector3{ -1.0f, -1.0f, -1.0f };
	_vertices[12].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[12].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[13].position = DxVector3{ 1.0f, -1.0f , -1.0f };
	_vertices[13].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[13].uv = DxVector2{ 1.0f, 0.0f };
	_vertices[14].position = DxVector3{ 1.0f, -1.0f, 1.0f };
	_vertices[14].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[14].uv = DxVector2{ 1.0f, 1.0f };
	_vertices[15].position = DxVector3{ -1.0f, -1.0f, 1.0f };
	_vertices[15].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[15].uv = DxVector2{ 0.0f, 1.0f };

	// 좌
	_vertices[16].position = DxVector3{ -1.0f, 1.0f, 1.0f };
	_vertices[16].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[16].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[17].position = DxVector3{ -1.0f, 1.0f , -1.0f };
	_vertices[17].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[17].uv = DxVector2{ 1.0f, 0.0f };
	_vertices[18].position = DxVector3{ -1.0f, -1.0f, -1.0f };
	_vertices[18].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[18].uv = DxVector2{ 1.0f, 1.0f };
	_vertices[19].position = DxVector3{ -1.0f, -1.0f, 1.0f };
	_vertices[19].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[19].uv = DxVector2{ 0.0f, 1.0f };

	// 우
	_vertices[20].position = DxVector3{ 1.0f, 1.0f, -1.0f };
	_vertices[20].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	_vertices[20].uv = DxVector2{ 0.0f, 0.0f };
	_vertices[21].position = DxVector3{ 1.0f, 1.0f , 1.0f };
	_vertices[21].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	_vertices[21].uv = DxVector2{ 1.0f, 0.0f };
	_vertices[22].position = DxVector3{ 1.0f, -1.0f, 1.0f };
	_vertices[22].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	_vertices[22].uv = DxVector2{ 1.0f, 1.0f };
	_vertices[23].position = DxVector3{ 1.0f, -1.0f, -1.0f };
	_vertices[23].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	_vertices[23].uv = DxVector2{ 0.0f, 1.0f };

	_init = _vertices;
}

void ShapeBox::CreateIndexData()
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
}

HRESULT ShapeBox::Frame()
{
	return TRUE;
}

HRESULT ShapeBox::Render()
{
	PreRender();
	PostRender();

	return TRUE;
}
