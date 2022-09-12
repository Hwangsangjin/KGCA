#pragma once

#include "Core.h"

class Sample : public Core
{
private:
	POINT _pos{ 0, 0 };
	std::vector<Object*> _objects;

	Object2D* _map = nullptr;
	Object2D* _ground = nullptr;
	Object2D* _net = nullptr;
	Player2D* _player = nullptr;

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

