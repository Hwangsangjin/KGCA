#pragma once

#include "Quadtree.h"
#include "FbxLoader.h"

class Scene
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	std::vector<FbxLoader*> _pFbxObjects;
	Quadtree _quadtree;
	D3D11_VIEWPORT _viewport[4];

	class Camera* _pMainCamera = nullptr;
	class Camera* _pCamera[4];
	class Map* _pMap = nullptr;
	class Actor* _pRyan = nullptr;
	class TextureBox* _pBox = nullptr;
	class TextureBox* _pBox2 = nullptr;
	class Cube* _pCube = nullptr;

	std::vector<class Object*> _pObjects;

	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT Render();
	// 메모리 해제
	virtual HRESULT Release();

	void CreateScene(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmedtateContext);
	void AddObject(Object* pObject);
};

