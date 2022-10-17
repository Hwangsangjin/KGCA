#include "pch.h"
#include "Camera.h"
#include "Input.h"
#include "Timer.h"

void Camera::CreateView(MyVector3 Eye, MyVector3 At, MyVector3 Up)
{
	_Position = Eye;
	_Target = At;
	_Up = Up;

	_View.ViewLookAt(Eye, At, Up);
}

void Camera::CreateProjection(float Near, float Far, float FovY, float AspectRatio)
{
	_Near = Near;
	_Far = Far;
	_FovY = FovY;
	_AspectRatio = AspectRatio;

	_Projection.PerspectiveFovLH(1.0f, 100.0f, 3.141592f * 0.5f, 800.0f / 600.0f);
}

HRESULT Camera::Frame()
{
	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		_Position._z += 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		_Position._z -= 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		_Position._x -= 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		_Position._x += 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('Q') == KEY_STATE::HOLD)
	{
		_Position._y += 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('E') == KEY_STATE::HOLD)
	{
		_Position._y -= 10.0f * DELTA_TIME;
	}

	_View.ViewLookAt(_Position, _Target, _Up);

    return TRUE;
}
