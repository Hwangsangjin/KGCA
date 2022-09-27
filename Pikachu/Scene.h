#pragma once

#include "Core.h"
#include "Background.h"
#include "BattleText.h"
#include "DynamicText.h"
#include "StaticText.h"
#include "Map.h"
#include "Cloud.h"
#include "Wave.h"
#include "Player.h"
#include "PlayerScore.h"
#include "PlayerShadow.h"
#include "Enemy.h"
#include "EnemyScore.h"
#include "EnemyShadow.h"
#include "Ball.h"
#include "BallShadow.h"
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
	DynamicText* _pDynamicText = nullptr;
	StaticText* _pPokeMonText = nullptr;
	StaticText* _pCompanyText = nullptr;
	Map* _pMap = nullptr;
	Cloud* _pCloud = nullptr;
	Wave* _pWave = nullptr;
	Player* _pPlayer = nullptr;
	PlayerScore* _pPlayerScore = nullptr;
	PlayerShadow* _pPlayerShadow = nullptr;
	Enemy* _pEnemy = nullptr;
	EnemyScore* _pEnemyScore = nullptr;
	EnemyShadow* _pEnemyShadow = nullptr;
	Ball* _pBall = nullptr;
	BallShadow* _pBallShadow = nullptr;

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

