#include "pch.h"
#include "ShaderManager.h"
#include "Shader.h"

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
	for (auto& shader : shaders_)
	{
		if (shader.second)
		{
			shader.second->Release();
			delete shader.second;
			shader.second = nullptr;
		}
	}

	shaders_.clear();

	return TRUE;
}

HRESULT ShaderManager::SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context)
{
	device_ = device;
	device_context_ = device_context;

	return TRUE;
}

Shader* ShaderManager::Load(std::wstring shader_file)
{
	HRESULT hr;

	// 중복 제거
	for (auto& shader : shaders_)
	{
		if (shader.first == shader_file)
		{
			return shader.second;
		}
	}

	// 셰이더 생성
	Shader* new_shader = new Shader;
	if (new_shader)
	{
		hr = new_shader->CreateShader(device_.Get(), device_context_.Get(), shader_file);
		if (SUCCEEDED(hr))
		{
			shaders_.insert(std::make_pair(shader_file, new_shader));
		}
	}

	return new_shader;
}
