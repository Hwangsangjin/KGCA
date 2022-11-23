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
    // ����̽� ����
    SetDevice(device, device_context);

    // ���� ���̴� ������
    Microsoft::WRL::ComPtr<ID3DBlob> error_code;
    assert(SUCCEEDED(D3DCompileFromFile(L"../../Resource/Shader/Sample.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, vertex_shader_code_.GetAddressOf(), error_code.GetAddressOf())));

    // ���� ���̴� ����
    assert(SUCCEEDED(device_->CreateVertexShader(vertex_shader_code_->GetBufferPointer(), vertex_shader_code_->GetBufferSize(), nullptr, vertex_shader_.GetAddressOf())));

    // �ȼ� ���̴� ������  
    assert(SUCCEEDED(D3DCompileFromFile(L"../../Resource/Shader/Sample.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, pixel_shader_code_.GetAddressOf(), error_code.GetAddressOf())));

    // �ȼ� ���̴� ����
    assert(SUCCEEDED(device_->CreatePixelShader(pixel_shader_code_->GetBufferPointer(), pixel_shader_code_->GetBufferSize(), nullptr, pixel_shader_.GetAddressOf())));

    return TRUE;
}
