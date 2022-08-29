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
	// 초기화
	HRESULT Init(const WindowInfo& info);
	HRESULT InitDevice(const WindowInfo& info);
	HRESULT InitShader();
	// 계산
	HRESULT Frame();
	// 렌더링
	HRESULT PreRender();
	HRESULT Render();
	HRESULT PostRender();
	// 소멸 및 삭제
	HRESULT Release();
	HRESULT ReleaseDevice();
	HRESULT ReleaseShader();

	// 디바이스 생성
	HRESULT CreateDevice();
	// 팩토리 생성
	HRESULT CreateDXGIDevice();
	// 스왑체인 생성
	HRESULT CreateSwapChain(const WindowInfo& info);
	// 렌더타켓뷰 생성
	HRESULT CreateRenderTargetView();
	// 뷰포트 설정
	HRESULT CreateViewport(const WindowInfo& info);

	// 정점 버퍼 생성
	HRESULT CreateVertexBuffer();
	// 정점 셰이더 생성
	HRESULT CreateVertexShader();
	// 픽셀 셰이더 생성
	HRESULT CreatePixelShader();
	// 정점 레이아웃 생성
	HRESULT CreateVertexLayout();
};

