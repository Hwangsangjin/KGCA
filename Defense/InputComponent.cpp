#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(Actor* owner)
	: MoveComponent(owner)
	, _forwardKey(0)
	, _backwardKey(0)
	, _clockwiseKey(0)
	, _counterClockwiseKey(0)
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// ������ ���°� Paused�̸� �Է��� ���� ����
	if (_owner->GetState() == Actor::Paused)
	{
		return;
	}

	// MoveComponent�� ���� ���� �ӵ� ���
	float forwardSpeed = 0.0f;
	if (keyState[_forwardKey])
	{
		forwardSpeed += _maxForwardSpeed;
	}

	if (keyState[_backwardKey])
	{
		forwardSpeed -= _maxForwardSpeed;
	}

	SetForwardSpeed(forwardSpeed);

	// MoveComponent�� ���� �� �ӵ� ���
	float angularSpeed = 0.0f;
	if (keyState[_clockwiseKey])
	{
		angularSpeed += _maxAngularSpeed;
	}

	if (keyState[_counterClockwiseKey])
	{
		angularSpeed -= _maxAngularSpeed;
	}

	SetAngularSpeed(angularSpeed);
}
