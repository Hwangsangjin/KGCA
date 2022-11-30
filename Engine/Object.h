#pragma once

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

struct ConstantData
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

class Texture;
class Shader;

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
	ConstantData constant_data;
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer_;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_;

	std::wstring texture_name_;
	std::wstring shader_name_;
	std::shared_ptr<Texture> texture_;
	std::shared_ptr<Shader> shader_;
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

	// ����̽� ����
	virtual HRESULT SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context);

	// ���� ����
	virtual void SetMatrix(DxMatrix* world_matrix, DxMatrix* view_matrix, DxMatrix* projection_matrix);

	// ������Ʈ ����
	virtual HRESULT CreateObject(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring shader_file, std::wstring texture_file);

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

	// ���� ���� ������Ʈ
	virtual void UpdateVertexBuffer();
	// ��� ���� ������Ʈ
	virtual void UpdateConstantBuffer();
};

namespace DX
{
	// ���� ���� ����
	Microsoft::WRL::ComPtr<ID3D11Buffer> CreateVertexBuffer(ID3D11Device* device, void* data_address, UINT vertex_count, UINT vertex_size);
}