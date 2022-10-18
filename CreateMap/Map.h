#pragma once

#include "Object.h"

class Map : public Object
{
public:
	HRESULT Customize(UINT Width, UINT Height);
};

