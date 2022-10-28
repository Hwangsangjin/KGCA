#include "pch.h"
#include "Map.h"
#include "Camera.h"

HRESULT Map::Customize(UINT width, UINT height)
{
	// 전체 정점 갯수 = width * height
	// 전체 셀 갯수 = (width - 1) * (height - 1)
	// 전체 페이스 갯수 = (width - 1) * (height - 1) * 2
	_x = width;
	_y = height;
	_vertices.resize(width * height);

	const int centerX = width * 0.5f;
	const int centerY = height * 0.5f;
	const float distance = 1.0f;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			_vertices[x + width * y].position = { (float)(x - centerX) * distance, 0.0f, (float)(centerY - y) * distance };
			//_vertices[x + width * y].position = { (float)(x - centerX) * distance, cosf(DEGREE_TO_RADIAN(x)) * 20.0f + sinf(DEGREE_TO_RADIAN(y)) * 20.0f, (float)(centerY - y) * distance };
			_vertices[x + width * y].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			_vertices[x + width * y].uv = { ((float)x / (float)(width - 1)) * 10.0f, ((float)y / (float)(height - 1)) * 10.0f };
		}
	}

	_indices.resize((width - 1) * (height - 1) * 2 * 3.0f);

	UINT index = 0;
	for (int y = 0; y < height - 1; y++)
	{
		for (int x = 0; x < width - 1; x++)
		{
			UINT nextX = x + 1;
			UINT nextY = y + 1;

			_indices[index + 0] = x + width * y;
			_indices[index + 1] = _indices[index + 0] + 1;
			_indices[index + 2] = x + width * nextY;

			_indices[index + 3] = _indices[index + 2];
			_indices[index + 4] = _indices[index + 1];
			_indices[index + 5] = _indices[index + 3] + 1;

			index += 6;
		}
	}

	_index.resize(_indices.size());
	_face = _indices.size() / 3;

	return TRUE;
}

HRESULT Map::UpdateBuffer(class CameraDebug* pMainCamera)
{
	_face = 0;
	DWORD index = 0;
	MyVector3 vector[3];

	for (size_t i = 0; i < _indices.size() / 3; i++)
	{
		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];
		vector[0] = _vertices[index0].position;
		vector[1] = _vertices[index1].position;
		vector[2] = _vertices[index2].position;

		for (size_t i = 0; i < 3; i++)
		{
			HRESULT isRender = pMainCamera->_frustum.ClassifyPoint(vector[i]);
			if (SUCCEEDED(isRender))
			{
				_index[index++] = index0;
				_index[index++] = index1;
				_index[index++] = index2;
				_face++;
				break;
			}
		}
	}

	_pImmediateContext->UpdateSubresource(_pIndexBuffer, 0, nullptr, &_index.at(0), 0, 0);

	return TRUE;
}
