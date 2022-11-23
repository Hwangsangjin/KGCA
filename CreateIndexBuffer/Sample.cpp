#include "pch.h"
#include "Sample.h"

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
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(SampleVertex) * vertex_size;	// �����Ǵ� ���� ũ��(����Ʈ ����)
	bd.Usage = D3D11_USAGE_DEFAULT;					// �����Ǵ� ������ �б� �� ���� ��� ����
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		// ���� ���� ���������� ���ε�
	bd.CPUAccessFlags = 0;							// CPU�� �����Ǵ� ���ۿ� �����ϴ� ���� ����
	bd.MiscFlags = 0;								// �߰� �ɼ� �÷���
	bd.StructureByteStride = 0;						// ����ȭ�� ���۸� ����� ��쿡 ����ü ������ ũ��(����Ʈ ����)

	// ���긮�ҽ� ������
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = vertices;							// �ʱ�ȭ �����Ϳ� ���� ������
	sd.SysMemPitch = 0;								// �ؽ�ó ���ҽ��� ������ ũ��(����Ʈ ����)
	sd.SysMemSlicePitch = 0;						// 3���� �ؽ�ó�� ������ ����(����Ʈ ����)

	// ���� ����
	assert(SUCCEEDED(device_->CreateBuffer(
		&bd, // ���� �Ҵ�
		&sd, // �ʱ� �Ҵ�� ���۸� ä��� CPU �޸� �ּ�
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
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(SampleVertex) * index_size;	// �����Ǵ� ���� ũ��(����Ʈ ����)
	bd.Usage = D3D11_USAGE_DEFAULT;						// �����Ǵ� ������ �б� �� ���� ��� ����
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;				// �ε��� ���� ���������� ���ε�
	bd.CPUAccessFlags = 0;								// CPU�� �����Ǵ� ���ۿ� �����ϴ� ���� ����
	bd.MiscFlags = 0;									// �߰� �ɼ� �÷���
	bd.StructureByteStride = 0;							// ����ȭ�� ���۸� ����� ��쿡 ����ü ������ ũ��(����Ʈ ����)

	// ���긮�ҽ� ������
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = indices;								// �ʱ�ȭ �����Ϳ� ���� ������
	sd.SysMemPitch = 0;									// �ؽ�ó ���ҽ��� ������ ũ��(����Ʈ ����)
	sd.SysMemSlicePitch = 0;							// 3���� �ؽ�ó�� ������ ����(����Ʈ ����)

	// ���� ����
	assert(SUCCEEDED(device_->CreateBuffer(
		&bd, // ���� �Ҵ�
		&sd, // �ʱ� �Ҵ�� ���۸� ä��� CPU �޸� �ּ�
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
