#pragma once

#include "Object3D.h"

class Map : public Object
{
public:
	DWORD _x;
	DWORD _y;
	std::vector<DWORD> _index;

	HRESULT Customize(UINT Width, UINT Height);
	HRESULT UpdateBuffer(class CameraDebug* pMainCamera);
};

