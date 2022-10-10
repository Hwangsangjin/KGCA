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

	// 리스폰 시간
	float _respawnTime;
	// 부활 후 무적 시간
	float _invincibleTime;
};

