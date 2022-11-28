#pragma once

class DxRenderTarget
{
public:
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view_;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view_;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view_;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> depth_stencil_shader_resource_view_;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D_;
	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_desc_;
	D3D11_TEXTURE2D_DESC texture2D_desc_;
	DXGI_FORMAT dxgi_format_;
	D3D11_VIEWPORT viewport_;

	D3D11_VIEWPORT old_viewport_[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	ID3D11RenderTargetView* old_render_target_view_;
	ID3D11DepthStencilView* old_depth_stencil_view_;

	HRESULT Init();
	HRESULT Frame();
	HRESULT Render();
	HRESULT Release();

	HRESULT CreateRenderTarget(ID3D11Device* device, ID3D11DeviceContext* device_context, float width, float height);
	HRESULT Apply(ID3D11DeviceContext* device_context, ID3D11RenderTargetView* render_target_view, ID3D11DepthStencilView* depth_stencil_view);
	HRESULT Begin(ID3D11DeviceContext* device_context);
	HRESULT End(ID3D11DeviceContext* device_context);
};

