#pragma once

class SamplerState
{
public:
	static Microsoft::WRL::ComPtr<ID3D11BlendState> alpha_blend_;
	static Microsoft::WRL::ComPtr<ID3D11SamplerState> default_wrap_;
	static Microsoft::WRL::ComPtr<ID3D11SamplerState> default_mirror_;
	static Microsoft::WRL::ComPtr<ID3D11RasterizerState> default_solid_;
	static Microsoft::WRL::ComPtr<ID3D11RasterizerState> default_wire_frame_;
	static Microsoft::WRL::ComPtr<ID3D11DepthStencilState> default_depth_stencil_;
	static Microsoft::WRL::ComPtr<ID3D11DepthStencilState> greater_depth_stencil_;

	// 초기화
	HRESULT Init();
	// 프레임 계산
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	static HRESULT Release();

	// 샘플러 상태 설정
	static HRESULT SetSamplerState(ID3D11Device* device);
};

