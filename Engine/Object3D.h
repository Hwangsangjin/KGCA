#pragma once

#include "Object.h"

class Object3D : public Object
{
public:
	Object3D() {}
	virtual ~Object3D() {}

	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;

	MyVector3 _look;
	MyVector3 _up;
	MyVector3 _right;
};

