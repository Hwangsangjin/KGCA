#pragma once

#include "Object.h"

class Object3D : public Object
{
public:
	W_STR _name;

	DxVector3 _look;
	DxVector3 _up;
	DxVector3 _right;

	Object3D() {}
	virtual ~Object3D() {}

	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;
};

