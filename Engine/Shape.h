#pragma once

#include "Object.h"

class Shape : public Object
{
public:
	Shape() {}
	virtual ~Shape() {}
};

class ShapeLine : public Shape
{
public:
	ShapeLine() {}
	virtual ~ShapeLine() {}

	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
};

class ShapeDirectionLine : public ShapeLine
{
public:
	ShapeDirectionLine() {}
	virtual ~ShapeDirectionLine() {}

	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
};

class ShapePlane : public Shape
{
public:
	ShapePlane() {}
	virtual ~ShapePlane() {}

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

