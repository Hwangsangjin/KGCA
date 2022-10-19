#pragma once

#include "Object3D.h"

class Shape : public Object3D
{
public:
	Shape() {}
	~Shape() {}
};

class ShapeBox: public Object3D
{
public:
	ShapeBox() {}
	virtual ~ShapeBox() {}

	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
};

