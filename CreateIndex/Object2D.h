#pragma once

#include "Object.h"

class Object2D : public Object
{
protected:
	Rect _rect;
	Rect _uv;
	float _speed;
	Vector2 _dir;
	Vector2 _pos;
	POINT _image;
	Vector2	_drawPos;
	Vector2	_drawSize;

public:
	Texture* _pMaskTexture = nullptr;

	virtual HRESULT Frame() override;

	void SetMask(Texture* pMaskTexture);
	void SetRectangle(Rect rect);
	void SetSpeed(float speed);
	void SetScale(float x, float y);
	void SetDirection(Vector2 dir);
	void SetPosition(Vector2 pos);
	void UpdateVertexBuffer();
};

