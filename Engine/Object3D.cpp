#include "pch.h"
#include "Object3D.h"

HRESULT Object3D::Init()
{
	Object::Init();

	return TRUE;
}

HRESULT Object3D::Frame()
{
	Object::Frame();

	return TRUE;
}

HRESULT Object3D::Render()
{
	Object::Render();

	return TRUE;
}

HRESULT Object3D::Release()
{
	Object::Release();

	return TRUE;
}
