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
		// ������ ����Ʈ�� ��Ÿ �ð��� �������
		// ���� ������ ����
		_currFrame += _animFPS * deltaTime;

		// �ִϸ��̼� �ؽ�ó ���� �ʰ��ϸ� ���� �������� �����Ѵ�.
		while (_currFrame >= _animTextures.size())
		{
			_currFrame -= _animTextures.size();
		}

		// ���� �ؽ�ó�� ����
		SetTexture(_animTextures[static_cast<int>(_currFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	_animTextures = textures;
	if (_animTextures.size() > 0)
	{
		// Ȱ�� �ؽ�ó�� ù ��° ���������� ����
		_currFrame = 0.0f;
		SetTexture(_animTextures[0]);
	}
}
