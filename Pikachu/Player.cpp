#include "pch.h"
#include "Player.h"
#include "Input.h"
#include "Timer.h"
#include "SpriteManager.h"

HRESULT Player::Frame()
{
    Vector2 normal{ 1.0f, 1.0f };
    normal.Normalize();

    // ������ ó�� �ӵ�
    float jumpSpeed = -700.0f;

    // ������ ���ӵ�
    float jumpAccel = 1.0f;

    // �׶��忡 ���� ���� Y��ǥ
    // ���� ������ ����Ѵ�.
    float groundY = 485.0f;

    // ���� ������ ó��
    // isJump�� ���� ���¸� ǥ���ϴ� �÷���
    // true�� ���� ���� ����, false�� ���� ������ ���¸� ��Ÿ����.
    if (!_isJump)
    {    
        // ��ư�� ������ ���� ���·� ����
        // ���� ������ �÷��׿� �ʼ�(ó�� �ӵ�)�� �����Ѵ�.
        // VY�� ĳ������ Y�� ������ �ӵ�
        if (INPUT->GetKey('W') == KEY_STATE::DOWN)
        {
            _isJump = true;
            _velocity.y = jumpSpeed;
            _pSprite = SPRITE->GetPtr(L"rtPlayerToss");
        }
    }
    // ���� ������ ó��
    else
    {
        // Y�� ������ �ӵ��� ���ӵ��� �߰��Ѵ�.
        _velocity.y += jumpAccel;

        // Y��ǥ ����
        _position.y += _velocity.y * DELTA_TIME;

        // ���� ����
        // ĳ���Ͱ� ���� ���̸�(Y�� ������ �ӵ��� ���)
        // ĳ���Ͱ� ���鿡 ���� ���� Y��ǥ�� �����ϸ�
        // �����ߴٰ� �����Ѵ�.
        // ���� ������ �÷��׸� false�� �Ͽ� ���� ���·� �ǵ��ư�
        // Y��ǥ�� ���鿡 ���� ���� ��ǥ�� �����Ѵ�.
        if (_velocity.y > 0 && _position.y >= groundY)
        {
            _isJump = false;
            _position.y = groundY;
            _pSprite = SPRITE->GetPtr(L"rtPlayerRun");
        }
    }

    if (INPUT->GetKey('A'))
    {
        _position.x -= normal.x * _speed * DELTA_TIME;
        if (_position.x - _rect.w <= 0)
        {
            _position.x = _rect.w;
        }
    }

    if (!_isDig)
    {
        if (INPUT->GetKey('A') && INPUT->GetKey(VK_SPACE) == KEY_STATE::DOWN)
        {
            _position.x -= normal.x * _speed * DELTA_TIME;
            if (_position.x - _rect.w <= 0)
            {
                _position.x = _rect.w;
            }

            _isDig = true;
            _pSprite = SPRITE->GetPtr(L"rtPlayerDig");
        }
    }
    else
    {
        if (_spriteIndex >= _spriteMaxIndex)
        {
            _isDig = false;
            _pSprite = SPRITE->GetPtr(L"rtPlayerRun");
        }
    }

    if (INPUT->GetKey('D'))
    {
        _position.x += normal.x * _speed * DELTA_TIME;
        if (_position.x + _rect.w >= RESOLUTION_X / HALF)
        {
            _position.x = RESOLUTION_X / HALF - _rect.w;
        }
    }

    if (INPUT->GetKey('D') && INPUT->GetKey(VK_SPACE) == KEY_STATE::DOWN)
    {
        _position.x += normal.x * _speed * DELTA_TIME;
        if (_position.x + _rect.w >= RESOLUTION_X / HALF)
        {
            _position.x = RESOLUTION_X / HALF - _rect.w;
        }

        _pSprite = SPRITE->GetPtr(L"rtPlayerDig");
        if (_spriteIndex >= _spriteMaxIndex)
        {
            _pSprite = SPRITE->GetPtr(L"rtPlayerRun");
        }   
    }

    if (INPUT->GetKey(VK_SPACE))
    {

    }

    // ��������Ʈ
    _spriteTimer += DELTA_TIME;
    _spriteMaxIndex = _pSprite->_uvs.size();
    _spriteStep = 1.0f / _spriteMaxIndex;

    if (_spriteStep <= _spriteTimer)
    {
        _spriteTimer -= _spriteStep;
        _spriteIndex++;
    }

    if (_spriteIndex >= _spriteMaxIndex)
    {
        _spriteIndex = 0;
    }

    RECT rect = _pSprite->_uvs[_spriteIndex];
    _rect.x1 = rect.left;
    _rect.y1 = rect.top;
    _rect.w = rect.right;
    _rect.h = rect.bottom;

    SetRect(_rect);
    SetPosition(_position);

    return TRUE;
}
