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

	// �ʱ�ȭ
	HRESULT Init();
	// ������ ���
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	static HRESULT Release();

	// ���÷� ���� ����
	static HRESULT SetSamplerState(ID3D11Device* device);
};

