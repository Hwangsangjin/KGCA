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
		// x ������ ���� ����
		bg._offset.x += _scrollSpeed * deltaTime;

		// �� �ؽ�ó�� ȭ���� ������ ����� ������ ����
		// ������ ��� �ؽ�ó�� ������ ��ġ�� �ʱ�ȭ�Ѵ�.
		if (bg._offset.x < -_screenSize.x)
		{
			bg._offset.x = (_BGTextures.size() - 1) * _screenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	// �� ��� �ؽ�ó �׸���
	for (auto& bg : _BGTextures)
	{
		SDL_Rect rect;

		// ȭ�� ũ��
		rect.w = static_cast<int>(_screenSize.x);
		rect.h = static_cast<int>(_screenSize.y);

		// �������� ��ġ�� �߽����� �簢���� ��ġ
		rect.x = static_cast<int>(_owner->GetPosition().x - rect.w / 2 + bg._offset.x);
		rect.y = static_cast<int>(_owner->GetPosition().y - rect.h / 2 + bg._offset.y);

		// ��� �׸���
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

		// �� �ؽ�ó�� �������� ȭ���� (ȭ���� �ʺ�) * (count)
		temp._offset.x = count * _screenSize.x;
		temp._offset.y = 0;
		_BGTextures.emplace_back(temp);
		count++;
	}
}
