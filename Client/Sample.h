#pragma once

#include "Core.h"
#include "Object2D.h"
#include "Player2D.h"

class Sample : public Core
{
private:
	POINT _pos{ 0, 0 };
	std::vector<Object*> _objects;

	Object2D* _sky = nullptr;
	Object2D* _mountain = nullptr;
	Object2D* _cloud = nullptr;
	Object2D* _ground = nullptr;
	Object2D* _net = nullptr;
	Player2D* _player = nullptr;
	Object2D* _ball = nullptr;

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

	// ���� ������Ʈ �߰�
	void AddObject(Object* object);
};

