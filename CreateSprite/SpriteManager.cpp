#include "pch.h"
#include "SpriteManager.h"

HRESULT SpriteManager::Init()
{
    return TRUE;
}

HRESULT SpriteManager::Frame()
{
    return TRUE;
}

HRESULT SpriteManager::Render()
{
    return TRUE;
}

HRESULT SpriteManager::Release()
{
	for (auto& sprite : _sprites)
	{
		if (sprite.second)
		{
			sprite.second->Release();
		}
	}

	_sprites.clear();

    return TRUE;
}

HRESULT SpriteManager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;

	return TRUE;
}

HRESULT SpriteManager::GameDataLoad(const TCHAR* data)
{
	TCHAR buffer[256] = { 0 };
	TCHAR temp[256] = { 0 };

	int num = 0;
	FILE* file;
	_wfopen_s(&file, data, _T("rt"));
	if (file == nullptr)
	{
		return E_FAIL;
	}

	_fgetts(buffer, _countof(buffer), file);
	_stscanf_s(buffer, _T("%s%d%s"), temp, (unsigned int)_countof(temp), &num);
	_rects.resize(num);

	for (size_t i = 0; i < num; i++)
	{
		int frame = 0;
		_fgetts(buffer, _countof(buffer), file);
		_stscanf_s(buffer, _T("%s%d"), temp, (unsigned int)_countof(temp), &frame);
		_names.push_back(temp);

		RECT rect;
		for (size_t j = 0; j < frame; j++)
		{
			_fgetts(buffer, _countof(buffer), file);
			_stscanf_s(buffer, _T("%s%d%d%d%d"), temp, (unsigned int)_countof(temp), &rect.left, &rect.top, &rect.right, &rect.bottom);
			_rects[i].push_back(rect);
		}
	}

	fclose(file);

	return TRUE;
}

HRESULT SpriteManager::Load(std::wstring spriteFile)
{
	HRESULT hr;

	_rects.clear();
	_names.clear();

	HR(GameDataLoad(spriteFile.c_str()));

	_names.push_back(spriteFile);

	for (size_t i = 0; i < _rects.size(); i++)
	{
		// 중복 제거
		auto data = Find(_names[i]);
		if (data != nullptr)
		{
			continue;
		}

		Sprite* pNewSprite = new Sprite;
		pNewSprite->_name = _names[i];
		pNewSprite->_uvs = _rects[i];

		if (pNewSprite)
		{
			hr = pNewSprite->CreateSprite(_pd3dDevice, _pImmediateContext, spriteFile);

			if (SUCCEEDED(hr))
			{
				_sprites.insert(std::make_pair(pNewSprite->_name, pNewSprite));
			}
		}
	}

    return TRUE;
}

Sprite* SpriteManager::Find(std::wstring spriteFile)
{
	for (auto& sprite : _sprites)
	{
		if (sprite.first == spriteFile)
		{
			return sprite.second;
		}
	}

	return nullptr;
}

Sprite& SpriteManager::Get(W_STR str)
{
	for (auto& sprite : _sprites)
	{
		if (sprite.first == str)
		{
			return *sprite.second;
		}
	}

	/*auto iter = _sprites.find(str);
	if (iter != _sprites.end())
	{
		Sprite* pData = iter->second;
		return *pData;
	}*/
}

Sprite* SpriteManager::GetPtr(W_STR str)
{
	for (auto& sprite : _sprites)
	{
		if (sprite.first == str)
		{
			return sprite.second;
		}
	}

	/*auto iter = _sprites.find(str);
	if (iter != _sprites.end())
	{
		Sprite* pData = iter->second;
		return pData;
	}*/

	return nullptr;
}
