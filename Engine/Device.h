#pragma once

class Device
{
protected:
	// ����̽� ��ü
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	// ����̽� ���ؽ�Ʈ ��ü
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;
	// ���丮 ��ü
	Microsoft::WRL::ComPtr<IDXGIFactory> factory_;
	// ����ü�� ��ü
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
	// ���� ����Ÿ�� ��
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view_;

	// ����̹� Ÿ�� �Ӽ���
	D3D_DRIVER_TYPE driver_type_ = D3D_DRIVER_TYPE_NULL;
	// Ư�� ���� �Ӽ���
	D3D_FEATURE_LEVEL feature_level_ = D3D_FEATURE_LEVEL_11_1;
	// ����ü�� �Ӽ���
	DXGI_SWAP_CHAIN_DESC swap_chain_desc_;
	// �� ��Ʈ �Ӽ���
	D3D11_VIEWPORT viewport_;

public:
	// ������, �Ҹ���
	Device() = default;
	virtual ~Device() = default;

	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT Render();
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

	// ȭ�� ũ�� ����
	HRESULT ResizeDevice(UINT width, UINT height);

	// ���ҽ� ����, ����
	virtual HRESULT CreateResource();
	virtual HRESULT DeleteResource();
};

