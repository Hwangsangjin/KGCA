#pragma once

class Graphics
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGIFactory* _pFactory = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	ID3D11RenderTargetView* _pRenderTargetView = nullptr;

public:
	// �ʱ�ȭ
	HRESULT Init(const IWND& iWnd);
	HRESULT InitDevice(const IWND& iWnd);
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
};

