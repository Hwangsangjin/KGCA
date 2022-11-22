#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Collision.h"

struct SimpleVertex
{
	DxVector3 position;
	DxVector4 color;
	DxVector2 uv;
};

struct DefaultVertex
{
	DxVector3 position;
	DxVector3 normal;
	DxVector4 color;
	DxVector2 uv;
};

struct IndexWeightVertex
{
	DxVector4 index;
	DxVector4 weight;
};

struct ConstantBuffer
{
	DxMatrix world_matrix;
	DxMatrix view_matrix;
	DxMatrix projection_matrix;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float timer = 0.0f;
};

struct BoneBuffer
{
	DxMatrix bone_matrix[255];
};

class Object
{
public:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

	std::vector<DefaultVertex> init_vertices_;
	std::vector<DefaultVertex> vertices_;
	std::vector<DWORD> indices_;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_;
	Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer_;
	ConstantBuffer constant_buffer_data;
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer_;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_;

	std::wstring texture_name_;
	std::wstring shader_name_;
	Texture* texture_ = nullptr;
	Shader* shader_ = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader_;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader_;
	Microsoft::WRL::ComPtr<ID3DBlob> vertex_shader_code_;
	Microsoft::WRL::ComPtr<ID3DBlob> pixel_shader_code_;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view_;

	DxMatrix world_matrix_;
	DxMatrix view_matrix_;
	DxMatrix projection_matrix_;

	DxVector3 position_;

	DWORD face_ = 0;

	Object() {}
	virtual ~Object() {};

	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT PreRender();
	virtual HRESULT Render();
	virtual HRESULT PostRender();
	// 메모리 해제
	virtual HRESULT Release();

	// 공간 설정
	virtual void SetMatrix(DxMatrix* world_matrix, DxMatrix* view_matrix, DxMatrix* projection_matrix);

	// 디바이스 설정
	virtual HRESULT SetDevice(ID3D11Device* d3d11_device, ID3D11DeviceContext* d3d11_device_context);

	// 오브젝트 생성
	virtual HRESULT CreateObject(ID3D11Device* d3d11_device, ID3D11DeviceContext* d3d11_device_context, std::wstring shader_file, std::wstring texture_file);

	// 정점 데이터 생성
	virtual void CreateVertexData();
	// 정점 버퍼 생성
	virtual HRESULT CreateVertexBuffer();
	// 인덱스 데이터 생성
	virtual void CreateIndexData();
	// 인덱스 버퍼 생성
	virtual HRESULT CreateIndexBuffer();
	// 상수 데이터 생성
	virtual void CreateConstantData();
	// 상수 버퍼 생성
	virtual HRESULT CreateConstantBuffer();
	// 셰이더 생성
	virtual HRESULT CreateShader(std::wstring shader_file);
	// 입력 레이아웃 생성
	virtual HRESULT CreateInputLayout();
	// 텍스처 생성
	virtual HRESULT CreateTexture(std::wstring texture_file);

	// 정점 버퍼 설정 
	virtual void UpdateVertexBuffer();
	// 상수 버퍼 설정
	virtual void UpdateConstantBuffer();

	// 텍스처 로드
	virtual HRESULT LoadTexture(W_STR texture_file);
};

namespace DX
{
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* d3d_device, void* data_address, UINT vertex_count, UINT vertex_size);
}