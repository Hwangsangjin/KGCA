#pragma once

#include "Object.h"
#include "Collision.h"

class Object2D : public Object
{
public:
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
	Vector2 _cameraPosition;
	Vector2 _cameraViewSize;
	Texture* _pMaskTexture = nullptr;

	virtual HRESULT Frame() override;

	void SetMask(Texture* pMaskTexture);
	void SetRect(Rect rect);
	void SetSpeed(float speed);
	void SetScale(float x, float y);
	void SetPosition(Vector2 position);
	void SetPosition(Vector2 position, Vector2 cameraPosition);
	void SetDirection(Vector2 direction);
	void SetCameraPosition(Vector2 cameraPosition);
	void SetCameraViewSize(Vector2 cameraViewSize);
	void SetViewSpace(Vector2 cameraPosition, Vector2 camerViewSize = { 800.0f, 600.0f });
	void SetNDC();
	void SetVertexBuffer();
};

