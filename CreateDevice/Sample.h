#pragma once

#include "Window.h"
#include <wrl.h>
#include <d3d11.h>

#pragma comment	(lib, "d3d11.lib")

class Sample : public Window
{
public:
	// ����̽� ��ü
	Microsoft::WRL::ComPtr<ID3D11Device> _pd3dDevice;
	// ����̽� ���ؽ�Ʈ ��ü
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _pImmediateContext;
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

	Sample() = default;
	virtual ~Sample() = default;

	// �ʱ�ȭ
	virtual HRESULT Init() override;
	// ������ ���
	virtual HRESULT Frame() override;
	// ����
	virtual HRESULT Render() override;
	// �޸� ����
	virtual HRESULT Release() override;
};

