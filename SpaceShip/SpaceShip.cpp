#include "SpaceShip.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

SpaceShip::SpaceShip(Game* game)
	: Actor(game)
	, _rightSpeed(0.0f)
	, _upSpeed(0.0f)
{
	// �ִϸ��̼� ��������Ʈ ������Ʈ �����
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("../../../Resource/SpaceShip/Ship01.png"),
		game->GetTexture("../../../Resource/SpaceShip/Ship02.png"),
		game->GetTexture("../../../Resource/SpaceShip/Ship03.png"),
		game->GetTexture("../../../Resource/SpaceShip/Ship04.png")
	};
	asc->SetAnimTextures(anims);
}

void SpaceShip::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	// �ӵ��� ��Ÿ �ð����� ��ġ�� ������Ʈ
	Vector2 pos = GetPosition();
	pos.x += _rightSpeed * deltaTime;
	pos.y += _upSpeed * deltaTime;

	// ȭ���� ���� ������ ��ġ�� ����
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}

	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}

	SetPosition(pos);
}

void SpaceShip::ProcessKeyboard(const uint8_t* state)
{
	_rightSpeed = 0.0f;
	_upSpeed = 0.0f;

	// ��
	if (state[SDL_SCANCODE_W])
	{
		_upSpeed -= 300.0f;
	}

	// ��
	if (state[SDL_SCANCODE_S])
	{
		_upSpeed += 300.0f;
	}

	// ��
	if (state[SDL_SCANCODE_A])
	{
		_rightSpeed -= 250.0f;
	}

	// ��
	if (state[SDL_SCANCODE_D])
	{
		_rightSpeed += 250.0f;
	}
}
