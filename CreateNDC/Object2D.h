#pragma once

#include "Object.h"
#include "Collision.h"

class Object2D : public Object
{
protected:
	float _speed;
	Rect _collision;
	Rect _rect;
	Rect _uv;
	Vector2 _direction;
	Vector2 _position;
	Vector2	_drawPosition;
	Vector2	_drawSize;
	Vector2 _imageSize;
	Vector2 _scale = { 1.0f, 1.0f };

public:
	Texture* _pMaskTexture = nullptr;

	virtual HRESULT Frame() override;

	void SetMask(Texture* pMaskTexture);
	void SetRect(Rect rect);
	void SetSpeed(float speed);
	void SetScale(float x, float y);
	void SetPosition(Vector2 position);
	void SetDirection(Vector2 direction);
	void SetNDC();
	void SetVertexBuffer();
};

