#include "pch.h"
#include "Object.h"

Object::Object()
{
}

Object::Object(std::string name)
{
	Init();
	_name = name;
}

void Object::Init()
{
}

void Object::Frame(float fDeltaTime, float fGameTime)
{
}

void Object::SetSphere(Vector3 vCenter, float radius)
{
	_sphere._vCenter = vCenter;
	_sphere._radius = radius;
}

void Object::SetSphere(Box box)
{
	_sphere._vCenter = box._vCenter;
	// v0  -vC-  v1
	_sphere._radius = (box._vSize * 0.5f).Size();
}

void Object::SetPosition(Vector3 vPos, Vector3 vSize)
{
	_box.Set(vPos, vSize);
	SetSphere(_box);
}

void Object::AddForce(Vector3 vforce)
{
	_vForce += vforce;
}
