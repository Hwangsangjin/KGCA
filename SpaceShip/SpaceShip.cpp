#include "SpaceShip.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

SpaceShip::SpaceShip(Game* game)
	: Actor(game)
	, _rightSpeed(0.0f)
	, _upSpeed(0.0f)
{
	// 애니메이션 스프라이트 컴포넌트 만들기
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

	// 속도와 델타 시간으로 위치를 업데이트
	Vector2 pos = GetPosition();
	pos.x += _rightSpeed * deltaTime;
	pos.y += _upSpeed * deltaTime;

	// 화면의 왼쪽 반으로 위치를 제한
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

	// 상
	if (state[SDL_SCANCODE_W])
	{
		_upSpeed -= 300.0f;
	}

	// 하
	if (state[SDL_SCANCODE_S])
	{
		_upSpeed += 300.0f;
	}

	// 좌
	if (state[SDL_SCANCODE_A])
	{
		_rightSpeed -= 250.0f;
	}

	// 우
	if (state[SDL_SCANCODE_D])
	{
		_rightSpeed += 250.0f;
	}
}
