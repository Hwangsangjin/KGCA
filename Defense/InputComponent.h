#pragma once

#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	// ���� ������Ʈ�Ϸ��� ������Ʈ ������ �����.
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	// private ������ �����ϱ� ���� ����, ���� �Լ���
	float GetMaxForward() const { return _maxForwardSpeed; }
	float GetMaxAngular() const { return _maxAngularSpeed; }
	int GetForwardKey() const { return _forwardKey; }
	int GetBackwardKey() const { return _backwardKey; }
	int GetClockwiseKey() const { return _clockwiseKey; }
	int GetCounterClockwiseKey() const { return _counterClockwiseKey; }

	void SetMaxForwardSpeed(float speed) { _maxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { _maxAngularSpeed = speed; }
	void SetForwardKey(int key) { _forwardKey = key; }
	void SetBackwardKey(int key) { _backwardKey = key; }
	void SetClockwiseKey(int key) { _clockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { _counterClockwiseKey = key; }

private:
	// �ִ� ���� �ӵ�, �ִ� �� �ӵ�
	float _maxForwardSpeed;
	float _maxAngularSpeed;

	// ���� �� ������ ���� Ű
	int _forwardKey;
	int _backwardKey;

	// �� ��� ���� Ű
	int _clockwiseKey;
	int _counterClockwiseKey;
};

