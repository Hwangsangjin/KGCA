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

void Player::Frame(float fDeltaTime, float fGameTime)
{
    _speed = 30.0f;
    _mass = 10.0f;
    Vector3 vPos = _box.vMin;
    Vector3 vSize = _box.vSize;
    // 벡터의 직전의 방정식
    // 결과벡터 = 시작벡터 + 방향벡터* t(거리 내지는 시간) 
    // 최종위치 = 현재위치 + 방향벡터* 속력
    // 속도(벡터) = 방향벡터*속력(m_fSpeed)
    // 최종위치 = 현재위치 + 속도;
    // vPos = vPos + m_vVelocity * fDeltaTime(시간:0.1f);
    // time = 현재 프레임 시간 - 이전 프레임 시간
    // 1초에 10,0,0 으로 움직이자.
    // 0.5f   5,0,0
    // 0.1f   1,0,0

    // 가속도의 법칙
    // Force = Mass(무게) * Acceleration(가속도)
    // Force =  다수의 벡터의 합이다.
    // F=MA
    // A = F/M
    // V(속도) += A * t
    // 최종위치 = 현재위치 + V;
    // 속도 -= t ( max(0, velocity))

    Vector3 vKeyForce = _vDirection * _speed * fDeltaTime;
    AddForce(vKeyForce);

    _vAcceleration = _vForce / _mass;
    Vector3 linearAcc = _vAcceleration;
    _vVelocity += linearAcc;

    //벡터의 직전의 방정식
    //결과벡터 = 시작벡터 + 방향벡터* speed * t(거리 내지는 시간) 
    vPos = vPos + _vVelocity;

    if ( /*fabs(m_vForce.Size()) <= FLT_EPSILON &&*/
        fabs(_vVelocity.Size()) > FLT_EPSILON)
    {
        _friction -= fDeltaTime;
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
