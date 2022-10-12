#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include <algorithm>

Enemy::Enemy(Game* game)
	: Actor(game)
{
}

Enemy::~Enemy()
{
}

void Enemy::UpdateActor(float deltaTime)
{
}
