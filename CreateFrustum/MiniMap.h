#pragma once

#include "Camera.h"
#include "Shape.h"

class MiniMap : public Camera
{
public:
	MiniMap();
	virtual ~MiniMap();

	HRESULT Init();
	HRESULT Frame();
	HRESULT Render();
	HRESULT Release();

	void SetMiniMap(ID3D11Device* pDevice, float TopLeftX, float TopLeftY, float Width, float Height, float MinDepth = 0, float MaxDepth = 1);
	HRESULT CreateMiniMap(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile = 0, const TCHAR* pLoadTexture = 0);
	HRESULT CreateResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pDeviceContext, UINT Width, UINT Height);
	HRESULT DeleteResource();

	Plane _plane;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _pShaderResourceView;
	D3D11_VIEWPORT _viewport;
};

