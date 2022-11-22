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

	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT PreRender();
	virtual HRESULT Render();
	virtual HRESULT PostRender();
	// �޸� ����
	virtual HRESULT Release();

	// ���� ����
	virtual void SetMatrix(DxMatrix* world_matrix, DxMatrix* view_matrix, DxMatrix* projection_matrix);

	// ����̽� ����
	virtual HRESULT SetDevice(ID3D11Device* d3d11_device, ID3D11DeviceContext* d3d11_device_context);

	// ������Ʈ ����
	virtual HRESULT CreateObject(ID3D11Device* d3d11_device, ID3D11DeviceContext* d3d11_device_context, std::wstring shader_file, std::wstring texture_file);

	// ���� ������ ����
	virtual void CreateVertexData();
	// ���� ���� ����
	virtual HRESULT CreateVertexBuffer();
	// �ε��� ������ ����
	virtual void CreateIndexData();
	// �ε��� ���� ����
	virtual HRESULT CreateIndexBuffer();
	// ��� ������ ����
	virtual void CreateConstantData();
	// ��� ���� ����
	virtual HRESULT CreateConstantBuffer();
	// ���̴� ����
	virtual HRESULT CreateShader(std::wstring shader_file);
	// �Է� ���̾ƿ� ����
	virtual HRESULT CreateInputLayout();
	// �ؽ�ó ����
	virtual HRESULT CreateTexture(std::wstring texture_file);

	// ���� ���� ���� 
	virtual void UpdateVertexBuffer();
	// ��� ���� ����
	virtual void UpdateConstantBuffer();

	// �ؽ�ó �ε�
	virtual HRESULT LoadTexture(W_STR texture_file);
};

namespace DX
{
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* d3d_device, void* data_address, UINT vertex_count, UINT vertex_size);
}