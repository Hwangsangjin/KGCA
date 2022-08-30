#include "pch.h"
#include "Player.h"

void Player::Init()
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

void Player::Frame(float elapsedTime, float gameTime)
{
    _speed = 30.0f;
    _mass = 10.0f;
    Vector3 vPos = _box.vMin;
    Vector3 vSize = _box.vSize;
    Vector3 vKeyForce = _vDirection * _speed * elapsedTime;
    AddForce(vKeyForce);

    _vAcceleration = _vForce / _mass;
    Vector3 linearAcc = _vAcceleration;
    _vVelocity += linearAcc;
    vPos = vPos + _vVelocity;

    if (fabs(_vVelocity.Length()) > FLT_EPSILON)
    {
        _friction -= elapsedTime;
        if (0 >= _friction)
        {
            _vVelocity = { 0,0,0 };
            _friction = 1.0f;
        }

        _vVelocity *= _friction;
    }

    if (vPos.x > 100.0f)
    {
        vPos.x = 100.0f;
        _vForce = Vector3(0, 0, 0);
        _vVelocity = Vector3(0, 0, 0);
        _vDirection *= -1.0f;
        _friction = 1.0f;
    }

    if (vPos.x < 0.0f)
    {
        vPos.x = 0.0f;
        _vForce = Vector3(0, 0, 0);
        _vVelocity = Vector3(0, 0, 0);
        _vDirection.x = 1.0f;
        _friction = 1.0f;
    }

    if (vPos.y > 100.0f)
    {
        vPos.y = 100.0f;
        _vForce = Vector3(0, 0, 0);
        _vDirection.y = -1.0f;
        _friction = 1.0f;
    }

    if (vPos.y < 0.0f)
    {
        vPos.y = 0.0f;
        _vForce = Vector3(0, 0, 0);
        _vVelocity = Vector3(0, 0, 0);
        _vDirection.y = 1.0f;
        _friction = 1.0f;
    }

    if (vPos.z > 100.0f)
    {
        vPos.z = 100.0f;
        _vForce = Vector3(0, 0, 0);
        _friction = 1.0f;
        _vDirection.z *= -1.0f;
    }

    if (vPos.z < 0.0f)
    {
        vPos.z = 0.0f;
        _vForce = Vector3(0, 0, 0);
        _vVelocity = Vector3(0, 0, 0);
        _friction = 1.0f;
        _vDirection.z *= -1.0f;
    }

    _vDirection.Normalize();
    SetPosition(vPos, vSize);
}
