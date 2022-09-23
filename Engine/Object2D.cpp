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

    _imageSize.x = _pTexture->_desc.Width;
    _imageSize.y = _pTexture->_desc.Height;

    _uv.x = rect.x / _imageSize.x;
    _uv.y = rect.y / _imageSize.y;
    _uv.w = rect.w / _imageSize.x;
    _uv.h = rect.h / _imageSize.y;
}

void Object2D::SetSpeed(float speed)
{
    _speed = speed;
}

void Object2D::SetScale(float x, float y)
{
    _scale.x = x;
    _scale.y = y;
}

void Object2D::SetPosition(Vector2 position)
{
    _position = position;

    SetScreenSpace();
    SetVertexBuffer();
}

void Object2D::SetPosition(Vector2 position, Vector2 cameraPosition)
{
    _position = position;

    SetViewSpace(cameraPosition, _cameraViewSize);
    SetVertexBuffer();
}

void Object2D::SetDirection(Vector2 direction)
{
    _direction = direction;
}

void Object2D::SetCameraPosition(Vector2 cameraPosition)
{
    _cameraPosition = cameraPosition;
}

void Object2D::SetCameraViewSize(Vector2 cameraViewSize)
{
    _cameraViewSize = cameraViewSize;
}

void Object2D::SetViewSpace(Vector2 cameraPosition, Vector2 camerViewSize)
{
    Vector2 collision;
    collision.x = _rect.w / 2.0f;
    collision.y = _rect.h / 2.0f;

    _collision.Set(_position.x - collision.x * _scale.x, _position.y - collision.y * _scale.y, _rect.w, _rect.h);

    Vector2 viewPosition;
    viewPosition.x = _collision.x - cameraPosition.x;
    viewPosition.y = _collision.y - cameraPosition.y;

    _drawPosition.x = viewPosition.x * (2.0f / camerViewSize.x);
    _drawPosition.y = -(viewPosition.y * (2.0f / camerViewSize.y));
    _drawSize.x = (_rect.w / camerViewSize.x) * 2.0f * _scale.x;
    _drawSize.y = (_rect.h / camerViewSize.y) * 2.0f * _scale.y;
}

void Object2D::SetScreenSpace()
{
    Vector2 collision;
    collision.x = _rect.w / 2.0f;
    collision.y = _rect.h / 2.0f;

    _collision.Set(_position.x - collision.x * _scale.x, _position.y - collision.y * _scale.y, _rect.w, _rect.h);

    _drawPosition.x = (_collision.x / rtClient.right) * 2.0f - 1.0f;
    _drawPosition.y = -((_collision.y / rtClient.bottom) * 2.0f - 1.0f);
    _drawSize.x = (_rect.w / rtClient.right) * 2.0f * _scale.x;
    _drawSize.y = (_rect.h / rtClient.bottom) * 2.0f * _scale.y;
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
