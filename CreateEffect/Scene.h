#pragma once

#include "Core.h"
#include "Background.h"
#include "BattleText.h"
#include "Map.h"
#include "Cloud.h"
#include "Wave.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Effect.h"

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

	Background* _pBackground = nullptr;
	BattleText* _pBattleText = nullptr;
	Map* _pMap = nullptr;
	Cloud* _pCloud = nullptr;
	Wave* _pWave = nullptr;
	Player* _pPlayer = nullptr;
	Enemy* _pEnemy = nullptr;
	Ball* _pBall = nullptr;

	std::vector<Object*> _pObjects;
	std::list<Effect*> _pEffects;

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

	// ������Ʈ �߰�
	void AddObject(Object* pObject);

	// ����Ʈ �߰�
	void AddEffect();
};

