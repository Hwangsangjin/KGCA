#pragma once

#include "Core.h"
#include "Map.h"
#include "Tile.h"
#include "Cloud.h"
#include "Wave.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"

class Sample : public Core
{
private:
	POINT _pos{ 0, 0 };

	Sound* _bgm = nullptr;
	Sound* _effect1 = nullptr;
	Sound* _effect2 = nullptr;
	Sound* _effect3 = nullptr;
	Sound* _effect4 = nullptr;
	Sound* _effect5 = nullptr;
	Sound* _effect6 = nullptr;
	Sound* _effect7 = nullptr;

	Map* _map = nullptr;

	Tile* _sky = nullptr;
	Tile* _mountain = nullptr;
	Tile* _ground = nullptr;
	Tile* _net = nullptr;
	Cloud* _cloud = nullptr;
	Wave* _wave = nullptr;
	Player* _player = nullptr;
	Enemy* _enemy = nullptr;
	Ball* _ball = nullptr;

	std::vector<Object*> _objects;

public:
	Sample() = default;
	virtual ~Sample() = default;

	// 초기화
	virtual HRESULT Init() final;
	// 프레임 계산
	virtual HRESULT Frame() final;
	// 렌더
	virtual HRESULT Render() final;
	// 메모리 해제
	virtual HRESULT Release() final;

	// 오브젝트 추가
	void AddObject(Object* object);
};

