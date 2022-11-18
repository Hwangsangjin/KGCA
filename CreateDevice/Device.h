#pragma once

#include <wrl.h>
#include <d3d11.h>

#pragma comment	(lib, "d3d11.lib")
#pragma comment (lib, "dxgi")

class Device
{
protected:
	// ����̽� ��ü
	Microsoft::WRL::ComPtr<ID3D11Device> _pd3dDevice;
	// ����̽� ���ؽ�Ʈ ��ü
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _pImmediateContext;
	// ���丮 ��ü
	Microsoft::WRL::ComPtr<IDXGIFactory> _pFactory;
	// ����ü�� ��ü
	Microsoft::WRL::ComPtr<IDXGISwapChain> _pSwapChain;
	// ���� ����Ÿ�� ��
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _pRenderTargetView;

	// Ư�� ���� �Ӽ���
	D3D_FEATURE_LEVEL _featureLevel;
	// ����̹� Ÿ�� �Ӽ���
	D3D_DRIVER_TYPE _driverType;
	// ����ü�� �Ӽ���
	DXGI_SWAP_CHAIN_DESC _swapChainDesc;
	// �� ��Ʈ �Ӽ���
	D3D11_VIEWPORT _viewport;

public:
	Device() = default;
	virtual ~Device() = default;

	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	HRESULT PreRender();
	virtual HRESULT Render();
	HRESULT PostRender();
	// �޸� ����
	virtual HRESULT Release();

	// ����̽� ����
	HRESULT CreateDevice();
	// ���丮 ����
	HRESULT CreateFactory();
	// ����ü�� ����
	HRESULT CreateSwapChain();

	// ����Ÿ�ٺ� ����
	HRESULT SetRenderTargetView();
	// ����Ʈ ����
	HRESULT SetViewport();

	// ����̽� ��ü ����
	HRESULT CleanupDevice();
};

