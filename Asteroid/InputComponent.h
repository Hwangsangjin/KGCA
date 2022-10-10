#pragma once

#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	// 먼저 업데이트하려면 업데이트 순서를 낮춘다.
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	// private 변수에 접근하기 위한 게터, 세터 함수들
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
	// 최대 전방 속도, 최대 각 속도
	float _maxForwardSpeed;
	float _maxAngularSpeed;

	// 전진 및 후진을 위한 키
	int _forwardKey;
	int _backwardKey;

	// 각 운동을 위한 키
	int _clockwiseKey;
	int _counterClockwiseKey;
};

