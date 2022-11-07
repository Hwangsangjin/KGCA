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
	MyCircle _circle;
	MyRect _collision;
	MyRect _rect;
	MyRect _uv;
	DxVector2 _scale = { 1.0f, 1.0f };
	DxVector2 _direction = { 0.0f, 0.0f };
	DxVector2 _position;
	DxVector2 _drawPosition;
	DxVector2 _drawSize;
	DxVector2 _imageSize;
	DxVector2 _cameraPosition;
	DxVector2 _cameraViewSize;
	Texture* _pMaskTexture = nullptr;

	bool _isCollision = false;

	virtual HRESULT Frame() override;
	virtual bool CheckCollision(Object2D& object);

	void SetMask(Texture* pMaskTexture);
	void SetRect(MyRect rect);
	void SetSpeed(float speed);
	void SetScale(float x, float y);
	void SetDirection(DxVector2 direction);
	void SetPosition(DxVector2 position);
	void SetPosition(DxVector2 position, DxVector2 cameraPosition);
	void SetCameraPosition(DxVector2 cameraPosition);
	void SetCameraViewSize(DxVector2 cameraViewSize);
	void SetViewSpace(DxVector2 cameraPosition, DxVector2 camerViewSize);
	void SetScreenSpace();
	virtual void UpdateVertexBuffer() override;
};

