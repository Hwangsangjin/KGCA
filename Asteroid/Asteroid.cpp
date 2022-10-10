#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game)
	: Actor(game)
	, _circle(nullptr)
{
	// �����ϰ� ��ġ�� ������ �ʱ�ȭ�Ѵ�.
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// ��������Ʈ ������Ʈ�� �����ϰ� �ؽ�ó�� �����Ѵ�.
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("../../../Assets/Asteroid/Asteroid.png"));

	// �̵� ������Ʈ�� �����ϰ� ���� �ӵ��� �����Ѵ�.
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	// ���� ������Ʈ ���� (�浹��)
	_circle = new CircleComponent(this);
	_circle->SetRadius(40.0f);

	// ���ӿ� ���༺�� �߰��Ѵ�.
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
