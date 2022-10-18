#include "pch.h"
#include "Camera.h"
#include "Input.h"
#include "Timer.h"

void Camera::CreateView(MyVector3 eye, MyVector3 at, MyVector3 up)
{
	_position = eye;
	_target = at;
	_up = up;

	_view.ViewLookAt(eye, at, up);
}

void Camera::CreateProjection(float fNear, float fFar, float fovY, float aspectRatio)
{
	_near = fNear;
	_far = fFar;
	_fovY = fovY;
	_aspectRatio = aspectRatio;

	_projection.PerspectiveFovLH(_near, _far, _fovY, _aspectRatio);
}

HRESULT Camera::Frame()
{
	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		_position._z += 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		_position._z -= 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		_position._x -= 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		_position._x += 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('Q') == KEY_STATE::HOLD)
	{
		_position._y += 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('E') == KEY_STATE::HOLD)
	{
		_position._y -= 10.0f * DELTA_TIME;
	}

	_view.ViewLookAt(_position, _target, _up);

    return TRUE;
}
