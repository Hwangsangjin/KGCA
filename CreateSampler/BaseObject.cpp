#include "pch.h"
#include "BaseObject.h"
#include "ShaderManager.h"
#include "TextureManager.h"

HRESULT BaseObject::Init()
{
    return TRUE;
}

HRESULT BaseObject::Frame()
{
    return TRUE;
}

HRESULT BaseObject::Render()
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetInputLayout(_pInputLayout);
    _pImmediateContext->VSSetShader(_pShader->_pVertexShader, NULL, 0);
    _pImmediateContext->PSSetShader(_pShader->_pPixelShader, NULL, 0);
    _pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _pImmediateContext->PSSetShaderResources(0, 1, &_pTexture->_pShaderResourceView);

    _pImmediateContext->Draw(_vertices.size(), 0);

    return TRUE;
}

HRESULT BaseObject::Release()
{
    SAFE_RELEASE(_pVertexBuffer);
    SAFE_RELEASE(_pInputLayout);
    SAFE_RELEASE(_pShader);
    SAFE_RELEASE(_pTexture);
    return TRUE;
}

HRESULT BaseObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;

    return TRUE;
}

HRESULT BaseObject::CreateObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring shaderFile, std::wstring textureFile)
{
    HR(SetDevice(pd3dDevice, pImmediateContext));
    HR(CreateVertexBuffer());
    HR(CreateShader(shaderFile));
    HR(CreateInputLayout());
    HR(CreateTexture(textureFile));

    return TRUE;
}

HRESULT BaseObject::CreateVertexBuffer()
{
    _vertices.resize(6);
    _vertices[0].position = Vector3{ -0.1f, 0.2f, 0.0f };
    _vertices[0].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
    _vertices[0].uv = Vector2{ 0.0f, 0.0f };

    _vertices[1].position = Vector3{ 0.1f, 0.2f , 0.0f };
    _vertices[1].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
    _vertices[1].uv = Vector2{ 1.0f, 0.0f };

    _vertices[2].position = Vector3{ -0.1f, -0.2f, 0.0f };
    _vertices[2].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
    _vertices[2].uv = Vector2{ 0.0f, 1.0f };

    _vertices[3].position = Vector3{ -0.1f, -0.2f, 0.0f };
    _vertices[3].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
    _vertices[3].uv = Vector2{ 0.0f, 1.0f };

    _vertices[4].position = Vector3{ 0.1f, 0.2f, 0.0f };
    _vertices[4].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
    _vertices[4].uv = Vector2{ 1.0f, 0.0f };

    _vertices[5].position = Vector3{ 0.1f, -0.2f, 0.0f };
    _vertices[5].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
    _vertices[5].uv = Vector2{ 1.0f, 1.0f };
    UINT size = _vertices.size();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(Vertex) * size; // 바이트 용량
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

HRESULT BaseObject::CreateShader(std::wstring shaderFile)
{
    _pShader = SHADER->Load(shaderFile);
    if (_pShader)
    {
        return TRUE;
    }

    return E_FAIL;
}

HRESULT BaseObject::CreateInputLayout()
{
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

HRESULT BaseObject::CreateTexture(std::wstring textureFile)
{
    _pTexture = TEXTURE->Load(textureFile);
    if (_pTexture)
    {
        return TRUE;
    }

    return E_FAIL;
}
