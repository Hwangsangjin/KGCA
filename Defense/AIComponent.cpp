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
	// ���� ���� ���¸� ���� ���´�.
	if (_currentState)
	{
		_currentState->OnExit();
	}

	// �ʿ��� ���ο� ���¸� ã�´�.
	auto iter = _stateMap.find(name);
	if (iter != _stateMap.end())
	{
		_currentState = iter->second;

		// ���ο� ���·� �����Ѵ�.
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
