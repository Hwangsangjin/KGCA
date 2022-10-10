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

	// Game�� ȣ���ϴ� ProcessInput �Լ� (�����ǵ��� ����)
	void ProcessInput(const uint8_t* keyState);
	// Ư�� ���͸� ���� �Է� �ڵ� (������ ��)
	virtual void ActorInput(const uint8_t* keyState);

	// ���Ϳ� ����
	const Vector2& GetPosition() const { return _position; }
	void SetPosition(const Vector2& position) { _position = position; }
	float GetScale() const { return _scale; }
	void SetScale(float scale) { _scale = scale; }
	float GetRotation() const { return _rotation; }
	void SetRotation(float rotation) { _rotation = rotation; }

	Vector2 GetForward() const { return Vector2(Math::Cos(_rotation), -Math::Sin(_rotation)); }

	State GetState() const { return _state; }
	void SetState(State state) { _state = state; }

	class Game* GetGame() { return _game; }

	// ������Ʈ �߰�, ����
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

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

