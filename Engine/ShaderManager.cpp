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
		if (shader.second)
		{
			shader.second->Release();
			delete shader.second;
			shader.second = nullptr;
		}
	}

	_shaders.clear();

	return TRUE;
}

HRESULT ShaderManager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	device_ = pd3dDevice;
	device_context_ = pImmediateContext;

	return TRUE;
}

Shader* ShaderManager::Load(std::wstring shaderFile)
{
	HRESULT hr;

	// �ߺ� ����
	for (auto& shader : _shaders)
	{
		if (shader.first == shaderFile)
		{
			return shader.second;
		}
	}

	// ���̴� ����
	Shader* pNewShader = new Shader;
	if (pNewShader)
	{
		hr = pNewShader->CreateShader(device_, device_context_, shaderFile);
		if (SUCCEEDED(hr))
		{
			_shaders.insert(std::make_pair(shaderFile, pNewShader));
		}
	}

	return pNewShader;
}
