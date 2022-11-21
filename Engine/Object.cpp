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
    device_context_->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);
    device_context_->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    device_context_->IASetInputLayout(_pInputLayout);
    device_context_->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
    device_context_->VSSetShader(_pVertexShader, NULL, 0);
    device_context_->PSSetShader(_pPixelShader, NULL, 0);
    device_context_->PSSetShaderResources(0, 1, &_pShaderResourceView);

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
        device_context_->Draw(_vertices.size(), 0);
    }
    else
    {
        //device_context_->DrawIndexed(_face * 3, 0, 0);
        device_context_->DrawIndexed(_indices.size(), 0, 0);
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

void Object::SetMatrix(DxMatrix* pWorld, DxMatrix* pView, DxMatrix* pProjection)
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
    device_ = pd3dDevice;
    device_context_ = pImmediateContext;

    return TRUE;
}

HRESULT Object::CreateObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring shaderFile, std::wstring textureFile)
{
    assert(SUCCEEDED(SetDevice(pd3dDevice, pImmediateContext)));
    assert(SUCCEEDED(CreateVertexBuffer()));
    assert(SUCCEEDED(CreateIndexBuffer()));
    assert(SUCCEEDED(CreateConstantBuffer()));
    assert(SUCCEEDED(CreateShader(shaderFile)));
    assert(SUCCEEDED(CreateInputLayout()));

    if (SUCCEEDED(LoadTexture(textureFile)))
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

    _vertices[0].position = DxVector3{ -1.0f, 1.0f, 0.0f };
    _vertices[0].color = DxVector4{ 0.0f, 0.0f, 1.0f, 1.0f };
    _vertices[0].uv = DxVector2{ 0.0f, 0.0f };
    _vertices[1].position = DxVector3{ 1.0f, 1.0f , 0.0f };
    _vertices[1].color = DxVector4{ 0.0f, 1.0f, 0.0f, 1.0f };
    _vertices[1].uv = DxVector2{ 1.0f, 0.0f };
    _vertices[2].position = DxVector3{ -1.0f, -1.0f, 0.0f };
    _vertices[2].color = DxVector4{ 1.0f, 0.0f, 1.0f, 1.0f };
    _vertices[2].uv = DxVector2{ 0.0f, 1.0f };
    _vertices[3].position = DxVector3{ 1.0f, -1.0f, 0.0f };
    _vertices[3].color = DxVector4{ 1.0f, 1.0f, 0.0f, 1.0f };
    _vertices[3].uv = DxVector2{ 1.0f, 1.0f };

    _init = _vertices;
}

HRESULT Object::CreateVertexBuffer()
{
    CreateVertexData();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DefaultVertex) * _vertices.size(); // ����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���ۿ뵵
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_vertices.at(0);
    assert(SUCCEEDED(device_->CreateBuffer(
        &bd, // ���� �Ҵ�
        &sd, // �ʱ� �Ҵ�� ���۸� ä��� CPU �޸� �ּ�
        &_pVertexBuffer)));

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
    bd.ByteWidth = sizeof(DWORD) * _indices.size(); // ����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���ۿ뵵
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_indices.at(0);
    assert(SUCCEEDED(device_->CreateBuffer(
        &bd, // ���� �Ҵ�
        &sd, // �ʱ� �Ҵ�� ���۸� ü��� CPU�޸� �ּ�
        &_pIndexBuffer)));

    return TRUE;
}

void Object::CreateConstantData()
{
    D3DXMatrixIdentity(&_constantBuffer.world);
    D3DXMatrixIdentity(&_constantBuffer.view);
    D3DXMatrixIdentity(&_constantBuffer.projection);

    _constantBuffer.timer = 0.0f;

    D3DXMatrixTranspose(&_constantBuffer.world, &_constantBuffer.world);
    D3DXMatrixTranspose(&_constantBuffer.view, &_constantBuffer.view);
    D3DXMatrixTranspose(&_constantBuffer.projection, &_constantBuffer.projection);
}

HRESULT Object::CreateConstantBuffer()
{
    CreateConstantData();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(ConstantBuffer) * 1; // ����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���ۿ뵵
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_constantBuffer;
    assert(SUCCEEDED(device_->CreateBuffer(
        &bd, // ���� �Ҵ�
        &sd, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸� �ּ�
        &_pConstantBuffer)));

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

    // ����
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElements = ARRAYSIZE(ied);

    // ����
    assert(SUCCEEDED(device_->CreateInputLayout(ied, numElements, _pShader->_pVertexShaderCode->GetBufferPointer(),
        _pShader->_pVertexShaderCode->GetBufferSize(), &_pInputLayout)));

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
    device_context_->UpdateSubresource(_pVertexBuffer, NULL, NULL, &_vertices.at(0), 0, 0);
}

void Object::UpdateConstantBuffer()
{
    _constantBuffer.world = _world.Transpose();
    _constantBuffer.view = _view.Transpose();
    _constantBuffer.projection = _projection.Transpose();

    device_context_->UpdateSubresource(_pConstantBuffer, NULL, NULL, &_constantBuffer, 0, 0);
}

HRESULT Object::LoadTexture(W_STR filename)
{
    _pTexture = TEXTURE->Load(filename);
    if (_pTexture)
    {
        _pShaderResourceView = _pTexture->_pShaderResourceView;

        return TRUE;
    }

    return E_FAIL;
}

ID3D11Buffer* DX::CreateVertexBuffer(ID3D11Device* pd3dDevice, void* pDataAddress, UINT vertexCount, UINT vertexSize)
{
    ID3D11Buffer* pVertexBuffer = nullptr;
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = vertexCount * vertexSize; // ����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = pDataAddress;
    assert(SUCCEEDED(pd3dDevice->CreateBuffer(
        &bd, // ���� �Ҵ�
        &sd, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸� �ּ�
        &pVertexBuffer)));

    return pVertexBuffer;
}
