#pragma once

#include "Actor.h"

class Bullet : public Actor
{
public:
	Bullet(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class CircleComponent* _circle;
	float _liveTime;
};

