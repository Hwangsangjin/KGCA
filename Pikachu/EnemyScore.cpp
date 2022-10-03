#include "pch.h"
#include "EnemyScore.h"
#include "Timer.h"
#include "SpriteManager.h"

HRESULT EnemyScore::Frame()
{
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
