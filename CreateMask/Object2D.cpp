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

void Object2D::SetRectangle(Rect rect)
{
    _rect = rect;
    _image.x = _pTexture->_desc.Width;
    _image.y = _pTexture->_desc.Height;

    _uv.x1 = _rect.x1 / _image.x;
    _uv.y1 = _rect.y1 / _image.y;
    _uv.w = _rect.w / _image.x;
    _uv.h = _rect.h / _image.y;
}

void Object2D::SetSpeed(float speed)
{
    _speed = speed;
}

void Object2D::SetScale(float x, float y)
{
    _drawSize.x = (_rect.w / rtClient.right) * x;
    _drawSize.y = (_rect.h / rtClient.bottom) * y;
}

void Object2D::SetDirection(Vector2 dir)
{
    _dir = dir;
}

void Object2D::SetPosition(Vector2 pos)
{
    _pos = pos;

    _drawPos.x = (pos.x / rtClient.right) * 2.0f - 1.0f;
    _drawPos.y = -((pos.y / rtClient.bottom) * 2.0f - 1.0f);

    UpdateVertexBuffer();
}

void Object2D::UpdateVertexBuffer()
{
    _vertices[0].position = { _drawPos.x, _drawPos.y, 0.0f };
    _vertices[0].uv = { _uv.x1, _uv.y1 };

    _vertices[1].position = { _drawPos.x + _drawSize.x, _drawPos.y,  0.0f };
    _vertices[1].uv = { _uv.x1 + _uv.w, _uv.y1 };

    _vertices[2].position = { _drawPos.x, _drawPos.y - _drawSize.y, 0.0f };
    _vertices[2].uv = { _uv.x1, _uv.y1 + _uv.h };

    _vertices[3].position = _vertices[2].position;
    _vertices[3].uv = _vertices[2].uv;

    _vertices[4].position = _vertices[1].position;
    _vertices[4].uv = _vertices[1].uv;

    _vertices[5].position = { _drawPos.x + _drawSize.x, _drawPos.y - _drawSize.y, 0.0f };
    _vertices[5].uv = { _uv.x1 + _uv.w , _uv.y1 + _uv.h };

    _pImmediateContext->UpdateSubresource(_pVertexBuffer, NULL, NULL, &_vertices.at(0), 0, 0);
}
