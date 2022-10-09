#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	: _owner(owner)
	, _updateOrder(updateOrder)
{
	// ������ ������Ʈ ���Ϳ� �߰�
	_owner->AddComponent(this);
}

Component::~Component()
{
	_owner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
