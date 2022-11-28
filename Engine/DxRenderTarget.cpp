#include "pch.h"
#include "DxRenderTarget.h"

HRESULT DxRenderTarget::Init()
{
	return TRUE;
}

HRESULT DxRenderTarget::Frame()
{
	return TRUE;
}

HRESULT DxRenderTarget::Render()
{
	return TRUE;
}

HRESULT DxRenderTarget::Release()
{
	return TRUE;
}

HRESULT DxRenderTarget::CreateRenderTarget(ID3D11Device* device, ID3D11DeviceContext* device_context, float width, float height)
{
	viewport_.Width = width;
	viewport_.Height = height;
	viewport_.TopLeftX = 0;
	viewport_.TopLeftY = 0;
	viewport_.MinDepth = 0.0f;
	viewport_.MaxDepth = 1.0f;

	texture2D_desc_.Width = (UINT)width;
	texture2D_desc_.Height = (UINT)height;
	texture2D_desc_.MipLevels = 1;
	texture2D_desc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texture2D_desc_.SampleDesc.Count = 1;
	texture2D_desc_.SampleDesc.Quality = 0;
	texture2D_desc_.Usage = D3D11_USAGE_DEFAULT;
	texture2D_desc_.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texture2D_desc_.CPUAccessFlags = 0;
	texture2D_desc_.MiscFlags = 0;
	texture2D_desc_.ArraySize = 1;

	assert(device->CreateTexture2D(&texture2D_desc_, nullptr, texture2D_.GetAddressOf()));
	assert(device->CreateShaderResourceView(texture2D_.Get(), nullptr, shader_resource_view_.GetAddressOf()));
	assert(device->CreateRenderTargetView(texture2D_.Get(), nullptr, render_target_view_.GetAddressOf()));

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D = nullptr;
	D3D11_TEXTURE2D_DESC texture2D_desc;
	texture2D_desc.Width = width;
	texture2D_desc.Height = height;
	texture2D_desc.MipLevels = 1;
	texture2D_desc.ArraySize = 1;
	texture2D_desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	texture2D_desc.SampleDesc.Count = 1;
	texture2D_desc.SampleDesc.Quality = 0;
	texture2D_desc.Usage = D3D11_USAGE_DEFAULT;
	texture2D_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	texture2D_desc.CPUAccessFlags = 0;
	texture2D_desc.MiscFlags = 0;

	assert(device->CreateTexture2D(&texture2D_desc, nullptr, texture2D.GetAddressOf()));

	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	ZeroMemory(&depth_stencil_view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	assert(device->CreateDepthStencilView(texture2D.Get(), &depth_stencil_view_desc, depth_stencil_view_.GetAddressOf()));

	D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc;
	ZeroMemory(&shader_resource_view_desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shader_resource_view_desc.Texture2D.MipLevels = 1;
	shader_resource_view_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;

	assert(device->CreateShaderResourceView(texture2D.Get(), &shader_resource_view_desc, depth_stencil_shader_resource_view_.GetAddressOf()));

	return TRUE;
}

HRESULT DxRenderTarget::Apply(ID3D11DeviceContext* device_context, ID3D11RenderTargetView* render_target_view, ID3D11DepthStencilView* depth_stencil_view)
{
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> nullptr_render_target_view;
	device_context->OMSetRenderTargets(1, nullptr_render_target_view.GetAddressOf(), nullptr);

	if (device_context)
	{
		if (depth_stencil_view)
		{
			device_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);
		}
		else
		{
			device_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view_.Get());
		}
	}
	else
	{
		if (depth_stencil_view)
		{
			device_context->OMSetRenderTargets(1, render_target_view_.GetAddressOf(), depth_stencil_view);
		}
		else
		{
			device_context->OMSetRenderTargets(1, render_target_view_.GetAddressOf(), depth_stencil_view_.Get());
		}
	}

	device_context->RSSetViewports(1, &viewport_);

	return TRUE;
}

HRESULT DxRenderTarget::Begin(ID3D11DeviceContext* device_context)
{
	device_context->RSSetViewports(1, &viewport_);
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view = nullptr;
	device_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), nullptr);
	device_context->OMSetRenderTargets(1, render_target_view_.GetAddressOf(), depth_stencil_view_.Get());
	
	const float color[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	device_context->ClearRenderTargetView(render_target_view_.Get(), color);
	device_context->ClearDepthStencilView(depth_stencil_view_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return TRUE;
}

HRESULT DxRenderTarget::End(ID3D11DeviceContext* device_context)
{
	device_context->RSSetViewports(1, old_viewport_);
	device_context->OMSetRenderTargets(1, &old_render_target_view_, old_depth_stencil_view_);

	return TRUE;
}
