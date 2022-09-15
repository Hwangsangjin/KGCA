#pragma once

class Device
{
protected:
	D3D_DRIVER_TYPE _driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL _featureLevel = D3D_FEATURE_LEVEL_11_1;
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGIFactory* _pFactory = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	ID3D11RenderTargetView* _pRenderTargetView = nullptr;

public:
	Device() = default;
	virtual ~Device() = default;

	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT Render();
	// 메모리 해제
	virtual HRESULT Release();

	// 디바이스 생성
	HRESULT CreateDevice();
	// 팩토리 생성
	HRESULT CreateFactory();
	// 스왑체인 생성
	HRESULT CreateSwapChain();
	// 렌더타겟뷰 생성
	HRESULT CreateRenderTargetView();
	// 뷰포트 생성
	HRESULT CreateViewport();

	// 화면 리사이즈
	HRESULT ResizeDevice(UINT width, UINT height);
};

