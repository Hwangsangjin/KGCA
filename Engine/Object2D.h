#pragma once

#include "Object.h"
#include "Collision.h"

class Object2D : public Object
{
public:
	W_STR _name;
	UINT _index;
	W_STR _texturePath;
	W_STR _maskPath;
	W_STR _shaderPath;

	float _speed;
	Circle _circle;
	Rect _collision;
	Rect _rect;
	Rect _uv;
	Vector2 _scale = { 1.0f, 1.0f };
	Vector2 _direction = { 0.0f, 0.0f };
	Vector2 _position;
	Vector2	_drawPosition;
	Vector2	_drawSize;
	Vector2 _imageSize;
	Vector2 _cameraPosition;
	Vector2 _cameraViewSize;
	Texture* _pMaskTexture = nullptr;

	bool _isCollision = false;

	virtual HRESULT Frame() override;
	virtual bool CheckCollision(Object2D& object);

	void SetMask(Texture* pMaskTexture);
	void SetRect(Rect rect);
	void SetSpeed(float speed);
	void SetScale(float x, float y);
	void SetDirection(Vector2 direction);
	void SetPosition(Vector2 position);
	void SetPosition(Vector2 position, Vector2 cameraPosition);
	void SetCameraPosition(Vector2 cameraPosition);
	void SetCameraViewSize(Vector2 cameraViewSize);
	void SetViewSpace(Vector2 cameraPosition, Vector2 camerViewSize);
	void SetScreenSpace();
	void SetVertexBuffer();

};

