#include "pch.h"
#include "Box.h"

Box::Box(const Vector3& vPos, const Vector3& vSize)
{
    Set(vPos, vSize);
}

bool Box::operator==(const Box& dest)
{
    if (_vMin == dest._vMin)
    {
        if (_vSize == dest._vSize)
        {
            return true;
        }
    }

    return false;
}

void Box::Set(const Vector3& vPos, const Vector3& vSize)
{
	_vMin = vPos;
	_vSize = vSize;
	_vMax = _vMin + vSize;
	_vCenter = (_vMin + _vMax) / 2.0f;
}
