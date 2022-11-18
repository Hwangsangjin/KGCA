#pragma once

#include <wrl.h>
#include <d3d11.h>

#pragma comment	(lib, "d3d11.lib")
#pragma comment (lib, "dxgi")

class Device
{
protected:
	// 디바이스 객체
	Microsoft::WRL::ComPtr<ID3D11Device> _pd3dDevice;
	// 디바이스 컨텍스트 객체
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _pImmediateContext;
	// 팩토리 객체
	Microsoft::WRL::ComPtr<IDXGIFactory> _pFactory;
	// 스왑체인 객체
	Microsoft::WRL::ComPtr<IDXGISwapChain> _pSwapChain;
	// 메인 렌더타겟 뷰
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _pRenderTargetView;

	// 특성 레벨 속성값
	D3D_FEATURE_LEVEL _featureLevel;
	// 드라이버 타입 속성값
	D3D_DRIVER_TYPE _driverType;
	// 스왑체인 속성값
	DXGI_SWAP_CHAIN_DESC _swapChainDesc;
	// 뷰 포트 속성값
	D3D11_VIEWPORT _viewport;

public:
	Device() = default;
	virtual ~Device() = default;

	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	HRESULT PreRender();
	virtual HRESULT Render();
	HRESULT PostRender();
	// 메모리 해제
	virtual HRESULT Release();

	// 디바이스 생성
	HRESULT CreateDevice();
	// 팩토리 생성
	HRESULT CreateFactory();
	// 스왑체인 생성
	HRESULT CreateSwapChain();

	// 렌더타겟뷰 설정
	HRESULT SetRenderTargetView();
	// 뷰포트 설정
	HRESULT SetViewport();

	// 디바이스 객체 정리
	HRESULT CleanupDevice();
};

