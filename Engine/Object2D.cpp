#include "pch.h"
#include "Object2D.h"

HRESULT Object2D::Frame()
{
    return TRUE;
}

void Object2D::SetMask(std::shared_ptr<Texture> mask_texture)
{
    mask_texture_ = mask_texture;
}

void Object2D::SetRect(MyRect rect)
{
    rect_ = rect;

    image_size_.x = static_cast<float>(texture_->texture2D_desc_.Width);
    image_size_.y = static_cast<float>(texture_->texture2D_desc_.Height);

    uv_.x1 = rect.x1 / image_size_.x;
    uv_.y1 = rect.y1 / image_size_.y;
    uv_.w = rect.w / image_size_.x;
    uv_.h = rect.h / image_size_.y;
}

void Object2D::SetSpeed(float speed)
{
    speed_ = speed;
}

void Object2D::SetScale(float x, float y)
{
    scale_.x = x;
    scale_.y = y;
}

void Object2D::SetDirection(DxVector2 direction)
{
    direction_ = direction;
}

void Object2D::SetPosition(DxVector2 position)
{
    direction_ = position;

    SetScreenSpace();
    UpdateVertexBuffer();
}

void Object2D::SetPosition(DxVector2 position, DxVector2 cameraPosition)
{
    position_ = position;

    SetViewSpace(cameraPosition, camera_view_size_);
    UpdateVertexBuffer();
}

void Object2D::SetCameraPosition(DxVector2 cameraPosition)
{
    camera_position_ = cameraPosition;
}

void Object2D::SetCameraViewSize(DxVector2 cameraViewSize)
{
    camera_view_size_ = cameraViewSize;
}

void Object2D::SetViewSpace(DxVector2 camera_position, DxVector2 camera_view_size)
{
    DxVector2 center;
    center.x = rect_.w / 2.0f;
    center.y = rect_.h / 2.0f;

    collision_.Set(position_.x - center.x * scale_.x, position_.y - center.y * scale_.y, rect_.w * scale_.x, rect_.h * scale_.y);

    DxVector2 view_position;
    view_position.x = collision_.x1 - camera_position.x;
    view_position.y = collision_.y1 - camera_position.y;

    draw_position_.x = view_position.x * (2.0f / camera_view_size.x);
    draw_position_.y = -(view_position.y * (2.0f / camera_view_size.y));
    draw_size_.x = (rect_.w / camera_view_size.x) * 2.0f * scale_.x;
    draw_size_.y = (rect_.h / camera_view_size.y) * 2.0f * scale_.y;
}

bool Object2D::CheckCollision(Object2D& object)
{
    return false;
}

void Object2D::SetScreenSpace()
{
    DxVector2 center;
    center.x = rect_.w / 2.0f;
    center.y = rect_.h / 2.0f;

    collision_.Set(position_.x - center.x * scale_.x, position_.y - center.y * scale_.y, rect_.w * scale_.x, rect_.h * scale_.y);
    circle_.Set(position_.x, position_.y, 40.0f);

    draw_position_.x = (collision_.x1 / g_client_rect.right) * 2.0f - 1.0f;
    draw_position_.y = -((collision_.y1 / g_client_rect.bottom) * 2.0f - 1.0f);
    draw_size_.x = (rect_.w / g_client_rect.right) * 2.0f * scale_.x;
    draw_size_.y = (rect_.h / g_client_rect.bottom) * 2.0f * scale_.y;
}

void Object2D::UpdateVertexBuffer()
{
    vertices_[0].position = { draw_position_.x, draw_position_.y, 0.0f };
    vertices_[0].uv = { uv_.x1, uv_.y1 };
            
    vertices_[1].position = { draw_position_.x + draw_size_.x, draw_position_.y, 0.0f };
    vertices_[1].uv = { uv_.x1 + uv_.w, uv_.y1 };
            
    vertices_[2].position = { draw_position_.x, draw_position_.y - draw_size_.y, 0.0f };
    vertices_[2].uv = { uv_.x1, uv_.y1 + uv_.h };
            
    vertices_[3].position = { draw_position_.x + draw_size_.x, draw_position_.y - draw_size_.y, 0.0f };
    vertices_[3].uv = { uv_.x1 + uv_.w , uv_.y1 + uv_.h };

    device_context_->UpdateSubresource(vertex_buffer_.Get(), 0, 0, &vertices_.at(0), 0, 0);
}
