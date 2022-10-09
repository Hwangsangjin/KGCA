#pragma once

#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

	// �ִϸ��̼��� �����Ӹ��� ������Ʈ(Component�� Update �޼ҵ带 �������̵�)
	void Update(float deltaTime) override;

	// �ִϸ��̼ǿ� ���Ǵ� �ؽ�ó ����
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

	// �ִϸ��̼� FPS�� ��ų� �����ϴ� �Լ�
	float GetAnimFPS() const { return _animFPS; }
	void SetAnimFPS(float fps) { _animFPS = fps; }

private:
	// �ִϸ��̼ǿ� ���Ǵ� ��� �ؽ�ó
	std::vector<SDL_Texture*> _animTextures;

	// ���� ������
	float _currFrame;

	// �ִϸ��̼� ������ ���̵�
	float _animFPS;
};

