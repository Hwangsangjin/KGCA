#pragma once

class Scene
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	D3D11_VIEWPORT _viewport[4];

	class Camera* _pMainCamera = nullptr;
	class Camera* _pCamera[4];
	class Map* _pMap = nullptr;
	class Quadtree* _quadtree;
	class PixelCube* _pCube = nullptr;
	class TextureBox* _pBox = nullptr;
	class TextureBox* _pBox2 = nullptr;
	class Actor* _pActor = nullptr;

	std::vector<class Object3D*> _pObjects;
	std::vector<class FbxData*> _pFbxDatas;
	std::vector<class Actor*> _pActors;

	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT Render();
	// �޸� ����
	virtual HRESULT Release();

	void CreateScene(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmedtateContext);
	void AddObject(Object3D* pObject);
	void ClearDeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
};

