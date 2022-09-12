#pragma once

#include "Object.h"

class Object2D : public Object
{
protected:
	Rect _rect;
	Rect _uv;
	Vector2 _pos;
	Vector2 _dir;
	float _speed;
	POINT _image;
	Vector2	_drawPos;
	Vector2	_drawSize;

public:
	virtual HRESULT Frame() override;

	void SetRectangle(Rect rect);
	void SetSpeed(float speed);
	void SetScale(float x, float y);
	void SetPosition(Vector2 pos);
	void SetDirection(Vector2 dir);
	void UpdateVertexBuffer();
};

