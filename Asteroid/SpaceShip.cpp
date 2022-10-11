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
	// ��������Ʈ ������Ʈ �����
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("../../../Resource/Asteroid/ShipWithThrust.png"));

	// �Է� ������Ʈ ���� �� Ű, �ӵ� ����
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackwardKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	// ���� �˻縦 ���ؼ� ���� ������Ʈ ������ ������ ����
	_circle = new CircleComponent(this);
	_circle->SetRadius(30.0f);
}

void SpaceShip::UpdateActor(float deltaTime)
{
	_laserCooldown -= deltaTime;
	_respawnTime -= deltaTime;
	_invincibleTime -= deltaTime;

	// ������ �ð��� �����ִ� ��� Active ���°� �� �� ����.
	if (_respawnTime >= 0.0f)
	{
		return;
	}

	SetState(Active);

	// ��Ȱ �� ���� �ð��� �����ִ� ��� ���༺�� ���� �˻� ����
	if (_invincibleTime >= 0.0f)
	{
		return;
	}

	// ���༺�� ���� �˻�
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*_circle, *(ast->GetCircle())))
		{
			// ���ּ��� ���༺�� �����Ѵٸ� ���¸� Paused�� ����
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
		// �������� �����ϰ� �������� ��ġ�� ȸ������ ����
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// �������� ��ٿ� �� �缳�� (0.5��)
		_laserCooldown = 0.5f;
	}
}
