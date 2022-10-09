#pragma once

#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	// �⺻ �׸��� �������� ���� ������ ���� (����̹Ƿ�)
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);

	// ��� Ŭ�����κ��� �������̵��� Update, Draw �Լ�
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	// ��濡 ���Ǵ� �ؽ�ó ����
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);

	// ȭ�� ũ�⸦ ��ų� ��ũ�� �ӵ����� ���� �� ��� �Լ�
	void SetScreenSize(const Vector2& size) { _screenSize = size; }
	void SetScrollSpeed(float speed) { _scrollSpeed = speed; }
	float GetScrollSpeed() const { return _scrollSpeed; }

private:
	// �� ��� �̹����� ��� �̹����� ������ ���� ĸ��ȭ�� ����ü
	struct BGTexture
	{
		SDL_Texture* _texture;
		Vector2 _offset;
	};

	std::vector<BGTexture> _BGTextures;
	Vector2 _screenSize;
	float _scrollSpeed;
};

