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
	for (auto& sprite : m_List)
	{
		if (sprite.second)
		{
			sprite.second->Release();
		}
	}

	m_List.clear();

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
	TCHAR texturePath[256] = { 0 };
	TCHAR maskPath[256] = { 0 };
	TCHAR shaderPath[256] = { 0 };

	int num = 0;
	FILE* file;
	_wfopen_s(&file, data, _T("rt"));
	if (file == nullptr)
	{
		return E_FAIL;
	}

	_fgetts(buffer, _countof(buffer), file);
	_stscanf_s(buffer, _T("%s"), temp, (unsigned int)_countof(temp));

	int animation = 0;
	for (;;)
	{
		int frame = 0;
		_fgetts(buffer, _countof(buffer), file);
		_stscanf_s(buffer, _T("%s %d%d %s%s%s"), 
			temp, (unsigned int)_countof(temp), 
			&frame, &animation, 
			texturePath, (unsigned int)_countof(texturePath), 
			maskPath, (unsigned int)_countof(maskPath), 
			shaderPath, (unsigned int)_countof(shaderPath));

		W_STR name = temp;
		if (name == L"#END")
		{
			break;
		}

		m_iSpriteTypeList.push_back(animation);
		m_rtNameList.push_back(temp);
		m_TextureNameList.push_back(texturePath);
		m_MaskTextureNameList.push_back(maskPath);
		m_ShaderNameList.push_back(shaderPath);

		int iReadFrame = 0;

		if (animation == 0)
		{
			std::vector<RECT> rtList;
			RECT rt;
			for (int i = 0; i < frame; i++)
			{
				_fgetts(buffer, _countof(buffer), file);
				_stscanf_s(buffer, _T("%d %d %d %d %d"),
					&iReadFrame,
					&rt.left, &rt.top, &rt.right, &rt.bottom);
				rtList.push_back(rt);
			}

			m_rtSpriteList.push_back(rtList);
		}
		else
		{
			TCHAR_STRING_VECTOR list;
			for (int i = 0; i < frame; i++)
			{
				_fgetts(buffer, _countof(buffer), file);
				_stscanf_s(buffer, _T("%d %s"),
					&iReadFrame,
					temp, (unsigned int)_countof(temp));
				list.push_back(temp);
			}

			m_szSpriteList.push_back(list);
		}
	}

	fclose(file);

	return TRUE;
}

HRESULT SpriteManager::Load(std::wstring filename)
{
	m_rtSpriteList.clear();
	m_szSpriteList.clear();
	m_iSpriteTypeList.clear();
	m_rtNameList.clear();
	m_TextureNameList.clear();
	m_MaskTextureNameList.clear();
	m_ShaderNameList.clear();

	HR(GameDataLoad(filename.c_str()));

	for (int ifile = 0; ifile < filelist.size(); ifile++)
	{
		if (filelist[ifile] == filename)
		{
			return TRUE;
		}
	}

	filelist.push_back(filename);

	HRESULT hr;
	UINT iCurrentTexIndex = 0;
	UINT iCurrentUVIndex = 0;

	for (size_t i = 0; i < m_rtNameList.size(); i++)
	{
		// 중복 제거
		auto data = Find(m_rtNameList[i]);
		if (data != nullptr)
		{
			continue;
		}

		Sprite* pNewSprite = nullptr;
		if (m_iSpriteTypeList[i] == 0)
			pNewSprite = new Sprite;
		else
			pNewSprite = new SpriteTexture;

		pNewSprite->_name = m_rtNameList[i];
		pNewSprite->_texturePath = m_TextureNameList[i];
		pNewSprite->_maskPath = m_MaskTextureNameList[i];
		pNewSprite->_shaderPath = m_ShaderNameList[i];

		if (m_iSpriteTypeList[i] == 1)
		{
			pNewSprite->_textures = m_szSpriteList[iCurrentTexIndex++];
		}
		else
		{
			pNewSprite->_uvs = m_rtSpriteList[iCurrentUVIndex++];
		}

		if (pNewSprite)
		{
			bool bRet = pNewSprite->Load(_pd3dDevice, _pImmediateContext, filename);
			if (bRet)
			{
				m_List.insert(std::make_pair(pNewSprite->_name, std::move(pNewSprite)));
			}
			else
			{
				pNewSprite->Release();
				delete pNewSprite;
			}
		}
	}

    return TRUE;
}

Sprite* SpriteManager::Find(std::wstring name)
{
	auto iter = m_List.find(name);
	if (iter != m_List.end())
	{
		return iter->second;
	}
	return nullptr;
}

Sprite& SpriteManager::Get(W_STR str)
{
	for (auto& sprite : m_List)
	{
		if (sprite.first == str)
		{
			return *sprite.second;
		}
	}
}

Sprite* SpriteManager::GetPtr(W_STR str)
{
	for (auto& sprite : m_List)
	{
		if (sprite.first == str)
		{
			return sprite.second;
		}
	}

	return nullptr;
}
