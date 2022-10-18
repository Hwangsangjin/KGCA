#include "pch.h"
#include "Map.h"

HRESULT Map::CreateMap(UINT width, UINT height)
{
	// 전체 셀 갯수 = (width - 1) * (height - 1)
	// 전체 페이스 갯수 = (width - 1) * (height - 1) * 2
	// 전체 정점 갯수 = width * height
	_vertices.resize(width * height);

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			_vertices[x + width * y].position = { (float)x, 0.0f, (float)height - y };
			_vertices[x + width * y].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			_vertices[x + width * y].uv = { (float)y / (float) (width - 1), 
											(float)x / (float) (height - 1)
			};
		}
	}

	_indices.resize((width - 1)* (height - 1) * 2 * 3.0f);

	/*UINT index = 0;
	for (size_t y = 0; y < length; y++)
	{
		for (size_t x = 0; x < length; x++)
		{
			UINT nextRow = x + 1;
			UINT nextCol = y + 1;

			_indices[index + 0] = x + width * y;
			_indices[index + 1] = x + width * y;
			_indices[index + 2] = x + width * y;

			_indices[index + 3] = x + width * y;
			_indices[index + 4] = x + width * y;
			_indices[index + 5] = x + width * y;
		}
	}*/

    return TRUE;
}
