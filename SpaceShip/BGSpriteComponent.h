#pragma once

#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	// 기본 그리기 순서값을 낮은 값으로 설정 (배경이므로)
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);

	// 기반 클래스로부터 오버라이딩한 Update, Draw 함수
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	// 배경에 사용되는 텍스처 설정
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);

	// 화면 크기를 얻거나 스크롤 속도값을 설정 및 얻는 함수
	void SetScreenSize(const Vector2& size) { _screenSize = size; }
	void SetScrollSpeed(float speed) { _scrollSpeed = speed; }
	float GetScrollSpeed() const { return _scrollSpeed; }

private:
	// 각 배경 이미지와 배경 이미지의 오프셋 값을 캡슐화한 구조체
	struct BGTexture
	{
		SDL_Texture* _texture;
		Vector2 _offset;
	};

	std::vector<BGTexture> _BGTextures;
	Vector2 _screenSize;
	float _scrollSpeed;
};

