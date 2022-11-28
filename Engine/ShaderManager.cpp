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
	shaders_.clear();

	return TRUE;
}

HRESULT ShaderManager::SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context)
{
	device_ = device;
	device_context_ = device_context;

	return TRUE;
}

std::shared_ptr<Shader> ShaderManager::FindFile(std::wstring shader_file)
{
	for (auto& shader : shaders_)
	{
		if (shader.first == shader_file)
		{
			return shader.second;
		}
	}

	return nullptr;
}

std::shared_ptr<Shader> ShaderManager::LoadFile(std::wstring shader_file)
{
	// 중복 제거
	FindFile(shader_file);

	// 셰이더 생성
	shader_ = std::make_shared<Shader>();
	shader_->CreateShader(device_.Get(), device_context_.Get(), shader_file);
	shaders_.insert(std::make_pair(shader_file, shader_));

	return shader_;
}
