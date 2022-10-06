#include "pch.h"
#include "EnemyScore.h"
#include "SpriteManager.h"

HRESULT EnemyScore::Frame()
{
    // 스프라이트
    _spriteMaxIndex = _pSprite->_uvs.size();

    if (_spriteIndex >= _spriteMaxIndex - 1)
    {
        _spriteIndex = _spriteMaxIndex - 1;
        _isEnemyWin = true;
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

void EnemyScore::AddScore()
{
    _spriteIndex++;
}
