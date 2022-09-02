#pragma once

class Graphics
{
private:
	D3D_DRIVER_TYPE _driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL _featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGIFactory* _pFactory = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	ID3D11RenderTargetView* _pRenderTargetView = nullptr;
	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr;
	ID3DBlob* _pVertexShaderCode = nullptr;
	ID3DBlob* _pPixelShaderCode = nullptr;

public:
	// �ʱ�ȭ
	HRESULT Init(const IWND& iWnd);
	// ������
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();

	// ����̽� ����
	HRESULT CreateDevice();
	// ���丮 ����
	HRESULT CreateFactory();
	// ����ü�� ����
	HRESULT CreateSwapChain(const IWND& iWnd);
	// ����Ÿ�ٺ� ����
	HRESULT CreateRenderTargetView();
	// ����Ʈ ����
	HRESULT CreateViewport(const IWND& iWnd);
	// ���� ���� ����
	HRESULT CreateVertexBuffer();
	// ���̴� ����
	HRESULT CreateShader();
	// �Է� ���̾ƿ� ����
	HRESULT CreateInputLayout();
};

