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
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    _pImmediateContext->IASetInputLayout(_pInputLayout);
    _pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
    _pImmediateContext->VSSetShader(_pVertexShader, NULL, 0);
    _pImmediateContext->PSSetShader(_pPixelShader, NULL, 0);
    _pImmediateContext->PSSetShaderResources(0, 1, &_pShaderResourceView);

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
    if (!_pIndexBuffer)
    {
        _pImmediateContext->Draw(_vertices.size(), 0);
    }
    else
    {
        _pImmediateContext->DrawIndexed(_face * 3, 0, 0);
    }

    return TRUE;
}

HRESULT Object::Release()
{
    SAFE_RELEASE(_pVertexBuffer);
    SAFE_RELEASE(_pIndexBuffer);
    SAFE_RELEASE(_pConstantBuffer);
    SAFE_RELEASE(_pInputLayout);

    return TRUE;
}

void Object::SetMatrix(MyMatrix* pWorld, MyMatrix* pView, MyMatrix* pProjection)
{
    if (pWorld)
    {
        _world = *pWorld;
    }

    if (pView)
    {
        _view = *pView;
    }

    if (pProjection)
    {
        _projection = *pProjection;
    }

    UpdateConstantBuffer();
}

HRESULT Object::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;

    return TRUE;
}

HRESULT Object::CreateObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring shaderFile, std::wstring textureFile)
{
    HR(SetDevice(pd3dDevice, pImmediateContext));
    HR(CreateVertexBuffer());
    HR(CreateIndexBuffer());
    HR(CreateConstantBuffer());
    HR(CreateShader(shaderFile));
    HR(CreateInputLayout());

    _pTexture = TEXTURE->Load(textureFile);
    if (_pTexture)
    {
        _pShaderResourceView = _pTexture->_pShaderResourceView;
    }

    if (FAILED(Init()))
    {
        return E_FAIL;
    }

    return TRUE;
}

void Object::CreateVertexData()
{
    if (_vertices.size() > 0)
    {
        _init = _vertices;

        return;
    }

    _vertices.resize(4);

    _vertices[0].position = MyVector3{ -1.0f, 1.0f, 0.0f };
    _vertices[0].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
    _vertices[0].uv = MyVector2{ 0.0f, 0.0f };
    _vertices[1].position = MyVector3{ 1.0f, 1.0f , 0.0f };
    _vertices[1].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
    _vertices[1].uv = MyVector2{ 1.0f, 0.0f };
    _vertices[2].position = MyVector3{ -1.0f, -1.0f, 0.0f };
    _vertices[2].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
    _vertices[2].uv = MyVector2{ 0.0f, 1.0f };
    _vertices[3].position = MyVector3{ 1.0f, -1.0f, 0.0f };
    _vertices[3].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
    _vertices[3].uv = MyVector2{ 1.0f, 1.0f };

    _init = _vertices;
}

HRESULT Object::CreateVertexBuffer()
{
    CreateVertexData();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(Vertex) * _vertices.size(); // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_vertices.at(0);
    HR(_pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU 메모리 주소
        &_pVertexBuffer));

    return TRUE;
}

void Object::CreateIndexData()
{
    if (_indices.size() > 0)
    {
        return;
    }

    _indices.resize(6);

    _indices[0] = 0; _indices[1] = 1; _indices[2] = 2;
    _indices[3] = 2; _indices[4] = 1; _indices[5] = 3;

    _face = _indices.size() / 3;
}

HRESULT Object::CreateIndexBuffer()
{
    CreateIndexData();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DWORD) * _indices.size(); // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_indices.at(0);
    HR(_pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &_pIndexBuffer));

    return TRUE;
}

void Object::CreateConstantData()
{
    _constantBuffer.world.Identity();
    _constantBuffer.view.Identity();
    _constantBuffer.projection.Identity();

    _constantBuffer.world.Transpose();
    _constantBuffer.view.Transpose();
    _constantBuffer.projection.Transpose();
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
    sd.pSysMem = &_constantBuffer;
    HR(_pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU 메모리 주소
        &_pConstantBuffer));

    return TRUE;
}

HRESULT Object::CreateShader(std::wstring shaderFile)
{
    _pShader = SHADER->Load(shaderFile);
    if (_pShader)
    {
        _pVertexShader = _pShader->_pVertexShader;
        _pPixelShader = _pShader->_pPixelShader;
        _pVertexShaderCode = _pShader->_pVertexShaderCode;
        _pPixelShaderCode = _pShader->_pPixelShaderCode;

        return TRUE;
    }

    return E_FAIL;
}

HRESULT Object::CreateInputLayout()
{
    if (!_pVertexShaderCode)
    {
        return E_FAIL;
    }

    // 정의
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElements = ARRAYSIZE(ied);

    // 생성
    HR(_pd3dDevice->CreateInputLayout(ied, numElements, _pShader->_pVertexShaderCode->GetBufferPointer(),
        _pShader->_pVertexShaderCode->GetBufferSize(), &_pInputLayout));

    return TRUE;
}

HRESULT Object::CreateTexture(std::wstring textureFile)
{
    _pTexture = TEXTURE->Load(textureFile);
    if (_pTexture)
    {
        return TRUE;
    }

    return E_FAIL;
}

void Object::UpdateVertexBuffer()
{
    _pImmediateContext->UpdateSubresource(_pVertexBuffer, NULL, NULL, &_vertices.at(0), 0, 0);
}

void Object::UpdateConstantBuffer()
{
    _constantBuffer.world = _world.Transpose();
    _constantBuffer.view = _view.Transpose();
    _constantBuffer.projection = _projection.Transpose();

    _pImmediateContext->UpdateSubresource(_pConstantBuffer, NULL, NULL, &_constantBuffer, 0, 0);
}
