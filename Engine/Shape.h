#pragma once

#include "Object3D.h"

class Shape : public Object
{
public:
	Shape() {}
	~Shape() {}
};

class ShapeLine : public Shape
{
public:
	ShapeLine() {}
	~ShapeLine() {}

	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
};

class ShapeDirectionLine : public ShapeLine
{
public:
	ShapeDirectionLine() {}
	~ShapeDirectionLine() {}

	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
};

class ShapeBox : public Shape
{
public:
	ShapeBox() {}
	virtual ~ShapeBox() {}

	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
};

