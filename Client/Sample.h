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

