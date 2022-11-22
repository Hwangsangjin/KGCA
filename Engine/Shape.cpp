#include "pch.h"
#include "Shape.h"

void ShapeLine::CreateVertexData()
{
	vertices_.resize(2);

	vertices_[0].position = DxVector3{ 0.0f, 0.0f, 0.0f };
	vertices_[0].color = DxVector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertices_[0].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[1].position = DxVector3{ 0.0f, 0.0f, 1000.0f };
	vertices_[1].color = DxVector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertices_[1].uv = DxVector2{ 1.0f, 0.0f };

	init_vertices_ = vertices_;
}

void ShapeLine::CreateIndexData()
{
	indices_.resize(2);

	indices_[0] = 0;	indices_[1] = 1;
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
	vertices_.resize(6);
	vertices_[0].position = DxVector3{ 0.0f, 0.0f, 0.0f };
	vertices_[0].color = DxVector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertices_[0].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[1].position = DxVector3{ 1.0f, 0.0f, 0.0f };
	vertices_[1].color = DxVector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertices_[1].uv = DxVector2{ 1.0f, 0.0f };
	vertices_[2].position = DxVector3{ 0.0f, 0.0f, 0.0f };
	vertices_[2].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	vertices_[2].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[3].position = DxVector3{ 0.0f, 1.0f , 0.0f };
	vertices_[3].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	vertices_[3].uv = DxVector2{ 1.0f, 0.0f };
	vertices_[4].position = DxVector3{ 0.0f, 0.0f, 0.0f };
	vertices_[4].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	vertices_[4].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[5].position = DxVector3{ 0.0f, 0.0f , 1.0f };
	vertices_[5].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	vertices_[5].uv = DxVector2{ 1.0f, 0.0f };

	init_vertices_ = vertices_;
}

void ShapeDirectionLine::CreateIndexData()
{
	indices_.resize(6);
	indices_[0] = 0;	indices_[1] = 1;
	indices_[2] = 2;	indices_[3] = 3;
	indices_[4] = 4;	indices_[5] = 5;
}

void ShapePlane::CreateVertexData()
{
}

void ShapePlane::CreateIndexData()
{
}

void ShapeBox::CreateVertexData()
{
	vertices_.resize(24);

	// 앞
	vertices_[0].position = DxVector3{ -1.0f, 1.0f, -1.0f };
	vertices_[0].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	vertices_[0].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[1].position = DxVector3{ 1.0f, 1.0f, -1.0f };
	vertices_[1].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	vertices_[1].uv = DxVector2{ 1.0f, 0.0f };
	vertices_[2].position = DxVector3{ 1.0f, -1.0f, -1.0f };
	vertices_[2].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	vertices_[2].uv = DxVector2{ 1.0f, 1.0f };
	vertices_[3].position = DxVector3{ -1.0f, -1.0f, -1.0f };
	vertices_[3].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	vertices_[3].uv = DxVector2{ 0.0f, 1.0f };

	// 뒤
	vertices_[4].position = DxVector3{ 1.0f, 1.0f, 1.0f };
	vertices_[4].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	vertices_[4].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[5].position = DxVector3{ -1.0f, 1.0f, 1.0f };
	vertices_[5].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	vertices_[5].uv = DxVector2{ 1.0f, 0.0f };
	vertices_[6].position = DxVector3{ -1.0f, -1.0f, 1.0f };
	vertices_[6].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	vertices_[6].uv = DxVector2{ 1.0f, 1.0f };
	vertices_[7].position = DxVector3{ 1.0f, -1.0f, 1.0f };
	vertices_[7].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	vertices_[7].uv = DxVector2{ 0.0f, 1.0f };

	// 상
	vertices_[8].position = DxVector3{ -1.0f, 1.0f, 1.0f };
	vertices_[8].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	vertices_[8].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[9].position = DxVector3{ 1.0f, 1.0f , 1.0f };
	vertices_[9].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	vertices_[9].uv = DxVector2{ 1.0f, 0.0f };
	vertices_[10].position = DxVector3{ 1.0f, 1.0f, -1.0f };
	vertices_[10].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	vertices_[10].uv = DxVector2{ 1.0f, 1.0f };
	vertices_[11].position = DxVector3{ -1.0f, 1.0f, -1.0f };
	vertices_[11].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	vertices_[11].uv = DxVector2{ 0.0f, 1.0f };

	// 하
	vertices_[12].position = DxVector3{ -1.0f, -1.0f, -1.0f };
	vertices_[12].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	vertices_[12].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[13].position = DxVector3{ 1.0f, -1.0f , -1.0f };
	vertices_[13].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	vertices_[13].uv = DxVector2{ 1.0f, 0.0f };
	vertices_[14].position = DxVector3{ 1.0f, -1.0f, 1.0f };
	vertices_[14].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	vertices_[14].uv = DxVector2{ 1.0f, 1.0f };
	vertices_[15].position = DxVector3{ -1.0f, -1.0f, 1.0f };
	vertices_[15].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	vertices_[15].uv = DxVector2{ 0.0f, 1.0f };

	// 좌
	vertices_[16].position = DxVector3{ -1.0f, 1.0f, 1.0f };
	vertices_[16].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	vertices_[16].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[17].position = DxVector3{ -1.0f, 1.0f , -1.0f };
	vertices_[17].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	vertices_[17].uv = DxVector2{ 1.0f, 0.0f };
	vertices_[18].position = DxVector3{ -1.0f, -1.0f, -1.0f };
	vertices_[18].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	vertices_[18].uv = DxVector2{ 1.0f, 1.0f };
	vertices_[19].position = DxVector3{ -1.0f, -1.0f, 1.0f };
	vertices_[19].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	vertices_[19].uv = DxVector2{ 0.0f, 1.0f };

	// 우
	vertices_[20].position = DxVector3{ 1.0f, 1.0f, -1.0f };
	vertices_[20].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
	vertices_[20].uv = DxVector2{ 0.0f, 0.0f };
	vertices_[21].position = DxVector3{ 1.0f, 1.0f , 1.0f };
	vertices_[21].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
	vertices_[21].uv = DxVector2{ 1.0f, 0.0f };
	vertices_[22].position = DxVector3{ 1.0f, -1.0f, 1.0f };
	vertices_[22].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
	vertices_[22].uv = DxVector2{ 1.0f, 1.0f };
	vertices_[23].position = DxVector3{ 1.0f, -1.0f, -1.0f };
	vertices_[23].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
	vertices_[23].uv = DxVector2{ 0.0f, 1.0f };

	init_vertices_ = vertices_;
}

void ShapeBox::CreateIndexData()
{
	indices_.resize(36);

	// 앞
	indices_[0] = 0; indices_[1] = 1; indices_[2] = 2;
	indices_[3] = 0; indices_[4] = 2; indices_[5] = 3;

	// 뒤
	indices_[6] = 4; indices_[7] = 5; indices_[8] = 6;
	indices_[9] = 4; indices_[10] = 6; indices_[11] = 7;

	// 상
	indices_[12] = 8; indices_[13] = 9; indices_[14] = 10;
	indices_[15] = 8; indices_[16] = 10; indices_[17] = 11;

	// 하
	indices_[18] = 12; indices_[19] = 13; indices_[20] = 14;
	indices_[21] = 12; indices_[22] = 14; indices_[23] = 15;

	// 좌
	indices_[24] = 16; indices_[25] = 17; indices_[26] = 18;
	indices_[27] = 16; indices_[28] = 18; indices_[29] = 19;

	// 우
	indices_[30] = 20; indices_[31] = 21; indices_[32] = 22;
	indices_[33] = 20; indices_[34] = 22; indices_[35] = 23;
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
