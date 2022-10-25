#pragma once

class DxRenderTarget
{
public:
	//Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _pRenderTargetView;
	//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _pDepthStencilView;
	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _pShaderResourceView;
	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _pDepthStencilView;
	D3D11_DEPTH_STENCILOP_DESC _DepthStencilDesc;
	D3D11_TEXTURE2D_DESC _TextureDesc;
	DXGI_FORMAT _dxgiFormat;
	D3D11_VIEWPORT _viewport;
	MyMatrix _projection;

	D3D11_VIEWPORT _oldViewport[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	UINT _viewports;
	ID3D11RenderTargetView* _pOldRenderTargetView;
	ID3D11DepthStencilView* _pOldDepthStencilView;

	DxRenderTarget();
	~DxRenderTarget() {}

	HRESULT Create(ID3D11Device* pd3dDevice);
	void Begin(ID3D11DeviceContext* pDeviceContext);
	void End();
	HRESULT Release();
};

