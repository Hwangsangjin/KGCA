#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	: _owner(owner)
	, _updateOrder(updateOrder)
{
	// 액터의 컴포넌트 벡터에 추가
	_owner->AddComponent(this);
}

Component::~Component()
{
	_owner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
