#pragma once

#include "Core.h"

class Sample : public Core
{
public:
	// �ʱ�ȭ
	virtual HRESULT Init() override;
	// ������
	virtual HRESULT Frame() override;
	// ����
	virtual HRESULT Render() override;
	// ������
	virtual HRESULT Release() override;
};

