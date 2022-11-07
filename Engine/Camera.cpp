#include "pch.h"
#include "Camera.h"
#include "Input.h"
#include "Timer.h"
#include "Frustum.h"

HRESULT Camera::Init()
{
	return TRUE;
}

HRESULT Camera::Frame()
{
	return TRUE;
}

HRESULT Camera::Render()
{
	return TRUE;
}

HRESULT Camera::Release()
{
	return TRUE;
}

void Camera::CreateView(DxVector3 eye, DxVector3 at, DxVector3 up)
{
	_position = eye;
	_target = at;
	_up = up;

	D3DXMatrixLookAtLH(&_view, &eye, &at, &up);
	UpdateView();
}

void Camera::CreateProjection(float fNear, float fFar, float fovY, float aspectRatio)
{
	_near = fNear;
	_far = fFar;
	_fovY = fovY;
	_aspectRatio = aspectRatio;

	D3DXMatrixPerspectiveFovLH(&_projection, _fovY, _aspectRatio, _near, _far);
}

void Camera::UpdateView()
{
	_right.x = _view._11;
	_right.y = _view._21;
	_right.z = _view._31;

	_up.x = _view._12;
	_up.y = _view._22;
	_up.z = _view._32;

	_look.x = _view._13;
	_look.y = _view._23;
	_look.z = _view._33;

	D3DXVec3Normalize(&_right, &_right);
	D3DXVec3Normalize(&_up, &_up);
	D3DXVec3Normalize(&_look, &_look);

	_frustum.CreateFrustum(&_view, &_projection);
}

DxMatrix Camera::SetObjectView(DxVector3 min, DxVector3 max)
{
	DxMatrix view;
	DxVector3 vector{ 0.0f, 1.0f, 0.0f };
	DxVector3 center = (min + max) * 0.5f;
	float radius = DxVector3(max - min).Length() * 0.5f;

	DxVector3 target = { center.x, center.y, center.z };
	DxVector3 position = target + (-_look * (radius * 2));

	D3DXMatrixLookAtLH((DxMatrix*)&_view, (DxVector3*)&position, (DxVector3*)&target, &vector);

	_position = position;
	_target = target;

	return _view;
}

HRESULT CameraDebug::Init()
{
	return TRUE;
}

HRESULT CameraDebug::Frame()
{
	if (INPUT->GetKey(VK_RBUTTON) == KEY_STATE::HOLD)
	{
		_yaw += INPUT->_offset.x * 0.002f;
		_pitch += INPUT->_offset.y * 0.002f;
	}

	if (INPUT->GetKey(VK_SPACE) == KEY_STATE::DOWN)
	{
		_speed = 100.0f;
	}
	else if (INPUT->GetKey(VK_SPACE) == KEY_STATE::UP)
	{
		_speed = 50.0f;
	}

	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		_position += _look * _speed * DELTA_TIME;
	}

	if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		_position -= _look * _speed * DELTA_TIME;
	}

	if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		_position -= _right * _speed * DELTA_TIME;
	}

	if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		_position += _right * _speed * DELTA_TIME;

	}

	if (INPUT->GetKey('Q') == KEY_STATE::HOLD)
	{
		_position += _up * _speed * DELTA_TIME;
	}

	if (INPUT->GetKey('E') == KEY_STATE::HOLD)
	{
		_position -= _up * _speed * DELTA_TIME;
	}

	DxVector3 position;
	position.x = _position.x;
	position.y = _position.y;
	position.z = _position.z;

	DxMatrix world;
	DxMatrix view;
	DxMatrix rotation;
	DxQuaternion quaternion;
	D3DXQuaternionRotationYawPitchRoll(&quaternion, _yaw, _pitch, _roll);
	D3DXMatrixAffineTransformation(&world, 1.0f, nullptr, &quaternion, &position);
	D3DXMatrixInverse(&view, nullptr, &world);

	_view = *((DxMatrix*)&view);

	UpdateView();

	return TRUE;
}

HRESULT CameraDebug::Render()
{
	return TRUE;
}

HRESULT CameraDebug::Release()
{
	return TRUE;
}

void CameraDebug::CreateView(DxVector3 eye, DxVector3 at, DxVector3 up)
{
	_position = eye;
	_target = at;
	_up = up;

	D3DXMatrixLookAtLH(&_view, &eye, &at, &up);
}

void CameraDebug::CreateProjection(float fNear, float fFar, float fovY, float aspectRatio)
{
	_near = fNear;
	_far = fFar;
	_fovY = fovY;
	_aspectRatio = aspectRatio;

	D3DXMatrixPerspectiveFovLH(&_projection, _fovY, _aspectRatio, _near, _far);
}

void CameraDebug::UpdateView()
{
	_right.x = _view._11;
	_right.y = _view._21;
	_right.z = _view._31;

	_up.x = _view._12;
	_up.y = _view._22;
	_up.z = _view._32;

	_look.x = _view._13;
	_look.y = _view._23;
	_look.z = _view._33;

	D3DXVec3Normalize(&_right, &_right);
	D3DXVec3Normalize(&_up, &_up);
	D3DXVec3Normalize(&_look, &_look);

	_frustum.CreateFrustum(&_view, &_projection);
}