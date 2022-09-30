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

	_position += _direction * _speed * DELTA_TIME;
	_collision.x1 = _position.x;
	_collision.y1 = _position.y;

	return TRUE;
}
