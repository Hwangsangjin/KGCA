#pragma once

#include "Object.h"

class Map : public Object
{
public:
	Map() {}
	~Map() {}

	HRESULT CreateMap(UINT Width, UINT Height);
};

