#pragma once

#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

	// 애니메이션을 프레임마다 업데이트(Component의 Update 메소드를 오버라이드)
	void Update(float deltaTime) override;

	// 애니메이션에 사용되는 텍스처 설정
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

	// 애니메이션 FPS를 얻거나 설정하는 함수
	float GetAnimFPS() const { return _animFPS; }
	void SetAnimFPS(float fps) { _animFPS = fps; }

private:
	// 애니메이션에 사용되는 모든 텍스처
	std::vector<SDL_Texture*> _animTextures;

	// 현재 프레임
	float _currFrame;

	// 애니메이션 프레임 레이드
	float _animFPS;
};

