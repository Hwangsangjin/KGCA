#include "pch.h"
#include "BaseObject.h"
#include "ShaderManager.h"

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
    _pImmediateContext->VSSetShader(_pShader->GetVS(), NULL, 0);
    _pImmediateContext->PSSetShader(_pShader->GetPS(), NULL, 0);

    _pImmediateContext->Draw(_vertices.size(), 0);

    return TRUE;
}

HRESULT BaseObject::Release()
{
    SAFE_RELEASE(_pVertexBuffer);
    SAFE_RELEASE(_pInputLayout);
    SAFE_RELEASE(_pShader);
    return TRUE;
}

HRESULT BaseObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;

    return TRUE;
}

HRESULT BaseObject::CreateObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring filename)
{
    HR(SetDevice(pd3dDevice, pImmediateContext));
    HR(CreateVertexBuffer());
    HR(CreateShader(filename));
    HR(CreateInputLayout());

    return TRUE;
}

HRESULT BaseObject::CreateVertexBuffer()
{
    _vertices.resize(6);
    _vertices[0].pos = Vector3{ -0.15f, 0.2f, 0.0f };
    _vertices[0].color = Vector4{ 0.0f, 0.0f, 1.0f, 1.0f };
    _vertices[1].pos = Vector3{ 0.15f, 0.2f , 0.0f };
    _vertices[1].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
    _vertices[2].pos = Vector3{ -0.15f, -0.2f, 0.0f };
    _vertices[2].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
    _vertices[3].pos = Vector3{ -0.15f, -0.2f, 0.0f };
    _vertices[3].color = Vector4{ 1.0f, 0.0f, 1.0f, 1.0f };
    _vertices[4].pos = Vector3{ 0.15f, 0.2f, 0.0f };
    _vertices[4].color = Vector4{ 0.0f, 1.0f, 0.0f, 1.0f };
    _vertices[5].pos = Vector3{ 0.15f, -0.2f, 0.0f };
    _vertices[5].color = Vector4{ 1.0f, 1.0f, 0.0f, 1.0f };
    UINT size = _vertices.size();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(Vertex) * size; // ����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���ۿ뵵
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_vertices.at(0);
    HR(_pd3dDevice->CreateBuffer(
        &bd, // ���� �Ҵ�
        &sd, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸� �ּ�
        &_pVertexBuffer));

    return TRUE;
}

HRESULT BaseObject::CreateShader(std::wstring filename)
{
    _pShader = SHADER->Load(filename);
    if (_pShader) return TRUE;

    return E_FAIL;
}

HRESULT BaseObject::CreateInputLayout()
{
    // ����
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElements = ARRAYSIZE(ied);

    // ����
    HR(_pd3dDevice->CreateInputLayout(ied, numElements, _pShader->GetVSCode()->GetBufferPointer(),
        _pShader->GetVSCode()->GetBufferSize(), &_pInputLayout));

    return TRUE;
}
