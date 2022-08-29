#include "pch.h"
#include "Graphics.h"
#include "Vertex.h"

HRESULT Graphics::Init(const WindowInfo& info)
{
    if (FAILED(InitDevice(info))) return E_FAIL;
    if (FAILED(InitShader())) return E_FAIL;

	return TRUE;
}

HRESULT Graphics::InitDevice(const WindowInfo& info)
{
    if (FAILED(CreateDevice())) return E_FAIL;
    if (FAILED(CreateDXGIDevice())) return E_FAIL;
    if (FAILED(CreateSwapChain(info))) return E_FAIL;
    if (FAILED(CreateRenderTargetView())) return E_FAIL;

    CreateViewport(info);

    return TRUE;
}

HRESULT Graphics::InitShader()
{
    if (FAILED(CreateVertexBuffer())) return E_FAIL;
    if (FAILED(CreateVertexShader())) return E_FAIL;
    if (FAILED(CreatePixelShader())) return E_FAIL;
    if (FAILED(CreateVertexLayout())) return E_FAIL;

    return TRUE;
}

HRESULT Graphics::Frame()
{
	return TRUE;
}

HRESULT Graphics::PreRender()
{
    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, NULL);
    float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, color);

    return TRUE;
}

HRESULT Graphics::Render()
{
    if (FAILED(PreRender())) return E_FAIL;

    UINT stride = sizeof(Vertex);   // 정점 1개의 바이트 용량
    UINT offset = 0;                // 정점 버퍼에서 출발 지점(바이트)
    // 레지스터리
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetInputLayout(_pVertexLayout);
    _pImmediateContext->VSSetShader(_pVertexShader, NULL, 0);
    _pImmediateContext->HSSetShader(NULL, NULL, 0);
    _pImmediateContext->DSSetShader(NULL, NULL, 0);
    _pImmediateContext->GSSetShader(NULL, NULL, 0);
    _pImmediateContext->PSSetShader(_pPixelShader, NULL, 0);
    _pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _pImmediateContext->Draw(6, 0);

    if (FAILED(PostRender())) return E_FAIL;

    return TRUE;
}

HRESULT Graphics::PostRender()
{
    _pSwapChain->Present(0, 0);

    return TRUE;
}

HRESULT Graphics::Release()
{
    if (FAILED(ReleaseDevice())) return E_FAIL;
    if (FAILED(ReleaseShader())) return E_FAIL;

	return TRUE;
}

HRESULT Graphics::ReleaseDevice()
{
    if (_pd3dDevice) _pd3dDevice->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pGIFactory) _pGIFactory->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();

    return TRUE;
}

HRESULT Graphics::ReleaseShader()
{
    if (_pVertexBuffer) _pVertexBuffer->Release();
    if (_pVertexLayout) _pVertexLayout->Release();
    if (_pVertexShader) _pVertexShader->Release();
    if (_pPixelShader) _pPixelShader->Release();
    if (_pVertexShaderCode) _pVertexShaderCode->Release();
    if (_pPixelShaderCode) _pPixelShaderCode->Release();

    return TRUE;
}

HRESULT Graphics::CreateDevice()
{
    HRESULT hr;
    D3D_FEATURE_LEVEL pFeatureLevel;
    UINT Flags = 0;
    D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT FeatureLevels = 1;
    hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION,
        &_pd3dDevice,
        &pFeatureLevel,
        &_pImmediateContext
    );

    return hr;
}

HRESULT Graphics::CreateDXGIDevice()
{
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pGIFactory);
    return hr;
    return TRUE;
}

HRESULT Graphics::CreateSwapChain(const WindowInfo& info)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = info.client.right;
    sd.BufferDesc.Height = info.client.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = info.hWnd;
    sd.Windowed = true;

    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    return _pGIFactory->CreateSwapChain(_pd3dDevice, &sd, &_pSwapChain);
}

HRESULT Graphics::CreateRenderTargetView()
{
    HRESULT hr;
    ID3D11Texture2D* pBackBuffer = nullptr;
    _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &_pRenderTargetView);
    pBackBuffer->Release();
    return hr;
}

void Graphics::CreateViewport(const WindowInfo& info)
{
    D3D11_VIEWPORT vp;
    vp.Width = info.client.right;
    vp.Height = info.client.bottom;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    _pImmediateContext->RSSetViewports(1, &vp);
}

HRESULT Graphics::CreateVertexBuffer()
{
    HRESULT hr;
    Vertex vertices[] =
    {
        // 반드시 시계 방향(앞면)으로 구성한다.
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // v0
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // v1
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // v2
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // v3
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // v4
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // v5
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f   // v6

    };
    UINT num = ARRAYSIZE(vertices);

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(Vertex) * num;    // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = vertices;
    hr = _pd3dDevice->CreateBuffer(
        &bd,    // 버퍼 할당
        &sd,    // 초기 할당된 버퍼를 채우는 CPU 메모리 주소
        &_pVertexBuffer);

    return hr;
}

HRESULT Graphics::CreateVertexShader()
{
    HRESULT hr;

    // 정점 셰이더 컴파일
    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(L"VertexShader.hlsl", NULL, NULL, "main", "vs_5_0", 0, 0, &_pVertexShaderCode, &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();  // IUnknown을 상속 받은 객체는 반드시 Release
        }
        return hr;
    }

    hr = _pd3dDevice->CreateVertexShader(_pVertexShaderCode->GetBufferPointer(), _pVertexShaderCode->GetBufferSize(), NULL, &_pVertexShader);

    return hr;
}

HRESULT Graphics::CreatePixelShader()
{
    HRESULT hr;

    // 픽셀 셰이더 컴파일
    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(L"PixelShader.hlsl", NULL, NULL, "main", "vs_5_0", 0, 0, &_pPixelShaderCode, &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();  // IUnknown을 상속 받은 객체는 반드시 Release
        }
        return hr;
    }

    hr = _pd3dDevice->CreatePixelShader(_pPixelShaderCode->GetBufferPointer(), _pPixelShaderCode->GetBufferSize(), NULL, &_pPixelShader);

    return hr;
}

HRESULT Graphics::CreateVertexLayout()
{
    HRESULT hr;

    // 정점 레이아웃은 정점 셰이더와 밀접한 관련이 있다.
    // 정점 레이아웃 생성시 사전에 정점 셰이더 생성이 필요하다.
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElements = ARRAYSIZE(ied);

    hr = _pd3dDevice->CreateInputLayout(ied, numElements, _pVertexShaderCode->GetBufferPointer(), _pVertexShaderCode->GetBufferSize(), &_pVertexLayout);

    return hr;
}
