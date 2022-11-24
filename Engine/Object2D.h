#pragma once

#include "Object.h"
#include "Collision.h"

class Object2D : public Object
{
public:
	W_STR name_;
	UINT index_;
	W_STR texture_file_;
	W_STR mask_file_;
	W_STR shader_file_;

	float speed_;
	MyCircle circle_;
	MyRect collision_;
	MyRect rect_;
	MyRect uv_;
	DxVector2 scale_ = { 1.0f, 1.0f };
	DxVector2 direction_ = { 0.0f, 0.0f };
	DxVector2 position_;
	DxVector2 draw_position_;
	DxVector2 draw_size_;
	DxVector2 image_size_;
	DxVector2 camera_position_;
	DxVector2 camera_view_size_;

	std::shared_ptr<Texture> mask_texture_;

	bool is_collision_ = false;

	virtual HRESULT Frame() override;
	virtual bool CheckCollision(Object2D& object);

	void SetMask(std::shared_ptr<Texture> mask_texture);
	void SetRect(MyRect rect);
	void SetSpeed(float speed);
	void SetScale(float x, float y);
	void SetDirection(DxVector2 direction);
	void SetPosition(DxVector2 position);
	void SetPosition(DxVector2 position, DxVector2 camera_position);
	void SetCameraPosition(DxVector2 camera_position);
	void SetCameraViewSize(DxVector2 camera_view_size);
	void SetViewSpace(DxVector2 camera_position, DxVector2 camer_view_size);
	void SetScreenSpace();
	virtual void UpdateVertexBuffer() override;
};

