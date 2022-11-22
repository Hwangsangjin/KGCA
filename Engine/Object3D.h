#pragma once

#include "Object.h"

class Object3D : public Object
{
public:
	W_STR name_;

	DxVector3 look_;
	DxVector3 up_;
	DxVector3 right_;

	Object3D() {}
	virtual ~Object3D() {}

	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;
};

