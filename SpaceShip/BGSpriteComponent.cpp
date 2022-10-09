#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
	, _scrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	for (auto& bg : _BGTextures)
	{
		// x 오프셋 값을 갱신
		bg._offset.x += _scrollSpeed * deltaTime;

		// 이 텍스처가 화면을 완전히 벗어나면 오프셋 값을
		// 마지막 배경 텍스처의 오른쪽 위치로 초기화한다.
		if (bg._offset.x < -_screenSize.x)
		{
			bg._offset.x = (_BGTextures.size() - 1) * _screenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	// 각 배경 텍스처 그리기
	for (auto& bg : _BGTextures)
	{
		SDL_Rect rect;

		// 화면 크기
		rect.w = static_cast<int>(_screenSize.x);
		rect.h = static_cast<int>(_screenSize.y);

		// 소유자의 위치를 중심으로 사각형을 배치
		rect.x = static_cast<int>(_owner->GetPosition().x - rect.w / 2 + bg._offset.x);
		rect.y = static_cast<int>(_owner->GetPosition().y - rect.h / 2 + bg._offset.y);

		// 배경 그리기
		SDL_RenderCopy(renderer,
			bg._texture,
			nullptr,
			&rect
		);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;

	for (auto texture : textures)
	{
		BGTexture temp;
		temp._texture = texture;

		// 각 텍스처의 오프셋은 화면의 (화면의 너비) * (count)
		temp._offset.x = count * _screenSize.x;
		temp._offset.y = 0;
		_BGTextures.emplace_back(temp);
		count++;
	}
}
