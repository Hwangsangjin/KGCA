#pragma once

#include "Object.h"

class Object2D : public Object
{
protected:
	float _speed;
	Rect _rect;
	Rect _uv;
	Vector2 _direction;
	Vector2 _position;
	Vector2	_drawPosition;
	Vector2	_drawSize;
	Vector2 _imageSize;

public:
	Texture* _pMaskTexture = nullptr;

	virtual HRESULT Frame() override;

	void SetMask(Texture* pMaskTexture);
	void SetRect(Rect rect);
	void SetSpeed(float speed);
	void SetScale(float x, float y);
	void SetDirection(Vector2 direction);
	void SetPosition(Vector2 position);
	void UpdateVertexBuffer();
};

