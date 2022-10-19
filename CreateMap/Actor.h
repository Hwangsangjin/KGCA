#pragma once

#include "Object.h"

class Actor : public Object
{
public:
	Actor() {}
	virtual ~Actor() {}

	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
};

