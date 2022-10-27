#include "pch.h"
#include "MiniMap.h"

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
    Release();
}

HRESULT MiniMap::Init()
{
    return TRUE;
}

HRESULT MiniMap::Frame()
{
    return TRUE;
}

HRESULT MiniMap::Render()
{
    return TRUE;
}

HRESULT MiniMap::Release()
{
    return TRUE;
}

void MiniMap::SetMiniMap(ID3D11Device* pDevice, float TopLeftX, float TopLeftY, float Width, float Height, float MinDepth, float MaxDepth)
{
}

HRESULT MiniMap::CreateMiniMap(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTexture)
{
    return E_NOTIMPL;
}

HRESULT MiniMap::CreateResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pDeviceContext, UINT Width, UINT Height)
{
    return E_NOTIMPL;
}

HRESULT MiniMap::DeleteResource()
{
    return E_NOTIMPL;
}
