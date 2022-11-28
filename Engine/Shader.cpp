#include "pch.h"
#include "Shader.h"

HRESULT Shader::Init()
{
    return TRUE;
}

HRESULT Shader::Frame()
{
    return TRUE;
}

HRESULT Shader::Render()
{
    return TRUE;
}

HRESULT Shader::Release()
{
    return TRUE;
}

void Shader::SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context)
{
    device_ = device;
    device_context_ = device_context;
}

HRESULT Shader::CreateShader(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring shader_file)
{
    // µð¹ÙÀÌ½º ¼³Á¤
    SetDevice(device, device_context);

    // Á¤Á¡ ¼ÎÀÌ´õ ÄÄÆÄÀÏ
    Microsoft::WRL::ComPtr<ID3DBlob> error_code;
    HRESULT hr = D3DCompileFromFile(shader_file.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, vertex_shader_code_.GetAddressOf(), error_code.GetAddressOf());
    
    if (FAILED(hr))
    {
        if (error_code)
        {
            OutputDebugStringA((char*)error_code->GetBufferPointer());
        }

        assert(SUCCEEDED(hr));

        return hr;
    }

    // Á¤Á¡ ¼ÎÀÌ´õ »ý¼º
    assert(SUCCEEDED(device_->CreateVertexShader(vertex_shader_code_->GetBufferPointer(), vertex_shader_code_->GetBufferSize(), nullptr, vertex_shader_.GetAddressOf())));

    // ÇÈ¼¿ ¼ÎÀÌ´õ ÄÄÆÄÀÏ  
    assert(SUCCEEDED(D3DCompileFromFile(shader_file.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, pixel_shader_code_.GetAddressOf(), error_code.GetAddressOf())));

    // ÇÈ¼¿ ¼ÎÀÌ´õ »ý¼º
    assert(SUCCEEDED(device_->CreatePixelShader(pixel_shader_code_->GetBufferPointer(), pixel_shader_code_->GetBufferSize(), nullptr, pixel_shader_.GetAddressOf())));

    return TRUE;
}
