#include "pch.h"
#include "Map.h"
#include "Camera.h"

HRESULT Map::BuildMap(UINT width, UINT height)
{
	// ��ü ���� ���� = width * height
	// ��ü �� ���� = (width - 1) * (height - 1)
	// ��ü ���̽� ���� = (width - 1) * (height - 1) * 2
	_width = width;
	_height = height;
	_cellX = _width - 1;
	_cellY = _height - 1;
	_vertices.resize(width * height);

	const int centerX = width * 0.5f;
	const int centerY = height * 0.5f;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			_vertices[x + width * y].position = { (float)(x - centerX) * _cellDistance, 0.0f, (float)(centerY - y) * _cellDistance };
			//_vertices[x + width * y].position = { (float)(x - centerX) * _cellDistance, cosf(DEGREE_TO_RADIAN(x)) * 20.0f + sinf(DEGREE_TO_RADIAN(y)) * 20.0f, (float)(centerY - y) * _cellDistance };
			_vertices[x + width * y].position.y = _heights[x + y * _height] * _heightScale;
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

	GenerateVertexNormal();

	return TRUE;
}

HRESULT Map::UpdateBuffer(class CameraDebug* pMainCamera)
{
	_face = 0;
	DWORD index = 0;
	DxVector3 vector[3];

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

HRESULT Map::LoadHeightMap(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, W_STR loadTexture)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> pTexture;
	DirectX::CreateWICTextureFromFileEx(pd3dDevice, loadTexture.c_str(), 0, D3D11_USAGE_STAGING, 0, D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE, 0, WIC_LOADER_DEFAULT, pTexture.GetAddressOf(), nullptr);

	ID3D11Texture2D* pTexture2D = nullptr;
	if (FAILED(pTexture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D)))
	{
		return E_FAIL;
	}

	D3D11_TEXTURE2D_DESC td;
	pTexture2D->GetDesc(&td);

	_heights.resize(td.Height * td.Width);

	D3D11_MAPPED_SUBRESOURCE mappedFaceDest;
	if (SUCCEEDED(pImmediateContext->Map(pTexture2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &mappedFaceDest)))
	{
		UCHAR* pTexels = (UCHAR*)mappedFaceDest.pData;
		for (UINT y = 0; y < td.Height; y++)
		{
			UINT yStart = y * mappedFaceDest.RowPitch;
			for (UINT x = 0; x < td.Width; x++)
			{
				UINT xStart = x * 4;
				UINT uRed = pTexels[yStart + xStart + 0];
				_heights[x + td.Width * y] = (float)uRed / 255.0f;
			}
		}

		pImmediateContext->Unmap(pTexture2D, D3D11CalcSubresource(0, 0, 1));
	}

	_height = td.Height;
	_width = td.Width;

	pTexture2D->Release();

	return TRUE;
}

void Map::GenerateVertexNormal()
{
	std::vector<DxVector3> faceNormals;
	faceNormals.resize(_face);
	UINT face = 0;
	for (UINT i = 0; i < _indices.size(); i += 3)
	{
		UINT index0 = _indices[i + 0];
		UINT index1 = _indices[i + 1];
		UINT index2 = _indices[i + 2];
		faceNormals[face++] = ComputeFaceNormal(index0, index1, index2);
	}

	struct VertexInfo
	{
		std::vector<UINT> faceIndexArray;
		DxVector3 normal;
	};

	std::vector<VertexInfo> vertexInfos;
	vertexInfos.resize(_height * _width);

	for (UINT face = 0; face < _face; face++)
	{
		for (UINT i = 0; i < 3; i++)
		{
			UINT index0 = _indices[i + face * 3];
			vertexInfos[index0].faceIndexArray.push_back(face);
		}
	}

	for (UINT vertex = 0; vertex < vertexInfos.size(); vertex++)
	{
		for (UINT i = 0; i < vertexInfos[vertex].faceIndexArray.size(); i++)
		{
			vertexInfos[vertex].normal += faceNormals[vertexInfos[vertex].faceIndexArray[i]];
		}

		D3DXVec3Normalize(&vertexInfos[vertex].normal, &vertexInfos[vertex].normal);

		_vertices[vertex].normal = vertexInfos[vertex].normal;
#ifdef _DEBUG
		DxVector3 light = { 0, 1, 0 };
		float dot = D3DXVec3Dot(&light, &_vertices[vertex].normal);
		_vertices[vertex].color = { dot, dot, dot, 1.0f };
#endif
	}
}

DxVector3 Map::ComputeFaceNormal(UINT index0, UINT index1, UINT index2)
{
	DxVector3 normal;
	DxVector3 edge0 = _vertices[index1].position - _vertices[index0].position;
	DxVector3 edge1 = _vertices[index2].position - _vertices[index0].position;

	D3DXVec3Cross(&normal, &edge0, &edge1);
	D3DXVec3Normalize(&normal, &normal);

	return normal;
}

float Map::GetHeight(float positionX, float positionZ)
{
	// positionX, positionZ�� ��ġ�� �ش��ϴ� ���̸ʼ��� ã�´�.
	// _x, _y�� ����/������ ���� ũ�Ⱚ��
	float cellX = (float)(_width * _cellDistance / 2.0f + positionX);
	float cellZ = (float)(_height * _cellDistance / 2.0f + positionZ);

	// ���� ũ��� ������ 0 ~ 1 ������ ������ �ٲ� ���̸� �迭�� �����Ѵ�.
	cellX /= (float)_cellDistance;
	cellZ /= (float)_cellDistance;

	// cellX, cellZ ������ �۰ų� ���� �ִ� ����(�Ҽ� �κ��� �߶󳽴�.)
	float vertexX = ::floorf(cellX);
	float vertexY = ::floorf(cellZ);

	// ���̸� ������ ����� ������ �ʱ�ȭ�Ѵ�.
	if (vertexX < 0.0f)
	{
		vertexX = 0.0f;
	}

	if (vertexY < 0.0f)
	{
		vertexY = 0.0f;
	}

	if ((float)(_width - 2) < vertexX)
	{
		vertexX = (float)(_width - 2);
	}

	if ((float)(_height - 2) < vertexY)
	{
		vertexY = (float)(_height - 2);
	}

	// ���� ���� ����� �����ϴ� 4�� ������ ���̰��� ã�´�. 
	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D
	float A = GetHeightMap((int)vertexY, (int)vertexX);
	float B = GetHeightMap((int)vertexY, (int)vertexX + 1);
	float C = GetHeightMap((int)vertexY + 1, (int)vertexX);
	float D = GetHeightMap((int)vertexY + 1, (int)vertexX + 1);

	// a������ ��ġ���� ������ ��(������)�� ����Ѵ�.(0 ~ 1.0f)
	float deltaX = cellX - vertexX;
	float deltaZ = cellZ - vertexY;

	// ���� �۾��� ���� ���� ���̽��� ã�´�.
	float height = 0.0f;
	
	// ã�� ���̽��� �������� �����Ѵ�.
	if (deltaZ < (1.0f - deltaX))	// ABC
	{
		float uy = B - A;	// A->B
		float vy = C - A;	// A->C

		// �� ������ ���̰� ���̸� ���Ͽ� deltaX�� ���� ���� �������� ã�´�.
		height = D + Lerp(0.0f, uy, 1.0f - deltaX) + Lerp(0.0f, vy, 1.0f - deltaZ);
	}

	return height;
}

float Map::GetHeightMap(int height, int width)
{
	return _vertices[width + height * _height].position.y;
}

float Map::Lerp(float start, float end, float tangent)
{
	return 0.0f;
}
