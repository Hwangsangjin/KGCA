#pragma once

#include "Core.h"

class Object;

class Sample : public Core
{
private:
	std::unique_ptr<Object> object_;

public:
	// ������, �Ҹ���
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
};
