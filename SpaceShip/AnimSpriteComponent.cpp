#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
	, _currFrame(0.0f)
	, _animFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (_animTextures.size() > 0)
	{
		// 프레임 레이트와 델타 시간을 기반으로
		// 현재 프레임 갱신
		_currFrame += _animFPS * deltaTime;

		// 애니메이션 텍스처 수를 초과하면 현재 프레임을 래핑한다.
		while (_currFrame >= _animTextures.size())
		{
			_currFrame -= _animTextures.size();
		}

		// 현재 텍스처를 설정
		SetTexture(_animTextures[static_cast<int>(_currFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	_animTextures = textures;
	if (_animTextures.size() > 0)
	{
		// 활성 텍스처를 첫 번째 프레임으로 설정
		_currFrame = 0.0f;
		SetTexture(_animTextures[0]);
	}
}
