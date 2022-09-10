#include "pch.h"
#include "ShaderManager.h"

HRESULT ShaderManager::Init()
{
	return TRUE;
}

HRESULT ShaderManager::Frame()
{
	return TRUE;
}

HRESULT ShaderManager::Render()
{
	return TRUE;
}

HRESULT ShaderManager::Release()
{
	for (auto& shader : _shaders)
	{
		SAFE_RELEASE(shader.second);
	}

	_shaders.clear();

	return TRUE;
}

HRESULT ShaderManager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;

	return TRUE;
}

Shader* ShaderManager::Load(std::wstring filename)
{
	HRESULT hr;

	// �ߺ� ����
	for (auto& shader : _shaders)
	{
		if (!shader.first.find(filename))
		{
			return shader.second;
		}
	}

	// ���̴� ����
	Shader* pNewShader = new Shader;
	if (pNewShader)
	{
		hr = pNewShader->CreateShader(_pd3dDevice, _pImmediateContext, filename);
		if (SUCCEEDED(hr))
		{
			_shaders.insert(std::make_pair(filename, pNewShader));
		}
	}

	return pNewShader;
}
