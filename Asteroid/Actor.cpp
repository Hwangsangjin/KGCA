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

	// 컴포넌트 삭제 필요
	// ~Component가 RemoveComponent를 호출하므로 다른 스타일의 루프가 필요
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
		// 컴포넌트에 대한 첫 번째 프로세스 입력
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
	// 정렬된 벡터에서 삽입점 찾기
	// (자신보다 높은 차수의 첫 번째 요소)
	int myOrder = component->GetUpdateOrder();
	auto iter = _components.begin();
	for (; iter != _components.end(); iter++)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// 반복자 위치 앞에 요소를 삽입
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
