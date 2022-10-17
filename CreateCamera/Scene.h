#pragma once

#include "Shape.h"
#include "Camera.h"
#include "Object2D.h"

class Scene
{
public:
	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT Render();
	// 메모리 해제
	virtual HRESULT Release();

	void CreateScene(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmedtateContext);
	void AddObject(class Object* pObject);

private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	ShapeBox* _pBox = nullptr;
	Camera* _pMainCamera = nullptr;

	Object2D* _pRyan = nullptr;
	std::vector<Object*> _pObjects;
};

