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

		// �������� ������(����)������ �ʺ�, ���̸� ������
		rect.w = static_cast<int>(_texWidth * _owner->GetScale());
		rect.h = static_cast<int>(_texHeight * _owner->GetScale());

		// �������� ��ġ�� �߽����� �簢���� ��ġ
		rect.x = static_cast<int>(_owner->GetPosition().x - rect.w / 2);
		rect.y = static_cast<int>(_owner->GetPosition().y - rect.h / 2);

		// ��������Ʈ�� �׸���.
		SDL_RenderCopyEx(renderer,
			_texture,								// �׸� �ؽ�ó
			nullptr,								// �׸� �ؽ�ó�� ���� (nullptr�̸� ��ü ����)
			&rect,									// �׷��� �������� �簢�� ����
			Math::ToDegrees(_owner->GetRotation()),	// (������ ������ ��ȯ)
			nullptr,								// ȸ�� ������
			SDL_FLIP_NONE							// �ø� �ൿ
		);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	_texture = texture;

	// �ؽ�ó�� �ʺ�� ���̸� ��� ���ؼ� SDL_QuertTexture() �Լ� ���
	SDL_QueryTexture(texture, nullptr, nullptr, &_texWidth, &_texHeight);
}
