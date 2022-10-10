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
	// ��������Ʈ ������Ʈ ����
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("../../../Assets/Asteroid/Laser.png"));

	// �̵� ������Ʈ ������ ���� �ӵ� ����
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	// ���� ������Ʈ ���� (�浹��)
	_circle = new CircleComponent(this);
	_circle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	// �ð��� ������ �������� ���¸� Dead�� ����
	_deathTimer -= deltaTime;
	if (_deathTimer <= 0.0f)
	{
		SetState(Dead);
	}
	else
	{
		// ���༺�� ���� �˻�
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*_circle, *(ast->GetCircle())))
			{
				// ó�� �����ϴ� �������� ���༺�� ���¸� Dead�� ����
				SetState(Dead);
				ast->SetState(Dead);
				break;
			}
		}
	}
}
