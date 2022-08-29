#pragma once

class Graphics
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGIFactory* _pGIFactory = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	ID3D11RenderTargetView* _pRenderTargetView = nullptr;

	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11InputLayout* _pVertexLayout = nullptr;
	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3DBlob* _pVertexShaderCode = nullptr;
	ID3DBlob* _pPixelShaderCode = nullptr;

public:
	// �ʱ�ȭ
	HRESULT Init(const WindowInfo& info);
	HRESULT InitDevice(const WindowInfo& info);
	HRESULT InitShader();
	// ���
	HRESULT Frame();
	// ������
	HRESULT PreRender();
	HRESULT Render();
	HRESULT PostRender();
	// �Ҹ� �� ����
	HRESULT Release();
	HRESULT ReleaseDevice();
	HRESULT ReleaseShader();

	// ����̽� ����
	HRESULT CreateDevice();
	// ���丮 ����
	HRESULT CreateDXGIDevice();
	// ����ü�� ����
	HRESULT CreateSwapChain(const WindowInfo& info);
	// ����Ÿ�Ϻ� ����
	HRESULT CreateRenderTargetView();
	// ����Ʈ ����
	HRESULT CreateViewport(const WindowInfo& info);

	// ���� ���� ����
	HRESULT CreateVertexBuffer();
	// ���� ���̴� ����
	HRESULT CreateVertexShader();
	// �ȼ� ���̴� ����
	HRESULT CreatePixelShader();
	// ���� ���̾ƿ� ����
	HRESULT CreateVertexLayout();
};

