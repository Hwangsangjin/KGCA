#include "pch.h"
#include "Player.h"
#include "Input.h"
#include "Timer.h"
#include "SpriteManager.h"

HRESULT Player::Frame()
{
    Vector2 normal{ 1.0f, 1.0f };
    normal.Normalize();

    if (INPUT->GetKey('W'))
    {
        _position.y -= normal.y * _speed * DELTA_TIME;
    }

    if (INPUT->GetKey('A'))
    {
        _position.x -= normal.x * _speed * DELTA_TIME;
        if (_position.x - _rect.w <= 0)
        {
            _position.x = _rect.w;
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

    if (INPUT->GetKey(VK_SPACE))
    {

    }

    // 스프라이트
    _spriteTimer += DELTA_TIME;
    _spriteMaxIndex = _pSprite->_uvs.size();

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
