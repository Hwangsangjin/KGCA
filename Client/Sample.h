#pragma once

#include "Core.h"

class Sample : public Core
{
private:
	POINT pos;

public:
	Sample() = default;
	virtual ~Sample() = default;

	// �ʱ�ȭ
	virtual HRESULT Init() final;
	// ������
	virtual HRESULT Frame() final;
	// ����
	virtual HRESULT Render() final;
	// ������
	virtual HRESULT Release() final;
};

