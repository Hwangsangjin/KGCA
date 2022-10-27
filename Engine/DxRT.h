#pragma once

class DxRT
{
public:
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _pDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _pShaderResourceView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _pDSShaderResourceView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> _pTexture;
	D3D11_DEPTH_STENCIL_VIEW_DESC _depthStencilDesc;
	D3D11_TEXTURE2D_DESC _textureDesc;
	DXGI_FORMAT _dxgiFormat;
	D3D11_VIEWPORT _viewport;

	D3D11_VIEWPORT _oldViewport[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	ID3D11RenderTargetView* _pOldRenderTargetView;
	ID3D11DepthStencilView* _pOldDepthStencilView;

	HRESULT Init();
	HRESULT Frame();
	HRESULT Render();
	HRESULT Release();

	HRESULT CreateRenderTarget(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, float width, float height);
	HRESULT Apply(ID3D11DeviceContext* pImmediateContext, ID3D11RenderTargetView* pRenderTargetView, ID3D11DepthStencilView* pDepthStencilView);
	HRESULT Begin(ID3D11DeviceContext* pImmediateContext);
	HRESULT End(ID3D11DeviceContext* pImmediateContext);
};

