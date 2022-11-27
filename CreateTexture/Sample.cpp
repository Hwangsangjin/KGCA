#include "pch.h"
#include "Sample.h"
#include "Timer.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Sample sample;
	sample.SetWindow(hInstance, L"Client", 800, 600);
	sample.Run();

	return 0;
}

HRESULT Sample::Init()
{
	assert(SUCCEEDED(CreateVertexBuffer()));
	assert(SUCCEEDED(CreateIndexBuffer()));
	assert(SUCCEEDED(CreateShader()));
	assert(SUCCEEDED(CreateInputLayout()));
	assert(SUCCEEDED(CreateTexture()));

	return TRUE;
}

HRESULT Sample::Frame()
{
	return TRUE;
}

HRESULT Sample::Render()
{
	// �������� ����
	device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ���� ���� ����
	UINT stride = sizeof(SampleVertex);
	UINT offset = 0;
	device_context_->IASetVertexBuffers(0, 1, vertex_buffer_.GetAddressOf(), &stride, &offset);

	// �ε��� ���� ����
	device_context_->IASetIndexBuffer(index_buffer_.Get(), DXGI_FORMAT_R16_UINT, 0);

	// �Է� ���̾ƿ� ����
	device_context_->IASetInputLayout(input_layout_.Get());

	// ���� ���̴� ����
	device_context_->VSSetShader(vertex_shader_.Get(), nullptr, 0);

	// �����Ͷ����� ���� ����
	D3D11_RASTERIZER_DESC rasterizer_desc;
	ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));
	rasterizer_desc.DepthClipEnable = TRUE;
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_NONE;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state;
	device_->CreateRasterizerState(&rasterizer_desc, rasterizer_state.GetAddressOf());
	device_context_->RSSetState(rasterizer_state.Get());

	// �ȼ� ���̴� ����
	device_context_->PSSetShader(pixel_shader_.Get(), nullptr, 0);

	// �ȼ� ���̴� ���ҽ� ����
	device_context_->PSSetShaderResources(0, 1, shader_resource_view_.GetAddressOf());

	// ���÷� ���� ����
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state;
	device_->CreateSamplerState(&sampler_desc, sampler_state.GetAddressOf());
	device_context_->PSSetSamplers(0, 1, sampler_state.GetAddressOf());

	// �׸���
	device_context_->DrawIndexed(6, 0, 0);

	return TRUE;
}

HRESULT Sample::Release()
{
	return TRUE;
}

HRESULT Sample::CreateVertexBuffer()
{
	// ���� ��ǥ
	SampleVertex vertices[] =
	{
		-1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		0.0f, 1.0f
	};
	UINT vertex_size = ARRAYSIZE(vertices);

	// ���� ����ü
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(SampleVertex) * vertex_size;	// �����Ǵ� ���� ũ��(����Ʈ ����)
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;					// �����Ǵ� ������ �б� �� ���� ��� ����
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;			// ���� ���� ���������� ���ε�
	buffer_desc.CPUAccessFlags = 0;								// CPU�� �����Ǵ� ���ۿ� �����ϴ� ���� ����
	buffer_desc.MiscFlags = 0;									// �߰� �ɼ� �÷���
	buffer_desc.StructureByteStride = 0;						// ����ȭ�� ���۸� ����� ��쿡 ����ü ������ ũ��(����Ʈ ����)

	// ���긮�ҽ� ������
	D3D11_SUBRESOURCE_DATA subresource_data;
	subresource_data.pSysMem = vertices;						// �ʱ�ȭ �����Ϳ� ���� ������
	subresource_data.SysMemPitch = 0;							// �ؽ�ó ���ҽ��� ������ ũ��(����Ʈ ����)
	subresource_data.SysMemSlicePitch = 0;						// 3���� �ؽ�ó�� ������ ����(����Ʈ ����)

	// ���� ����
	assert(SUCCEEDED(device_->CreateBuffer(
		&buffer_desc,		// ���� �Ҵ�
		&subresource_data,	// �ʱ� �Ҵ�� ���۸� ä��� CPU �޸� �ּ�
		vertex_buffer_.GetAddressOf())));

	return TRUE;
}

HRESULT Sample::CreateIndexBuffer()
{
	// �ε��� ��ǥ
	WORD indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
	UINT index_size = ARRAYSIZE(indices);

	// ���� ����ü
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(SampleVertex) * index_size;	// �����Ǵ� ���� ũ��(����Ʈ ����)
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;					// �����Ǵ� ������ �б� �� ���� ��� ����
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;			// �ε��� ���� ���������� ���ε�
	buffer_desc.CPUAccessFlags = 0;								// CPU�� �����Ǵ� ���ۿ� �����ϴ� ���� ����
	buffer_desc.MiscFlags = 0;									// �߰� �ɼ� �÷���
	buffer_desc.StructureByteStride = 0;						// ����ȭ�� ���۸� ����� ��쿡 ����ü ������ ũ��(����Ʈ ����)

	// ���긮�ҽ� ������
	D3D11_SUBRESOURCE_DATA subresource_data;
	subresource_data.pSysMem = indices;							// �ʱ�ȭ �����Ϳ� ���� ������
	subresource_data.SysMemPitch = 0;							// �ؽ�ó ���ҽ��� ������ ũ��(����Ʈ ����)
	subresource_data.SysMemSlicePitch = 0;						// 3���� �ؽ�ó�� ������ ����(����Ʈ ����)

	// ���� ����
	assert(SUCCEEDED(device_->CreateBuffer(
		&buffer_desc,		// ���� �Ҵ�
		&subresource_data,	// �ʱ� �Ҵ�� ���۸� ä��� CPU �޸� �ּ�
		index_buffer_.GetAddressOf())));

	return TRUE;
}

HRESULT Sample::CreateShader()
{
    Microsoft::WRL::ComPtr<ID3DBlob> error_code;

    // ���� ���̴� ������ 
    assert(SUCCEEDED(D3DCompileFromFile(L"Sample.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, vertex_shader_code_.GetAddressOf(), error_code.GetAddressOf())));

    // ���� ���̴� ����
	assert(SUCCEEDED(device_->CreateVertexShader(vertex_shader_code_->GetBufferPointer(), vertex_shader_code_->GetBufferSize(), nullptr, vertex_shader_.GetAddressOf())));

    // �ȼ� ���̴� ������  
	assert(SUCCEEDED(D3DCompileFromFile(L"Sample.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, pixel_shader_code_.GetAddressOf(), error_code.GetAddressOf())));

    // �ȼ� ���̴� ����
	assert(SUCCEEDED(device_->CreatePixelShader(pixel_shader_code_->GetBufferPointer(), pixel_shader_code_->GetBufferSize(), nullptr, pixel_shader_.GetAddressOf())));

	return TRUE;
}

HRESULT Sample::CreateInputLayout()
{
	// ���� ���̴� �ڵ尡 ���� ���
	if (!vertex_shader_code_)
	{
		return E_FAIL;
	}

	// �Է� ���̾ƿ� ����
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT elements = ARRAYSIZE(layout);

	// �Է� ���̾ƿ� ����
	assert(SUCCEEDED(device_->CreateInputLayout(layout, elements, vertex_shader_code_->GetBufferPointer(), vertex_shader_code_->GetBufferSize(), input_layout_.GetAddressOf())));

	return TRUE;
}

HRESULT Sample::CreateTexture()
{
	// �ؽ�ó ����
	assert(SUCCEEDED(DirectX::CreateWICTextureFromFile(device_.Get(), device_context_.Get(), L"KGCA.bmp", (ID3D11Resource**)texture2D_.GetAddressOf(), &shader_resource_view_)));

	// �ؽ�ó ����ü ����
	texture2D_->GetDesc(&texture2D_desc_);

	return TRUE;
}
