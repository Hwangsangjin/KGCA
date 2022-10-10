#pragma once

#include "Component.h"

class MoveComponent : public Component
{
public:
	// ���� ������Ʈ�ǵ��� ���� �������� ����
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return _angularSpeed; }
	float GetForwardSpeed() const { return _forwardSpeed; }
	void SetAngularSpeed(float speed) { _angularSpeed = speed; }
	void SetForwardSpeed(float speed) { _forwardSpeed = speed; }
	
private:
	// ������ ����(�ʴ� ����)
	float _angularSpeed;

	// ���� �̵��� ����(�ʴ� ����)
	float _forwardSpeed;
};

