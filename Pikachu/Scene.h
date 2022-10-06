#pragma once

#include "Core.h"
#include "Background.h"
#include "BattleText.h"
#include "DynamicText.h"
#include "StaticText.h"
#include "SelectText.h"
#include "GameStartText.h"
#include "GameOverText.h"
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

	Background* _pBackground = nullptr;
	BattleText* _pBattleText = nullptr;
	DynamicText* _pVolleyballText = nullptr;
	StaticText* _pPokeMonText = nullptr;
	StaticText* _pCompanyText = nullptr;
	SelectText* _pSinglePlayText = nullptr;
	SelectText* _pMultiPlayText = nullptr;
	GameStartText* _pGameStartText = nullptr;
	GameOverText* _pGameOverText = nullptr;

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
	Object2D* _pNet1 = nullptr;
	Object2D* _pNet2 = nullptr;
	Object2D* _pNet3 = nullptr;
	Object2D* _pNet4 = nullptr;

	std::vector<Object*> _pObjects;
	std::list<Effect*> _pEffects;

public:
	// 플래그
	bool _isSelect = false;

	bool _isGameStart = false;
	bool _isGameOver = false;

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

	// 이펙트 추가
	void AddEffect(Object2D* pObject);
};

