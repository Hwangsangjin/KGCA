#pragma once

#include "Core.h"
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

	std::vector<Object*> _objects;

	Tile* _sky = nullptr;
	Tile* _mountain = nullptr;
	Tile* _ground = nullptr;
	Tile* _net = nullptr;
	Cloud* _cloud = nullptr;
	Wave* _wave = nullptr;
	Player* _player = nullptr;
	Enemy* _enemy = nullptr;
	Ball* _ball = nullptr;

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

