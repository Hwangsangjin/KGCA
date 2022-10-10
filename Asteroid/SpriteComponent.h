#pragma once

#include "Component.h"
#include "SDL/SDL.h"

class SpriteComponent : public Component
{
public:
	// (�׸��� �������� �������� �� �������� �׸���.)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return _drawOrder; }
	int GetTexWidth() const { return _texWidth; }
	int GetTexHeight() const { return _texHeight; }

protected:
	// �׸� �ؽ�ó
	SDL_Texture* _texture;

	// ȭ�� �˰��򿡼� ����ϴ� �׸��� ����
	int _drawOrder;

	// �ؽ�ó�� �ʺ�, ����
	int _texWidth;
	int _texHeight;
};

