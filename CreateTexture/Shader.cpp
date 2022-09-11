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
    SAFE_RELEASE(_pVertexShader);
    SAFE_RELEASE(_pPixelShader);
    SAFE_RELEASE(_pVertexShaderCode);
    SAFE_RELEASE(_pPixelShaderCode);

    return TRUE;
}

void Shader::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;
}

HRESULT Shader::CreateShader(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring filename)
{
    // µð¹ÙÀÌ½º ¼³Á¤
    SetDevice(pd3dDevice, pImmediateContext);

    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    // Á¤Á¡ ¼ÎÀÌ´õ ÄÄÆÄÀÏ 
    hr = D3DCompileFromFile(filename.c_str(), NULL, NULL, "VS", "vs_5_0", 0, 0, &_pVertexShaderCode, &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }

        return hr;
    }

    // Á¤Á¡ ¼ÎÀÌ´õ »ý¼º
    hr = _pd3dDevice->CreateVertexShader(_pVertexShaderCode->GetBufferPointer(), _pVertexShaderCode->GetBufferSize(), NULL, &_pVertexShader);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }

        return hr;
    }

    // ÇÈ¼¿ ¼ÎÀÌ´õ ÄÄÆÄÀÏ  
    hr = D3DCompileFromFile(filename.c_str(), NULL, NULL, "PS", "ps_5_0", 0, 0, &_pPixelShaderCode, &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }

        return hr;
    }

    // ÇÈ¼¿ ¼ÎÀÌ´õ »ý¼º
    hr = _pd3dDevice->CreatePixelShader(_pPixelShaderCode->GetBufferPointer(), _pPixelShaderCode->GetBufferSize(), NULL, &_pPixelShader);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }

        return hr;
    }

    return hr;
}
