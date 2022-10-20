#include "pch.h"
#include "Map.h"

HRESULT Map::Customize(UINT width, UINT height)
{
	// 전체 정점 갯수 = width * height
	// 전체 셀 갯수 = (width - 1) * (height - 1)
	// 전체 페이스 갯수 = (width - 1) * (height - 1) * 2
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

	return TRUE;
}
