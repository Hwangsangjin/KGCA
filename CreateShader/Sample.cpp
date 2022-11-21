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
	// 토포롤지 설정
	d3d11_device_context_.Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 정점 버퍼 설정
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3d11_device_context_.Get()->IASetVertexBuffers(0, 1, vertex_buffer_.GetAddressOf(), &stride, &offset);

	// 정점 셰이더 설정
	d3d11_device_context_.Get()->VSSetShader(vertex_shader_.Get(), nullptr, 0);

	// 픽셀 셰이더 설정
	d3d11_device_context_.Get()->PSSetShader(pixel_shader_.Get(), nullptr, 0);

	// 입력 레이아웃 설정
	d3d11_device_context_.Get()->IASetInputLayout(input_layout_.Get());

	// 그리기
	d3d11_device_context_.Get()->Draw(3, 0);

	return TRUE;
}

HRESULT Sample::Release()
{
	return TRUE;
}

HRESULT Sample::CreateVertexBuffer()
{
	// 정점 좌표
	Vertex vertices[] =
	{
		0.0f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f
	};
	UINT vertex_size = ARRAYSIZE(vertices);

	// 버퍼 구조체
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(Vertex) * vertex_size;	// 생성되는 버퍼 크기(바이트 단위)
	bd.Usage = D3D11_USAGE_DEFAULT;					// 생성되는 버퍼의 읽기 및 쓰기 방법 지정
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		// 정점 버퍼 파이프라인 바인딩
	bd.CPUAccessFlags = 0;							// CPU가 생성되는 버퍼에 접근하는 유형 지정
	bd.MiscFlags = 0;								// 추가 옵션 플래그
	bd.StructureByteStride = 0;						// 구조화된 버퍼를 사용할 경우에 구조체 버퍼의 크기(바이트 단위)

	// 서브리소스 데이터
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = vertices;							// 초기화 데이터에 대한 포인터
	sd.SysMemPitch = 0;								// 텍스처 리소스의 한줄의 크기(바이트 단위)
	sd.SysMemSlicePitch = 0;						// 3차원 텍스처의 깊이의 간격(바이트 단위)

	// 버퍼 생성
	assert(SUCCEEDED(d3d11_device_.Get()->CreateBuffer(
		&bd, // 버퍼 할당
		&sd, // 초기 할당된 버퍼를 채우는 CPU 메모리 주소
		vertex_buffer_.GetAddressOf())));

	return TRUE;
}

HRESULT Sample::CreateShader()
{
    Microsoft::WRL::ComPtr<ID3DBlob> pErrorCode;

    // 정점 셰이더 컴파일 
    assert(SUCCEEDED(D3DCompileFromFile(L"../../Resource/Shader/Sample.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, vertex_shader_code_.GetAddressOf(), pErrorCode.GetAddressOf())));

    // 정점 셰이더 생성
	assert(SUCCEEDED(d3d11_device_.Get()->CreateVertexShader(vertex_shader_code_->GetBufferPointer(), vertex_shader_code_->GetBufferSize(), nullptr, vertex_shader_.GetAddressOf())));

    // 픽셀 셰이더 컴파일  
	assert(SUCCEEDED(D3DCompileFromFile(L"../../Resource/Shader/Sample.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, pixel_shader_code_.GetAddressOf(), pErrorCode.GetAddressOf())));

    // 픽셀 셰이더 생성
	assert(SUCCEEDED(d3d11_device_.Get()->CreatePixelShader(pixel_shader_code_->GetBufferPointer(), pixel_shader_code_->GetBufferSize(), nullptr, pixel_shader_.GetAddressOf())));

	return TRUE;
}

HRESULT Sample::CreateInputLayout()
{
	if (!vertex_shader_code_)
	{
		return E_FAIL;
	}

	// 입력 레이아웃 정의
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// 입력 레이아웃 생성
	assert(SUCCEEDED(d3d11_device_.Get()->CreateInputLayout(layout, numElements, vertex_shader_code_->GetBufferPointer(), vertex_shader_code_->GetBufferSize(), input_layout_.GetAddressOf())));

	return TRUE;
}
