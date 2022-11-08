#pragma once

#include "Object.h"
#include "Frustum.h"

class Camera : public Object
{
public:
	DxVector3 _position;
	DxVector3 _target;
	DxVector3 _look;
	DxVector3 _up = { 0.0f, 1.0f, 0.0f };
	DxVector3 _right;

	float _near;
	float _far;
	float _fovY;
	float _aspectRatio;

	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _roll = 0.0f;

	float _distance = 0.0f;
	float _speed = 25.0f;

	Frustum _frustum;

	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;

	virtual void CreateView(DxVector3 eye, DxVector3 at, DxVector3 up);
	virtual void CreateProjection(float fNear, float fFar, float fovY, float aspectRatio);
	virtual void UpdateView();
	
	DxMatrix SetObjectView(DxVector3 min, DxVector3 max);
};

class CameraDebug : public Camera
{
public:
	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;

	virtual void CreateView(DxVector3 eye, DxVector3 at, DxVector3 up) override;
	virtual void CreateProjection(float fNear, float fFar, float fovY, float aspectRatio) override;
	virtual void UpdateView() override;
};

