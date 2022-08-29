#include "pch.h"
#include "Box.h"

Box::Box(const Vector3& vPos, const Vector3& vSize)
{
    Set(vPos, vSize);
}

bool Box::operator==(const Box& dest)
{
    if (vMin == dest.vMin)
    {
        if (vSize == dest.vSize)
        {
            return true;
        }
    }

    return false;
}

void Box::Set(const Vector3& vPos, const Vector3& vSize)
{
	vMin = vPos;
	this->vSize = vSize;
	vMax = vMin + vSize;
	vCenter = (vMin + vMax) / 2.0f;
}
