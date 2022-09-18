#include "pch.h"
#include "Object2D.h"

HRESULT Object2D::Frame()
{
    return TRUE;
}

void Object2D::SetMask(Texture* pMaskTexture)
{
    _pMaskTexture = pMaskTexture;
}

void Object2D::SetRect(Rect rect)
{
    _rect = rect;
}

void Object2D::SetPosition(Vector2 position)
{
    _position = position;
}

void Object2D::SetDirection(Vector2 direction)
{
    _direction = direction;
}

void Object2D::SetScale(float x, float y)
{
    _drawSize.x = (_rect.w / rtClient.right) * x;
    _drawSize.y = (_rect.h / rtClient.bottom) * y;
}

void Object2D::SetSpeed(float speed)
{
    _speed = speed;
}

void Object2D::SetUV()
{
    _imageSize.x = _pTexture->_desc.Width;
    _imageSize.y = _pTexture->_desc.Height;

    _uv.x = _rect.x / _imageSize.x;
    _uv.y = _rect.y / _imageSize.y;
    _uv.w = _rect.w / _imageSize.x;
    _uv.h = _rect.h / _imageSize.y;
}

void Object2D::SetNormalize()
{
    _drawPosition.x = (_position.x / rtClient.right) * 2.0f - 1.0f;
    _drawPosition.y = -((_position.y / rtClient.bottom) * 2.0f - 1.0f);
}

void Object2D::SetVertexBuffer()
{
    _vertices[0].position = { _drawPosition.x, _drawPosition.y, 0.0f };
    _vertices[0].uv = { _uv.x, _uv.y };

    _vertices[1].position = { _drawPosition.x + _drawSize.x, _drawPosition.y,  0.0f };
    _vertices[1].uv = { _uv.x + _uv.w, _uv.y };

    _vertices[2].position = { _drawPosition.x, _drawPosition.y - _drawSize.y, 0.0f };
    _vertices[2].uv = { _uv.x, _uv.y + _uv.h };

    _vertices[3].position = { _drawPosition.x + _drawSize.x, _drawPosition.y - _drawSize.y, 0.0f };
    _vertices[3].uv = { _uv.x + _uv.w , _uv.y + _uv.h };

    _pImmediateContext->UpdateSubresource(_pVertexBuffer, NULL, NULL, &_vertices.at(0), 0, 0);
}
