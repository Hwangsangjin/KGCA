#include "pch.h"
#include "Player.h"

void Player::Frame(float fDeltaTime, float fGameTime)
{
    _speed = 30.0f;
    _mass = 10.0f;
    Vector3 vPos = _box._vMin;
    Vector3 vSize = _box._vSize;
    // ������ ������ ������
    // ������� = ���ۺ��� + ���⺤��* t(�Ÿ� ������ �ð�) 
    // ������ġ = ������ġ + ���⺤��* �ӷ�
    // �ӵ�(����) = ���⺤��*�ӷ�(m_fSpeed)
    // ������ġ = ������ġ + �ӵ�;
    // vPos = vPos + m_vVelocity* fDeltaTime(�ð�:0.1f);
    // time = ���� ������ �ð� - ���� ������ �ð�
    // 1�ʿ� 10,0,0 ���� ��������.
    // 0.5f   5,0,0
    // 0.1f   1,0,0

    //���ӵ��� ��Ģ   Force=Mass(����)*Acceleration(���ӵ�)
    // Force =  �ټ��� ������ ���̴�.
    // F=MA
    // A = F/M
    // V(�ӵ�) += A * t
    // ������ġ = ������ġ + V;
    // �ӵ� -= t ( max(0, velocity))

    Vector3 vKeyForce = _vDirection * _speed * fDeltaTime;
    AddForce(vKeyForce);

    _vAcceleration = _vForce / _mass;
    Vector3 linearAcc = _vAcceleration;
    _vVelocity += linearAcc;

    //������ ������ ������
    //������� = ���ۺ��� + ���⺤��* speed * t(�Ÿ� ������ �ð�) 
    vPos = vPos + _vVelocity;

    if ( /*fabs(m_vForces.Length()) <= T_Epsilon &&*/
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
    if (vPos._x > 100.0f)
    {
        vPos._x = 100.0f;
        _vForce = Vector3(0, 0, 0);
        _vVelocity = Vector3(0, 0, 0);
        _vDirection *= -1.0f;
        _friction = 1.0f;
    }
    if (vPos._x < 0.0f)
    {
        vPos._x = 0.0f;
        _vForce = Vector3(0, 0, 0);
        _vVelocity = Vector3(0, 0, 0);
        _vDirection._x = 1.0f;
        _friction = 1.0f;
    }
    if (vPos._y > 100.0f)
    {
        vPos._y = 100.0f;
        _vForce = Vector3(0, 0, 0);
        _vDirection._y = -1.0f;
        _friction = 1.0f;
    }
    if (vPos._y < 0.0f)
    {
        vPos._y = 0.0f;
        _vForce = Vector3(0, 0, 0);
        _vVelocity = Vector3(0, 0, 0);
        _vDirection._y = 1.0f;
        _friction = 1.0f;
    }
    if (vPos._z > 100.0f)
    {
        vPos._z = 100.0f;
        _vForce = Vector3(0, 0, 0);
        _friction = 1.0f;
        _vDirection._z *= -1.0f;
    }
    if (vPos._z < 0.0f)
    {
        vPos._z = 0.0f;
        _vForce = Vector3(0, 0, 0);
        _vVelocity = Vector3(0, 0, 0);
        _friction = 1.0f;
        _vDirection._z *= -1.0f;
    }
    _vDirection.Normalize();
    SetPosition(vPos, vSize);
}
