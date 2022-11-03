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

			return pNewTexture;
		}
	}

	delete pNewTexture;
	return nullptr;
}

Texture* TextureManager::Find(std::wstring textureFile)
{
	for (auto& texture : _textures)
	{
		if (texture.first == textureFile)
		{
			return texture.second;
		}
	}

	return nullptr;
}

T_STR TextureManager::GetSplitName(std::wstring fullPath)
{
	W_STR name;
	TCHAR dirve[MAX_PATH] = { 0 };
	TCHAR dir[MAX_PATH] = { 0 };
	TCHAR filename[MAX_PATH] = { 0 };
	TCHAR ext[MAX_PATH] = { 0 };

	_tsplitpath_s(fullPath.c_str(), dirve, dir, filename, ext);
	name = filename;
	name += ext;

	return name;
}

T_STR TextureManager::GetSplitName(std::string fullPath)
{
	W_STR unicode = to_mw(fullPath);
	TCHAR dirve[MAX_PATH] = { 0 };
	TCHAR dir[MAX_PATH] = { 0 };
	TCHAR filename[MAX_PATH] = { 0 };
	TCHAR ext[MAX_PATH] = { 0 };

	_tsplitpath_s(unicode.c_str(), dirve, dir, filename, ext);
	W_STR name = filename;
	W_STR fileExt = ext;
	if (fileExt == L".tga" || fileExt == L".TGA")
	{
		fileExt = L".dds";
	}
	name += fileExt;

	return name;
}
