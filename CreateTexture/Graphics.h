#pragma once

class Graphics
{
private:
	D3D_DRIVER_TYPE _driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL _featureLevel = D3D_FEATURE_LEVEL_11_1;
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGIFactory* _pFactory = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	ID3D11RenderTargetView* _pRenderTargetView = nullptr;
	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr;
	ID3D11SamplerState* _pSamplerState = nullptr;
	ID3DBlob* _pVertexShaderCode = nullptr;
	ID3DBlob* _pPixelShaderCode = nullptr;
	ID3D11Texture2D* _pTexture = nullptr;
	ID3D11ShaderResourceView* _pShaderResourceView = nullptr;

public:
	// 초기화
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, UINT width, UINT height);
	HRESULT InitDevice(HINSTANCE hInstance, HWND hWnd, UINT width, UINT height);
	HRESULT InitShader();
	HRESULT InitScene();
	// 프레임
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();

	// 디바이스 생성
	HRESULT CreateDevice();
	// 팩토리 생성
	HRESULT CreateFactory();
	// 스왑체인 생성
	HRESULT CreateSwapChain(HWND hWnd, UINT width, UINT height);
	// 렌더타겟뷰 생성
	HRESULT CreateRenderTargetView();
	// 뷰포트 생성
	HRESULT CreateViewport(UINT width, UINT height);
	// 정점 버퍼 생성
	HRESULT CreateVertexBuffer();
	// 셰이더 생성
	HRESULT CreateShader();
	// 샘플러 생성
	HRESULT CreateSampler();
	// 텍스처 생성
	HRESULT CreateTexture();
	// 입력 레이아웃 생성
	HRESULT CreateInputLayout();
};


