#include "pch.h"
#include "Effect.h"

Rect Effect::Convert(RECT rect)
{
	Rect rt;
	rt.x1 = rect.left;
	rt.y1 = rect.top;
	rt.w = rect.right;
	rt.h = rect.bottom;

	return rt;
}

HRESULT Effect::Update()
{
	_effectTimer += DELTA_TIME;

	if (_step <= _effectTimer)
	{
		_effectTimer -= _step;
		_index++;
	}

	if (_index >= _maxIndex)
	{
		return E_FAIL;
	}

	RECT rect = _pSprite->_uvs[_index];
	_rect = Convert(rect);

	Vector2 center;
	center.x = _pSprite->_rect.w / 2.0f;
	center.y = _pSprite->_rect.h / 2.0f;

	_collision.Set(_position.x - center.x * _pSprite->_scale.x, _position.y - center.y * _pSprite->_scale.y, _pSprite->_rect.w * _pSprite->_scale.x, _pSprite->_rect.h * _pSprite->_scale.y);

	return TRUE;
}
