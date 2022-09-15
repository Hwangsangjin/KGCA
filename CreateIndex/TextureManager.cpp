#include "pch.h"
#include "TextureManager.h"

HRESULT TextureManager::Init()
{
	return TRUE;
}

HRESULT TextureManager::Frame()
{
	return TRUE;
}

HRESULT TextureManager::Render()
{
	return TRUE;
}

HRESULT TextureManager::Release()
{
	for (auto& texture : _textures)
	{
		SAFE_RELEASE(texture.second);
	}

	_textures.clear();

	return TRUE;
}

HRESULT TextureManager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;

	return TRUE;
}

Texture* TextureManager::Load(std::wstring textureFile)
{
	HRESULT hr;

	// 중복 제거
	Find(textureFile);

	// 텍스처 생성
	Texture* pNewTexture = new Texture;
	if (pNewTexture)
	{
		hr = pNewTexture->CreateTexture(_pd3dDevice, _pImmediateContext, textureFile);
		if (SUCCEEDED(hr))
		{
			_textures.insert(std::make_pair(textureFile, pNewTexture));
		}
	}

	return pNewTexture;
}

Texture* TextureManager::Find(std::wstring texturefile)
{
	for (auto& texture : _textures)
	{
		if (texture.first == texturefile)
		{
			return texture.second;
		}
	}

	return nullptr;
}
