#pragma once

#include "Core.h"

class Sample : public Core
{
private:
	class Scene* _pScene = nullptr;

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

	// ���ҽ� ����
	virtual HRESULT CreateDXResource() override;
};

