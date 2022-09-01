#include "pch.h"
#include "Graphics.h"
#include "Vertex.h"

// �ʱ�ȭ
HRESULT Graphics::Init(const IWND& iWnd)
{
    if (FAILED(CreateDevice()))
    {
        return E_FAIL;
    }

    if (FAILED(CreateFactory()))
    {
        return E_FAIL;
    }

    if (FAILED(CreateSwapChain(iWnd)))
    {
        return E_FAIL;
    }

    if (FAILED(CreateRenderTargetView()))
    {
        return E_FAIL;
    }

    if (FAILED(CreateViewport(iWnd)))
    {
        return E_FAIL;
    }

    if (FAILED(CreateVertexBuffer()))
    {
        return E_FAIL;
    }

    if (FAILED(CreateShader()))
    {
        return E_FAIL;
    }

    if (FAILED(CreateInputLayout()))
    {
        return E_FAIL;
    }

    return TRUE;
}

// ������
HRESULT Graphics::Frame()
{
    return TRUE;
}

// ����
HRESULT Graphics::Render()
{
    // �ĸ� ���� Ŭ����
    float color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, color);

    // �׷��Ƚ� ���������� ���ε�
    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, NULL);
    _pImmediateContext->IASetInputLayout(_pInputLayout);
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _pImmediateContext->VSSetShader(_pVertexShader, NULL, 0);
    _pImmediateContext->PSSetShader(_pPixelShader, NULL, 0);

    // �ﰢ�� �׸���
    _pImmediateContext->Draw(3, 0);

    // �ø���
    _pSwapChain->Present(0, 0);

    return TRUE;
}

// ������
HRESULT Graphics::Release()
{
    if (_pImmediateContext)
    {
        _pImmediateContext->ClearState();
    }

    if (_pInputLayout)
    {
        _pInputLayout->Release();
    }

    if (_pVertexBuffer)
    {
        _pVertexBuffer->Release();
    }

    if (_pVertexShader)
    {
        _pVertexShader->Release();
    }

    if (_pPixelShader)
    {
        _pPixelShader->Release();
    }

    if (_pRenderTargetView)
    {
        _pRenderTargetView->Release();
    }

    if (_pSwapChain)
    {
        _pSwapChain->Release();
    }

    if (_pFactory)
    {
        _pFactory->Release();
    }

    if (_pImmediateContext)
    {
        _pImmediateContext->Release();
    }

    if (_pd3dDevice)
    {
        _pd3dDevice->Release();
    }

    _pd3dDevice = nullptr;
    _pFactory = nullptr;
    _pSwapChain = nullptr;
    _pRenderTargetView = nullptr;
    _pImmediateContext = nullptr;
    _pPixelShader = nullptr;
    _pVertexShader = nullptr;
    _pVertexBuffer = nullptr;
    _pInputLayout = nullptr;

    return TRUE;
}

// ����̽�
HRESULT Graphics::CreateDevice()
{
    HRESULT hr;
    UINT createDeviceFlags = 0;
#ifdef _DEBUG

    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        _driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDevice(NULL, _driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &_pd3dDevice, &_featureLevel, &_pImmediateContext);

        if (SUCCEEDED(hr))
        {
            break;
        }
    }

    return hr;
}

// ���丮
HRESULT Graphics::CreateFactory()
{
    HRESULT hr;
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pFactory);

    return hr;
}

// ���� ü��
HRESULT Graphics::CreateSwapChain(const IWND& iWnd)
{
    HRESULT hr;
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = iWnd.width;
    sd.BufferDesc.Height = iWnd.height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.Windowed = true;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    hr = _pFactory->CreateSwapChain(_pd3dDevice, &sd, &_pSwapChain);

    return hr;
}

// ���� Ÿ�� ��
HRESULT Graphics::CreateRenderTargetView()
{
    HRESULT hr;
    ID3D11Texture2D* pBackBuffer = nullptr;
    _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &_pRenderTargetView);
    pBackBuffer->Release();

    return hr;
}

// �� ��Ʈ
HRESULT Graphics::CreateViewport(const IWND& iWnd)
{
    D3D11_VIEWPORT vp;
    vp.Width = iWnd.width;
    vp.Height = iWnd.height;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    _pImmediateContext->RSSetViewports(1, &vp);

    return TRUE;
}

// ���̴�
HRESULT Graphics::CreateShader()
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    // ���� ���̴� ������ 
    hr = D3DCompileFromFile(L"VertexShader.hlsl", NULL, NULL, "main", "vs_5_0", 0, 0, &_pVertexShaderCode, &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }

        return hr;
    }

    hr = _pd3dDevice->CreateVertexShader(_pVertexShaderCode->GetBufferPointer(), _pVertexShaderCode->GetBufferSize(), NULL, &_pVertexShader);

    // �ȼ� ���̴� ������  
    hr = D3DCompileFromFile(L"PixelShader.hlsl", NULL, NULL, "main", "ps_5_0", 0, 0, &_pPixelShaderCode, &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }

        return hr;
    }

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

// ��ǲ ���̾ƿ�
HRESULT Graphics::CreateInputLayout()
{
    HRESULT hr;

    // ����
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElements = ARRAYSIZE(layout);

    // ����
    hr = _pd3dDevice->CreateInputLayout(layout, numElements, _pVertexShaderCode->GetBufferPointer(),
        _pVertexShaderCode->GetBufferSize(), &_pInputLayout);

    return hr;
}

// ���� ����
HRESULT Graphics::CreateVertexBuffer()
{
    HRESULT hr;
    Vertex vertices[] =
    {
        0.0f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f
    };
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(Vertex) * 3; // ����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���ۿ뵵
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    //bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = vertices;
    hr = _pd3dDevice->CreateBuffer(
        &bd, // ���� �Ҵ�
        &sd, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸� �ּ�
        &_pVertexBuffer);

    return hr;
}
