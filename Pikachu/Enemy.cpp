#include "pch.h"
#include "Enemy.h"
#include "Input.h"
#include "Timer.h"
#include "SpriteManager.h"

HRESULT Enemy::Frame()
{
    const float offsetX = 15.0f;
    Vector2 normal{ 1.0f, 1.0f };
    normal.Normalize();

    // 점프의 처음 속도
    float jumpSpeed = -800.0f;

    // 점프의 가속도
    float jumpAccel = 1.0f;

    // 그라운드에 있을 때의 Y좌표
    // 착지 판정에 사용한다.
    float groundY = 485.0f;

    // 스파이크 판정에 사용하는 네트의 높이
    const float netY = 400.0f;

    // 평상시 상태의 처리
    // isJump는 점프 상태를 표시하는 플래그
    // true일 때는 점프 상태, false일 때는 평상시의 상태를 나타낸다.
    if (!_isJump)
    {
        // 버튼을 누르면 점프 상태로 이행
        // 점프 상태의 플래그와 초속(처음 속도)을 설정한다.
        // VY는 캐릭터의 Y축 방향의 속도
        if (INPUT->GetKey(VK_UP) == KEY_STATE::DOWN)
        {
            _velocity.y = jumpSpeed;
            _pSprite = SPRITE->GetPtr(L"rtEnemyToss");
            _isJump = true;
        }
    }
    // 점프 상태의 처리
    else
    {
        if (_position.y <= netY && INPUT->GetKey(VK_RETURN) == KEY_STATE::DOWN)
        {
            _pSprite = SPRITE->GetPtr(L"rtEnemySpike");
            _isSpike = true;
        }

        // Y축 방향의 속도에 가속도를 추가한다.
        _velocity.y += jumpAccel;

        // Y좌표 갱신
        _position.y += _velocity.y * DELTA_TIME;
        if (_position.y <= 200.0f)
        {
            _position.y = 200.0f;
        }

        // 착지 판정
        // 캐릭터가 낙하 중이며(Y축 방향의 속도가 양수)
        // 캐릭터가 지면에 있을 때의 Y좌표에 도달하면
        // 착지했다고 판정한다.
        // 점프 상태의 플래그를 false로 하여 평상시 상태로 되돌아가
        // Y좌표를 지면에 있을 때의 좌표로 설정한다.
        if (_velocity.y > 0 && _position.y >= groundY)
        {
            _isJump = false;
            _isSpike = false;
            _position.y = groundY;
            _pSprite = SPRITE->GetPtr(L"rtEnemyRun");
        }
    }

    // 좌
    if (INPUT->GetKey(VK_LEFT))
    {
        _position.x -= normal.x * _speed * DELTA_TIME;
        if (_position.x + _rect.w - offsetX <= RESOLUTION_X / HALF)
        {
            _position.x = RESOLUTION_X / HALF - _rect.w + offsetX;
        }
    }

    if (!_isDig)
    {
        if (_position.y >= groundY && INPUT->GetKey(VK_LEFT) && INPUT->GetKey(VK_SPACE) == KEY_STATE::DOWN)
        {
            _position.x -= normal.x * _speed * DELTA_TIME;
            if (_position.x + _rect.w - offsetX <= RESOLUTION_X / HALF)
            {
                _position.x = RESOLUTION_X / HALF - _rect.w + offsetX;
            }

            _pSprite = SPRITE->GetPtr(L"rtEnemyRightDig");
            _isDig = true;
        }
    }

    // 우
    if (INPUT->GetKey(VK_RIGHT))
    {
        _position.x += normal.x * _speed * DELTA_TIME;
        if (_position.x - _rect.w >= RESOLUTION_X)
        {
            _position.x = RESOLUTION_X + _rect.w;
        }
    }

    if (!_isDig)
    {
        if (_position.y >= groundY && INPUT->GetKey(VK_RIGHT) && INPUT->GetKey(VK_SPACE) == KEY_STATE::DOWN)
        {
            _position.x += normal.x * _speed * DELTA_TIME;
            if (_position.x - _rect.w >= RESOLUTION_X)
            {
                _position.x = RESOLUTION_X + _rect.w;
            }

            _pSprite = SPRITE->GetPtr(L"rtEnemyRightDig");
            _isDig = true;
        }
    }

    // 스프라이트
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
        if (_isDig)
        {
            _pSprite = SPRITE->GetPtr(L"rtEnemyRun");
            _isDig = false;
        }
        else if (_isWin)
        {
            _pSprite = SPRITE->GetPtr(L"rtEnemyWin");
        }
        else if (_isLose)
        {
            _pSprite = SPRITE->GetPtr(L"rtEnemyLose");
        }

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

bool Enemy::IsSpike()
{
    return _isSpike;
}

bool Enemy::IsJump()
{
    return _isJump;
}

bool Enemy::IsDig()
{
    return _isDig;
}
