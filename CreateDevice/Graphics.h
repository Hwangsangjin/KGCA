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
	// 초기화
	HRESULT Init(const WindowInfo& gInfo);
	HRESULT InitDevice(const WindowInfo& gInfo);
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
	HRESULT CreateSwapChain(const WindowInfo& gInfo);
	// 렌더타겟뷰 생성
	HRESULT CreateRenderTargetView();
	// 뷰포트 설정
	HRESULT CreateViewport(const WindowInfo& gInfo);
};

