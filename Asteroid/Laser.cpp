#include "Laser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Laser::Laser(Game* game)
	: Actor(game)
	, _deathTimer(1.0f)
{
	// 스프라이트 컴포넌트 생성
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("../../../Assets/Asteroid/Laser.png"));

	// 이동 컴포넌트 생성과 전방 속도 설정
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	// 원형 컴포넌트 생성 (충돌용)
	_circle = new CircleComponent(this);
	_circle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	// 시간이 지나면 레이저의 상태를 Dead로 설정
	_deathTimer -= deltaTime;
	if (_deathTimer <= 0.0f)
	{
		SetState(Dead);
	}
	else
	{
		// 소행성과 교차 검사
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*_circle, *(ast->GetCircle())))
			{
				// 처음 교차하는 레이저와 소행성의 상태를 Dead로 설정
				SetState(Dead);
				ast->SetState(Dead);
				break;
			}
		}
	}
}
