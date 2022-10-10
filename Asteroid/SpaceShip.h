#pragma once

#include "Actor.h"

class SpaceShip : public Actor
{
public:
	SpaceShip(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

private:
	float _laserCooldown;

	class CircleComponent* _circle;

	// ������ �ð�
	float _respawnTime;
	// ��Ȱ �� ���� �ð�
	float _invincibleTime;
};

