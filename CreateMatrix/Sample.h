#pragma once

#include "Core.h"
#include "Scene.h"

class Sample : public Core
{
public:
	Sample() = default;
	virtual ~Sample() = default;

	// �ʱ�ȭ
	virtual HRESULT Init() override;
	// ������ ���
	virtual HRESULT Frame() override;
	// ����
	virtual HRESULT Render() override;
	// �޸� ����
	virtual HRESULT Release() override;

private:
	POINT _point = { 0, 0 };
	Scene* _pScene = nullptr;
};
