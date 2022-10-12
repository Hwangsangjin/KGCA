#include "Bullet.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Enemy.h"

Bullet::Bullet(Game* game)
	: Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("../../../Resource/Defense/Projectile.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(400.0f);

	_circle = new CircleComponent(this);
	_circle->SetRadius(5.0f);

	_liveTime = 1.0f;
}

void Bullet::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	// 적과 충돌 체크
	for (Enemy* e : GetGame()->GetEnemies())
	{
		if (Intersect(*_circle, *(e->GetCircle())))
		{
			// 충돌로 둘다 죽음
			e->SetState(Dead);
			SetState(Dead);
			break;
		}
	}

	_liveTime -= deltaTime;
	if (_liveTime <= 0.0f)
	{
		// 시간 제한 적중, 사망
		SetState(Dead);
	}
}
