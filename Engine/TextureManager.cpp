#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

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
	for (auto& texture : textures_)
	{
		if (texture.second)
		{
			texture.second->Release();
			delete texture.second;
			texture.second = nullptr;
		}
	}

	textures_.clear();

	return TRUE;
}

HRESULT TextureManager::SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context)
{
	device_ = device;
	device_context_ = device_context;

	return TRUE;
}

Texture* TextureManager::Load(std::wstring texture_file)
{
	HRESULT hr;

	// 중복 제거
	Find(texture_file);

	// 텍스처 생성
	Texture* new_texture = new Texture;
	if (new_texture)
	{
		hr = new_texture->CreateTexture(device_.Get(), device_context_.Get(), texture_file);
		if (SUCCEEDED(hr))
		{
			textures_.insert(std::make_pair(texture_file, new_texture));

			return new_texture;
		}
	}

	delete new_texture;
	return nullptr;
}

Texture* TextureManager::Find(std::wstring texture_file)
{
	for (auto& texture : textures_)
	{
		if (texture.first == texture_file)
		{
			return texture.second;
		}
	}

	return nullptr;
}

T_STR TextureManager::GetSplitName(std::wstring full_path)
{
	W_STR name;
	TCHAR dirve[MAX_PATH] = { 0 };
	TCHAR dir[MAX_PATH] = { 0 };
	TCHAR file_name[MAX_PATH] = { 0 };
	TCHAR ext[MAX_PATH] = { 0 };

	_tsplitpath_s(full_path.c_str(), dirve, dir, file_name, ext);
	name = file_name;
	name += ext;

	return name;
}

T_STR TextureManager::GetSplitName(std::string full_path)
{
	W_STR unicode = to_mw(full_path);
	TCHAR dirve[MAX_PATH] = { 0 };
	TCHAR dir[MAX_PATH] = { 0 };
	TCHAR file_name[MAX_PATH] = { 0 };
	TCHAR ext[MAX_PATH] = { 0 };

	_tsplitpath_s(unicode.c_str(), dirve, dir, file_name, ext);
	W_STR name = file_name;
	W_STR file_ext = ext;
	if (file_ext == L".tga" || file_ext == L".TGA")
	{
		file_ext = L".dds";
	}
	name += file_ext;

	return name;
}
