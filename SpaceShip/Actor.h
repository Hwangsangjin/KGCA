#pragma once

#include <vector>
#include "Math.h"

class Actor
{
public:
	// ������ ���¸� �����ϴµ� ���ȴ�.
	enum State
	{
		Active,
		Paused,
		Dead
	};

	// ������
	Actor(class Game* game);
	// �Ҹ���
	virtual ~Actor();

	// Game���� ȣ���ϴ� Update �Լ� (���� �Լ� �ƴ�)
	void Update(float deltaTime);

	// ���Ϳ� ������ ��� ������Ʈ�� ������Ʈ (���� �Լ� �ƴ�)
	void UpdateComponents(float deltaTime);

	// Ư�� ���Ϳ� Ưȭ�� ������Ʈ �ڵ� (�������̵� ����)
	virtual void UpdateActor(float deltaTime);

	// 
	const Vector2& GetPosition() const { return _position; }

private:
	// ������ ����
	State _state;

	// ��ȯ
	Vector2 _position;	// ������ �߽���
	float _scale;		// ������ ���� (100%�� ��� 1.0f)
	float _rotation;	// ȸ�� ���� (����)

	// �� ���Ͱ� ������ ������Ʈ��
	std::vector<class Component*> _components;
	class Game* _game;
};

