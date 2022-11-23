#include "pch.h"
#include "Object.h"
#include "ShaderManager.h"
#include "TextureManager.h"

HRESULT Object::Init()
{
    return TRUE;
}

HRESULT Object::Frame()
{
    return TRUE;
}

HRESULT Object::PreRender()
{
    UINT stride = sizeof(DefaultVertex);
    UINT offset = 0;
    device_context_->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
    device_context_->IASetIndexBuffer(index_buffer_.Get(), DXGI_FORMAT_R32_UINT, 0);
    device_context_->IASetInputLayout(input_layout_.Get());
    device_context_->VSSetConstantBuffers(0, 1, constant_buffer_.GetAddressOf());
    device_context_->VSSetShader(vertex_shader_.Get(), NULL, 0);
    device_context_->PSSetShader(pixel_shader_.Get(), NULL, 0);
    device_context_->PSSetShaderResources(0, 1, shader_resource_view_.GetAddressOf());

    return TRUE;
}

HRESULT Object::Render()
{
    PreRender();
    PostRender();

    return TRUE;
}

HRESULT Object::PostRender()
{
    if (!index_buffer_)
    {
        device_context_->Draw(vertices_.size(), 0);
    }
    else
    {
        //device_context_->DrawIndexed(face_ * 3, 0, 0);
        device_context_->DrawIndexed(indices_.size(), 0, 0);
    }

    return TRUE;
}

HRESULT Object::Release()
{
    return TRUE;
}

void Object::SetMatrix(DxMatrix* world_matrix, DxMatrix* view_matrix, DxMatrix* projection_matrix)
{
    if (world_matrix)
    {
        world_matrix_ = *world_matrix;
    }

    if (view_matrix)
    {
        view_matrix_ = *view_matrix;
    }

    if (projection_matrix)
    {
        projection_matrix_ = *projection_matrix;
    }

    UpdateConstantBuffer();
}

HRESULT Object::SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context)
{
    device_ = device;
    device_context_ = device_context;

    return TRUE;
}

HRESULT Object::CreateObject(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring shader_file, std::wstring texture_file)
{
    assert(SUCCEEDED(SetDevice(device, device_context)));
    assert(SUCCEEDED(CreateVertexBuffer()));
    assert(SUCCEEDED(CreateIndexBuffer()));
    assert(SUCCEEDED(CreateConstantBuffer()));
    assert(SUCCEEDED(CreateShader(shader_file)));
    assert(SUCCEEDED(CreateInputLayout()));

    if (SUCCEEDED(LoadTexture(texture_file)))
    {
        shader_resource_view_ = texture_->shader_resource_view_;
    }

    if (FAILED(Init()))
    {
        return E_FAIL;
    }

    return TRUE;
}

void Object::CreateVertexData()
{
    if (vertices_.size() > 0)
    {
        init_vertices_ = vertices_;

        return;
    }

    vertices_.resize(4);
    vertices_[0].position = DxVector3{ -1.0f, 1.0f, 0.0f };
    vertices_[0].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
    vertices_[0].uv = DxVector2{ 0.0f, 0.0f };
    vertices_[1].position = DxVector3{ 1.0f, 1.0f , 0.0f };
    vertices_[1].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
    vertices_[1].uv = DxVector2{ 1.0f, 0.0f };
    vertices_[2].position = DxVector3{ -1.0f, -1.0f, 0.0f };
    vertices_[2].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
    vertices_[2].uv = DxVector2{ 0.0f, 1.0f };
    vertices_[3].position = DxVector3{ 1.0f, -1.0f, 0.0f };
    vertices_[3].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
    vertices_[3].uv = DxVector2{ 1.0f, 1.0f };

    init_vertices_ = vertices_;
}

HRESULT Object::CreateVertexBuffer()
{
    CreateVertexData();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DefaultVertex) * vertices_.size(); // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &vertices_.at(0);
    assert(SUCCEEDED(device_->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 채우는 CPU 메모리 주소
        vertex_buffer_.GetAddressOf())));

    return TRUE;
}

void Object::CreateIndexData()
{
    if (indices_.size() > 0)
    {
        return;
    }

    indices_.resize(6);

    indices_[0] = 0; indices_[1] = 1; indices_[2] = 2;
    indices_[3] = 2; indices_[4] = 1; indices_[5] = 3;

    face_ = indices_.size() / 3;
}

HRESULT Object::CreateIndexBuffer()
{
    CreateIndexData();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DWORD) * indices_.size(); // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &indices_.at(0);
    assert(SUCCEEDED(device_->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &index_buffer_)));

    return TRUE;
}

void Object::CreateConstantData()
{
    D3DXMatrixIdentity(&constant_buffer_data.world_matrix);
    D3DXMatrixIdentity(&constant_buffer_data.view_matrix);
    D3DXMatrixIdentity(&constant_buffer_data.projection_matrix);

    constant_buffer_data.timer = 0.0f;

    D3DXMatrixTranspose(&constant_buffer_data.world_matrix, &constant_buffer_data.world_matrix);
    D3DXMatrixTranspose(&constant_buffer_data.view_matrix, &constant_buffer_data.view_matrix);
    D3DXMatrixTranspose(&constant_buffer_data.projection_matrix, &constant_buffer_data.projection_matrix);
}

HRESULT Object::CreateConstantBuffer()
{
    CreateConstantData();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(ConstantBuffer) * 1; // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = constant_buffer_.GetAddressOf();
    assert(SUCCEEDED(device_->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU 메모리 주소
        constant_buffer_.GetAddressOf())));

    return TRUE;
}

HRESULT Object::CreateShader(std::wstring shaderFile)
{
    shader_ = ShaderManager::GetInstance()->Load(shaderFile);
    if (shader_)
    {
        vertex_shader_ = shader_->vertex_shader_;
        pixel_shader_ = shader_->pixel_shader_;
        vertex_shader_code_ = shader_->vertex_shader_code_;
        pixel_shader_code_ = shader_->pixel_shader_code_;

        return TRUE;
    }

    return E_FAIL;
}

HRESULT Object::CreateInputLayout()
{
    if (!vertex_shader_code_)
    {
        return E_FAIL;
    }

    // 정의
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT elements = ARRAYSIZE(layout);

    // 생성
    assert(SUCCEEDED(device_->CreateInputLayout(layout, elements, shader_->vertex_shader_code_->GetBufferPointer(),
        shader_->vertex_shader_code_->GetBufferSize(), &input_layout_)));

    return TRUE;
}

HRESULT Object::CreateTexture(std::wstring texture_file)
{
    texture_ = TextureManager::GetInstance()->Load(texture_file);
    if (texture_)
    {
        return TRUE;
    }

    return E_FAIL;
}

void Object::UpdateVertexBuffer()
{
    device_context_->UpdateSubresource(vertex_buffer_.Get(), NULL, NULL, &vertices_.at(0), 0, 0);
}

void Object::UpdateConstantBuffer()
{
    constant_buffer_data.world_matrix = world_matrix_.Transpose();
    constant_buffer_data.view_matrix = view_matrix_.Transpose();
    constant_buffer_data.projection_matrix = projection_matrix_.Transpose();

    device_context_->UpdateSubresource(constant_buffer_.Get(), NULL, NULL, constant_buffer_.GetAddressOf(), 0, 0);
}

HRESULT Object::LoadTexture(W_STR texture_file)
{
    texture_ = TextureManager::GetInstance()->Load(texture_file);
    if (texture_)
    {
        shader_resource_view_ = texture_->shader_resource_view_;

        return TRUE;
    }

    return E_FAIL;
}

ID3D11Buffer* DX::CreateVertexBuffer(ID3D11Device* device, void* data_address, UINT vertex_count, UINT vertex_size)
{
    ID3D11Buffer* vertex_buffer = nullptr;
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = vertex_count * vertex_size; // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼 용도
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = data_address;
    assert(SUCCEEDED(device->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU 메모리 주소
        &vertex_buffer)));

    return vertex_buffer;
}
