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
	// 초기화
	HRESULT Init(const WindowInfo& info);
	// 실시간 계산
	HRESULT Frame();
	// 실시간 렌더링
	HRESULT Render();
	// 소멸 및 삭제
	HRESULT Release();

	// 디바이스 생성
	HRESULT CreateDevice();
	// 팩토리 생성
	HRESULT CreateDXGIDevice();
	// 스왑체인 생성
	HRESULT CreateSwapChain();
	// 렌더타켓뷰 생성
	HRESULT CreateRenderTargetView();
	// 뷰포트 설정
	void CreateViewport();
};

