#pragma once

class Graphics
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGIFactory* _pGIFactory = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

public:
	// �ʱ�ȭ
	HRESULT Init(const WindowInfo& info);
	// �ǽð� ���
	HRESULT Frame();
	// �ǽð� ������
	HRESULT Render();
	// �Ҹ� �� ����
	HRESULT Release();

	// ����̽� ����
	HRESULT CreateDevice();
	// ���丮 ����
	HRESULT CreateDXGIDevice();
	// ����ü�� ����
	HRESULT CreateSwapChain();
	// ����Ÿ�Ϻ� ����
	HRESULT CreateRenderTargetView();
	// ����Ʈ ����
	void CreateViewport();
};

