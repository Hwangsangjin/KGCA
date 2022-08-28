#include "pch.h"
#include "Enemy.h"

// ������ ���Ģ
// 1)������ ��Ģ:���¸� ���� �ҷ��� Ư��
// 2)���ӵ��� ��Ģ: ��(Force)�� ����Ͽ� ���� �������� �����δ�.
//   ���ӵ� : �ð��� ���� �ӵ��� �������� ��ȭ��
// 3)�ۿ�, ���ۿ� ��Ģ
//   ��(�ۿ�)�� ���� ��ü�� �ݴ�������� ��(���ۿ�)�� ��������. 
void Enemy::Frame(float fDeltaTime, float fGameTime)
{
    Vector3 vPos = _box._vMin;
    Vector3 vSize = _box._vSize;

    //������ ������ ������ &  �ð��� ����ȭ
    _vVelocity = _vDirection * _speed * fDeltaTime;
    vPos = vPos + _vVelocity;
    _friction = (fDeltaTime * _speed * 0.1f);
    _speed -= _friction;
    if (0 >= _speed)
    {
        _speed = rand() % 10;
    }

    if (vPos._x > 100.0f)
    {
        vPos._x = 100.0f;
        _vDirection._x *= -1.0f;
    }
    if (vPos._x < 0.0f)
    {
        vPos._x = 0.0f;
        _vDirection._x *= -1.0f;
    }
    if (vPos._y > 100.0f)
    {
        vPos._y = 100.0f;
        _vDirection._y *= -1.0f;
    }
    if (vPos._y < 0.0f)
    {
        vPos._y = 0.0f;
        _vDirection._y *= -1.0f;
    }
    if (vPos._z > 100.0f)
    {
        vPos._z = 100.0f;
        _vDirection._z *= -1.0f;
    }
    if (vPos._z < 0.0f)
    {
        vPos._z = 0.0f;
        _vDirection._z *= -1.0f;
    }
    SetPosition(vPos, vSize);
}
