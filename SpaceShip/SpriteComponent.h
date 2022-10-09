#pragma once

#include "Component.h"
#include "SDL/SDL.h"

class SpriteComponent : public Component
{
public:
	// (그리기 순서값이 낮을수록 더 뒤쪽으로 그린다.)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return _drawOrder; }
	int GetTexWidth() const { return _texWidth; }
	int GetTexHeight() const { return _texHeight; }

protected:
	// 그릴 텍스처
	SDL_Texture* _texture;

	// 화가 알고리즘에서 사용하는 그리기 순서
	int _drawOrder;

	// 텍스처의 너비, 높이
	int _texWidth;
	int _texHeight;
};

