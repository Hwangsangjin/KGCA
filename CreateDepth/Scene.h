#pragma once

class Scene
{
public:
	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT Render();
	// �޸� ����
	virtual HRESULT Release();

	void CreateScene(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmedtateContext);
	void AddObject(class Object* pObject);

private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	class Camera* _pMainCamera = nullptr;
	class Actor* _pRyan = nullptr;
	class ShapeBox* _pBox = nullptr;
	class ShapeBox* _pBox2 = nullptr;

	std::vector<Object*> _pObjects;
};

