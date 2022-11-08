#pragma once

#include "Object3D.h"

class Actor : public Object3D
{
public:
	Actor() {}
	virtual ~Actor() {}

	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;

	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;

	virtual void SetMatrix(DxMatrix* pWorld, DxMatrix* pView, DxMatrix* pProjection);

	class Shape* _pDirectionLine = nullptr;
};

