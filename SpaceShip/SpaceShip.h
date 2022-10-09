#pragma once

#include "Actor.h"

class SpaceShip : public Actor
{
public:
	SpaceShip(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return _rightSpeed; }
	float GetDownSpeed() const { return _upSpeed; }

private:
	float _upSpeed;
	float _rightSpeed;
};

