#include "AIComponent.h"
#include "Actor.h"
#include "AIState.h"
#include <SDL/SDL_log.h>

AIComponent::AIComponent(Actor* owner)
	: Component(owner)
	, _currentState(nullptr)
{
}

void AIComponent::Update(float deltaTime)
{
	if (_currentState)
	{
		_currentState->Update(deltaTime);
	}
}

void AIComponent::ChangeState(const std::string& name)
{
	// 먼저 현재 상태를 빠져 나온다.
	if (_currentState)
	{
		_currentState->OnExit();
	}

	// 맵에서 새로운 상태를 찾는다.
	auto iter = _stateMap.find(name);
	if (iter != _stateMap.end())
	{
		_currentState = iter->second;

		// 새로운 상태로 진입한다.
		_currentState->OnEnter();
	}
	else
	{
		SDL_Log("Could not find AIState %s in state map", name.c_str());
		_currentState = nullptr;
	}
}

void AIComponent::RegisterState(AIState* state)
{
	_stateMap.emplace(state->GetName(), state);
}
