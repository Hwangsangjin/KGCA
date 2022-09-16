#pragma once

#include "Camera.h"
#include "Core.h"
#include "Map.h"
#include "Tile.h"
#include "Cloud.h"
#include "Wave.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"

class Scene
{
protected:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	Sound* _pBGM = nullptr;
	Sound* _pEffect1 = nullptr;
	Sound* _pEffect2 = nullptr;
	Sound* _pEffect3 = nullptr;
	Sound* _pEffect4 = nullptr;
	Sound* _pEffect5 = nullptr;
	Sound* _pEffect6 = nullptr;
	Sound* _pEffect7 = nullptr;

	Camera* _pCamera = nullptr;
	Map* _pMap = nullptr;
	Tile* _pSky = nullptr;
	Tile* _pMountain = nullptr;
	Tile* _pGround = nullptr;
	Tile* _pNet = nullptr;
	Cloud* _pCloud = nullptr;
	Wave* _pWave = nullptr;
	Player* _pPlayer = nullptr;
	Enemy* _pEnemy = nullptr;
	Ball* _pBall = nullptr;

	std::vector<Object*> _pObjects;

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

	// 오브젝트 추가
	void AddObject(Object* pObject);
};

