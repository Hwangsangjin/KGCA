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
	assert(SUCCEEDED(CreateConstantBuffer()));
	assert(SUCCEEDED(CreateShader()));
	assert(SUCCEEDED(CreateInputLayout()));

	return TRUE;
}

HRESULT Sample::Frame()
{
	const float elapsed_time = Timer::GetInstance()->GetElapsedTime();
	const float bounded_time = cosf(elapsed_time) * 0.5f + 0.5f;

	D3D11_MAPPED_SUBRESOURCE mapped_subresource;
	device_context_->Map(constant_buffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);

	ConstantData* constant_data = (ConstantData*)mapped_subresource.pData;
	constant_data->color[0] = cosf(elapsed_time);
	constant_data->color[1] = sinf(elapsed_time);
	constant_data->color[2] = 1.0f - cosf(elapsed_time);
	constant_data->color[3] = 1.0f;
	constant_data->time = bounded_time;

	device_context_->Unmap(constant_buffer_.Get(), 0);

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

	// ��� ���� ����
	device_context_->VSSetConstantBuffers(0, 1, constant_buffer_.GetAddressOf());

	// ���� ���̴� ����
	device_context_->VSSetShader(vertex_shader_.Get(), nullptr, 0);

	// �ȼ� ���̴� ����
	device_context_->PSSetShader(pixel_shader_.Get(), nullptr, 0);

	// �Է� ���̾ƿ� ����
	device_context_->IASetInputLayout(input_layout_.Get());

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
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
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

HRESULT Sample::CreateConstantBuffer()
{
	// ���� ����ü
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(ConstantData);				// �����Ǵ� ���� ũ��(����Ʈ ����)
	buffer_desc.Usage = D3D11_USAGE_DYNAMIC;					// �����Ǵ� ������ �б� �� ���� ��� ����
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			// ��� ���� ���������� ���ε�
	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		// CPU�� �����Ǵ� ���ۿ� �����ϴ� ���� ����
	buffer_desc.MiscFlags = 0;									// �߰� �ɼ� �÷���
	buffer_desc.StructureByteStride = 0;						// ����ȭ�� ���۸� ����� ��쿡 ����ü ������ ũ��(����Ʈ ����)

	// ���� ����
	assert(SUCCEEDED(device_->CreateBuffer(
		&buffer_desc,		// ���� �Ҵ�
		nullptr,			// �ʱ� �Ҵ�� ���۸� ä��� CPU �޸� �ּ�
		constant_buffer_.GetAddressOf())));

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

	// ����
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT elements = ARRAYSIZE(layout);

	// ����
	assert(SUCCEEDED(device_->CreateInputLayout(layout, elements, vertex_shader_code_->GetBufferPointer(), vertex_shader_code_->GetBufferSize(), input_layout_.GetAddressOf())));

	return TRUE;
}
