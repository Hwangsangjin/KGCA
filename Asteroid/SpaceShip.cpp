#include "SpaceShip.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"

SpaceShip::SpaceShip(Game* game)
	: Actor(game)
	, _laserCooldown(0.0f)
{
	// 스프라이트 컴포넌트 만들기
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("../../../Resource/Asteroid/ShipWithThrust.png"));

	// 입력 컴포넌트 생성 및 키, 속도 설정
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackwardKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	// 교차 검사를 위해서 원형 컴포넌트 생성과 반지름 설정
	_circle = new CircleComponent(this);
	_circle->SetRadius(30.0f);
}

void SpaceShip::UpdateActor(float deltaTime)
{
	_laserCooldown -= deltaTime;
	_respawnTime -= deltaTime;
	_invincibleTime -= deltaTime;

	// 리스폰 시간이 남아있는 경우 Active 상태가 될 수 없다.
	if (_respawnTime >= 0.0f)
	{
		return;
	}

	SetState(Active);

	// 부활 후 무적 시간이 남아있는 경우 소행성과 교차 검사 안함
	if (_invincibleTime >= 0.0f)
	{
		return;
	}

	// 소행성과 교차 검사
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*_circle, *(ast->GetCircle())))
		{
			// 우주선과 소행성이 교차한다면 상태를 Paused로 설정
			SetState(Paused);
			SetPosition(Vector2(512.0f, 386.0f));
			SetRotation(0.0f);
			_respawnTime = 1.5f;
			_invincibleTime = 3.0f;
			break;
		}
	}
}

void SpaceShip::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && _laserCooldown <= 0.0f)
	{
		// 레이저를 생성하고 레이저의 위치와 회전값을 설정
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// 레이저의 쿨다운 값 재설정 (0.5초)
		_laserCooldown = 0.5f;
	}
}
