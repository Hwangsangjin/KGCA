#include "pch.h"
#include "Box.h"

Box::Box(Vector3 vPos, Vector3 vSize)
{
    Set(vPos, vSize);
}

bool Box::operator==(Box& dest)
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

void Box::Set(Vector3 vPos, Vector3 vSize)
{
	vMin = vPos;
	this->vSize = vSize;
	vMax = vMin + vSize;
	vCenter = (vMin + vMax) / 2.0f;
}
