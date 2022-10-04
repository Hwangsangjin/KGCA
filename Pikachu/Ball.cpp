#include "pch.h"
#include "Ball.h"
#include "Timer.h"
#include "SpriteManager.h"

HRESULT Ball::Frame()
{
    _direction.y += GRAVITY * DELTA_TIME;
    _position += _direction * _speed * DELTA_TIME;

    // 상
    if (_position.y <= 0.0f + _rect.h)
    {
        _position.y = 0.0f + _rect.h;

        if (_direction.y <= 0.0f)
        {
            _direction.y *= -1.0f * COEFFICIENT;
        }
    }
    // 하
    else if (_position.y >= 470.0f + _rect.h)
    {
        _position.y = 470.0f + _rect.h;

        if (_direction.y >= 0.0f)
        {
            _direction.y *= -1.0f * COEFFICIENT;
        }

        _direction.x *= FRICTION;
    }
    // 좌
    else if (_position.x <= 0.0f + _rect.w)
    {
        _position.x = 0.0f + _rect.h;

        if (_direction.x <= 0.0f)
        {
            _direction.x *= -1.0f * COEFFICIENT;
        }
    }
    // 우
    else if (_position.x >= 800.0f - _rect.w)
    {
        _position.x = 800.0f - _rect.h;

        if (_direction.x >= 0.0f)
        {
            _direction.x *= -1.0f * COEFFICIENT;
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

bool Ball::CheckCollision(Object2D& object)
{
    if (!_isCollision && Collision::CircleToCircle(this->_circle, object._circle))
    {
        Vector2 v1(this->_circle.cx, this->_circle.cy);
        Vector2 v2(object._circle.cx, object._circle.cy);
        v1 -= v2;
        v1.Normalize();
        
        _direction.x = v1.x * 3.0f * COEFFICIENT;
        _direction.y = v1.y * 6.0f * COEFFICIENT;

        _isCollision = true;

        return true;
    }
    else
    {
        _isCollision = false;
    }

    return false;
}
