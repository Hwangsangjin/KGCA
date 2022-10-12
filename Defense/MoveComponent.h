#pragma once

#include "Component.h"

class MoveComponent : public Component
{
public:
	// 먼저 업데이트되도록 갱신 순서값을 낮춤
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return _angularSpeed; }
	float GetForwardSpeed() const { return _forwardSpeed; }
	void SetAngularSpeed(float speed) { _angularSpeed = speed; }
	void SetForwardSpeed(float speed) { _forwardSpeed = speed; }
	
private:
	// 최전을 제어(초당 라디안)
	float _angularSpeed;

	// 전방 이동을 제어(초당 단위)
	float _forwardSpeed;
};

