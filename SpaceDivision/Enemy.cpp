#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{
    Init();
}

Enemy::Enemy(std::string name)
{
    Init();
    _name = name;
}

void Enemy::Init()
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

// 뉴턴의 운동법칙
// 1)관성의 법칙:상태를 유지 할려는 특성
// 2)가속도의 법칙: 힘(Force)에 비례하여 힘의 방향으로 움직인다.
//   가속도 : 시간에 따라서 속도의 순간적인 변화량
// 3)작용, 반작용 법칙
//   힘(작용)을 받은 물체는 반대방향으로 힘(반작용)이 가해진다. 
void Enemy::Frame(float fDeltaTime, float fGameTime)
{
    Vector3 vPos = _box.vMin;
    Vector3 vSize = _box.vSize;

    // 벡터의 직선의 방정식 &  시간의 동기화
    _vVelocity = _vDirection * _speed * fDeltaTime;
    vPos = vPos + _vVelocity;
    _friction = (fDeltaTime * _speed * 0.1f);
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
