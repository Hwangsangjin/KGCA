#pragma once

class Device
{
protected:
	// 디바이스 객체
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	// 디바이스 컨텍스트 객체
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;
	// 팩토리 객체
	Microsoft::WRL::ComPtr<IDXGIFactory> factory_;
	// 스왑체인 객체
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
	// 메인 렌더타겟 뷰
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view_;

	// 드라이버 타입 속성값
	D3D_DRIVER_TYPE driver_type_ = D3D_DRIVER_TYPE_NULL;
	// 특성 레벨 속성값
	D3D_FEATURE_LEVEL feature_level_ = D3D_FEATURE_LEVEL_11_1;
	// 스왑체인 속성값
	DXGI_SWAP_CHAIN_DESC swap_chain_desc_;
	// 뷰 포트 속성값
	D3D11_VIEWPORT viewport_;

public:
	// 생성자, 소멸자
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

	// 렌더타겟뷰 설정
	HRESULT SetRenderTargetView();
	// 뷰포트 설정
	HRESULT SetViewport();

	// 디바이스 객체 정리
	HRESULT CleanupDevice();

	// 화면 크기 조정
	HRESULT ResizeDevice(UINT width, UINT height);

	// 리소스 생성, 삭제
	virtual HRESULT CreateResource();
	virtual HRESULT DeleteResource();
};

