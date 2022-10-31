#include "pch.h"
#include "Camera.h"
#include "Input.h"
#include "Timer.h"
#include "TMath.h"
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

void Camera::CreateView(MyVector3 eye, MyVector3 at, MyVector3 up)
{
	_position = eye;
	_target = at;
	_up = up;

	_view.ViewLookAt(eye, at, up);
	UpdateView();
}

void Camera::CreateProjection(float fNear, float fFar, float fovY, float aspectRatio)
{
	_near = fNear;
	_far = fFar;
	_fovY = fovY;
	_aspectRatio = aspectRatio;

	_projection.PerspectiveFovLH(_near, _far, _fovY, _aspectRatio);
}

void Camera::UpdateView()
{
	_right._x = _view._11;
	_right._y = _view._21;
	_right._z = _view._31;

	_up._x = _view._12;
	_up._y = _view._22;
	_up._z = _view._32;

	_look._x = _view._13;
	_look._y = _view._23;
	_look._z = _view._33;

	_right = _right.Normalize();
	_up = _up.Normalize();
	_look = _look.Normalize();

	_frustum.CreateFrustum(&_view, &_projection);
}

MyMatrix Camera::SetObjectView(MyVector3 min, MyVector3 max)
{
	MyMatrix view;
	TBASIS_EX::TVector3 vector{ 0.0f, 1.0f, 0.0f };
	MyVector3 center = (min + max) * 0.5f;
	float radius = MyVector3(max - min).Length() * 0.5f;

	MyVector3 target = { center._x, center._y, center._z };
	MyVector3 position = target + (-_look * (radius * 2));

	TBASIS_EX::D3DXMatrixLookAtLH((TBASIS_EX::TMatrix*)&_view, (TBASIS_EX::TVector3*)&position, (TBASIS_EX::TVector3*)&target, &vector);

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

	if (INPUT->GetKey('W') == KEY_STATE::HOLD)
	{
		_position += _look * 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('S') == KEY_STATE::HOLD)
	{
		_position -= _look * 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('A') == KEY_STATE::HOLD)
	{
		_position -= _right * 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('D') == KEY_STATE::HOLD)
	{
		_position += _right * 10.0f * DELTA_TIME;

	}

	if (INPUT->GetKey('Q') == KEY_STATE::HOLD)
	{
		_position += _up * 10.0f * DELTA_TIME;
	}

	if (INPUT->GetKey('E') == KEY_STATE::HOLD)
	{
		_position -= _up * 10.0f * DELTA_TIME;
	}

	TBASIS_EX::TVector3 position;
	position.x = _position._x;
	position.y = _position._y;
	position.z = _position._z;

	TBASIS_EX::TMatrix world;
	TBASIS_EX::TMatrix view;
	TBASIS_EX::TMatrix rotation;
	TBASIS_EX::TQuaternion quaternion;
	TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&quaternion, _yaw, _pitch, _roll);
	TBASIS_EX::D3DXMatrixAffineTransformation(&world, 1.0f, nullptr, &quaternion, &position);
	TBASIS_EX::D3DXMatrixInverse(&view, nullptr, &world);

	_view = *((MyMatrix*)&view);

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

void CameraDebug::CreateView(MyVector3 eye, MyVector3 at, MyVector3 up)
{
	_position = eye;
	_target = at;
	_up = up;

	_view.ViewLookAt(eye, at, up);
}

void CameraDebug::CreateProjection(float fNear, float fFar, float fovY, float aspectRatio)
{
	_near = fNear;
	_far = fFar;
	_fovY = fovY;
	_aspectRatio = aspectRatio;

	_projection.PerspectiveFovLH(_near, _far, _fovY, _aspectRatio);
}

void CameraDebug::UpdateView()
{
	_right._x = _view._11;
	_right._y = _view._21;
	_right._z = _view._31;

	_up._x = _view._12;
	_up._y = _view._22;
	_up._z = _view._32;

	_look._x = _view._13;
	_look._y = _view._23;
	_look._z = _view._33;

	_right = _right.Normalize();
	_up = _up.Normalize();
	_look = _look.Normalize();

	_frustum.CreateFrustum(&_view, &_projection);
}