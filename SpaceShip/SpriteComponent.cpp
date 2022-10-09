#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	: Component(owner)
	, _texture(nullptr)
	, _drawOrder(drawOrder)
	,_texWidth(0)
	,_texHeight(0)
{
	_owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	_owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (_texture)
	{
		SDL_Rect rect;

		// 소유자의 스케일(배율)값으로 너비, 높이를 스케일
		rect.w = static_cast<int>(_texWidth * _owner->GetScale());
		rect.h = static_cast<int>(_texHeight * _owner->GetScale());

		// 소유자의 위치를 중심으로 사각형을 배치
		rect.x = static_cast<int>(_owner->GetPosition().x - rect.w / 2);
		rect.y = static_cast<int>(_owner->GetPosition().y - rect.h / 2);

		// 스프라이트를 그린다.
		SDL_RenderCopyEx(renderer,
			_texture,								// 그릴 텍스처
			nullptr,								// 그릴 텍스처의 영역 (nullptr이면 전체 영역)
			&rect,									// 그려질 목적지의 사각형 영역
			Math::ToDegrees(_owner->GetRotation()),	// (라디안을 각도로 변환)
			nullptr,								// 회전 기준점
			SDL_FLIP_NONE							// 플립 행동
		);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	_texture = texture;

	// 텍스처의 너비와 높이를 얻기 위해서 SDL_QuertTexture() 함수 사용
	SDL_QueryTexture(texture, nullptr, nullptr, &_texWidth, &_texHeight);
}
