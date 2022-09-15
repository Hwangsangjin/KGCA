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

	// �ʱ�ȭ
	virtual HRESULT Init() final;
	// ������ ���
	virtual HRESULT Frame() final;
	// ����
	virtual HRESULT Render() final;
	// �޸� ����
	virtual HRESULT Release() final;

	// ������Ʈ �߰�
	void AddObject(Object* object);
};

