#pragma once

#include "Object.h"

class Camera : public Object
{
public:
	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;

	virtual void CreateView(MyVector3 eye, MyVector3 at, MyVector3 up);
	virtual void CreateProjection(float fNear, float fFar, float fovY, float aspectRatio);
	
	MyMatrix SetObjectView(MyVector3 min, MyVector3 max);

	void UpdateView();

	MyVector3 _position;
	MyVector3 _target;
	MyVector3 _look;
	MyVector3 _up = { 0.0f, 1.0f, 0.0f };
	MyVector3 _right;
	
	float _near;
	float _far;
	float _fovY;
	float _aspectRatio;

	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _roll = 0.0f;

	float _speed = 10.0f;
};

class CamerDebug : public Camera
{
public:
	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;

	virtual void CreateView(MyVector3 eye, MyVector3 at, MyVector3 up) override;
	virtual void CreateProjection(float fNear, float fFar, float fovY, float aspectRatio) override;
};