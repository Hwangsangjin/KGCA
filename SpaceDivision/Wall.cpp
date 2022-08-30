#include "pch.h"
#include "Wall.h"

Wall::Wall()
{
	Init();
}

Wall::Wall(std::string name)
{
	Init();
	_name = name;
}

void Wall::Init()
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

void Wall::Frame(float elapsedTime, float fGameTime)
{
    Vector3 vPos = _box.vMin;
    Vector3 vSize = _box.vSize;

    _vVelocity = _vDirection * _speed * elapsedTime;
    vPos = vPos + _vVelocity;
    _friction = (elapsedTime * _speed * 0.1f);
    _speed -= _friction;

    if (0 >= _speed)
    {
        _speed = rand() % 10;
    }

    if (vPos.x > 100.0f)
    {
        vPos.x = 100.0f;
        _vDirection.x *= -1.0f;
    }

    if (vPos.x < 0.0f)
    {
        vPos.x = 0.0f;
        _vDirection.x *= -1.0f;
    }

    if (vPos.y > 100.0f)
    {
        vPos.y = 100.0f;
        _vDirection.y *= -1.0f;
    }

    if (vPos.y < 0.0f)
    {
        vPos.y = 0.0f;
        _vDirection.y *= -1.0f;
    }

    if (vPos.z > 100.0f)
    {
        vPos.z = 100.0f;
        _vDirection.z *= -1.0f;
    }

    if (vPos.z < 0.0f)
    {
        vPos.z = 0.0f;
        _vDirection.z *= -1.0f;
    }

    SetPosition(vPos, vSize);
}
