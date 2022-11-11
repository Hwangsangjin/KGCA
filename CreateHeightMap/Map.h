#pragma once

#include "Object.h"

class Map : public Object
{
public:
	DWORD _width;
	DWORD _height;
	UINT _cellX;
	UINT _cellY;
	float _cellDistance = 1.0f;
	float _heightScale = 100.0f;
	std::vector<DWORD> _index;
	std::vector<float> _heights;

	HRESULT BuildMap(UINT Width, UINT Height);
	HRESULT UpdateBuffer(class CameraDebug* pMainCamera);
	HRESULT LoadHeightMap(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, W_STR loadTexture);
	void GenerateVertexNormal();
	DxVector3 ComputeFaceNormal(UINT index0, UINT index1, UINT index2);

	float GetHeight(float positionX, float positionZ);
	float GetHeightMap(int height, int width);
	float Lerp(float start, float end, float tangent);
};

