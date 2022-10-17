#pragma once

#include "Camera.h"
#include "Actor.h"
#include "Shape.h"

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

	ShapeBox* _pBox = nullptr;
	Camera* _pMainCamera = nullptr;

	Actor* _pRyan = nullptr;
	std::vector<Object*> _pObjects;
};

