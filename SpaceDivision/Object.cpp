#include "pch.h"
#include "Object.h"

Object::Object()
{
    Init();
}

Object::Object(std::string name)
{
	Init();
	_name = name;
}

void Object::Init()
{
    Vector3 vPos, vSize;
    vPos.x = 20 + (rand() % 80);
    vPos.y = 20 + (rand() % 80);
    vPos.z = 20 + (rand() % 80);
    vSize.x = 5.0f + (rand() % 5);
    vSize.y = 5.0f + (rand() % 5);
    vSize.z = 5.0f + (rand() % 5);
    _box.Set(vPos, vSize);
    SetSphere(_box);
    _vDirection.x = cos(rand());
    _vDirection.y = sin(rand());
    _vDirection.z = 1.0f - cos(rand());
    _vDirection.Normalize();
    _friction = 0.0f;
    _mass = 100.0f;
    _speed = 10.0f;
}

void Object::SetSphere(Vector3 vCenter, float radius)
{
	_sphere.vCenter = vCenter;
	_sphere.radius = radius;
}

void Object::SetSphere(Box box)
{
	_sphere.vCenter = box.vCenter;
	// v0  -vC-  v1
	_sphere.radius = (box.vSize * 0.5f).Size();
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
