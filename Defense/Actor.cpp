#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	: _state(Active)
	, _position(Vector2::Zero)
	, _scale(1.0f)
	, _rotation(0.0f)
	, _game(game)
{
	_game->AddActor(this);
}

Actor::~Actor()
{
	_game->RemoveActor(this);

	// ������Ʈ ���� �ʿ�
	// ~Component�� RemoveComponent�� ȣ���ϹǷ� �ٸ� ��Ÿ���� ������ �ʿ�
	while (!_components.empty())
	{
		delete _components.back();
	}
}

void Actor::Update(float deltaTime)
{
	UpdateComponents(deltaTime);
	UpdateActor(deltaTime);
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto component : _components)
	{
		component->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (_state == Active)
	{
		// ������Ʈ�� ���� ù ��° ���μ��� �Է�
		for (auto component : _components)
		{
			component->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::AddComponent(Component* component)
{
	// ���ĵ� ���Ϳ��� ������ ã��
	// (�ڽź��� ���� ������ ù ��° ���)
	int myOrder = component->GetUpdateOrder();
	auto iter = _components.begin();
	for (; iter != _components.end(); iter++)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// �ݺ��� ��ġ �տ� ��Ҹ� ����
	_components.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(_components.begin(), _components.end(), component);
	if (iter != _components.end())
	{
		_components.erase(iter);
	}
}
