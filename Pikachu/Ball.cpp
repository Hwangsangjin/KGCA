#include "pch.h"
#include "Ball.h"
#include "Timer.h"
#include "SpriteManager.h"

HRESULT Ball::Frame()
{
    _direction.y += GRAVITY * DELTA_TIME;
    _position += _direction * _speed * DELTA_TIME;

    // ╩С
    if (_position.y <= 0.0f + _rect.h)
    {
        _position.y = 0.0f + _rect.h;

        if (_direction.y <= 0.0f)
        {
            _direction.y *= -1.0f * COEFFICIENT;
        }
    }
    // го
    else if (_position.y >= 470.0f + _rect.h)
    {
        _position.y = 470.0f + _rect.h;

        if (_direction.y >= 0.0f)
        {
            _direction.y *= -1.0f * COEFFICIENT;
        }

        _direction.x *= FRICTION;
    }
    // аб
    else if (_position.x <= 0.0f + _rect.w)
    {
        _position.x = 0.0f + _rect.h;

        if (_direction.x <= 0.0f)
        {
            _direction.x *= -1.0f * COEFFICIENT;
        }
    }
    // ©Л
    else if (_position.x >= 800.0f - _rect.w)
    {
        _position.x = 800.0f - _rect.h;

        if (_direction.x >= 0.0f)
        {
            _direction.x *= -1.0f * COEFFICIENT;
        }
    }

    _effectTimer += DELTA_TIME;
    _index = 0;
    _maxIndex = _pSprite->_uvs.size();

    if (_step <= _effectTimer)
    {
        _effectTimer -= _step;
        _index++;
    }

    if (_index >= _maxIndex)
    {
        0;
    }

    RECT rect = _pSprite->_uvs[_index];
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

HRESULT Ball::Update()
{
    _effectTimer += _speed * DELTA_TIME;

    if (_step <= _effectTimer)
    {
        _effectTimer -= _step;
        _index++;
    }

    if (_index >= _maxIndex)
    {
        _index = 0;
    }

    RECT rect = _pSprite->_uvs[_index];
    _rect.x1 = rect.left;
    _rect.y1 = rect.top;
    _rect.w = rect.right;
    _rect.h = rect.bottom;

    Vector2 center;
    center.x = _pSprite->_rect.w / 2.0f;
    center.y = _pSprite->_rect.h / 2.0f;

    SetRect(_rect);
    SetPosition(_position);

    return TRUE;
}
